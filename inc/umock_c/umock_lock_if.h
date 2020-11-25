// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef UMOCK_LOCK_IF_H
#define UMOCK_LOCK_IF_H

#include "macro_utils/macro_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef const struct UMOCK_C_LOCK_IF_TAG* UMOCK_C_LOCK_HANDLE;

typedef void (*UMOCK_C_LOCK_ACQUIRE_SHARED_FUNC)(UMOCK_C_LOCK_HANDLE lock);
typedef void (*UMOCK_C_LOCK_RELEASE_SHARED_FUNC)(UMOCK_C_LOCK_HANDLE lock);
typedef void (*UMOCK_C_LOCK_ACQUIRE_EXCLUSIVE_FUNC)(UMOCK_C_LOCK_HANDLE lock);
typedef void (*UMOCK_C_LOCK_RELEASE_EXCLUSIVE_FUNC)(UMOCK_C_LOCK_HANDLE lock);
typedef void (*UMOCK_C_LOCK_DESTROY_FUNC)(UMOCK_C_LOCK_HANDLE lock);

typedef struct UMOCK_C_LOCK_IF_TAG
{
    UMOCK_C_LOCK_ACQUIRE_SHARED_FUNC acquire_shared;
    UMOCK_C_LOCK_RELEASE_SHARED_FUNC release_shared;
    UMOCK_C_LOCK_ACQUIRE_EXCLUSIVE_FUNC acquire_exclusive;
    UMOCK_C_LOCK_RELEASE_EXCLUSIVE_FUNC release_exclusive;
    UMOCK_C_LOCK_DESTROY_FUNC destroy;
} UMOCK_C_LOCK_IF;

#ifdef __cplusplus
}
#endif

#endif /* UMOCK_LOCK_IF_H */
