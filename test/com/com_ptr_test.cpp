#include "stdafx.h"
#include "stub_IUnknown.h"

using namespace simply;
using namespace std;

namespace simply { namespace com 
{
    TEST_CLASS(com_ptr_test)
    {
    public:
        TEST_METHOD(default_constructor_initializes_instance_with_nullptr)
        {
            com_ptr<IUnknown> sut;
            assert::is_null(sut.get());
        }

        TEST_METHOD(raw_constructor_throws_invalid_argument_when_given_object_is_null)
        {
            IUnknown* object = nullptr;
            assert::throws<invalid_argument>([&] { com_ptr<IUnknown> sut(object); });
        }

        TEST_METHOD(raw_constructor_stores_given_raw_pointer)
        {
            stub_IUnknown stub;
            com_ptr<IUnknown> sut { &stub };
            assert::is_equal<void*>(&stub, sut.get());
        }

        TEST_METHOD(raw_constructor_calls_AddRef_because_it_stores_new_copy_of_raw_pointer)
        {
            stub_IUnknown stub;
            bool reference_added = false;
            stub.add_ref = [&]
            {
                reference_added = true;
                return 2;
            };

            com_ptr<IUnknown> sut { &stub };

            assert::is_true(reference_added);
        }

        TEST_METHOD(copy_constructor_stores_raw_pointer_extracted_from_source)
        {
            stub_IUnknown stub;
            com_ptr<IUnknown> source { &stub };
            com_ptr<IUnknown> sut { source };
            assert::is_equal<void*>(&stub, sut.get());
        }

        TEST_METHOD(copy_constructor_calls_AddRef_because_it_stores_new_copy_of_raw_pointer)
        {
            stub_IUnknown stub;
            int reference_count = 0;
            stub.add_ref = [&] { return ++reference_count; };
            com_ptr<IUnknown> source { &stub };

            com_ptr<IUnknown> sut { source };

            assert::is_equal(2, reference_count);
        }

        TEST_METHOD(copy_constructor_does_nothing_when_source_raw_pointer_is_null)
        {
            com_ptr<IUnknown> source;
            com_ptr<IUnknown> sut { source };
            assert::is_null(sut.get());
        }

        TEST_METHOD(move_constructor_stores_raw_pointer_extracted_from_source)
        {
            stub_IUnknown stub;
            com_ptr<IUnknown> source { &stub };
            com_ptr<IUnknown> sut { move(source) };
            assert::is_equal<void*>(&stub, sut.get());
        }

        TEST_METHOD(move_constructor_removes_pointer_from_source)
        {
            stub_IUnknown stub;
            com_ptr<IUnknown> source { &stub };
            com_ptr<IUnknown> sut { move(source) };
            assert::is_null(source.get());
        }

        TEST_METHOD(move_constructor_doesnt_call_AddRef_because_it_moves_raw_pointer)
        {
            stub_IUnknown stub;
            com_ptr<IUnknown> source { &stub };

            int references_added = 0;
            stub.add_ref = [&] { return ++references_added; };
            com_ptr<IUnknown> sut { move(source) };

            assert::is_equal(0, references_added);
        }

        TEST_METHOD(copy_assignment_stores_raw_pointer_extracted_from_source)
        {
            stub_IUnknown stub;
            com_ptr<IUnknown> source { &stub };
            com_ptr<IUnknown> sut;

            sut = source;

            assert::is_equal<void*>(&stub, sut.get());
        }

        TEST_METHOD(copy_assignment_returns_reference_to_self)
        {
            com_ptr<IUnknown> source;
            com_ptr<IUnknown> sut;

            com_ptr<IUnknown>& result = (sut = source);

            assert::is_equal<void*>(&sut, &result);
        }

        TEST_METHOD(copy_assignment_calls_AddRef_for_newly_stored_raw_pointer)
        {
            stub_IUnknown stub;
            com_ptr<IUnknown> source { &stub };
            com_ptr<IUnknown> sut;

            int references_added = 0;
            stub.add_ref = [&] { return ++references_added; };
            sut = source;

            assert::is_equal(1, references_added);
        }

        TEST_METHOD(copy_assigned_calls_Release_for_previously_stored_raw_pointer)
        {
            com_ptr<IUnknown> source;
            stub_IUnknown stub;
            com_ptr<IUnknown> sut { &stub };

            int references_released = 0;
            stub.release = [&] { return ++references_released; };
            sut = source;

            assert::is_equal(1, references_released);
        }

        TEST_METHOD(move_assignment_stores_raw_pointer_extracted_from_source)
        {
            stub_IUnknown stub;
            com_ptr<IUnknown> sut;

            sut = com_ptr<IUnknown> { &stub };

            assert::is_equal<void*>(&stub, sut.get());
        }

        TEST_METHOD(move_assignment_returns_reference_to_self)
        {
            com_ptr<IUnknown> sut;

            com_ptr<IUnknown>& result = (sut = com_ptr<IUnknown> {});

            assert::is_equal<void*>(&sut, &result);
        }

        TEST_METHOD(move_assignment_calls_Release_for_previously_stored_raw_pointer)
        {
            stub_IUnknown stub;
            com_ptr<IUnknown> sut { &stub };

            int references_released = 0;
            stub.release = [&] { return ++references_released; };
            sut = com_ptr<IUnknown> {};

            assert::is_equal(1, references_released);
        }

        TEST_METHOD(move_assignment_doesnt_call_AddRef_because_it_moves_raw_pointer)
        {
            stub_IUnknown stub;
            com_ptr<IUnknown> source { &stub };
            com_ptr<IUnknown> sut;

            int references_added = 0;
            stub.add_ref = [&] { return ++references_added; };
            sut = move(source);

            assert::is_equal(0, references_added);
        }

        TEST_METHOD(move_assignment_prevents_source_from_calling_Release_because_it_moves_raw_pointer)
        {
            stub_IUnknown stub;
            com_ptr<IUnknown> source { &stub };
            com_ptr<IUnknown> sut;

            int references_released = 0;
            stub.release = [&] { return ++references_released; };
            sut = move(source);

            assert::is_equal(0, references_released);
        }

        TEST_METHOD(destructor_calls_Release_because_raw_pointer_is_going_out_of_scope)
        {
            stub_IUnknown stub;
            com_ptr<IUnknown> sut { &stub };
            bool reference_released = false;
            stub.release = [&]
            {
                reference_released = true;
                return 1;
            };

            sut.~com_ptr();

            assert::is_true(reference_released);
        }

        TEST_METHOD(destructor_does_nothing_if_object_is_null)
        {
            com_ptr<IUnknown> sut;
            sut.~com_ptr(); // no exceptions expected
        }

        TEST_METHOD(voidpp_conversion_operator_returns_address_of_object_field_for_use_with_QueryInterface)
        {
            com_ptr<IUnknown> sut;

            void** result = sut;

            assert::is_true(result == reinterpret_cast<void**>(&sut.object));
        }

        TEST_METHOD(IUnknownpp_conversion_operator_returns_address_of_object_field_for_use_with_metadata_apis)
        {
            com_ptr<IUnknown> sut;

            IUnknown** result = sut;

            assert::is_true(result == &sut.object);
        }

        TEST_METHOD(dereferencing_operator_returns_object_for_accessing_its_members)
        {
            stub_IUnknown stub;
            com_ptr<IUnknown> sut { &stub };

            IUnknown* result = sut.operator->();

            assert::is_equal<IUnknown*>(&stub, result);
        }

        TEST_METHOD(dereferencing_operator_throws_logic_error_when_object_is_null)
        {
            com_ptr<IUnknown> sut;
            auto e = assert::throws<logic_error>([&] { sut.operator->(); });
            assert::find("null", e->what());
        }
    };
}}