//
// ZOS Software Engineer Applicant Test 2.3.0
//
// Submitted by: Seres Alex
//
// Date: 2022.11.11.
//
// Time taken: 12 hours
//
// Notes:
// from the main body, trying to create logic groups
// announceWinner function created to prints which teams won
// runner function simulates the game, there can be mines exploded
// workerThreadPopulating function which populates workerthreads
// addObjectsToSystem function created
// initialization function which takes the command line arguments and do init few things
// removed brackets from main body, that was unnecessary
// separated WorkerThread to a separate file
//
//
//
// 
//
#include <thread>
#include "Minefield.h"


//int Minefield::s_numberOfWorkerThreadsStarted;
//int Minefield::s_numberOfWorkerThreadsActive;
Mutex Minefield::s_lock;


//void Minefield::FindTargets(void* aIgnored)
//{
//
//    {
//        MutexLock lock(s_lock);
//        s_numberOfWorkerThreadsActive++;
//        s_numberOfWorkerThreadsStarted++;
//    }
//    bool done = false;
//    int checker= 0;
//    while(!done)
//    {
//        int index = ObjectManager::GetSingleton().GetNextFindTargetsIndex();
//        if(index < ObjectManager::GetSingleton().GetNumberOfObjects())
//        {
//            Mine* pMineObject = static_cast<Mine*>(ObjectManager::GetSingleton().GetObject(index));
//            pMineObject->FindCurrentTargets();
//        }
//        else
//        {
//            done = true;
//        }
//    }
//    {
//        MutexLock lock(s_lock);
//        s_numberOfWorkerThreadsActive--;
//    }
//}

void Minefield::Find_Targets()
{

    {
        //MutexLock lock(s_lock);
        s_numberOfWorkerThreadsActive++;
        s_numberOfWorkerThreadsStarted++;
    }
    bool done = false;
    int checker= 0;
    while(!done)
    {
        checker++;
        int index = objectManager.GetNextFindTargetsIndex();
        if(index < objectManager.GetNumberOfObjects())
        {
            Mine* pMineObject = static_cast<Mine*>(objectManager.GetObject(index));
            pMineObject->FindCurrentTargets();
        }
        else
        {
            done = true;
        }
    }
    {
        //MutexLock lock(s_lock);
        s_numberOfWorkerThreadsActive--;
    }
}

void Minefield::FindTargetsForAllMines(WorkerThread& wTread)
{
    wTread.init();
//    pthread_create(&wTread.threadId, &wTread.attributes, (void*(*)(void*))FindTargets, NULL);
    std::thread t_object(&Minefield::Find_Targets, this);
    t_object.join();
}

void Minefield::announceWinner(){
    int winningTeam = 0;
    int winningObjectCount = 0;
    for(int i = 0; i < g_numberOfTeams; i++)
    {
        printf("Team %d has %d mines remaining\n", i, objectManager.GetNumberOfObjectForTeam(i));

        if(objectManager.GetNumberOfObjectForTeam(i) > winningObjectCount)
        {
            winningObjectCount = objectManager.GetNumberOfObjectForTeam(i);
            winningTeam = i;
        }
    }

    printf("Team %d WINS after %d turns!!\n", winningTeam, numberOfTurns);
}

void Minefield::runner(int numberOfWorkerThreads){
    bool targetsStillFound = true;
    while(targetsStillFound)
    {
        numberOfTurns++;
        targetsStillFound = false;
        objectManager.ResetNextFindTargetIndex();
        s_numberOfWorkerThreadsStarted = 0;

        for(int i = 0; i < numberOfWorkerThreads; i++)
        {
            FindTargetsForAllMines(workerThreadList[i]);
        }

        int checker = 0;
        do
        {
            // sleep until all worker threads have finished doing their thing
            usleep(1000);
            checker++;
        } while(s_numberOfWorkerThreadsActive > 0 || s_numberOfWorkerThreadsStarted == 0);

        for(int i = 0; i < g_numberOfTeams; i++)
        {
            Mine* pMine = static_cast<Mine*>(objectManager.GetObjectWithMostEnemyTargets(i));
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

void Minefield::workerThreadPopulating(int numberOfWorkerThreads){
    for(int i = 0; i < numberOfWorkerThreads; i++)
    {
        WorkerThread workerThread;
        workerThreadList.push_back(workerThread);
    }
}

void Minefield::printInformationsOfObjects(){
    for(int i = 0; i < 10; i++)
    {
        Object* pObject = objectManager.GetObject(i);
        if(pObject)
        {
            float* pPosition = pObject->GetPosition();
            printf("Object id %d position (%0.3f, %0.3f, %0.3f) active %s invulnerable %s\n", pObject->GetObjectId(),
                   pPosition[0], pPosition[1], pPosition[2], pObject->GetActive() ? "Y" : "N", pObject->GetInvulnerable() ? "Y" : "N");
        }
    }
    printf("Number of objects in system %u\n", objectManager.GetNumberOfObjects());

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
                //std::cout << "POSITION: " << position[i] << std::endl;

            unsigned int objectId = GetRandomUInt32() % (g_numberOfMinesPerTeam * 10);
            objectManager.AddMineObject(objectId, position, i);
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
    timer.start();
    addObjectsToSystem();
    printInformationsOfObjects();
    workerThreadPopulating(numberOfWorkerThreads);
    runner(numberOfWorkerThreads);
    announceWinner();
    timer.finish();
    return 0;
}





