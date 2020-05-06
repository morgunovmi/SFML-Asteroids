#pragma once
#include <memory>
#include <unordered_set>
#include "Animation.hpp"
#include "Entity.hpp"
#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Player.hpp"

class Game {
private:
	float windowHeight, windowWidth;
	Texture t1, t2, t3, t4, t5, t6, t7;
	Sprite background;
	RenderWindow app{VideoMode{static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight) }, "Asteroids!" };
	std::unordered_set<std::shared_ptr<Entity>> entities;
	std::shared_ptr<Player> p;
	size_t playerScore = 0;

private:
	Animation sExplosion, sRock, sRock_small, sBullet, sPlayer, sPlayer_go, sExplosion_ship;

private:
	std::random_device rd;
	std::default_random_engine dre{ rd() };
	std::uniform_real_distribution<float> urdWidth{ 0, windowWidth };
	std::uniform_real_distribution<float> urdHeight{ 0, windowHeight };
	std::uniform_real_distribution<float> urd360{ 0, 360 };

private:
	Text livesText{};
	Text scoreText{};
	Text gameOverText{};

private:
	const bool isCollide(const std::shared_ptr<Entity> a, const std::shared_ptr<Entity> b) const;
	void initialize();
	void handleKeyPressed(const Keyboard::Key code);
	void handleEvents();
	void handleCollisions();
	void update();
	void draw();

public:
	Game(const float width, const float height) : windowWidth(width), windowHeight(height) {}

	void play();

};
