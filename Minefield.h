#ifndef MINE_MINEFIELD_H
#define MINE_MINEFIELD_H
#include <iostream>
#include "WorkerThread.h"

class Minefield {
private:
    int g_numberOfTeams = 3;
    int g_numberOfMinesPerTeam = 1500;
    int numberOfTurns = 0;

public:
    void FindTargets(void* aIgnored);
    void FindTargetsForAllMines(WorkerThread wTread);
    void announceWinner();
    std::vector<WorkerThread *> workerThreadPopulating(int numberOfWorkerThreads);
    void printInformationsOfObjects();
    void addObjectsToSystem();
    void initialization(int aArgc, char* aArgv[], int& numberOfWorkerThreads, int& randomSeed);
    void runner(std::vector<WorkerThread*> &workerThreadList, int numberOfWorkerThreads);
    int simulation(int aArgc, char* aArgv[]);
};

#endif //MINE_MINEFIELD_H
