#pragma once
#include <random>
#include <SFML/Graphics.hpp>
#include "Animation.hpp"

namespace ast {
    enum eName { ASTEROID, PLAYER, BULLET, EXPLOSION };
    class Entity {
    protected:
        float mX, mY, mDx, mDy, mR, mAngle, mWindowWidth, mWindowHeight;
        bool mIsAlive;
        eName mName;
        Animation mAnimation;
        std::default_random_engine mRand;

    public:
        Entity(const Animation& a, float x, float y,
                float angle = 0.f, float radius = 1.f)
            : mX(x), mY(y), mDx(), mDy(), mR(radius), mAngle(angle),
            mWindowWidth(), mWindowHeight(), 
            mIsAlive(true), mName(ASTEROID), mAnimation(a), mRand() {}

        float x() const { return mX; }
        float y() const { return mY; }
        float radius() const { return mR; }
        float angle() const { return mAngle; }
        bool isAlive() const { return mIsAlive; }
        eName name() const { return mName; }
        const Animation animation() const { return mAnimation; }

        void setAngle(const float angle) { mAngle = angle; }
        void setAlive(const bool alive) { mIsAlive = alive; }
        void setName(const eName name) { mName = name; }
        void setAnimation(const Animation& a) { mAnimation = a; }

        virtual void update() { mAnimation.update(); };
        void draw(sf::RenderWindow& app);

        virtual ~Entity() = default;
    };
}
