#pragma once
#include "Entity.hpp"

class Bullet : public Entity {
private:
    std::uniform_int_distribution<> mAngleDistribution{ -4, 4 };

public:
    Bullet(std::default_random_engine& dre, float width, float height);
    void update();
};
