#pragma once
#include "Entity.hpp"

class Player : public Entity {
public:
    bool mThrust;
    int mNumLives = 5;

public:
    Player(float width, float height);

    void update();
};
