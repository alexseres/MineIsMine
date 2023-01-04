#ifndef MINE_MINEFIELD_H
#define MINE_MINEFIELD_H
#pragma once
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
    static Mutex s_lock;
    void Find_TargetsForAllMines();
    void ConstructWorkThreads(WorkerThread& wTread);
    void announceWinner();
    void workerThreadPopulating(int numberOfWorkerThreads);
    void printInformationsOfObjects();
    void addObjectsToSystem();
    void initialization(int aArgc, char* aArgv[], int& numberOfWorkerThreads, int& randomSeed);
    void runner(int numberOfWorkerThreads);
    int simulation(int aArgc, char* aArgv[]);

    void printNumberOfMinesPerTeam();

    void IfExplodedMinesAreMoreThan2ChanceToExplodeAgain(int& explodedMineCounter, int teamNumber);
};


#endif //MINE_MINEFIELD_H
