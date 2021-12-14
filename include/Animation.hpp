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
        Animation(const sf::Texture& t, int x, int y, int width, int height, int count, float speed);

        const sf::Sprite sprite() const { return mSprite; }

        void update();
        bool isEnd() const;
    };
}
