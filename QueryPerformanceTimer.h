//
// Created by Alex Seres on 2022. 11. 11..
//

#ifndef MINE_QUERYPERFORMANCETIMER_H
#define MINE_QUERYPERFORMANCETIMER_H
#include <time.h>

class QueryPerformanceTimer
{
    // created private section to variable, and moved them in
    //make constructor simplier
private:
    double m_start;
    double m_stop;
public:
    QueryPerformanceTimer();
    void Start();
    double Get();
};


#endif //MINE_QUERYPERFORMANCETIMER_H
