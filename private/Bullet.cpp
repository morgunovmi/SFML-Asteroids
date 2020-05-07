#include "../public/Bullet.hpp"
#include <iostream>

Bullet::Bullet(const std::default_random_engine& dre, const float width, const float height) {
    mName = "bullet";
    mWindowWidth = width;
    mWindowHeight = height;

    mRand = dre;
}

void Bullet::update() {
    float degtorad = 0.017453f;
    mDx = cos(mAngle * degtorad) * 6;
    mDy = sin(mAngle * degtorad) * 6;
    mAngle += mAngleDistribution(mRand);  /*try this*/
    mX += mDx;
    mY += mDy;

    if (mX > mWindowWidth || mX < 0 || mY > mWindowHeight || mY < 0) mIsAlive = false;
}