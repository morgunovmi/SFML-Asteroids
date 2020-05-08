#include "../public/Player.hpp"
#include <cmath>

namespace ast {
    Player::Player(const float width, const float height,
        const Animation& a, const float x, const float y, const float angle, const float radius) :
        Entity(a, x, y, angle, radius) {

        mName = PLAYER;
        mWindowWidth = width;
        mWindowHeight = height;
        mDx = 0;
        mDy = 0;
    }

    void Player::reset(const Animation& a, const float x, const float y, const float angle, const float radius) {
        mAnimation = a;
        mX = x;
        mY = y;
        mAngle = angle;
        mR = radius;
        mDx = 0;
        mDy = 0;
    }

    void Player::update() {
        Entity::update();

        if (mThrust) {
            mDx += std::cos(mAngle * degtorad) * mAcceleration;
            mDy += std::sin(mAngle * degtorad) * mAcceleration;
        } else {
            mDx *= mDrag;
            mDy *= mDrag;
        }

        float speed = std::sqrt(mDx * mDx + mDy * mDy);
        if (speed > mMaxSpeed) {
            mDx *= mMaxSpeed / speed;
            mDy *= mMaxSpeed / speed;
        }

        mX += mDx;
        mY += mDy;

        if (mX > mWindowWidth) {
            mX = 0;
        }
        if (mX < 0) {
            mX = mWindowWidth;
        }
        if (mY > mWindowHeight) {
            mY = 0;
        }
        if (mY < 0) {
            mY = mWindowHeight;
        }
    }
}