#ifndef MINE_SCOPEDQUERYPERFORMANCETIMER_H
#define MINE_SCOPEDQUERYPERFORMANCETIMER_H
#include "QueryPerformanceTimer.h"
#include <stdio.h>


class ScopedQueryPerformanceTimer {
public:
    QueryPerformanceTimer m_timer;
    ScopedQueryPerformanceTimer(const char*	aMsg = NULL)
    {
        m_msg = aMsg;
        m_timer.Start();
    }

    ~ScopedQueryPerformanceTimer()
    {
        double timeUsed = m_timer.Get();
        printf("%s %f\n", m_msg, timeUsed / 1000.0);
    }


    const char*	m_msg;
};


#endif //MINE_SCOPEDQUERYPERFORMANCETIMER_H
