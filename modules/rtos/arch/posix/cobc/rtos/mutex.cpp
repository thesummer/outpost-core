/*
 * Copyright (c) 2013, German Aerospace Center (DLR)
 *
 * This file is part of libCOBC 0.3-pre.
 *
 * It is distributed under the terms of the GNU General Public License with
 * a linking exception. See the file "LICENSE" for the full license governing
 * this code.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "mutex.h"

#include <time.h>

#include "internal/time.h"

using namespace cobc::rtos;

bool
Mutex::acquire(cobc::time::Duration timeout)
{
    timespec time = toRelativeTime(timeout);
    return (pthread_mutex_timedlock(&mutex, &time) == 0);
}
