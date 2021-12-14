#pragma once
#include "Entity.hpp"

namespace ast {
    class Bullet final : public Entity {
    private:
        const float mDegtorad = 0.017453f;
        std::uniform_real_distribution<float> mAngleDistribution{ -2.f, 2.f };

    public:
        Bullet(const std::default_random_engine& mDre, float width, float height,
            const Animation& a, float x, float y, float angle = 0.f, float radius = 1.f);

        void update() override;
    };
}
