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
        std::cout<< "Before ObjectID is " << GetObjectId() << ", Set_Active: " << (m_bitFlags) << std::endl;
        m_bitFlags &= OBF_ACTIVE;
        std::cout<< "After ObjectID is " << GetObjectId() << ", Set_Active: " << (m_bitFlags) << std::endl;
    }
    else
    {
        std::cout<< "Before ObjectID is " << GetObjectId() << ", SetInActive: " << (m_bitFlags) << std::endl;
        m_bitFlags &= ~OBF_ACTIVE;
        std::cout<< "After ObjectID is " << GetObjectId() << ", SetInActive: " << (m_bitFlags) << std::endl;
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
        std::cout<< "After ObjectID is " << GetObjectId() << ", Set_Invulnerable: " << (m_bitFlags) << std::endl;
        m_bitFlags &= OBF_INVULNERABLE;
        std::cout<< "After ObjectID is " << GetObjectId() << ", Set_Invulnerable: " << (m_bitFlags) << std::endl;
        std::cout<< "Object id: " << GetObjectId() << ", bitflags is true: " << (m_bitFlags) << std::endl;
    }
    else
    {
        std::cout<< "Before ObjectID is " << GetObjectId() << ", SetVulnerable: " << (m_bitFlags) << std::endl;
        m_bitFlags &= ~OBF_INVULNERABLE;
        std::cout<< "AFTER ObjectID is " << GetObjectId() << ", SetVulnerable: " << (m_bitFlags) << std::endl;
    }
}
