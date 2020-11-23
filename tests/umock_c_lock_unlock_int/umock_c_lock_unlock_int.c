// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
#else
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#endif

#include "macro_utils/macro_utils.h"

#include "testrunnerswitcher.h"

#define ENABLE_MOCKS

#include "umock_c/umock_c.h"

MOCKABLE_FUNCTION(, void, test_mock_function);

#undef ENABLE_MOCKS

MU_DEFINE_ENUM_STRINGS(UMOCK_C_ERROR_CODE, UMOCK_C_ERROR_CODE_VALUES)

static void test_on_umock_c_error(UMOCK_C_ERROR_CODE error_code)
{
    ASSERT_FAIL("umock_c reported error :%s", MU_ENUM_TO_STRING(UMOCK_C_ERROR_CODE, error_code));
}

static TEST_MUTEX_HANDLE test_mutex;

static int test_lock_function(void* context, UMOCK_C_LOCK_TYPE lock_type)
{
    (void)context;
    (void)lock_type;
    return 0;
}

static int test_unlock_function(void* context)
{
    (void)context;
    return 0;
}

BEGIN_TEST_SUITE(umock_c_lock_unlock_integrationtests)

TEST_SUITE_INITIALIZE(suite_init)
{
    test_mutex = TEST_MUTEX_CREATE();
    ASSERT_IS_NOT_NULL(test_mutex);

    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
}

TEST_SUITE_CLEANUP(suite_cleanup)
{
    umock_c_deinit();

    TEST_MUTEX_DESTROY(test_mutex);
}

TEST_FUNCTION_INITIALIZE(test_function_init)
{
    int mutex_acquire_result = TEST_MUTEX_ACQUIRE(test_mutex);
    ASSERT_ARE_EQUAL(int, 0, mutex_acquire_result);

    umock_c_reset_all_calls();
}

TEST_FUNCTION_CLEANUP(test_function_cleanup)
{
    TEST_MUTEX_RELEASE(test_mutex);
}

TEST_FUNCTION(expected_calls_and_actual_calls_from_multiple_threads_do_not_crash)
{
    // arrange
    umock_c_set_lock_functions(test_lock_function, test_unlock_function, (void*)0x4242);

    // act

    // assert
}

END_TEST_SUITE(umock_c_lock_unlock_integrationtests)