#include "../public/Bullet.hpp"
#include <cmath>
#include <iostream>

namespace ast {
    Bullet::Bullet(const std::default_random_engine& mDre, const float width, const float height,
        const Animation& a, const float x, const float y, const float angle, const float radius) :
        Entity(a, x, y, angle, radius) {

        mName = BULLET;
        mWindowWidth = width;
        mWindowHeight = height;

        mRand = mDre;
    }

    void Bullet::update() {
        Entity::update();
        mDx = std::cos(mAngle * degtorad) * 6;
        mDy = std::sin(mAngle * degtorad) * 6;
        mAngle += mAngleDistribution(mRand);  
        mX += mDx;
        mY += mDy;

        if (mX > mWindowWidth || mX < 0 || mY > mWindowHeight || mY < 0) {
            mIsAlive = false;
        }
    }
}