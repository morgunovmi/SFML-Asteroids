#include "../public/Player.hpp"

Player::Player(const float width, const float height) {
    mName = "player";
    mWindowWidth = width;
    mWindowHeight = height;
    mDx = 0;
    mDy = 0;
}

void Player::update() {
    if (mThrust) {
        float degtorad = 0.017453f;
        mDx += cos(mAngle * degtorad) * 0.17f;
        mDy += sin(mAngle * degtorad) * 0.17f;
    } else {
        mDx *= 0.99f;
        mDy *= 0.99f;
    }

    float maxSpeed = 12.f;
    float speed = sqrt(mDx * mDx + mDy * mDy);
    if (speed > maxSpeed) {
        mDx *= maxSpeed / speed;
        mDy *= maxSpeed / speed;
    }

    mX += mDx;
    mY += mDy;

    if (mX > mWindowWidth) mX = 0; if (mX < 0) mX = mWindowWidth;
    if (mY > mWindowHeight) mY = 0; if (mY < 0) mY = mWindowHeight;
}