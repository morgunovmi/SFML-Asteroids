#pragma once
#include "Entity.hpp"

namespace ast {
    class Player : public Entity {
    private:
        bool mThrust = false;
        size_t mNumLives = 5;
        const float mAcceleration = 0.17f;
        const float mMaxSpeed = 12.f;
        const float mDrag = 0.99f;
        const float mDegtorad = 0.017453f; 

    public:
        Player(float width, float height, 
            const Animation& a, float x, float y, float angle = 0.f, float radius = 1.f);

        const bool thrust() const { return mThrust; }
        void setThrust(const bool thrust) { mThrust = thrust; }
        
        const size_t lives() const { return mNumLives; }
        void setLives(const size_t lives) { mNumLives = lives; }

        void reset(const Animation& a, float x, float y, float angle);

        void update() override;
    };
}
