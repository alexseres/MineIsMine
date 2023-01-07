//
// Created by Alex Seres on 2022. 11. 11..
//

#ifndef MINE_WORKERTHREAD_H
#define MINE_WORKERTHREAD_H
#include <pthread.h>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>


class WorkerThread
{
public:
    pthread_attr_t attributes;
    void init()
    {
        pthread_attr_init(&attributes);
    }
};



#endif //MINE_WORKERTHREAD_H
