#include "Entity.hpp"

namespace ast {
    void Entity::draw(sf::RenderWindow& app) {
        sf::Sprite sprite = mAnimation.sprite();
        sprite.setPosition(mX, mY);
        sprite.setRotation(mAngle + 90);
        app.draw(sprite);
    }
}
