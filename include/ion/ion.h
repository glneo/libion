/*
 * ION Userspace Memory Allocator Library
 *
 * Copyright 2011 Google, Inc
 * Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
 *     Andrew F. Davis <afd@ti.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __ION_H
#define __ION_H

#include <sys/types.h>
#include <linux/ion.h>

#ifdef __cplusplus
extern "C" {
#endif

int ion_open();
int ion_close(int fd);
int ion_alloc(int fd, size_t len, unsigned int heap_mask, unsigned int flags, int *handle_fd);
int ion_free(int fd, int handle_fd);

int ion_query_heap_cnt(int fd, int* cnt);
int ion_query_get_heaps(int fd, int cnt, void* buffers);

#ifdef __cplusplus
}
#endif

#endif /* __ION_H */
