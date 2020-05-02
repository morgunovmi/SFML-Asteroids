#include <SFML/Graphics.hpp>
#include <time.h>
#include <random>
#include <memory>
#include <list>

using namespace sf;

const int W = 1200;
const int H = 800;

class Animation {
private:
    float frame, speed;
    Sprite sprite;
    std::vector<IntRect> frames;

public:
    Animation() {}

    Animation(Texture& t, int x, int y, int width, int height, int count, float Speed) {
        frame = 0;
        speed = Speed;

        for (int i = 0; i < count; i++) {
            frames.push_back(IntRect(x + i * width, y, width, height));
        }

        sprite.setTexture(t);
        sprite.setOrigin(width / 2.f, height / 2.f);
        sprite.setTextureRect(frames[0]);
    }

    Sprite getSprite() {
        return sprite;
    }

    void update() {
        frame += speed;
        int n = frames.size();
        if (frame >= n) frame -= n;
        if (n > 0) sprite.setTextureRect(frames[static_cast<int>(frame)]);
    }

    bool isEnd() {
        return frame + speed >= frames.size();
    }
};


class Entity {
public:
    float x, y, dx, dy, R, angle;
    bool isAlive;
    std::string name;
    Animation animation;

    Entity() {
        isAlive = true;
    }

    void settings(Animation& a, float X, float Y, float Angle = 0, float radius = 1.f) {
        animation = a;
        x = X;
        y = Y;
        angle = Angle;
        R = radius;
    }

    virtual void update() {};

    void draw(RenderWindow& app) {
        Sprite sprite = animation.getSprite();
        sprite.setPosition(x, y);
        sprite.setRotation(angle + 90);
        app.draw(sprite);

        CircleShape circle(R);
        circle.setFillColor(Color(255, 0, 0, 170));
        circle.setPosition(x, y);
        circle.setOrigin(R, R);
        //app.draw(circle);
    }

    virtual ~Entity() {};
};


class Asteroid : public Entity {
public:
    Asteroid() {
        name = "asteroid";

        dx = static_cast<float>(uid(dre));
        dy = static_cast<float>(uid(dre));
    }

    void update() {
        x += dx;
        y += dy;

        if (x > W) x = 0;  if (x < 0) x = W;
        if (y > H) y = 0;  if (y < 0) y = H;
    }
private:
    std::random_device rd{};
    std::default_random_engine dre{ rd() };
    std::uniform_int_distribution<> uid{ -4, 4 };

};


class Bullet : public Entity {
public:
    Bullet() {
        name = "bullet";
    }

    void update() {
        float degtorad = 0.017453f;
        dx = cos(angle * degtorad) * 6;
        dy = sin(angle * degtorad) * 6;
        angle += uid(dre);  /*try this*/
        x += dx;
        y += dy;

        if (x > W || x < 0 || y > H || y < 0) isAlive = false;
    }

private:
    std::random_device rd{};
    std::default_random_engine dre{ rd() };
    std::uniform_int_distribution<> uid{ -4, 4 };

};


class Player : public Entity {
public:
    bool thrust;

    Player() {
        name = "player";
    }

    void update() {
        if (thrust) {
            float degtorad = 0.017453f;
            dx += cos(angle * degtorad) * 0.2f;
            dy += sin(angle * degtorad) * 0.2f;
        } else {
            dx *= 0.99f;
            dy *= 0.99f;
        }

        float maxSpeed = 15.f;
        float speed = sqrt(dx * dx + dy * dy);
        if (speed > maxSpeed) {
            dx *= maxSpeed / speed;
            dy *= maxSpeed / speed;
        }

        x += dx;
        y += dy;

        if (x > W) x = 0; if (x < 0) x = W;
        if (y > H) y = 0; if (y < 0) y = H;
    }

};


bool isCollide(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) {
    return (b->x - a->x) * (b->x - a->x) +
        (b->y - a->y) * (b->y - a->y) <
        (a->R + b->R) * (a->R + b->R);
}


int main() {
    RenderWindow app(VideoMode(W, H), "Asteroids!");
    app.setFramerateLimit(60);

    Texture t1, t2, t3, t4, t5, t6, t7;
    t1.loadFromFile("images/spaceship.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/explosions/type_C.png");
    t4.loadFromFile("images/rock.png");
    t5.loadFromFile("images/fire_blue.png");
    t6.loadFromFile("images/rock_small.png");
    t7.loadFromFile("images/explosions/type_B.png");

    t1.setSmooth(true);
    t2.setSmooth(true);

    Sprite background(t2);

    Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5f);
    Animation sRock(t4, 0, 0, 64, 64, 16, 0.2f);
    Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2f);
    Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8f);
    Animation sPlayer(t1, 40, 0, 40, 40, 1, 0);
    Animation sPlayer_go(t1, 40, 40, 40, 40, 1, 0);
    Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5f);


    std::list<std::shared_ptr<Entity>> entities;


    std::random_device rd;
    std::default_random_engine dre{ rd() };
    std::uniform_real_distribution<float> w_uid{ 0, W };
    std::uniform_real_distribution<float> h_uid{ 0, H };
    std::uniform_real_distribution<float> c_uid{ 0, 360 };

    for (int i = 0; i < 15; i++) {
        auto a = std::make_shared<Asteroid>();
        a->settings(sRock, w_uid(dre), h_uid(dre), c_uid(dre), 25);
        entities.push_back(a);
    }

    auto p = std::make_shared<Player>();
    p->settings(sPlayer, 200, 200, 0, 20);
    entities.push_back(p);

    /////main loop/////
    while (app.isOpen()) {
        Event event;
        while (app.pollEvent(event)) {
            if (event.type == Event::Closed) {
                app.close();
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    app.close();
                }

                if (event.key.code == Keyboard::Space) {
                    auto b = std::make_shared<Bullet>();
                    b->settings(sBullet, p->x, p->y, p->angle, 10);
                    entities.push_back(b);
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) p->angle += 3;
        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))  p->angle -= 3;
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) p->thrust = true;
        else p->thrust = false;


        for (auto a : entities) {
            for (auto b : entities) {
                if (a->name == "asteroid" && b->name == "bullet") {
                    if (isCollide(a, b)) {
                        a->isAlive = false;
                        b->isAlive = false;

                        auto e = std::make_shared<Entity>();
                        e->settings(sExplosion, a->x, a->y);
                        e->name = "explosion";
                        entities.push_back(e);


                        for (int i = 0; i < 2; i++) {
                            if (a->R == 15) continue;
                            auto e = std::make_shared<Asteroid>();
                            e->settings(sRock_small, a->x, a->y, c_uid(dre), 15);
                            entities.push_back(e);
                        }

                    }
                }

                if (a->name == "player" && b->name == "asteroid") {
                    if (isCollide(a, b)) {
                        b->isAlive = false;

                        auto e = std::make_shared<Entity>();
                        e->settings(sExplosion_ship, a->x, a->y);
                        e->name = "explosion";
                        entities.push_back(e);

                        p->settings(sPlayer, W / 2, H / 2, 0, 20);
                        p->dx = 0; p->dy = 0;
                    }
                }
            }
        }


        if (p->thrust) p->animation = sPlayer_go;
        else p->animation = sPlayer;


        for (auto e : entities) {
            if (e->name == "explosion") {
                if (e->animation.isEnd()) e->isAlive = false;
            }
        }

        std::uniform_int_distribution uid_150{ 0, 150 };
        if (uid_150(dre) == 0) {
            auto a = std::make_shared<Asteroid>();
            a->settings(sRock, 0, h_uid(dre), c_uid(dre), 25);
            entities.push_back(a);
        }

        for (auto i = entities.begin(); i != entities.end();) {
            std::shared_ptr<Entity> e = *i;

            e->update();
            e->animation.update();

            if (e->isAlive == false) {
                i = entities.erase(i);
            } else i++;
        }

        //////draw//////
        app.draw(background);
        for (auto i : entities) i->draw(app);
        app.display();
    }

    return 0;
}
