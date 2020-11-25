// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stddef.h>
#include <pthread.h>

void* mock_malloc(size_t size);
void mock_free(void* ptr);

#define umockalloc_malloc(size) mock_malloc(size)
#define umockalloc_free(ptr) mock_free(ptr)

#define pthread_rwlock_init(rwlock, attr) mock_pthread_rwlock_init(rwlock, attr)
#define pthread_rwlock_rdlock(rwlock) mock_pthread_rwlock_rdlock(rwlock)
#define pthread_rwlock_unlock(rwlock) mock_pthread_rwlock_unlock(rwlock)
#define pthread_rwlock_wrlock(rwlock) mock_pthread_rwlock_wrlock(rwlock)
#define pthread_rwlock_destroy(rwlock) mock_pthread_rwlock_destroy(rwlock)

int mock_pthread_rwlock_init(pthread_rwlock_t *rwlock,
    const pthread_rwlockattr_t *attr);
int mock_pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
int mock_pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
int mock_pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
int mock_pthread_rwlock_destroy(pthread_rwlock_t *rwlock);

/* include code under test */
#include "../../src/umock_lock_factory_pthread.c"
