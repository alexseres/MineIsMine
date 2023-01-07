#include <stdio.h>
#include "../Utils/stdafx.h"
#include "ObjectManager.h"
#include "../Models/Object.h"
#include "../Models/Mine.h"

enum directionToMovePossibilities{x=0,y,z};

ObjectManager::ObjectManager()
    : m_numberOfObjects(0)
    , m_nextFindTargetIndex(0)
{
}

ObjectManager::~ObjectManager()
{
    for(int i = 0;i < starterNumberOfObjects;i++){
        delete m_objects[i];
    }
}

void ObjectManager::ObjectMove(){
    // Mines now move. Add a velocity to each mine, with a random magnitude between zero and 15 units, in a random direction
    // selected at time of mine creation. All mines move at the end of a turn.

    for(unsigned int i = 0; i < m_numberOfObjects; i++)
    {
        float* oldPositions = m_objects[i]->GetPosition();
        float newPositions[3];
        for(int j = 0;j < 3;j++){
            if(j == m_objects[i]->GetDirectionToMove())
                newPositions[j] = oldPositions[j] + m_objects[i]->GetDirectionLength();
            else
                newPositions[j] = oldPositions[j];
        }
        m_objects[i]->SetPosition(newPositions);
    }
}

void ObjectManager::AddMineObject(unsigned int aObjectId, float aPosition[3], int aTeam)
{
    MutexLock lock(m_lock);
    //timer.start();
    for(unsigned int i = 0; i < m_numberOfObjects; i++)
    {
        if(m_objects[i]->GetObjectId() == aObjectId)
        {
            // If objectId matches an existing entry then just consider it as getting updated (even potentially switched to a new team)
            Mine* pMineObject = new Mine();
            pMineObject->SetObjectId(m_objects[i]->GetObjectId());
            pMineObject->SetTeam(aTeam);
            pMineObject->SetPosition(aPosition);
            pMineObject->m_bitFlags = m_objects[i]->m_bitFlags;
            pMineObject->SetActive(m_objects[i]->GetActive());
            pMineObject->SetInvulnerable(m_objects[i]->GetInvulnerable());
            pMineObject->SetDestructiveRadius(static_cast<Mine*>(m_objects[i])->GetDestructiveRadius());
            pMineObject->SetDirectionToMove(m_objects[i]->GetDirectionToMove());
            pMineObject->SetDirectionLength(m_objects[i]->GetDirectionLength());
            delete m_objects[i];
            m_objects[i] = pMineObject;
            return;
        }
    }
    //timer.finish();

	m_objects[m_numberOfObjects] = new Mine();
    m_objects[m_numberOfObjects]->SetObjectId(aObjectId);
    m_objects[m_numberOfObjects]->SetTeam(aTeam);
    m_objects[m_numberOfObjects]->SetPosition(aPosition);
    static_cast<Mine*>(m_objects[m_numberOfObjects])->SetDestructiveRadius(GetRandomFloat32_Range(0, 100.0f));
    GetRandomFloat32() < 0.2f ? m_objects[m_numberOfObjects]->m_bitFlags = Object::OBF_INVULNERABLE: m_objects[m_numberOfObjects]->m_bitFlags = Object::OBF_ACTIVE;
    m_objects[m_numberOfObjects]->SetActive(GetRandomFloat32() < 0.95f);
    m_objects[m_numberOfObjects]->SetInvulnerable(GetRandomFloat32() > 0.80f);
    m_objects[m_numberOfObjects]->SetDirectionToMove(GetRandomFloat32_Range(x,z));
    m_objects[m_numberOfObjects]->SetDirectionLength(GetRandomFloat32_Range(-15,15));
    m_numberOfObjects++;
    return;
}



void ObjectManager::RemoveObject(unsigned int aObjectId)
{

    for(unsigned int i = 0; i < m_numberOfObjects; i++)
    {
        if(m_objects[i]->GetObjectId() == aObjectId)
        {
            //delete m_objects[i];
            // Do a fast remove and replace this location with object currently at end
            m_objects[i] = m_objects[m_numberOfObjects - 1];
            m_objects[m_numberOfObjects - 1] = NULL;
            m_numberOfObjects--;
            return;
        }
    }
}

Object* ObjectManager::GetObjectByObjectId(int aObjectId)
{
    for(unsigned int i = 0; i < m_numberOfObjects; i++)
    {
        if(m_objects[i]->GetObjectId() == aObjectId)
        {
            return m_objects[i];
        }
    }
    return NULL;
}

bool ObjectManager::IsValidObject(Object* apObject)
{
    for(unsigned int i = 0; i < m_numberOfObjects; i++)
    {
        if(m_objects[i] == apObject)
        {
            return true;
        }
    }
    return false;
}

int ObjectManager::GetNextFindTargetsIndex()
{
    MutexLock lock(m_lock);
    int index = m_nextFindTargetIndex;
    m_nextFindTargetIndex++;
    return index;
}

int ObjectManager::GetObjectWithMostEnemyTargets(int aTeam)
{
    int currentObjectIndex = 0;
    for(unsigned int i = 0; i < m_numberOfObjects; i++)
    {
        if(m_objects[i]->GetTeam() == aTeam)
        {
            if(!static_cast<Mine *>(m_objects[currentObjectIndex])->GetActive())
                continue;

            if(static_cast<Mine *>(m_objects[currentObjectIndex])->targetNumber <= static_cast<Mine *>(m_objects[i])->targetNumber)
                currentObjectIndex = i;
        }
    }
    return currentObjectIndex;
}

int ObjectManager::GetNumberOfObjectForTeam(int aTeam)
{
    int count = 0;
    for(unsigned int i = 0; i < m_numberOfObjects; i++)
    {
        if(m_objects[i]->GetTeam() == aTeam)
        {
            count++;
        }
    }

    return count;
}


void ObjectManager::GiveStealthForAlliedObjects(int objectId)
{
    // There is a 1% chance that a mine will provide stealth for allied mines within 200% of its destructive radius.
    // Allied mines within the stealth radius will not be picked up in a targeting pass (similar to how invulnerable
    // mines are ignored) but can still be damaged if within the destructive radius of an exploding mine.
    if(GetRandomFloat32() > 0.01){
        return;
    }

    Mine* mine = static_cast<Mine*>(GetObjectByObjectId(objectId));
    for(int i = 0; i < GetNumberOfObjects();i++)
    {
        Object* pObject = GetObject(i);

        if(pObject->GetTeam() != mine->GetTeam())
        {
            continue;
        }

        float distance = mine->GetDistance(mine->GetPosition(), pObject->GetPosition());
        if(distance > (mine->GetDestructiveRadius() * 2))
        {
            continue;
        }

        //std::cout<< "Mine with object_id = " << std::to_string(mine->GetObjectId()) << " has added allied mine with objectId: " << pObject->m_objectId << std::endl;
        pObject->hasStealth = true;
        mine->m_alliedStealthList.push_back(pObject);
    }
}



void ObjectManager::FindCurrentTargetsForObject(int objectId)
{
    Mine* mine = static_cast<Mine*>(GetObjectByObjectId(objectId));
    if(!mine->GetActive())
    {
        return;
    }
    mine->m_targetList.clear();
    mine->targetNumber = 0;

    for(int i = 0; i < GetNumberOfObjects();i++)
    {
        Object* pObject = GetObject(i);

        if(pObject->GetObjectId()== mine->GetObjectId())
        {
            continue;
        }

        if(pObject->GetInvulnerable())
            continue;

        float distance = mine->GetDistance(mine->GetPosition(), pObject->GetPosition());
        if(distance > mine->GetDestructiveRadius())
        {
            continue;
        }
        if(pObject->hasStealth){
            continue;
        }

        mine->m_targetList.push_back(pObject);
        mine->targetNumber++;
    }


}
