#pragma once
#include <iostream>



class Object
{
public:
    Object() { IsDestroyed = false;}
    ~Object() {}

    int GetObjectId() { return m_objectId; }

    bool GetActive();
    void SetActive(bool aActive);
    bool IsDestroyed;

    bool GetInvulnerable();
    void SetInvulnerable(bool aInvulnerable);
    bool hasStealth = false;



    virtual float* GetPosition() { return 0; }
    virtual void SetPosition(float pos[3]) {}
    unsigned int m_objectId;
    int m_team;
    int m_directionToMove;
    int GetDirectionToMove(){return m_directionToMove;}
    void SetDirectionToMove(int value){m_directionToMove = value;}
    int m_directionLength;
    int GetDirectionLength(){return m_directionLength;}
    void SetDirectionLength(int value){m_directionLength = value;}

    int GetTeam() { return m_team; }

    enum ObjectBitFlags
    {
        OBF_ACTIVE = 0x0003,
        OBF_INVULNERABLE = 0x0001,
    };

    int m_bitFlags;
};