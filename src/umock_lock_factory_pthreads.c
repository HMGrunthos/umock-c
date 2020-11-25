// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>
#include <pthread.h>

#include "macro_utils/macro_utils.h"

#include "umock_c/umockalloc.h"
#include "umock_c/umock_log.h"
#include "umock_c/umock_lock_factory.h"
#include "umock_c/umock_lock_factory_default.h"

typedef struct UMOCK_C_LOCK_PTHREADS_TAG
{
    UMOCK_C_LOCK_IF lock_if;
    pthread_rwlock_t rw_lock;
} UMOCK_C_LOCK_PTHREADS;

static void umock_lock_pthreads_acquire_shared(UMOCK_C_LOCK_HANDLE lock)
{
    UMOCK_C_LOCK_PTHREADS* umock_c_lock_windows = (UMOCK_C_LOCK_PTHREADS*)lock;
    if (pthread_rwlock_rdlock(&umock_c_lock_windows->rw_lock) != 0)
    {
        UMOCK_LOG("pthread_rwlock_rdlock failed");
    }
}

static void umock_lock_pthreads_release_shared(UMOCK_C_LOCK_HANDLE lock)
{
    UMOCK_C_LOCK_PTHREADS* umock_c_lock_windows = (UMOCK_C_LOCK_PTHREADS*)lock;
    if (pthread_rwlock_unlock(&umock_c_lock_windows->rw_lock) != 0)
    {
        UMOCK_LOG("pthread_rwlock_unlock failed");
    }
}

static void umock_lock_pthreads_acquire_exclusive(UMOCK_C_LOCK_HANDLE lock)
{
    UMOCK_C_LOCK_PTHREADS* umock_c_lock_windows = (UMOCK_C_LOCK_PTHREADS*)lock;
    if (pthread_rwlock_wrlock(&umock_c_lock_windows->rw_lock) != 0)
    {
        UMOCK_LOG("pthread_rwlock_rdlock failed");
    }
}

static void umock_lock_pthreads_release_exclusive(UMOCK_C_LOCK_HANDLE lock)
{
    UMOCK_C_LOCK_PTHREADS* umock_c_lock_windows = (UMOCK_C_LOCK_PTHREADS*)lock;
    if (pthread_rwlock_unlock(&umock_c_lock_windows->rw_lock) != 0)
    {
        UMOCK_LOG("pthread_rwlock_unlock failed");
    }
}

static void umock_lock_pthreads_destroy(UMOCK_C_LOCK_HANDLE lock)
{
    UMOCK_C_LOCK_PTHREADS* umock_c_lock_windows = (UMOCK_C_LOCK_PTHREADS*)lock;
    pthread_rwlock_destroy(&umock_c_lock_windows->rw_lock);
    umockalloc_free(umock_c_lock_windows);
}

UMOCK_C_LOCK_HANDLE umock_lock_factory_create_lock(void* params)
{
    (void)params;

    UMOCK_C_LOCK_HANDLE result;
    UMOCK_C_LOCK_PTHREADS* rw_lock_pthreads = umockalloc_malloc(sizeof(UMOCK_C_LOCK_PTHREADS));
    if (rw_lock_pthreads == NULL)
    {
        UMOCK_LOG("umockalloc_malloc(%zu) failed", sizeof(UMOCK_C_LOCK_PTHREADS));
    }
    else
    {
        rw_lock_pthreads->lock_if.acquire_shared = umock_lock_pthreads_acquire_shared;
        rw_lock_pthreads->lock_if.release_shared = umock_lock_pthreads_release_shared;
        rw_lock_pthreads->lock_if.acquire_exclusive = umock_lock_pthreads_acquire_exclusive;
        rw_lock_pthreads->lock_if.release_exclusive = umock_lock_pthreads_release_exclusive;
        rw_lock_pthreads->lock_if.destroy = umock_lock_pthreads_destroy;

        if (pthread_rwlock_init(&rw_lock_pthreads->rw_lock, NULL) != 0)
        {
            UMOCK_LOG("pthread_rwlock_init failed");
        }
        else
        {
            result = &rw_lock_pthreads->lock_if;
            goto all_ok;
        }

        umockalloc_free(rw_lock_pthreads);
    }

    result = NULL;

all_ok:
    return result;
}
