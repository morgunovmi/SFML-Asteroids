#include "Asteroid.hpp"

Asteroid::Asteroid(std::default_random_engine& dre, float width, float height) {
    mName = "asteroid";
    mWindowWidth = width;
    mWindowHeight = height;

    mDx = static_cast<float>(mSpeedDistribution(dre));
    mDy = static_cast<float>(mSpeedDistribution(dre));
}

void Asteroid::update() {
    mX += mDx;
    mY += mDy;

    if (mX > mWindowWidth) mX = 0;  if (mX < 0) mX = mWindowWidth;
    if (mY > mWindowHeight) mY = 0;  if (mY < 0) mY = mWindowHeight;
}