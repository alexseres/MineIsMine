#pragma once

#include <iostream>
#include <list>
#include "Object.h"
#include "../Utils/Random.h"
#include <vector>
#include "../Managers/ObjectManager.h"



class Mine : public Object
{
private:
    float m_position[3];
    float m_destructiveRadius;
    float m_health;
    float m_explosiveYield;
// put m_... fields into private
public:
    Mine();
    ~Mine();
    ScopedQueryPerformanceTimer timer;
    float GetDestructiveRadius(){return m_destructiveRadius;}
    void SetDestructiveRadius(float value){m_destructiveRadius = value;}
    float GetHealth(){return m_health;}
    void SetHealth(float value){m_health = value;}
    float GetExplosiveYield(){return m_explosiveYield;}
    void SetExplosiveYield(float value){m_explosiveYield=value;}

    float* GetPosition() { return m_position; }
    void SetPosition(float aPosition[3]);

    float GetDistance(float aPositionA[3], float aPositionB[3]);
    int GetNumberOfEnemyTargets();

    void Explode(ObjectManager& objectManager, std::string text, int& explodedMineCounter);
    void Explode(ObjectManager& objectManager, std::string text);
    int targetNumber = 0;
    void TakeDamage(float aDamage);



    std::vector<Object*> m_targetList;
    std::vector<Object*> m_alliedStealthList;
    bool MisFired(ObjectManager& objectManager);

};
