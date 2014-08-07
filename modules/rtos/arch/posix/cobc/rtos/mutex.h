/*
 * Copyright (c) 2013, German Aerospace Center (DLR)
 * All Rights Reserved.
 *
 * See the file "LICENSE" for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#ifndef COBC_RTOS_POSIX_MUTEX_HPP
#define COBC_RTOS_POSIX_MUTEX_HPP

#include <pthread.h>

#include <cobc/time/duration.h>

namespace cobc
{
namespace rtos
{

/**
 * Mutex
 *
 * \author    Fabian Greif
 */
class Mutex
{
public:
    inline
    Mutex()
    {
        pthread_mutex_init(&mutex, 0);
    }

    inline
    ~Mutex()
    {
        pthread_mutex_destroy(&mutex);
    }

    /**
     * Acquire the mutex.
     *
     * This function may block if the mutex is currently held by an
     * other thread.
     *
     * \returns    \c true if the mutex could be acquired.
     */
    inline bool
    acquire()
    {
        return (pthread_mutex_lock(&mutex) == 0);
    }

    /**
     * Acquire the mutex.
     *
     * Same as acquire() but blocks only for \p timeout milliseconds.
     *
     * \param    timeout
     *         Timeout in milliseconds.
     *
     * \return    \c true if the mutex could be acquired, \c false in
     *             case of an error or timeout.
     */
    bool
    acquire(time::Duration timeout);

    /**
     * Release the mutex.
     */
    inline void
    release()
    {
        pthread_mutex_unlock(&mutex);
    }

private:
    // disable copy constructor
    Mutex(const Mutex& other);

    // disable assignment operator
    Mutex&
    operator=(const Mutex& other);

    pthread_mutex_t mutex;
};

}
}

#include <cobc/rtos/mutex_guard.h>

#endif // COBC_RTOS_POSIX_MUTEX_HPP