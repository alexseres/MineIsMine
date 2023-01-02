#include <stdio.h>
#include "../Utils/stdafx.h"
#include "ObjectManager.h"
#include "../Models/Object.h"
#include "../Models/Mine.h"

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

void ObjectManager::AddMineObject(unsigned int aObjectId, float aPosition[3], int aTeam)
{
    MutexLock lock(m_lock);
    //timer.start();
    for(unsigned int i = 0; i < m_numberOfObjects; i++)
    {
        if(m_objects[i]->m_objectId == aObjectId)
        {
            // If objectId matches an existing entry then just consider it as getting updated (even potentially switched to a new team)
            Mine* pMineObject = new Mine();
            pMineObject->m_objectId = m_objects[i]->m_objectId;
            pMineObject->m_team = aTeam;
            pMineObject->SetPosition(aPosition);
            pMineObject->m_bitFlags = m_objects[i]->m_bitFlags;
            pMineObject->SetActive(m_objects[i]->GetActive());
            pMineObject->SetInvulnerable(m_objects[i]->GetInvulnerable());
            pMineObject->m_destructiveRadius = static_cast<Mine*>(m_objects[i])->m_destructiveRadius;

            delete m_objects[i];
            m_objects[i] = pMineObject;
            return;
        }
    }
    //timer.finish();
    
	m_objects[m_numberOfObjects] = new Mine();
    m_objects[m_numberOfObjects]->m_objectId = aObjectId;
    m_objects[m_numberOfObjects]->m_team = aTeam;
    m_objects[m_numberOfObjects]->SetPosition(aPosition);
    static_cast<Mine*>(m_objects[m_numberOfObjects])->m_destructiveRadius = GetRandomFloat32_Range(0, 100.0f);
    GetRandomFloat32() < 0.2f ? m_objects[m_numberOfObjects]->m_bitFlags = Object::OBF_INVULNERABLE: m_objects[m_numberOfObjects]->m_bitFlags = Object::OBF_ACTIVE;
    m_objects[m_numberOfObjects]->SetActive(GetRandomFloat32() < 0.95f);
    m_objects[m_numberOfObjects]->SetInvulnerable(GetRandomFloat32() > 0.80f);
    m_numberOfObjects++;
    return;
}



void ObjectManager::RemoveObject(unsigned int aObjectId)
{

    for(unsigned int i = 0; i < m_numberOfObjects; i++)
    {
        if(m_objects[i]->m_objectId == aObjectId)
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
        if(m_objects[i]->m_objectId == aObjectId)
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
        if(m_objects[i]->m_team == aTeam)
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
        if(m_objects[i]->m_team == aTeam)
        {
            count++;
        }
    }

    return count;
}
