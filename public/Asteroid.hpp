#pragma once
#include <random>
#include "Entity.hpp"

namespace ast {
    class Asteroid : public Entity {
    private:
        std::uniform_real_distribution<float> mSpeedDistribution{ -4.f, 4.f };

    public:
        Asteroid(std::default_random_engine& mDre, const float width, const float height,
            const Animation& a, float x, float y, const float angle = 0.f, const float radius = 1.f);
        void update() override;
    };
}
