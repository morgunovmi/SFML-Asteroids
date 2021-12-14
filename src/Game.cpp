#include <iostream>

#include "../include/Game.hpp"

namespace ast {
    bool Game::isCollide(const std::shared_ptr<Entity> a,
            const std::shared_ptr<Entity> b) const {
        return std::pow((b->x() - a->x()), 2) +
            std::pow((b->y() - a->y()), 2) <
            std::pow((a->radius() + b->radius()), 2);
    }

    void Game::initialize() {
        mWindow.setFramerateLimit(60);

        mPlayerTexture.loadFromFile("images/spaceship.png");
        mBackgroundTexture.loadFromFile("images/background.jpg");
        mExplosionTexture.loadFromFile("images/explosions/type_C.png");
        mRockTexture.loadFromFile("images/rock.png");
        mBulletTexture.loadFromFile("images/fire_red.png");
        mSmallRockTexture.loadFromFile("images/rock_small.png");
        mShipExplosionTexture.loadFromFile("images/explosions/type_B.png");

        mPlayerTexture.setSmooth(true);
        mBackgroundTexture.setSmooth(true);

        mBackground.setTexture(mBackgroundTexture);


        for (int i = 0; i < 15; i++) {
            auto a = std::make_shared<Asteroid>(
                mDre, mWindowWidth, mWindowHeight, mRockAnimation,
                mUrdWidth(mDre), mUrdHeight(mDre), mUrd360(mDre), 25);
            mEntities.insert(a);
        }

        mPlayer = std::make_shared<Player>(
            mWindowWidth, mWindowHeight, mPlayerAnimation, mWindowWidth / 2,
            mWindowHeight / 2, 0, 20);

        mEntities.insert(mPlayer);

        if (!mFont.loadFromFile("fonts/aero.ttf")) {
            std::cerr << "Error loading font\n";
        }

        mLivesText.setFont(mFont);
        mLivesText.setCharacterSize(35);
        mLivesText.setFillColor(sf::Color::White);
        mLivesText.setString("Lives left: " + std::to_string(mPlayer->lives()));

        mScoreText.setFont(mFont);
        mScoreText.setCharacterSize(35);
        mScoreText.setFillColor(sf::Color::White);
        mScoreText.setString("Score: " + std::to_string(playerScore));
        mScoreText.setPosition(0, 40);

        mGameOverText.setFont(mFont);
        mGameOverText.setCharacterSize(50);
        mGameOverText.setFillColor(sf::Color::Red);
        mGameOverText.setPosition(mWindowWidth / 2 - 50, mWindowHeight / 2 - 20);
    }

    void Game::handleEvents() {
        sf::Event event;
        while (mWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                mWindow.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    mWindow.close();
                }

                if (event.key.code == sf::Keyboard::Space) {
                    if (mPlayer->isAlive()) {
                        auto b = std::make_shared<Bullet>(
                            mDre, mWindowWidth, mWindowHeight, mBulletAnimation,
                            mPlayer->x(), mPlayer->y(), mPlayer->angle(), 10);
                        mEntities.insert(b);
                    }
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            mPlayer->setAngle(mPlayer->angle() + 3);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            mPlayer->setAngle(mPlayer->angle() - 3);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            mPlayer->setThrust(true);

        } else {
            mPlayer->setThrust(false);
        }
    }

    bool Game::isEqualFloat(const float lhs, const float rhs) {
        return std::abs(rhs - lhs) < FLOAT_PRECISION;
    }

    void Game::handleCollisions() {
        for (auto a : mEntities) {
            for (auto b : mEntities) {
                if (a->name() == ASTEROID && b->name() == BULLET) {
                    if (isCollide(a, b)) {
                        a->setAlive(false);
                        b->setAlive(false);

                        auto explAnimEntity = std::make_shared<Entity>(mExplosionAnimation,
                                a->x(), a->y());

                        explAnimEntity->setName(EXPLOSION);
                        mEntities.insert(explAnimEntity);

                        if (mPlayer->isAlive()) {
                            if (isEqualFloat(a->radius(), 15)) {
                                playerScore += 20;

                            } else {
                                playerScore += 10;
                            }

                            mScoreText.setString("Score: " +
                                    std::to_string(playerScore));
                        }

                        for (int i = 0; i < 2; i++) {
                            if (isEqualFloat(a->radius(), 15)) {
                                continue;
                            }

                            auto astEntity = std::make_shared<Asteroid>(
                                mDre, mWindowWidth, mWindowHeight,
                                mSmallRockAnimation, a->x(), a->y(),
                                mUrd360(mDre), 15);

                            mEntities.insert(astEntity);
                        }

                    }
                }

                if (a->name() == PLAYER && b->name() == ASTEROID) {
                    if (isCollide(a, b)) {
                        b->setAlive(false);

                        auto shipExlAnimEntity = std::make_shared<Entity>(
                                mShipExplosionAnimation,
                                a->x(), a->y());
                        shipExlAnimEntity->setName(EXPLOSION);
                        mEntities.insert(shipExlAnimEntity);

                        mPlayer->reset(mPlayerAnimation, mWindowWidth / 2,
                                mWindowHeight / 2, 0);

                        mPlayer->setLives(mPlayer->lives() - 1);
                        mLivesText.setString("Lives left: " +
                                std::to_string(mPlayer->lives()));
                        if (mPlayer->lives() == 0) {
                            mPlayer->setAlive(false);
                            mGameOverText.setString("Game Over\nFinal Score: "
                                    + std::to_string(playerScore));
                            mLivesText.setString("");
                            mScoreText.setString("");
                        }
                    }
                }
            }
        }
    }

    void Game::update() {
        if (mPlayer->thrust()) {
            mPlayer->setAnimation(mPlayerGoAnimation);
        } else {
            mPlayer->setAnimation(mPlayerAnimation);
        }

        for (auto e : mEntities) {
            if (e->name() == EXPLOSION) {
                if (e->animation().isEnd()) {
                    e->setAlive(false);
                }
            }
        }

        std::uniform_int_distribution uid150{ 0, 150 };
        if (uid150(mDre) == 0) {
            auto a = std::make_shared<Asteroid>(
                mDre, mWindowWidth, mWindowHeight, mRockAnimation, 0,
                mUrdHeight(mDre), mUrd360(mDre), 25);
            mEntities.insert(a);
        }

        for (auto i = mEntities.begin(); i != mEntities.end();) {
            std::shared_ptr<Entity> e = *i;

            e->update();

            if (!e->isAlive()) {
                i = mEntities.erase(i);
            } else {
                i++;
            }
        }
    }

    void Game::draw() {
        mWindow.clear();
        mWindow.draw(mBackground);
        for (auto i : mEntities) {
            i->draw(mWindow);
        }

        mWindow.draw(mScoreText);
        mWindow.draw(mLivesText);
        mWindow.draw(mGameOverText);
        mWindow.display();
    }

    void Game::play() {
        initialize();

        while (mWindow.isOpen()) {
            handleEvents();
            handleCollisions();

            update();
            draw();
        }
    }
}
