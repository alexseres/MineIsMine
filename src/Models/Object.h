#pragma once
#include <iostream>



class Object
{
private:
    int m_directionToMove;
    int m_directionLength;
    int m_team;
    unsigned int m_objectId;

public:
    Object() { IsDestroyed = false;}
    ~Object() {}

    int GetObjectId() { return m_objectId; }
    void SetObjectId(int value){m_objectId = value;}

    bool GetActive();
    void SetActive(bool aActive);
    bool IsDestroyed;

    bool GetInvulnerable();
    void SetInvulnerable(bool aInvulnerable);
    bool hasStealth = false;

    void SetTeam(int team){m_team = team;}
    int GetTeam(){return m_team;}




    virtual float* GetPosition() { return 0; }
    virtual void SetPosition(float pos[3]) {}

    int GetDirectionToMove(){return m_directionToMove;}
    void SetDirectionToMove(int value){m_directionToMove = value;}
    int GetDirectionLength(){return m_directionLength;}
    void SetDirectionLength(int value){m_directionLength = value;}


    enum ObjectBitFlags
    {
        OBF_ACTIVE = 0x0003,
        OBF_INVULNERABLE = 0x0001,
    };

    int m_bitFlags;
};