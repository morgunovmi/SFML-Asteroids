#include "../public/Asteroid.hpp"

namespace ast {
    Asteroid::Asteroid(std::default_random_engine& mDre, const float width, const float height,
        const Animation& a, const float x, const float y, const float angle, const float radius) :
        Entity(a, x, y, angle, radius) {

        mName = ASTEROID;
        mWindowWidth = width;
        mWindowHeight = height;

        mDx = static_cast<float>(mSpeedDistribution(mDre));
        mDy = static_cast<float>(mSpeedDistribution(mDre));
    }

    void Asteroid::update() {
        Entity::update();

        mX += mDx;
        mY += mDy;

        if (mX > mWindowWidth) {
            mX = 0.f;
        }
        if (mX < 0.f) {
            mX = mWindowWidth;
        }
        if (mY > mWindowHeight) {
            mY = 0.f;
        }
        if (mY < 0.f) {
            mY = mWindowHeight;
        }
    }
}