#pragma once
#include "Entity.hpp"

class Bullet : public Entity {
private:
    std::uniform_int_distribution<> mAngleDistribution{ -4, 4 };

public:
    Bullet(const std::default_random_engine& dre, const float width, const float height);
    void update();
};
