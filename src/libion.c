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

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

#include <linux/ion.h>
#include <ion/ion.h>

int ion_open()
{
	int fd = open("/dev/ion", O_RDONLY | O_CLOEXEC);
	if (fd < 0)
		return -errno;

	return fd;
}

int ion_close(int fd)
{
	int ret = close(fd);
	if (ret < 0)
		return -errno;

	return 0;
}

static int ion_ioctl(int fd, int req, void* arg)
{
	int ret = ioctl(fd, req, arg);
	if (ret < 0)
		return -errno;

	return 0;
}

int ion_alloc(int fd, size_t len, unsigned int heap_mask, unsigned int flags, int* handle_fd)
{
	if (handle_fd == NULL)
		return -EINVAL;

	struct ion_allocation_data data = {
		.len = len,
		.heap_id_mask = heap_mask,
		.flags = flags,
	};

	int ret = ion_ioctl(fd, ION_IOC_ALLOC, &data);
	if (ret < 0)
		return ret;

	*handle_fd = data.fd;

	return 0;
}

int ion_free(int fd, int handle_fd)
{
	int ret = close(handle_fd);
	if (ret < 0)
		return -errno;

	return 0;
}

int ion_query_heap_cnt(int fd, int* cnt)
{
	struct ion_heap_query query = { 0 };

	int ret = ion_ioctl(fd, ION_IOC_HEAP_QUERY, &query);
	if (ret < 0)
		return ret;

	*cnt = query.cnt;

	return 0;
}

int ion_query_get_heaps(int fd, int cnt, void* buffers)
{
	struct ion_heap_query query = {
		.cnt = cnt,
		.heaps = (uintptr_t) buffers,
	};

	int ret = ion_ioctl(fd, ION_IOC_HEAP_QUERY, &query);
	if (ret < 0)
		return ret;

	return 0;
}
