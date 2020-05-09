#pragma once
#include <memory>
#include <unordered_set>
#include "Animation.hpp"
#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Entity.hpp"
#include "Player.hpp"

namespace ast {
	class Game {
	private:
		float mWindowHeight, mWindowWidth;
		sf::RenderWindow mWindow{
			sf::VideoMode{
				static_cast<unsigned int>(mWindowWidth), static_cast<unsigned int>(mWindowHeight) }, "Asteroids!" };
		std::unordered_set<std::shared_ptr<Entity>> mEntities;
		std::shared_ptr<Player> mPlayer;
		size_t playerScore = 0;

	private:
		sf::Texture mPlayerTexture, mBackgroundTexture, mExplosionTexture,
			mRockTexture, mBulletTexture, mSmallRockTexture, mShipExplosionTexture;
		sf::Sprite mBackground;
		Animation mExplosionAnimation{ mExplosionTexture, 0, 0, 256, 256, 48, 0.5f };
		Animation mRockAnimation{ mRockTexture, 0, 0, 64, 64, 16, 0.2f };
		Animation mSmallRockAnimation{ mSmallRockTexture, 0, 0, 64, 64, 16, 0.2f };
		Animation mBulletAnimation{ mBulletTexture, 0, 0, 32, 64, 16, 0.8f };
		Animation mPlayerAnimation{ mPlayerTexture, 40, 0, 40, 40, 1, 0 };
		Animation mPlayerGoAnimation{ mPlayerTexture, 40, 40, 40, 40, 1, 0 };
		Animation mShipExplosionAnimation{ mShipExplosionTexture, 0, 0, 192, 192, 64, 0.5f };

	private:
		std::random_device mRd;
		std::default_random_engine mDre{ mRd() };
		std::uniform_real_distribution<float> mUrdWidth{ 0, mWindowWidth };
		std::uniform_real_distribution<float> mUrdHeight{ 0, mWindowHeight };
		std::uniform_real_distribution<float> mUrd360{ 0, 360 };

	private:
		sf::Font mFont;
		sf::Text mLivesText;
		sf::Text mScoreText;
		sf::Text mGameOverText;

	private:
		const bool isCollide(const std::shared_ptr<Entity> a, const std::shared_ptr<Entity> b) const;
		void initialize();
		void handleEvents();
		void handleCollisions();
		void update();
		void draw();

	public:
		Game(const float width, const float height) : mWindowWidth(width), mWindowHeight(height) {}

		void play();

	};
}
