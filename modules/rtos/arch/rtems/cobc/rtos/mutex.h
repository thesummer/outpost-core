/*
 * Copyright (c) 2013, German Aerospace Center (DLR)
 * All Rights Reserved.
 *
 * See the file "LICENSE" for the full license governing this code.
 */

#ifndef COBC_RTOS_RTEMS_MUTEX_HPP
#define COBC_RTOS_RTEMS_MUTEX_HPP

#include <rtems.h>
#include <cobc/time/duration.h>

namespace cobc
{
    namespace rtos
    {
        /**
         * Mutex class.
         *
         * Mutexes can be used to enforce mutual exclusion for a critical
         * section in user code.
         *
         * Implemented using RTEMS binary semaphores with priority pool locking
         * and priority inheritance.
         *
         * \author    Fabian Greif
         * \ingroup    rtos
         */
        class Mutex
        {
        public:
            /**
             * Create a new Mutex.
             *
             * The mutex is released after creation.
             *
             * RTEMS has only one pool for mutexes and semaphores. Make sure
             * the maximum number of allocated mutexes and semaphores combined
             * is smaller than the number given via \c CONFIGURE_MAXIMUM_SEMAPHORES.
             */
            Mutex();

            /**
             * Destroy the mutex and free it's resources.
             *
             * The resources are added back to the resource pool created by
             * CONFIGURE_MAXIMUM_SEMAPHORES.
             */
            ~Mutex();

            /**
             * Acquire the mutex.
             *
             * This function may block if the mutex is currently held by an
             * other thread.
             *
             * \returns    \c true if the mutex could be acquired.
             */
            bool
            acquire();

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
             *
             * This function will never block.
             */
            inline void
            release()
            {
                rtems_semaphore_release(id);
            }

        private:
            // disable copy constructor
            Mutex(const Mutex& other);

            // disable assignment operator
            Mutex&
            operator=(const Mutex& other);

            rtems_id id;
        };
    }
}

#endif // COBC_RTOS_RTEMS_MUTEX_HPP