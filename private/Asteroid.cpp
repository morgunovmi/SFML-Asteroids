#include "../public/Asteroid.hpp"

namespace ast {
    Asteroid::Asteroid(std::default_random_engine& mDre, float width, float height,
        const Animation& a, float x, float y, float angle, float radius) :
        Entity(a, x, y, angle, radius) {

        mName = ASTEROID;
        mWindowWidth = width;
        mWindowHeight = height;

        mDx = mSpeedDistribution(mDre);
        mDy = mSpeedDistribution(mDre);
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