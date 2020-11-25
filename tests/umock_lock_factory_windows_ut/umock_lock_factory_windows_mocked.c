// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stddef.h>

#include "windows.h"

void* mock_malloc(size_t size);
void mock_free(void* ptr);

#define umockalloc_malloc(size) mock_malloc(size)
#define umockalloc_free(ptr) mock_free(ptr)

#define InitializeSRWLock(SRWLock) mock_InitializeSRWLock(SRWLock)
#define AcquireSRWLockShared(SRWLock) mock_AcquireSRWLockShared(SRWLock)
#define ReleaseSRWLockShared(SRWLock) mock_ReleaseSRWLockShared(SRWLock)
#define AcquireSRWLockExclusive(SRWLock) mock_AcquireSRWLockExclusive(SRWLock)
#define ReleaseSRWLockExclusive(SRWLock) mock_ReleaseSRWLockExclusive(SRWLock)

void mock_InitializeSRWLock(PSRWLOCK SRWLock);
void mock_AcquireSRWLockShared(PSRWLOCK SRWLock);
void mock_ReleaseSRWLockShared(PSRWLOCK SRWLock);
void mock_AcquireSRWLockExclusive(PSRWLOCK SRWLock);
void mock_ReleaseSRWLockExclusive(PSRWLOCK SRWLock);

/* include code under test */
#include "../../src/umock_lock_factory_windows.c"
