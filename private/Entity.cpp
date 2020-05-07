#include "../public/Entity.hpp"

void Entity::settings(const Animation& a, const float x, const float y, const float angle, const float radius) {
    mAnimation = a;
    mX = x;
    mY = y;
    mAngle = angle;
    mR = radius;
}

void Entity::draw(RenderWindow& app) {
    Sprite sprite = mAnimation.getSprite();
    sprite.setPosition(mX, mY);
    sprite.setRotation(mAngle + 90);
    app.draw(sprite);

    CircleShape circle(mR);
    circle.setFillColor(Color(255, 0, 0, 170));
    circle.setPosition(mX, mY);
    circle.setOrigin(mR, mR);
    //app.draw(circle);
}