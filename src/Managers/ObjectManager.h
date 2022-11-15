#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#pragma once

#include "../Utils/Mutex.h"

class Object;

const int cMaximumNumberOfObjects = 1000000;

class ObjectManager
{
private:
    Mutex m_lock;
    int m_numberOfObjects;
    Object* m_objects[cMaximumNumberOfObjects];
    int m_nextFindTargetIndex;

public:
    ObjectManager();
    ~ObjectManager();
    static ObjectManager& GetSingleton();
    int GetNumberOfObjects() { return m_numberOfObjects; }
    Object* GetObject(int aIndex) { return m_objects[aIndex]; }
    Object* GetObjectByObjectId(int aObjectId);
    bool IsValidObject(Object* apObject);
    void RemoveObject(unsigned int aObjectId);
    void AddMineObject(unsigned int aObjectId, float aPosition[3], int aTeam);
    int GetNextFindTargetsIndex();
    void ResetNextFindTargetIndex() { m_nextFindTargetIndex = 0; }

    Object* GetObjectWithMostEnemyTargets(int aTeam);
    int GetNumberOfObjectForTeam(int aTeam);

};
// - replaced private members to be up, and public to be down
// - moved constructor from private to public


#endif // OBJECTMANAGER_H
