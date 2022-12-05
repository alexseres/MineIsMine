#ifndef MINE_MINEFIELD_H
#define MINE_MINEFIELD_H
#include <iostream>
#include "../Models/WorkerThread.h"
#include "../Utils/stdafx.h"
#include "ObjectManager.h"
#include "../Models/Object.h"
#include "../Models/Mine.h"
#include "../Utils/ScopedQueryPerformanceTimer.h"
#include "../Utils/QueryPerformanceTimer.h"
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <mutex>


class Minefield {
private:
    int g_numberOfTeams = 3;
    int g_numberOfMinesPerTeam = 1500;
    int numberOfTurns = 0;
    std::vector<WorkerThread> workerThreadList;
    ScopedQueryPerformanceTimer timer;
    ObjectManager objectManager;


public:
//    static int s_numberOfWorkerThreadsActive;
//    static int s_numberOfWorkerThreadsStarted;
    int s_numberOfWorkerThreadsActive;
    int s_numberOfWorkerThreadsStarted;
    static Mutex s_lock;
    static void FindTargets(void* aIgnored);
    void FindCurrentTargets(Mine* mine);
    void Find_Targets();
    void FindTargetsForAllMines(WorkerThread& wTread);
    void announceWinner();
    void workerThreadPopulating(int numberOfWorkerThreads);
    void printInformationsOfObjects();
    void addObjectsToSystem();
    void initialization(int aArgc, char* aArgv[], int& numberOfWorkerThreads, int& randomSeed);
    void runner(int numberOfWorkerThreads);
    int simulation(int aArgc, char* aArgv[]);

    void printNumberOfMinesPerTeam();
};


#endif //MINE_MINEFIELD_H
