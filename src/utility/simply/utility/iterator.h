#pragma once

#include <iterator>
#include <stdexcept>
#include <simply/utility/enumerable.h>
#include <simply/utility/iterator_position.h>

namespace simply { namespace utility
{
	template<typename element_t> class iterator
	{
	public:
		using value_type = element_t;
		using reference = element_t&;
		using iterator_category = std::input_iterator_tag;

		// Definitions not valid for this type but expected by iterator_traits<T>
		using difference_type = void; 
		using pointer = void;

		iterator(std::shared_ptr<enumerable<element_t>> enumerable, iterator_position position)
			: pimpl { new impl(enumerable, position) }
		{
		}

		iterator(const iterator& source)
			: pimpl { source.pimpl }
		{
		}

		iterator& operator=(const iterator& source)
		{
			pimpl = source.pimpl;
			return *this;
		}

		element_t& operator*()
		{
			return pimpl->dereference();
		}

		iterator& operator++()
		{
			pimpl->increment(this);
			return *this;
		}

		bool operator==(iterator& other)
		{
			return pimpl->equal(*other.pimpl);
		}

		bool operator!=(iterator& other)
		{
			return !(*this == other);
		}

	private:
		class impl
		{
			const std::shared_ptr<simply::utility::enumerable<element_t>> enumerable;
			std::unique_ptr<enumerator<element_t>> enumerator;
#pragma warning (disable: 4624) // union destructor is deleted
			union { element_t current; };
#pragma warning (default: 4624)
			const iterator* incrementor;

			void destroy_current()
			{
				if (position == iterator_position::in_range)
				{
					current.~element_t();
				}
			}

			void get_next()
			{
				destroy_current();
				if (enumerator->get_next(&current))
				{
					position = iterator_position::in_range;
				}
				else
				{
					position = iterator_position::after_last;
				}
			}

			void initialize_before_first()
			{
				if (position == iterator_position::before_first)
				{
					enumerator = enumerable->create_enumerator();
					get_next();
				}
			}
		public:
			iterator_position position;

			impl(std::shared_ptr<simply::utility::enumerable<element_t>> enumerable, iterator_position position)
				: enumerable { enumerable }, position { position }, incrementor { nullptr }
			{
				if (!enumerable)
				{
					throw std::invalid_argument { "enumerable must not be nullptr" };
				}

				if (position == iterator_position::in_range)
				{
					throw std::invalid_argument { "position must not be in_range" };
				}
			}

			~impl()
			{
				destroy_current();
			}

			void increment(const iterator* iterator)
			{
				initialize_before_first();

				if (position == iterator_position::after_last)
				{
					throw std::logic_error { "iterator cannot be incremented when it points after last enumerable element" };
				}

				if (incrementor == nullptr)
				{
					incrementor = iterator;
				}

				if (incrementor != iterator)
				{
					throw std::logic_error { "Incrementing iterator copied from previously incremented iterator is not supported." };
				}

				get_next();
			}

			element_t& dereference()
			{
				initialize_before_first();

				if (position == iterator_position::after_last)
				{
					throw std::logic_error { "iterator cannot be dereferenced when it points after last enumerable element" };
				}

				return current;
			}

			bool equal(impl& other)
			{
				if (enumerable != other.enumerable)
				{
					return false;
				}

				if (position == iterator_position::in_range || other.position == iterator_position::in_range)
				{
					return false;
				}

				if (position == iterator_position::after_last)
				{
					other.initialize_before_first();
				}

				if (other.position == iterator_position::after_last)
				{
					initialize_before_first();
				}

				return position == other.position;
			}
		};

		std::shared_ptr<impl> pimpl;
	};
}}