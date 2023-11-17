// Utilities for the program
// @license MIT
// @author Lexi Charron

#include <time.h>
#include <errno.h>

// Use the POSIX nanosleep() to allow for milisecond sleep
int msleep(long msec)
{
    struct timespec ts;
    int res;

    // Make sure the number is not negative
    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    // Convert seconds to miliseconds
    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    // Pass it off to nanosleep()
    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}