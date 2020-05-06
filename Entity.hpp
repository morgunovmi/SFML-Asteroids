#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <random>
#include "Animation.hpp"

using namespace sf;

class Entity {
public:
    float mX, mY, mDx, mDy, mR, mAngle, mWindowWidth, mWindowHeight;
    bool mIsAlive;
    std::string mName;
    Animation mAnimation;
    std::default_random_engine mRand;

    Entity() : mIsAlive(true) {}

    void settings(Animation& a, float x, float y, float angle = 0, float radius = 1.f);
    
    virtual void update() {};

    void draw(RenderWindow& app);

    virtual ~Entity() {};
};
