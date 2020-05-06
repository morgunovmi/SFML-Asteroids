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
    Animation(Texture& t, int x, int y, int width, int height, int count, float speed);

    Sprite getSprite() { return mSprite; }

    void update();
    bool isEnd();
};
