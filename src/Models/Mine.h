#pragma once

#include <iostream>
#include <list>
#include "Object.h"
#include "../Utils/Random.h"
#include <vector>
#include "../Managers/ObjectManager.h"



class Mine : public Object
{
// put m_... fields into private
public:
    Mine();
    ~Mine();
    ScopedQueryPerformanceTimer timer;

    float* GetPosition() { return m_position; }
    void SetPosition(float aPosition[3]);

    float GetDistance(float aPositionA[3], float aPositionB[3]);
    int GetNumberOfEnemyTargets();

    void Explode(ObjectManager& objectManager, std::string text);
    int targetNumber = 0;
    void TakeDamage(float aDamage);

    float m_position[3];
    float m_destructiveRadius;
    float m_health;
    float m_explosiveYield;

    std::vector<Object*> m_targetList;
    std::vector<Object*> m_alliedStealthList;
    bool MisFired(ObjectManager& objectManager);

};
