#include <thread>
#include "Minefield.h"


Mutex Minefield::s_lock;
std::vector<Mine *> allMinesThatHasTargets;

void Minefield::FindCurrentTargets(Mine* mine)
{
    if(!mine->GetActive())
    {
        return;
    }


    mine->m_targetList.clear();

    for(int i = 0; i < objectManager.GetNumberOfObjects(); ++i)
    {
        Object* pObject = objectManager.GetObject(i);
        if(pObject->GetObjectId() == mine->GetObjectId()) continue;
        float distance = mine->GetDistance(mine->GetPosition(), pObject->GetPosition());
        if(distance > mine->m_destructiveRadius)
        {
            continue;
        }
        //TODO: Any other reasons to not add this object?
        if(pObject->GetInvulnerable())
            continue;

        mine->m_targetList.push_back(pObject);
        mine->targetNumber++;
    }
    if(mine->targetNumber > 0)
        allMinesThatHasTargets.push_back(mine);
}

void Minefield::Find_Targets()
{
    MutexLock lock(s_lock);
    bool done = false;
    while(!done)
    {
        int index = objectManager.GetNextFindTargetsIndex();
        if(index < objectManager.GetNumberOfObjects())
        {
            Mine* pMineObject = static_cast<Mine*>(objectManager.GetObject(index));
            FindCurrentTargets(pMineObject);
        }
        else
        {
            done = true;
        }
    }
}

void Minefield::FindTargetsForAllMines(WorkerThread& wTread)
{
    wTread.init();
    std::thread t_object(&Minefield::Find_Targets, this);
    t_object.join();
}

void Minefield::announceWinner(){
    int winningTeam = 0;
    int winningObjectCount = 0;
    for(int i = 0; i < g_numberOfTeams; i++)
    {
        std::cout << "Team " << i << " has " << objectManager.GetNumberOfObjectForTeam(i) << " mines remaining" <<std::endl;

        if(objectManager.GetNumberOfObjectForTeam(i) > winningObjectCount)
        {
            winningObjectCount = objectManager.GetNumberOfObjectForTeam(i);
            winningTeam = i;
        }
    }

    std::cout << "Team " << winningTeam << " WINS after " <<  numberOfTurns << " turns" <<std::endl;
    std::cout << "Number of objects destroyed: " << objectManager.GetNumberofObjectsDestroyed() << std::endl;
}

void Minefield::runner(int numberOfWorkerThreads){
    bool targetsStillFound = true;
    while(targetsStillFound)
    {
        numberOfTurns++;
        targetsStillFound = false;
        objectManager.ResetNextFindTargetIndex();

        for(int i = 0; i < numberOfWorkerThreads; i++)
        {
            FindTargetsForAllMines(workerThreadList[i]);

        }

        for(int i = 0; i < g_numberOfTeams; i++)
        {
            int idWithMostEnemyTargets = objectManager.GetObjectWithMostEnemyTargets(i);
            Mine* pMine = static_cast<Mine *>(objectManager.GetObject(idWithMostEnemyTargets));
            if(pMine->targetNumber > 0)
            {
                targetsStillFound = true;
            }
            else{
                continue;
            }
            std::cout << "Turn " <<  numberOfTurns << ": Team " << i << " picks Mine with object id " << pMine->GetObjectId() << " with " << pMine->targetNumber << " targets to explode" << std::endl;

            std::string text =  "Mine with object_id = ";
            text+= std::to_string(pMine->GetObjectId());
            text += " exploded by having picked up with most target";
            pMine->Explode(objectManager, text);
        }

        if(targetsStillFound) printNumberOfMinesPerTeam();
        std::cout << "Number of objects in system: " << objectManager.Get_m_numberOfobjects() <<std::endl;
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
    objectManager.SetStarterNumberOfObjects();
    for(int i = 0; i < objectManager.GetNumberOfObjects(); i++)
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
    printNumberOfMinesPerTeam();
}

void Minefield::printNumberOfMinesPerTeam(){
    for(int i = 0;i < g_numberOfTeams;i++){
        int mines = objectManager.GetNumberOfObjectForTeam(i);
        std::cout << "Number of mines: " << mines << " for team " << i << std::endl;
    }
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

            unsigned int objectId = GetRandomUInt32() % (g_numberOfMinesPerTeam * 10000);
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

