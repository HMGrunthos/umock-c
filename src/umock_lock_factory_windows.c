// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "windows.h"

#include "macro_utils/macro_utils.h"

#include "umock_c/umockalloc.h"
#include "umock_c/umock_log.h"
#include "umock_c/umock_lock_factory.h"

typedef struct UMOCK_C_LOCK_WINDOWS_TAG
{
    UMOCK_C_LOCK_IF lock_if;
    SRWLOCK srw_lock;
} UMOCK_C_LOCK_WINDOWS;

static void umock_lock_windows_acquire_shared(UMOCK_C_LOCK_HANDLE lock)
{
    UMOCK_C_LOCK_WINDOWS* wmock_c_lock_windows = (UMOCK_C_LOCK_WINDOWS*)lock;
    AcquireSRWLockShared(&wmock_c_lock_windows->srw_lock);
}

static void umock_lock_windows_release_shared(UMOCK_C_LOCK_HANDLE lock)
{
    UMOCK_C_LOCK_WINDOWS* wmock_c_lock_windows = (UMOCK_C_LOCK_WINDOWS*)lock;
    ReleaseSRWLockShared(&wmock_c_lock_windows->srw_lock);
}

static void umock_lock_windows_acquire_exclusive(UMOCK_C_LOCK_HANDLE lock)
{
    UMOCK_C_LOCK_WINDOWS* wmock_c_lock_windows = (UMOCK_C_LOCK_WINDOWS*)lock;
    AcquireSRWLockExclusive(&wmock_c_lock_windows->srw_lock);
}

static void umock_lock_windows_release_exclusive(UMOCK_C_LOCK_HANDLE lock)
{
    UMOCK_C_LOCK_WINDOWS* wmock_c_lock_windows = (UMOCK_C_LOCK_WINDOWS*)lock;
    ReleaseSRWLockExclusive(&wmock_c_lock_windows->srw_lock);
}

UMOCK_C_LOCK_HANDLE umock_lock_factory_create_lock(void)
{
    UMOCK_C_LOCK_HANDLE result;
    UMOCK_C_LOCK_WINDOWS* srw_lock_windows = umockalloc_malloc(sizeof(UMOCK_C_LOCK_WINDOWS));
    if (srw_lock_windows == NULL)
    {
        UMOCK_LOG("umockalloc_malloc(%zu) failed", sizeof(UMOCK_C_LOCK_WINDOWS));
        result = NULL;
    }
    else
    {
        srw_lock_windows->lock_if.acquire_shared = umock_lock_windows_acquire_shared;
        srw_lock_windows->lock_if.release_shared = umock_lock_windows_release_shared;
        srw_lock_windows->lock_if.acquire_exclusive = umock_lock_windows_acquire_exclusive;
        srw_lock_windows->lock_if.release_exclusive = umock_lock_windows_release_exclusive;

        InitializeSRWLock(&srw_lock_windows->srw_lock);

        result = &srw_lock_windows->lock_if;
    }

    return result;
}
