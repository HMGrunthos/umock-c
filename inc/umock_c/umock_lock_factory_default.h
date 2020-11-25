// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef UMOCK_LOCK_FACTORY_DEFAULT_H
#define UMOCK_LOCK_FACTORY_DEFAULT_H

#include "umock_c/umock_lock_if.h"

#ifdef __cplusplus
extern "C" {
#endif

    UMOCK_C_LOCK_HANDLE umock_lock_factory_create_lock(void* params);

#ifdef __cplusplus
}
#endif

#endif /* UMOCK_LOCK_FACTORY_DEFAULT_H */
