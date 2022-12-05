#include "stdafx.h"

#include <iostream>
#include <random>

//static std::mt19937 s_mersenneTwisterRand(std::mt19937::default_seed);
std::random_device rd;
std::mt19937 gen(rd());
//static std::mt19937 s_mersenneTwisterRand(nullptr_t);

void SetRandomSeed(const unsigned int aSeed)
{
//    s_mersenneTwisterRand.seed(static_cast<std::mt19937::result_type>(aSeed));

}

unsigned int GetRandomUInt32()
{
    return gen();
}

float GetRandomFloat32()
{
    return static_cast<float>(GetRandomUInt32()) / static_cast<float>(0xFFFFFFFF);
}

float GetRandomFloat32_Range(float aMin, float aMax)
{
    unsigned int randomValue = GetRandomUInt32();
    return aMin + (static_cast<float>(randomValue) * (aMax - aMin) / 4294967295.0f);
}
