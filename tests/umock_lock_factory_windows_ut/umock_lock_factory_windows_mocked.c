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

extern void mock_InitializeSRWLock(PSRWLOCK SRWLock);
extern void AcquireSRWLockShared(PSRWLOCK SRWLock);
extern void ReleaseSRWLockShared(PSRWLOCK SRWLock);
extern void AcquireSRWLockExclusive(PSRWLOCK SRWLock);
extern void ReleaseSRWLockExclusive(PSRWLOCK SRWLock);

/* include code under test */
#include "../../src/umock_lock_factory_windows.c"
