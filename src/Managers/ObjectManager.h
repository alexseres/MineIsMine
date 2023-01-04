#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#pragma once
#include <iostream>
#include "../Utils/Mutex.h"
#include "../Utils/ScopedQueryPerformanceTimer.h"
#include "../Models/Object.h"

const int cMaximumNumberOfObjects = 1000000;

class ObjectManager
{
private:
    int starterNumberOfObjects;
    Mutex m_lock;
    int m_numberOfObjects;
    Object* m_objects[cMaximumNumberOfObjects];
    int m_nextFindTargetIndex;
    ScopedQueryPerformanceTimer timer;

public:
    ObjectManager();
    ~ObjectManager();
    void SetStarterNumberOfObjects(){starterNumberOfObjects = m_numberOfObjects;}
    int GetNumberOfObjects() { return m_numberOfObjects; }
    int Get_m_numberOfobjects(){return m_numberOfObjects;}
    Object* GetObject(int aIndex) { return m_objects[aIndex]; }
    Object* GetObjectByObjectId(int aObjectId);
    bool IsValidObject(Object* apObject);
    void RemoveObject(unsigned int aObjectId);
    void AddMineObject(unsigned int aObjectId, float aPosition[3], int aTeam);
    int GetNextFindTargetsIndex();
    void ResetNextFindTargetIndex() { m_nextFindTargetIndex = 0; }

    int GetObjectWithMostEnemyTargets(int aTeam);
    int GetNumberOfObjectForTeam(int aTeam);
    int GetNumberofObjectsDestroyed(){return starterNumberOfObjects - m_numberOfObjects;}
    void FindCurrentTargetsForObject(int index);

    void GiveStealthForAlliedObjects(int objectId);
};
// - replaced private members to be up, and public to be down
// - moved constructor from private to public


#endif // OBJECTMANAGER_H
