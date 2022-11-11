//
// ZOS Software Engineer Applicant Test 2.3.0
//
// Submitted by: 
//
// Date:
//
// Time taken:
//
// Notes:
//
//
//
// 
//


#include "stdafx.h"
#include "ObjectManager.h"
#include "Object.h"
#include "Mine.h"
#include "ScopedQueryPerformanceTimer.h"
#include "Minefield.h"
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>


static int s_numberOfWorkerThreadsActive = 0;
static int s_numberOfWorkerThreadsStarted = 0;
static Mutex s_lock;




void Minefield::FindTargets(void* aIgnored)
{
    {
        MutexLock lock(s_lock);
        s_numberOfWorkerThreadsActive++;
        s_numberOfWorkerThreadsStarted++;
    }
    bool done = false;
    while(!done)
    {
        int index = ObjectManager::GetSingleton().GetNextFindTargetsIndex();
        if(index < ObjectManager::GetSingleton().GetNumberOfObjects())
        {
            Mine* pMineObject = static_cast<Mine*>(ObjectManager::GetSingleton().GetObject(index));
            pMineObject->FindCurrentTargets();
        }
        else
        {
            done = true;
        }
    }
    {
        MutexLock lock(s_lock);
        s_numberOfWorkerThreadsActive--;
    }
}



//class WorkerThread
//{
//public:
//    WorkerThread();
//    ~WorkerThread();
//    pthread_t threadId = 0;
//    pthread_attr_t attributes;
////    void FindTargets(void* aIgnored);
////    void FindTargetsForAllMines()
////    {
////        pthread_t threadId = 0;
////        pthread_attr_t attributes;
////        pthread_attr_init(&attributes);
////        pthread_create(&threadId, &attributes, (void*(*)(void*))FindTargets, NULL);
////    }
//
//    void init()
//    {
//        pthread_attr_init(&attributes);
//    }
//};

void Minefield::FindTargetsForAllMines(WorkerThread wTread)
{
    wTread.init();
    pthread_create(&wTread.threadId, &wTread.attributes, (void*(*)(void*))FindTargets, NULL);
}



void Minefield::announceWinner(){
    int winningTeam = 0;
    int winningObjectCount = 0;
    for(int i = 0; i < g_numberOfTeams; i++)
    {
        printf("Team %d has %d mines remaining\n", i, ObjectManager::GetSingleton().GetNumberOfObjectForTeam(i));

        if(ObjectManager::GetSingleton().GetNumberOfObjectForTeam(i) > winningObjectCount)
        {
            winningObjectCount = ObjectManager::GetSingleton().GetNumberOfObjectForTeam(i);
            winningTeam = i;
        }
    }

    printf("Team %d WINS after %d turns!!\n", winningTeam, numberOfTurns);
}

void Minefield::runner(std::vector<WorkerThread*> &workerThreadList, int numberOfWorkerThreads){
    bool targetsStillFound = true;
    while(targetsStillFound)
    {
        numberOfTurns++;
        targetsStillFound = false;
        ObjectManager::GetSingleton().ResetNextFindTargetIndex();
        s_numberOfWorkerThreadsStarted = 0;

        for(int i = 0; i < numberOfWorkerThreads; i++)
        {
            workerThreadList[i]->FindTargetsForAllMines();
        }

        do
        {
            // sleep until all worker threads have finished doing their thing
            usleep(1000);
        } while(s_numberOfWorkerThreadsActive > 0 || s_numberOfWorkerThreadsStarted == 0);

        for(int i = 0; i < g_numberOfTeams; i++)
        {
            Mine* pMine = static_cast<Mine*>(ObjectManager::GetSingleton().GetObjectWithMostEnemyTargets(i));
            if(pMine->GetNumberOfEnemyTargets() > 0)
            {
                targetsStillFound = true;
            }
            if(numberOfTurns < 5)
            {
                printf("Turn %d: Team %d picks Mine with object id %d (with %d targets) to explode\n", numberOfTurns, i,
                       pMine->GetObjectId(), pMine->GetNumberOfEnemyTargets());
            }
            pMine->Explode();
        }
    }
}

std::vector<WorkerThread *> Minefield::workerThreadPopulating(int numberOfWorkerThreads){
    std::vector<WorkerThread*> workerThreadList;
    for(int i = 0; i < numberOfWorkerThreads; i++)
    {
        workerThreadList.push_back(new WorkerThread());
    }
    return workerThreadList;
}

void Minefield::printInformationsOfObjects(){
    for(int i = 0; i < 10; i++)
    {
        Object* pObject = ObjectManager::GetSingleton().GetObject(i);
        if(pObject)
        {
            float* pPosition = pObject->GetPosition();
            printf("Object id %d position (%0.3f, %0.3f, %0.3f) active %s invulnerable %s\n", pObject->GetObjectId(),
                   pPosition[0], pPosition[1], pPosition[2], pObject->GetActive() ? "Y" : "N", pObject->GetInvulnerable() ? "Y" : "N");
        }
    }
    printf("Number of objects in system %u\n", ObjectManager::GetSingleton().GetNumberOfObjects());

}

void Minefield::addObjectsToSystem(){
    // Let's add lots of mine objects to the system before starting things up
    for(int i = 0; i < g_numberOfTeams; i++)
    {
        for(int j = 0; j < g_numberOfMinesPerTeam; j++)
        {
            float position[3];
            for(int i = 0; i < 3; i++)
                position[i] = GetRandomFloat32_Range(-1000.0f, 1000.0f);

            unsigned int objectId = GetRandomUInt32() % (g_numberOfMinesPerTeam * 10);
            ObjectManager::GetSingleton().AddMineObject(objectId, position, i);
        }
    }
}

void Minefield::initialization(int aArgc, char* aArgv[], int& numberOfWorkerThreads, int& randomSeed){
    if(aArgc > 1)
    {
        randomSeed = atoi(aArgv[1]);
        SetRandomSeed(randomSeed);
    }
    if(aArgc > 2)
    {
        numberOfWorkerThreads = atoi(aArgv[2]);
    }
    if(aArgc > 3)
    {
        g_numberOfTeams = atoi(aArgv[3]);
    }
    if(aArgc > 4)
    {
        g_numberOfMinesPerTeam = atoi(aArgv[4]);
    }

    printf("Random seed: %d\n", randomSeed);
    printf("Number of worker threads: %d\n", numberOfWorkerThreads);
    printf("Number of teams: %d  \n", g_numberOfTeams);
    printf("Number of mines per team: %d\n", g_numberOfMinesPerTeam);
}

int Minefield::simulation(int aArgc, char* aArgv[])
{
    int numberOfWorkerThreads = 16;
    int randomSeed = 0;
    initialization(aArgc, aArgv, numberOfWorkerThreads, randomSeed);
    //ScopedQueryPerformanceTimer timer("Time taken in milliseconds:");
    addObjectsToSystem();
    printInformationsOfObjects();
    std::vector<WorkerThread*> workerThreadList = workerThreadPopulating(numberOfWorkerThreads);
    runner(workerThreadList, numberOfWorkerThreads);
    announceWinner();
    //usleep(-1);
    return 0;
}

// from the main body, trying to create logic groups
// announceWinner function created to prints which teams won
// runner function simulates the game, there can be mines exploded
// workerThreadPopulating function which populates workerthreads
// addObjectsToSystem function created
// initialization function which takes the command line arguments and do init few things
// removed brackets from main body, that was unnecessary
//separated WorkerThread to a separate file
