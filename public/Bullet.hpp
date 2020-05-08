#pragma once
#include "Entity.hpp"

namespace ast {
    class Bullet : public Entity {
    private:
        const float degtorad = 0.017453f;
        std::uniform_real_distribution<float> mAngleDistribution{ -4.f, 4.f };

    public:
        Bullet(const std::default_random_engine& mDre, const float width, const float height,
            const Animation& a, const float x, const float y, const float angle = 0.f, const float radius = 1.f);
        void update() override;
    };
}
