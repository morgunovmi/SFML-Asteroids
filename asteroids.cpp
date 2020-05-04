#include <SFML/Graphics.hpp>
#include <time.h>
#include <random>
#include <memory>
#include <list>
#include <unordered_set>

using namespace sf;

class Animation {
private:
    float frame, speed;
    Sprite sprite;
    std::vector<IntRect> frames;

public:
    Animation() {}

    Animation(Texture& t, int x, int y, int width, int height, int count, float _speed) {
        frame = 0;
        speed = _speed;

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
    float x, y, dx, dy, r, angle, windowWidth, windowHeight;
    bool isAlive;
    std::string name;
    Animation animation;
    std::default_random_engine rnd;

    Entity() {
        isAlive = true;
    }

    void settings(Animation& a, float _x, float _y, float _angle = 0, float radius = 1.f) {
        animation = a;
        x = _x;
        y = _y;
        angle = _angle;
        r = radius;
    }

    virtual void update() {};

    void draw(RenderWindow& app) {
        Sprite sprite = animation.getSprite();
        sprite.setPosition(x, y);
        sprite.setRotation(angle + 90);
        app.draw(sprite);

        CircleShape circle(r);
        circle.setFillColor(Color(255, 0, 0, 170));
        circle.setPosition(x, y);
        circle.setOrigin(r, r);
        //app.draw(circle);
    }

    virtual ~Entity() {};
};


class Asteroid : public Entity {
public:
    Asteroid(std::default_random_engine& dre, float width, float height) {
        name = "asteroid";
        windowWidth = width;
        windowHeight = height;

        dx = static_cast<float>(uid(dre));
        dy = static_cast<float>(uid(dre));
    }

    void update() {
        x += dx;
        y += dy;

        if (x > windowWidth) x = 0;  if (x < 0) x = windowWidth;
        if (y > windowHeight) y = 0;  if (y < 0) y = windowHeight;
    }
private:
    std::uniform_int_distribution<> uid{ -4, 4 };
};


class Bullet : public Entity {
public:
    Bullet(std::default_random_engine& dre, float width, float height) {
        name = "bullet";
        windowWidth = width;
        windowHeight = height;

        rnd = dre;
    }

    void update() {
        float degtorad = 0.017453f;
        dx = cos(angle * degtorad) * 6;
        dy = sin(angle * degtorad) * 6;
        angle += uid(rnd);  /*try this*/
        x += dx;
        y += dy;

        if (x > windowWidth || x < 0 || y > windowHeight || y < 0) isAlive = false;
    }

private:
    std::uniform_int_distribution<> uid{ -4, 4 };
};


class Player : public Entity {
public:
    bool thrust;
    int numLives = 5;

    Player(float width, float height) {
        name = "player";
        windowWidth = width;
        windowHeight = height;
        dx = 0;
        dy = 0;
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

        if (x > windowWidth) x = 0; if (x < 0) x = windowWidth;
        if (y > windowHeight) y = 0; if (y < 0) y = windowHeight;
    }

};


bool isCollide(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) {
    return (b->x - a->x) * (b->x - a->x) +
        (b->y - a->y) * (b->y - a->y) <
        (a->r + b->r) * (a->r + b->r);
}


int main() {
    float windowWidth = 1280;
    float windowHeight = 720;
    RenderWindow app(VideoMode(static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight)), "Asteroids!");
    app.setFramerateLimit(60);

    Texture t1, t2, t3, t4, t5, t6, t7;
    t1.loadFromFile("images/spaceship.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/explosions/type_C.png");
    t4.loadFromFile("images/rock.png");
    t5.loadFromFile("images/fire_red.png");
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
    std::uniform_real_distribution<float> urdWidth{ 0, windowWidth };
    std::uniform_real_distribution<float> urdHeight{ 0, windowHeight };
    std::uniform_real_distribution<float> urd360{ 0, 360 };

    for (int i = 0; i < 15; i++) {
        auto a = std::make_shared<Asteroid>(dre, windowWidth, windowHeight);
        a->settings(sRock, urdWidth(dre), urdHeight(dre), urd360(dre), 25);
        entities.push_back(a);
    }

    auto p = std::make_shared<Player>(windowWidth, windowHeight);
    p->settings(sPlayer, windowWidth / 2, windowHeight / 2, 0, 20);
    entities.push_back(p);
    
    Text livesText;
    Font font;
    font.loadFromFile("fonts/aero.ttf");
    livesText.setFont(font);
    livesText.setCharacterSize(35);
    livesText.setFillColor(Color::White);
    livesText.setString("Lives left: " + std::to_string(p->numLives));
    
    int playerScore = 0;
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(35);
    scoreText.setFillColor(Color::White);
    scoreText.setString("Score: " + std::to_string(playerScore));
    scoreText.setPosition(0, 40);

    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(Color::Red);
	gameOverText.setPosition(windowWidth / 2 - 50, windowHeight / 2 - 20);
    
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
                    if (p->isAlive) {
                        auto b = std::make_shared<Bullet>(dre, windowWidth, windowHeight);
                        b->settings(sBullet, p->x, p->y, p->angle, 10);
                        entities.push_back(b);
                    }
                }
            }
        }

        if (p->isAlive) {
            if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) p->angle += 3;
            if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))  p->angle -= 3;

            if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) p->thrust = true;
            else p->thrust = false;
        }

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

                        if (p->isAlive) {
                            if (a->r == 15) playerScore += 20;
                            else playerScore += 10;
                            scoreText.setString("Score: " + std::to_string(playerScore));
                        }

                        for (int i = 0; i < 2; i++) {
                            if (a->r == 15) continue;
                            auto e = std::make_shared<Asteroid>(dre, windowWidth, windowHeight);
                            e->settings(sRock_small, a->x, a->y, urd360(dre), 15);
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

                        p->settings(sPlayer, windowWidth / 2, windowHeight / 2, 0, 20);
                        p->dx = 0; p->dy = 0;

                        p->numLives--;
                        livesText.setString("Lives left: " + std::to_string(p->numLives));
                        if (p->numLives == 0) {
                            p->isAlive = false;
                            gameOverText.setString("Game Over\nFinal Score: " + std::to_string(playerScore));
                            livesText.setString("");
                            scoreText.setString("");
                        }
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

        std::uniform_int_distribution uid150{ 0, 150 };
        if (uid150(dre) == 0) {
            auto a = std::make_shared<Asteroid>(dre, windowWidth, windowHeight);
            a->settings(sRock, 0, urdHeight(dre), urd360(dre), 25);
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
        app.draw(livesText);
        app.draw(scoreText);
        app.draw(gameOverText);
        app.display();
    }

    return 0;
}
