#include "stdafx.h"
#include <memory>
#include <vector>
#include "stub_enumerable.h"
#include "stub_enumerator.h"

using namespace std;

namespace simply { namespace utility
{
	TEST_CLASS(iterator_test)
	{
		template<typename element_t> shared_ptr<enumerable<element_t>> create_enumerable(initializer_list<element_t> elements)
		{
			auto enumerable_stub = new stub_enumerable<element_t>(elements);
			return shared_ptr<enumerable<element_t>> { enumerable_stub };
		}

	public:
		TEST_METHOD(iterator_implements_iterator_concept)
		{
			using actual = iterator<int>;
			assert::is_copy_constructible<actual>();
			assert::is_copy_assignable<actual>();
			assert::is_destructible<actual>();
		}

		#pragma region iterator(shared_ptr<enumerable<element_t>>, position)

		TEST_METHOD(constructor_throws_invalid_argument_when_enumerable_is_null)
		{
			shared_ptr<enumerable<int>> enumerable { nullptr };
			auto e = assert::throws<invalid_argument>([&] { iterator<int> { enumerable, iterator_position::before_first }; });
			assert::find("enumerable must not be nullptr", e->what());
		}

		TEST_METHOD(constructor_throws_invalid_argument_when_position_is_in_range)
		{
			auto e = assert::throws<invalid_argument>([&] { iterator<int> { create_enumerable<int>({}), iterator_position::in_range }; });
			assert::find("position must not be in_range", e->what());
		}

		TEST_METHOD(constructor_sets_position_to_given_value)
		{
			auto expected_value = iterator_position::after_last;
			iterator<int> sut { create_enumerable<int>({}), expected_value };
			assert::is_true(expected_value == sut.position()); // TODO: define << for position enum
		}

		#pragma endregion

		#pragma region iterator(const iterator&)

		TEST_METHOD(copy_constructor_throws_invalid_argument_when_source_position_is_in_range)
		{
			iterator<int> source { create_enumerable<int>({ 41, 42 }), iterator_position::before_first };
			++source;
			auto e = assert::throws<invalid_argument>([&] { iterator<int> { source }; });
			assert::find("position must not be in_range", e->what());
		}

		TEST_METHOD(copy_constructor_sets_position_to_value_from_source)
		{
			iterator<int> source { create_enumerable<int>({}), iterator_position::after_last };
			iterator<int> sut { source };
			assert::is_true(source.position() == sut.position()); // TODO: define << for position
		}

		TEST_METHOD(copy_constructor_initializes_iterator_with_enumerable_from_source)
		{
			iterator<int> source { create_enumerable<int>({ 42 }), iterator_position::before_first };
			iterator<int> sut { source };
			assert::is_equal(*source, *sut);
		}

		#pragma endregion

		#pragma region operator=(const iterator&)

		TEST_METHOD(copy_assignment_operator_throws_invalid_argument_when_source_position_is_in_range)
		{
			iterator<int> source { create_enumerable<int>({ 41, 42 }), iterator_position::before_first };
			++source;
			iterator<int> target { create_enumerable<int>({}), iterator_position::after_last };
			auto e = assert::throws<invalid_argument>([&] { target = source; });
			assert::find("position must not be in_range", e->what());
		}

		TEST_METHOD(copy_assignment_operator_sets_position_to_value_from_source)
		{
			const auto expected = iterator_position::after_last;
			iterator<int> source { create_enumerable<int>({}), expected };
			iterator<int> target { create_enumerable<int>({}), iterator_position::before_first };
			target = source;
			assert::is_true(expected == target.position()); // TODO: define << for position
		}

		TEST_METHOD(copy_assignment_operator_sets_enumerable_from_source)
		{
			const int expected = 42;
			iterator<int> source { create_enumerable<int>({ expected }), iterator_position::before_first };
			iterator<int> target { create_enumerable<int>({}), iterator_position::before_first };;
			target = source;
			assert::is_equal(expected, *target);
		}

		TEST_METHOD(copy_assignment_operator_returns_reference_to_itself)
		{
			iterator<int> source { create_enumerable<int>({}), iterator_position::before_first };
			iterator<int> target { create_enumerable<int>({}), iterator_position::before_first };;
			iterator<int>& result = (target = source);
			assert::is_equal(&target, &result);
		}

		#pragma endregion

		#pragma region operator*()

		TEST_METHOD(dereferencing_operator_returns_reference_of_element_type)
		{
			using expected = int&;
			using actual = decltype(declval<iterator<int>>().operator*());
			assert::is_same<expected, actual>();
		}

		TEST_METHOD(dereferencing_operator_throws_logic_error_in_past_end_of_enumerable)
		{
			iterator<int> sut { create_enumerable<int>({}), iterator_position::after_last };
			auto e = assert::throws<logic_error>([&] { *sut; });
			assert::find("range iterator is not dereferencable", e->what());
		}

		TEST_METHOD(dereferencing_operator_throws_logic_error_when_enumerable_is_empty)
		{
			iterator<int> sut { create_enumerable<int>({}), iterator_position::before_first };
			auto e = assert::throws<logic_error>([&] { *sut; });
			assert::find("range iterator is not dereferencable", e->what());
		}

		TEST_METHOD(dereferencing_operator_throws_logic_error_when_invoked_after_last_element)
		{
			iterator<int> sut { create_enumerable<int>({ 42 }), iterator_position::before_first };
			++sut;
			auto e = assert::throws<logic_error>([&] { *sut; });
			assert::find("range iterator is not dereferencable", e->what());
		}

		TEST_METHOD(dereferencing_operator_creates_enumerator_and_gets_next_value_when_called_first_time)
		{
			iterator<int> sut { create_enumerable<int>({ 42 }), iterator_position::before_first };
			assert::is_equal(42, *sut);
		}

		TEST_METHOD(dereferencing_operator_returns_same_value_when_called_second_time)
		{
			iterator<int> sut { create_enumerable<int>({ 42 }), iterator_position::before_first };
			*sut;
			assert::is_equal(42, *sut);
		}

		#pragma endregion

		#pragma region operator++()

		TEST_METHOD(increment_operator_returns_reference_of_iterator_type)
		{
			using expected = iterator<int>&;
			using actual = decltype(declval<iterator<int>>().operator++());
			assert::is_same<expected, actual>();
		}

		TEST_METHOD(increment_operator_returns_reference_to_itself)
		{
			iterator<int> expected { create_enumerable<int>({ 42 }), iterator_position::before_first };
			iterator<int>& actual = ++expected;
			assert::is_equal(&expected, &actual);
		}

		TEST_METHOD(increment_operator_throws_logic_error_in_past_end_iterator)
		{
			iterator<int> sut { create_enumerable<int>({}), iterator_position::after_last };
			auto e = assert::throws<logic_error>([&] { ++sut; });
			assert::find("range iterator is not incrementable", e->what());
		}

		TEST_METHOD(increment_operator_throws_logic_error_when_enumerable_is_empty)
		{
			iterator<int> sut { create_enumerable<int>({}), iterator_position::before_first };
			auto e = assert::throws<logic_error>([&] { ++sut; });
			assert::find("range iterator is not incrementable", e->what());
		}

		TEST_METHOD(increment_operator_throws_logic_error_when_invoked_after_last_element)
		{
			iterator<int> sut { create_enumerable<int>({ 42 }), iterator_position::before_first };
			++sut;
			auto e = assert::throws<logic_error>([&] { ++sut; });
			assert::find("range iterator is not incrementable", e->what());
		}

		TEST_METHOD(increment_operator_gets_first_element_before_getting_next)
		{
			iterator<int> sut { create_enumerable<int>({ 41, 42 }), iterator_position::before_first };
			++sut;
			assert::is_equal(42, *sut);
		}

		TEST_METHOD(increment_operator_doesnt_get_first_element_after_previous_dereferencing)
		{
			iterator<int> sut { create_enumerable<int>({ 41, 42 }), iterator_position::before_first };
			*sut;
			++sut;
			assert::is_equal(42, *sut);
		}

		TEST_METHOD(increment_operator_doesnt_get_first_element_after_previous_increment)
		{
			iterator<int> sut { create_enumerable<int>({ 40, 41, 42 }), iterator_position::before_first };
			++sut;
			++sut;
			assert::is_equal(42, *sut);
		}

		#pragma endregion

		#pragma region iterator::operator==() and iterator::operator!=()

		TEST_METHOD(iterators_are_equal_when_they_are_both_before_first_element_of_same_enumerable)
		{
			auto enumerable = create_enumerable<int>({ 42 });
			iterator<int> x { enumerable, iterator_position::before_first };
			iterator<int> y { enumerable, iterator_position::before_first };
			assert::is_true(x == y);
			assert::is_false(x != y);
		}

		TEST_METHOD(iterators_are_equal_when_they_are_both_after_last_element_of_same_enumerable)
		{
			auto enumerable = create_enumerable<int>({ 42 });
			iterator<int> x { enumerable, iterator_position::after_last };
			iterator<int> y { enumerable, iterator_position::after_last };
			assert::is_true(x == y);
			assert::is_false(x != y);
		}

		TEST_METHOD(iterators_are_not_equal_when_they_point_to_different_enumerables_in_same_position)
		{
			iterator<int> x { create_enumerable<int>({ 42 }), iterator_position::before_first };
			iterator<int> y { create_enumerable<int>({ 42 }), iterator_position::before_first };
			assert::is_false(x == y);
			assert::is_true(x != y);
		}

		TEST_METHOD(iterators_are_not_equal_when_they_point_to_different_position_in_same_enumerables)
		{
			auto enumerable = create_enumerable<int>({ 42 });
			iterator<int> x { enumerable, iterator_position::before_first };
			iterator<int> y { enumerable, iterator_position::after_last };
			assert::is_false(x == y);
			assert::is_true(x != y);
		}

		TEST_METHOD(iterators_are_not_equal_when_they_point_in_range_of_same_enumerable_because_exact_position_is_undefined)
		{
			auto enumerable = create_enumerable<int>({ 41, 42 });
			iterator<int> x { enumerable, iterator_position::before_first };
			iterator<int> y { enumerable, iterator_position::before_first };
			++x;
			++y;
			assert::is_false(x == y);
			assert::is_true(x != y);
		}

		TEST_METHOD(iterator_equality_operator_gets_first_element_of_left_operand_if_right_operand_is_after_last_to_guarantee_equality_of_begin_and_end_iterators_for_empty_range)
		{
			shared_ptr<enumerable<int>> enumerable = create_enumerable<int>({});
			iterator<int> begin { enumerable, iterator_position::before_first };
			iterator<int> end { enumerable, iterator_position::after_last };
			assert::is_true(begin == end);
		}

		TEST_METHOD(iterator_equality_operator_gets_first_element_of_right_operand_if_left_operand_is_after_last_to_guarantee_equality_of_begin_and_end_iterators_for_empty_range)
		{
			shared_ptr<enumerable<int>> enumerable = create_enumerable<int>({});
			iterator<int> begin { enumerable, iterator_position::before_first };
			iterator<int> end { enumerable, iterator_position::after_last };
			assert::is_true(end == begin);
		}

		#pragma endregion
	};
}}