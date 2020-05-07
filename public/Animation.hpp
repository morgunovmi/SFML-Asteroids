#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

class Animation {
private:
    float mFrame, mSpeed;
    Sprite mSprite;
    std::vector<IntRect> mFrames;

public:
    Animation() {}
    Animation(const Texture& t, const int x, const int y, const int width, const int height, const int count, const float speed);

    const Sprite getSprite() const { return mSprite; }

    void update();
    bool isEnd();
};
