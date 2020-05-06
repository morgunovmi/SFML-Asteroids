#include "Game.hpp"

const bool Game::isCollide(const std::shared_ptr<Entity> a, const std::shared_ptr<Entity> b) const {
    return (b->mX - a->mX) * (b->mX - a->mX) +
        (b->mY - a->mY) * (b->mY - a->mY) <
        (a->mR + b->mR) * (a->mR + b->mR);
}

void Game::initialize() {
    app.setFramerateLimit(60);

    t1.loadFromFile("images/spaceship.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/explosions/type_C.png");
    t4.loadFromFile("images/rock.png");
    t5.loadFromFile("images/fire_red.png");
    t6.loadFromFile("images/rock_small.png");
    t7.loadFromFile("images/explosions/type_B.png");

    t1.setSmooth(true);
    t2.setSmooth(true);

    background.setTexture(t2);
	sExplosion = Animation{ t3, 0, 0, 256, 256, 48, 0.5f };
    sRock = Animation{ t4, 0, 0, 64, 64, 16, 0.2f };
	sRock_small = Animation{ t6, 0, 0, 64, 64, 16, 0.2f };
	sBullet = Animation{ t5, 0, 0, 32, 64, 16, 0.8f };
	sPlayer = Animation{ t1, 40, 0, 40, 40, 1, 0 };
    sPlayer_go = Animation{ t1, 40, 40, 40, 40, 1, 0 };
	sExplosion_ship = Animation{ t7, 0, 0, 192, 192, 64, 0.5f };

    for (int i = 0; i < 15; i++) {
        auto a = std::make_shared<Asteroid>(dre, windowWidth, windowHeight);
        a->settings(sRock, urdWidth(dre), urdHeight(dre), urd360(dre), 25);
        entities.insert(a);
    }

    p = std::make_shared<Player>(windowWidth, windowHeight);
    p->settings(sPlayer, windowWidth / 2, windowHeight / 2, 0, 20);
    entities.insert(p);


    Font font;
    font.loadFromFile("fonts/aero.ttf");

    livesText.setFont(font);
    livesText.setCharacterSize(35);
    livesText.setFillColor(Color::White);
    livesText.setString("Lives left: " + std::to_string(p->mNumLives));

    scoreText.setFont(font);
    scoreText.setCharacterSize(35);
    scoreText.setFillColor(Color::White);
    scoreText.setString("Score: " + std::to_string(playerScore));
    scoreText.setPosition(0, 40);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setPosition(windowWidth / 2 - 50, windowHeight / 2 - 20);
}

void Game::handleKeyPressed(const Keyboard::Key code) {
    if (code == Keyboard::Escape) {
        app.close();
    }

    if (p->mIsAlive) {
        switch (code) {
        case Keyboard::Space:
            if (p->mIsAlive) {
                auto b = std::make_shared<Bullet>(dre, windowWidth, windowHeight);
                b->settings(sBullet, p->mX, p->mY, p->mAngle, 10);
                entities.insert(b);
            }
            break;
        case Keyboard::Right:
        case Keyboard::D:
            p->mAngle += 3;
            break;
        case Keyboard::Left:
        case Keyboard::A:
            p->mAngle -= 3;
            break;
        case Keyboard::Up:
        case Keyboard::W:
            p->mThrust = true;
            break;
        default:
            p->mThrust = false;
            break;
        }
    }
}

void Game::handleEvents() {
    Event event;
    while (app.pollEvent(event)) {
        switch (event.type) {
        case Event::Closed:
            app.close();
            break;
        case Event::KeyPressed:
            handleKeyPressed(event.key.code);
            break;
        default:
            break;
        }
    }
}

void Game::handleCollisions() {
    for (auto a : entities) {
        for (auto b : entities) {
            if (a->mName == "asteroid" && b->mName == "bullet") {
                if (isCollide(a, b)) {
                    a->mIsAlive = false;
                    b->mIsAlive = false;

                    auto e = std::make_shared<Entity>();
                    e->settings(sExplosion, a->mX, a->mY);
                    e->mName = "explosion";
                    entities.insert(e);

                    if (p->mIsAlive) {
                        if (a->mR == 15) playerScore += 20;
                        else playerScore += 10;
                        scoreText.setString("Score: " + std::to_string(playerScore));
                    }

                    for (int i = 0; i < 2; i++) {
                        if (a->mR == 15) continue;
                        auto e = std::make_shared<Asteroid>(dre, windowWidth, windowHeight);
                        e->settings(sRock_small, a->mX, a->mY, urd360(dre), 15);
                        entities.insert(e);
                    }

                }
            }

            if (a->mName == "player" && b->mName == "asteroid") {
                if (isCollide(a, b)) {
                    b->mIsAlive = false;

                    auto e = std::make_shared<Entity>();
                    e->settings(sExplosion_ship, a->mX, a->mY);
                    e->mName = "explosion";
                    entities.insert(e);

                    p->settings(sPlayer, windowWidth / 2, windowHeight / 2, 0, 20);
                    p->mDx = 0; p->mDy = 0;

                    p->mNumLives--;
                    livesText.setString("Lives left: " + std::to_string(p->mNumLives));
                    if (p->mNumLives == 0) {
                        p->mIsAlive = false;
                        gameOverText.setString("Game Over\nFinal Score: " + std::to_string(playerScore));
                        livesText.setString("");
                        scoreText.setString("");
                    }
                }
            }
        }
    }
}

void Game::update() {
    if (p->mThrust) p->mAnimation = sPlayer_go;
    else p->mAnimation = sPlayer;

    for (auto e : entities) {
        if (e->mName == "explosion") {
            if (e->mAnimation.isEnd()) e->mIsAlive = false;
        }
    }

    std::uniform_int_distribution uid150{ 0, 150 };
    if (uid150(dre) == 0) {
        auto a = std::make_shared<Asteroid>(dre, windowWidth, windowHeight);
        a->settings(sRock, 0, urdHeight(dre), urd360(dre), 25);
        entities.insert(a);
    }

    for (auto i = entities.begin(); i != entities.end();) {
        std::shared_ptr<Entity> e = *i;

        e->update();
        e->mAnimation.update();

        if (e->mIsAlive == false) {
            i = entities.erase(i);
        } else i++;
    }
}

void Game::draw() {
    app.draw(background);
    for (auto i : entities) {
        i->draw(app);
    }

    app.draw(livesText);
    app.draw(scoreText);
    app.draw(gameOverText);
    app.display();
}

void Game::play() {
    initialize();

    while (app.isOpen()) {
        handleEvents();
        handleCollisions();

        update();
        draw();
    }
}