#pragma once
#include <random>
#include "Entity.hpp"

namespace ast {
    class Asteroid : public Entity {
    private:
        std::uniform_real_distribution<float> mSpeedDistribution{ -4.f, 4.f };

    public:
        Asteroid(std::default_random_engine& mDre, float width, float height,
            const Animation& a, float x, float y, float angle = 0.f, float radius = 1.f);

        void update() override;
    };
}
