
#include "QueryPerformanceTimer.h"

void QueryPerformanceTimer::Start() {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    m_start = now.tv_sec + now.tv_nsec/1000000000.0;
}

double QueryPerformanceTimer::Get() {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    m_stop = now.tv_sec + now.tv_nsec/1000000000.0;
    double time = m_stop - m_start;
    m_start = m_stop;
    // time value is in micro seconds
    return time;
}