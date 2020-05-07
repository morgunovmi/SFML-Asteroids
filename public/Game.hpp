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
	RenderWindow app{
		VideoMode{
			static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight) }, "Asteroids!" };
	std::unordered_set<std::shared_ptr<Entity>> entities;
	std::shared_ptr<Player> p;
	size_t playerScore = 0;

private:
	Animation sExplosion{ t3, 0, 0, 256, 256, 48, 0.5f };
	Animation sRock{ t4, 0, 0, 64, 64, 16, 0.2f };
	Animation sRock_small{ t6, 0, 0, 64, 64, 16, 0.2f };
	Animation sBullet{ t5, 0, 0, 32, 64, 16, 0.8f };
	Animation sPlayer{ t1, 40, 0, 40, 40, 1, 0 };
	Animation sPlayer_go{ t1, 40, 40, 40, 40, 1, 0 };
	Animation sExplosion_ship{ t7, 0, 0, 192, 192, 64, 0.5f };

private:
	std::random_device rd;
	std::default_random_engine dre{ rd() };
	std::uniform_real_distribution<float> urdWidth{ 0, windowWidth };
	std::uniform_real_distribution<float> urdHeight{ 0, windowHeight };
	std::uniform_real_distribution<float> urd360{ 0, 360 };

private:
	Font font;
	Text livesText;
	Text scoreText;
	Text gameOverText;

private:
	const bool isCollide(const std::shared_ptr<Entity> a, const std::shared_ptr<Entity> b) const;
	void initialize();
	void handleEvents();
	void handleCollisions();
	void update();
	void draw();

public:
	Game(const float width, const float height) : windowWidth(width), windowHeight(height) {}

	void play();

};
