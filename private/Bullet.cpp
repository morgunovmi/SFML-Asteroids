#include <cmath>
#include <iostream>
#include "../public/Bullet.hpp"

namespace ast {
    Bullet::Bullet(const std::default_random_engine& mDre, float width, float height,
        const Animation& a, float x, float y, float angle, float radius) :
        Entity(a, x, y, angle, radius) {

        mName = BULLET;
        mWindowWidth = width;
        mWindowHeight = height;

        mRand = mDre;
    }

    void Bullet::update() {
        Entity::update();

        mDx = std::cos(mAngle * mDegtorad) * 6;
        mDy = std::sin(mAngle * mDegtorad) * 6;
        mAngle += mAngleDistribution(mRand);  
        mX += mDx;
        mY += mDy;

        if (mX > mWindowWidth || mX < 0 || mY > mWindowHeight || mY < 0) {
            mIsAlive = false;
        }
    }
}