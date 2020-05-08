#pragma once
#include <SFML/Graphics.hpp>
#include <random>
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

        Entity(const Animation& a, const float x, const float y, const float angle = 0.f, const float radius = 1.f)
            : mX(x), mY(y), mAngle(angle), mR(radius), mIsAlive(true), mAnimation(a) {}

        const float x() const { return mX; }
        const float y() const { return mY; }
        const float radius() const { return mR; }
        const float angle() const { return mAngle; }
        const bool isAlive() const { return mIsAlive; }
        const eName name() const { return mName; }
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
