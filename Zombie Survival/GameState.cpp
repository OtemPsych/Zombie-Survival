#include "GameState.h"
#include "Math.h"

GameState::GameState(pyro::StateStack& stack, sf::RenderWindow& window)
	: State(stack, window)
	, mWorldBounds(0, 0, 5000, 5000)
	, mPlayer(mWorldBounds, mWindow, mSoundPlayer)
	, mCamera(window, dynamic_cast<Survivor*>(&mPlayer), mWorldBounds)
	, mWave(0)
	, mNetwork(stack, mMutex, &mPlayer, &mSurvivors, &mZombies)
{
	mWindow.setFramerateLimit(60);

	setupResources();

	sf::Texture& groundTexture = mTextures.get(Textures::Ground);
	groundTexture.setRepeated(true);
	mGround.setTexture(mTextures.get(Textures::Ground));
	mGround.setTextureRect(mWorldBounds);

	mMutex.lock();
	mPlayer.setTexture(mTextures.get(Textures::Player));
	mPlayer.setPosition(mWorldBounds.width / 2.f, mWorldBounds.height / 2.f);
	mMutex.unlock();

	mFont.loadFromFile("Assets/Fonts/WaveFont.ttf");
	mWaveText.setFont(mFont);
	mWaveText.setColor(sf::Color::Black);
	mWaveText.setCharacterSize(40);
	mWaveText.setStyle(sf::Text::Bold);
}

void GameState::updateWaveText()
{
	mWaveText.setString("Wave " + std::to_string(mWave));

	sf::Vector2f cameraCenter(mCamera.getCenter());
	sf::Vector2f cameraSize(mCamera.getSize());
	sf::FloatRect textBounds(mWaveText.getGlobalBounds());
	mWaveText.setPosition(cameraCenter.x + cameraSize.x / 2.f - textBounds.width - 10.f,
						  cameraCenter.y - cameraSize.y / 2.f);
}

void GameState::setupResources()
{
	mTextures.load(Textures::Ground, "Assets/Textures/Ground.png");
	mTextures.load(Textures::Player, "Assets/Textures/Player.png");
	mTextures.load(Textures::Zombie, "Assets/Textures/Zombie.png");

	mSoundPlayer.loadEffect(Survivor::Sound::Gunshot, "Assets/Sounds/GunFire.wav");
}

bool GameState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed
		&& event.key.code == sf::Keyboard::Escape)
		requestStateClear();

	mMutex.lock();
	mPlayer.handleEvent(event);
	mMutex.unlock();

	return true;
}

bool GameState::update(sf::Time dt)
{
	mMutex.lock();
	mPlayer.update(dt);
	mMutex.unlock();

	for (unsigned i = mSurvivors.size(); i < mNetwork.getTotalSurvivors(); i++)
	{
		mSurvivors.push_back(Survivor(mSoundPlayer, mWindow));
		mSurvivors.back().setTexture(mTextures.get(Textures::Player));
		mSurvivors.back().setPosition(mWorldBounds.width / 2.f, mWorldBounds.height / 2.f);
	}

	mMutex.lock();
	for (auto& survivor : mSurvivors)
		survivor.update(dt);
	mMutex.unlock();

	if (mZombies.empty())
	{
		mWave++;
		for (int i = 0; i < mWave * 10; i++)
			mZombies.push_back(Zombie(&mPlayer, &mSurvivors, mTextures.get(Textures::Zombie), mWorldBounds));
	}

	//for (auto& zombie : mZombies)
	//	zombie.update(dt);

	mCamera.update();
	updateWaveText();

	for (unsigned i = 0; i < mZombies.size(); i++)
	{
		Player::CollisionChecker collisionChecker(mPlayer.checkCollision(mZombies[i]));
		if (collisionChecker.eraseZombie)
			mZombies.erase(mZombies.begin() + i);
		else
			for (unsigned j = 0; j < mSurvivors.size(); j++)
			{
				Survivor::CollisionChecker survivorCollisionChecker(mSurvivors[j].checkCollision(mZombies[i]));
				if (survivorCollisionChecker.eraseZombie)
					mZombies.erase(mZombies.begin() + i);
			}
	}

	return true;
}

void GameState::draw()
{
	mWindow.draw(mGround);
	mWindow.draw(mPlayer);
	for (const auto& survivor : mSurvivors)
		mWindow.draw(survivor);
	for (const auto& zombie : mZombies)
		mWindow.draw(zombie);

	mWindow.draw(mWaveText);
}