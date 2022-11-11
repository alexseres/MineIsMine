
#include "WorkerThread.h"




void WorkerThread::FindTargetsForAllMines(){
    pthread_t threadId = 0;
    pthread_attr_t attributes;
    pthread_attr_init(&attributes);
    pthread_create(&threadId, &attributes, (void*(*)(void*))FindTargets, NULL);
}

