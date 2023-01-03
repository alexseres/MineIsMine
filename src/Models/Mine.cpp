#include "../Utils/stdafx.h"

//#ifdef __linux
//#include <math.h>
//#endif
#include "Mine.h"
#include <math.h>


Mine::Mine()
{
    m_team = 0;
    m_destructiveRadius = 0.0f; 
    m_health = 100.0f;
    m_explosiveYield = 500;

}

Mine::~Mine()
{
}

void Mine::SetPosition(float aPosition[3])
{
    for(int i = 0; i < 3; i++)
         m_position[i] = aPosition[i];
}

float Mine::GetDistance(float aPositionA[3], float aPositionB[3])
{
    float distance = 0.0f;
    for(int i = 0; i < 3; i++)
    {
        float exp_value =  pow((aPositionA[i] - aPositionB[i]), 2);
        distance += exp_value;
    }

    return sqrt(distance);
}


// There is a 10% chance that when a mine explodes it will misfire and its destructive radius is cut by 50%. There
// is an additional 5% chance that it will do the opposite and its destructive radius is now 150% the original value.
bool Mine::MisFired()
{
    if(targetNumber == 0) return false;
    bool misFiredWhichReduceRadius = GetRandomUInt32() < 0.10f;
    bool misFireWhhichIncreaseRadius = GetRandomUInt32() < 0.05f;
    if(!misFiredWhichReduceRadius && !misFireWhhichIncreaseRadius)
        return false;

    misFireWhhichIncreaseRadius ? m_destructiveRadius = m_destructiveRadius * 1.5 : m_destructiveRadius = m_destructiveRadius *  0.5;
    std::vector<Object *> new_targetList;

    for(unsigned int i = 0; i < m_targetList.size(); ++i)
    {
        float distance = GetDistance(GetPosition(), m_targetList[i]->GetPosition());
        if(distance > m_destructiveRadius)
        {
            new_targetList.push_back(m_targetList[i]);
        }
        m_targetList = std::move(new_targetList);
    }
    return true;
}

void Mine::Explode(ObjectManager& objectManager, std::string text)
{
    m_health = 0;
    IsDestroyed = true;

    bool misFired = MisFired();
    if(targetNumber > 0)
    {

        for(unsigned int i = 0; i < m_targetList.size(); ++i)
        {
            if(!m_targetList[i]->IsDestroyed){
                Mine* mine = static_cast<Mine*>(m_targetList[i]);

                if(mine->GetInvulnerable())
                    continue;


                float distance = GetDistance(GetPosition(), m_targetList[i]->GetPosition());
                // damage is inverse-squared of distance
                float factor = 1.0f - (distance / m_destructiveRadius);
                float damage = (factor * factor) * m_explosiveYield;

                mine->TakeDamage(damage);
                if(mine->m_health <= 0){
                    std::string text;
                    text += "Mine with object_id = ";
                    text += std::to_string(mine->GetObjectId());
                    text += " exploded by reaction";
                    mine->Explode(objectManager, text);
                }
                else{
                    std::cout<< "Mine with object_id = " << std::to_string(mine->GetObjectId()) << "damaged, but not destroyed, current health: " << std::to_string(mine->m_health) << std::endl;
                }
            }
        }
    }

    std::cout << text << std::endl;
    objectManager.RemoveObject(GetObjectId());
}


void Mine::TakeDamage(float aDamage)
{
    m_health -= aDamage;
}
