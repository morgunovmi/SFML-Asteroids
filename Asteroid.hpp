#pragma once
#include <random>
#include "Entity.hpp"

class Asteroid : public Entity {
private:
    std::uniform_int_distribution<> mSpeedDistribution{ -4, 4 };

public:
    Asteroid(std::default_random_engine& dre, float width, float height);
    void update();
};

