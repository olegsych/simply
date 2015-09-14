#pragma once

#include <stdexcept>
#include <simply/utility/enumerable.h>
#include <simply/utility/iterator_position.h>

namespace simply { namespace utility
{
	template<typename element_t> class iterator
	{
	public:
		iterator(std::shared_ptr<enumerable<element_t>> enumerable, iterator_position position)
			: _enumerable { enumerable }
			, _position { position }
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

		iterator(const iterator& source)
			: iterator(source._enumerable, source._position)
		{
		}

		~iterator()
		{
			destroy_current();
		}

		iterator_position position() const
		{
			return _position;
		}

		iterator& operator=(const iterator& source)
		{
			if (source._position == iterator_position::in_range)
			{
				throw std::invalid_argument { "position must not be in_range" };
			}

			destroy_current();
			_position = source._position;
			_enumerable = source._enumerable;
			return *this;
		}

		element_t& operator*()
		{
			initialize_before_first();

			if (_position == iterator_position::after_last)
			{
				throw std::logic_error { "range iterator is not dereferencable" };
			}

			return _current;
		}

		iterator& operator++()
		{
			initialize_before_first();

			if (_position == iterator_position::after_last)
			{
				throw std::logic_error { "range iterator is not incrementable" };
			}

			get_next();
			return *this;
		}

		bool operator==(iterator& other)
		{
			if (_enumerable != other._enumerable)
			{
				return false;
			}

			if (_position == iterator_position::in_range || other._position == iterator_position::in_range)
			{
				return false;
			}

			if (_position == iterator_position::after_last)
			{
				other.initialize_before_first();
			}

			if (other._position == iterator_position::after_last)
			{
				initialize_before_first();
			}

			return _position == other._position;
		}

		bool operator!=(iterator& other)
		{
			return !(*this == other);
		}

	private:
		iterator_position _position;
		std::shared_ptr<enumerable<element_t>> _enumerable;
		std::unique_ptr<enumerator<element_t>> _enumerator;
		#pragma warning (disable: 4624) // union destructor is deleted
		union { element_t _current; };
		#pragma warning (default: 4624)

		void destroy_current()
		{
			if (_position == iterator_position::in_range)
			{
				_current.~element_t();
			}
		}

		void get_next()
		{
			destroy_current();
			if (_enumerator->get_next(&_current))
			{
				_position = iterator_position::in_range;
			}
			else
			{
				_position = iterator_position::after_last;
			}
		}

		void initialize_before_first()
		{
			if (_position == iterator_position::before_first)
			{
				_enumerator = _enumerable->create_enumerator();
				get_next();
			}
		}
	};
}}