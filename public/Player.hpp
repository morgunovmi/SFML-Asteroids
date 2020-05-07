#pragma once
#include "Entity.hpp"

class Player : public Entity {
public:
    bool mThrust;
    int mNumLives = 5;

public:
    Player(const float width, const float height);

    void update();
};
