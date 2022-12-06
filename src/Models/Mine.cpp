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


void Mine::Explode(ObjectManager& objectManager, std::string text)
{
    m_health = 0;
    IsDestroyed = true;

    if(targetNumber > 0){

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
