#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace ast {
    class Animation {
    private:
        float mFrame, mSpeed;
        sf::Sprite mSprite;
        std::vector<sf::IntRect> mFrames;

    public:
        Animation(const sf::Texture& t, const int x, const int y, const int width, const int height, const int count, const float speed);

        const sf::Sprite sprite() const { return mSprite; }

        void update();
        const bool isEnd() const;
    };
}
