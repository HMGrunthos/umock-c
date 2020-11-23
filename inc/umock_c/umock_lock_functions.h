// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef UMOCK_LOCK_FUNCTIONS_H
#define UMOCK_LOCK_FUNCTIONS_H

#include "macro_utils/macro_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UMOCK_C_LOCK_TYPE_VALUES \
    UMOCK_C_LOCK_TYPE_READ, \
    UMOCK_C_LOCK_TYPE_WRITE

MU_DEFINE_ENUM(UMOCK_C_LOCK_TYPE, UMOCK_C_LOCK_TYPE_VALUES)

typedef int (*UMOCK_C_LOCK_FUNCTION)(void* context, UMOCK_C_LOCK_TYPE lock_type);
typedef int (*UMOCK_C_UNLOCK_FUNCTION)(void* context, UMOCK_C_LOCK_TYPE lock_type);

#ifdef __cplusplus
}
#endif

#endif /* UMOCK_LOCK_FUNCTIONS_H */
