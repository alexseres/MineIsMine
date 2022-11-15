#ifndef MINE_SCOPEDQUERYPERFORMANCETIMER_H
#define MINE_SCOPEDQUERYPERFORMANCETIMER_H
#include "QueryPerformanceTimer.h"
#include <stdio.h>
#include <iostream>


class ScopedQueryPerformanceTimer {
private:
    const char*	m_msg;
    QueryPerformanceTimer m_timer;

public:
    void start()
    {
        m_msg = "Time taken in milliseconds:";
        m_timer.Start();
    }
    void finish()
    {
        double timeUsed = m_timer.Get();
        printf("%s %f\n", m_msg, timeUsed / 1000.0);
    }
};


#endif //MINE_SCOPEDQUERYPERFORMANCETIMER_H
