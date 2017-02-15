/*
 * Copyright (c) 2013, German Aerospace Center (DLR)
 *
 * This file is part of outpost 0.6.
 *
 * It is distributed under the terms of the GNU General Public License with a
 * linking exception. See the file "LICENSE" for the full license governing
 * this code.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 */
// ----------------------------------------------------------------------------

#ifndef COBC_RTOS_POSIX_TIMER_H
#define COBC_RTOS_POSIX_TIMER_H

#include <signal.h>
#include <time.h>

#include <outpost/time/duration.h>

#include <outpost/utils/callable.h>

namespace outpost
{
namespace rtos
{

/**
 * Software timer.
 *
 * \author    Fabian Greif
 * \ingroup    rtos
 */
class Timer
{
public:
    /**
     * Type of the timer handler function.
     *
     * \param timer
     *         Timer which caused the function to be called. Can be used
     *         to restart the timer.
     */
    typedef void (Callable::*Function)(Timer* timer);

    template <typename T>
    struct TimerFunction
    {
        typedef void (T::*type)(Timer* timer);
    };

    /**
     * Create a timer.
     *
     * \param object
     *         Instance to with the function to be called belongs. Must
     *         be sub-class of outpost::rtos::Callable.
     * \param function
     *         Member function of \p object to call when the timer
     *         expires.
     * \param name
     *         Name of the timer. Maximum length is four characters. Longer
     *         names will be truncated.
     *
     * \see    outpost::Callable
     */
    template <typename T>
    Timer(T* object,
          typename TimerFunction<T>::type function,
          const char* name = "TIM-");

    /**
     * Delete the timer.
     *
     * If the timer is running, it is automatically canceled. All it's
     * allocated resources are reclaimed and can be used for another
     * timer.
     */
    ~Timer();

    /**
     * Start the timer.
     *
     * If the timer is running it is automatically reset before being
     * initiated.
     *
     * \param duration
     *         Runtime duration.
     */
    void
    start(time::Duration duration);

    /**
     * Reset the timer interval to it's original value when it is
     * currently running.
     */
    void
    reset();

    /**
     * Abort operation.
     *
     * The timer will not fire until the next invocation of reset() or
     * start().
     */
    void
    cancel();

    /**
     * Check whether the timer is currently running.
     *
     * \retval  true    Timer is running
     * \retval  false   Timer has not been started or was stopped.
     */
    bool
    isRunning();

    /**
     * Start the timer daemon.
     *
     * Not used for the POSIX implementation.
     */
    static void
    startTimerDaemonThread(uint8_t priority,
                           size_t stack = 0);

private:
    // disable copy-constructor and assignment operator
    Timer(const Timer& other);
    Timer& operator=(const Timer& other);

    void
    createTimer(const char* name);

    /**
     * Helper function to map the void-pointer to a
     * member function pointer and call the member function.
     */
    static void
    invokeTimer(union sigval parameter);

    /// Object and member function to call when the timer expires.
    Callable* const mObject;
    Function const mFunction;

    timer_t mTid;
    itimerspec mInterval;
};

}
}

// ----------------------------------------------------------------------------
// Implementation of the template constructor
template <typename T>
outpost::rtos::Timer::Timer(T* object,
                         typename TimerFunction<T>::type function,
                         const char* name) :
    mObject(reinterpret_cast<Callable *>(object)),
    mFunction(reinterpret_cast<Function>(function)),
    mTid()
{
    this->createTimer(name);
}

#endif // COBC_RTOS_POSIX_TIMER_H