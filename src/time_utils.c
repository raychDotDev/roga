#include "time_utils.h"
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif

f32 Time_getElapsedSeconds() {
#ifdef _WIN32
    static LARGE_INTEGER freq = {0};
    static LARGE_INTEGER start = {0};

    if (freq.QuadPart == 0) {
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&start);
    }

    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return (float)(now.QuadPart - start.QuadPart) / (float)freq.QuadPart;
#else
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
        perror("clock_gettime failed");
        return -1.0f;
    }
    return (float)ts.tv_sec + (float)ts.tv_nsec / 1e9f;
#endif
}
