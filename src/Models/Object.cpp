#include "../Utils/stdafx.h"
#include "Object.h"


bool Object::GetActive()
{
    return m_bitFlags & OBF_ACTIVE;
}

void Object::SetActive(bool aActive)
{
    if(aActive)
    {
        m_bitFlags &= OBF_ACTIVE;
        std::cout<< "ObjectID is " << GetObjectId() << ", Set_Active: " << (m_bitFlags) << std::endl;
    }
    else
    {
        m_bitFlags &= ~OBF_ACTIVE;
        std::cout<< "ObjectID is " << GetObjectId() << ", SetInActive: " << (m_bitFlags) << std::endl;
    }
}

bool Object::GetInvulnerable()
{

    return m_bitFlags & OBF_INVULNERABLE;
}

void Object::SetInvulnerable(bool aInvulnerable)
{
    if(aInvulnerable)
    {
        m_bitFlags &= OBF_INVULNERABLE;
        std::cout<< "ObjectID is " << GetObjectId() << ", Set_Invulnerable: " << (m_bitFlags) << std::endl;
    }
    else
    {
        m_bitFlags &= ~OBF_INVULNERABLE;
        std::cout<< "ObjectID is " << GetObjectId() << ", SetVulnerable: " << (m_bitFlags) << std::endl;
    }
}
