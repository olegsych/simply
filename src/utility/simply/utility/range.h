#pragma once

#include <stdexcept>
#include <utility>
#include <simply/utility/enumerable.h>

namespace simply { namespace utility
{
    template<typename element_t> class range
    {
    public:
		enum class position : char
		{
			before_first,
			in_range,
			after_last
		};

		class iterator
        {
        public:
			iterator(std::shared_ptr<enumerable<element_t>> enumerable, position position)
				: _enumerable { enumerable }
				, _position { position }
			{
				if (!enumerable)
				{
					throw std::invalid_argument { "enumerable must not be nullptr" };
				}

				if (position == position::in_range)
				{
					throw std::invalid_argument { "position must not be in_range" };
				}
			}

			iterator(const iterator& source)
				: iterator(source._enumerable, source._position)
			{
			}

			position position() const
			{
				return _position;
			}

			iterator& operator=(const iterator& source)
			{
				if (source._position == position::in_range)
				{
					throw std::invalid_argument{ "position must not be in_range" };
				}

				_position = source._position;
				_enumerable = source._enumerable;
				return *this;
			}

            element_t& operator*() 
            {
				initialize_before_first();

                if (_position == position::after_last)
                {
                    throw std::logic_error { "range iterator is not dereferencable" };
                }

                return _current;
            }

            iterator& operator++()
            {
				initialize_before_first();

                if (_position == position::after_last)
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

				if (_position == position::in_range || other._position == position::in_range)
				{
					return false;
				}

				if (_position == position::after_last)
				{
					other.initialize_before_first();
				}

				if (other._position == position::after_last)
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
			typename range<element_t>::position _position;
			std::shared_ptr<enumerable<element_t>> _enumerable;
			std::unique_ptr<enumerator<element_t>> _enumerator;
            element_t _current;

            void get_next()
            {
                if (_enumerator->get_next(&_current))
                {
                    _position = position::in_range;
                }
                else
                {
                    _position = position::after_last;
                }
            }

			void initialize_before_first()
			{
				if (_position == position::before_first)
				{
					_enumerator = _enumerable->create_enumerator();
					get_next();
				}
			}
        };

		range(std::shared_ptr<enumerable<element_t>> enumerable)
			: _enumerable { enumerable }
		{
			if (!enumerable)
			{
				throw std::invalid_argument{ "enumerable must not be nullptr" };
			}
		}

        iterator begin() const
        {
			return iterator { _enumerable, position::before_first };
        }

        iterator end() const
        {
            return iterator { _enumerable, position::after_last };
        }

	private:
		std::shared_ptr<enumerable<element_t>> _enumerable;
    };
}}