#include "../public/Animation.hpp"

namespace ast {
    Animation::Animation(
        const sf::Texture& t, int x, int y, int width, int height, int count, float speed) :
        mFrame(0), mSpeed(speed) {

        for (int i = 0; i < count; i++) {
            mFrames.push_back(sf::IntRect(x + i * width, y, width, height));
        }

        mSprite.setTexture(t);
        mSprite.setOrigin(width / 2.f, height / 2.f);
        mSprite.setTextureRect(mFrames[0]);
    }

    void Animation::update() {
        mFrame += mSpeed;
        auto n = mFrames.size();
        if (mFrame >= n) {
            mFrame -= n;
        }
        if (n > 0) {
            mSprite.setTextureRect(mFrames[static_cast<int>(mFrame)]);
        }
    }

    const bool Animation::isEnd() const {
        return mFrame + mSpeed >= mFrames.size();
    }
}