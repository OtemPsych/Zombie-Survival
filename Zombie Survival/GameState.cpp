#include "GameState.h"
#include "Math.h"

GameState::GameState(pyro::StateStack& stack, sf::RenderWindow& window)
	: State(stack, window)
	, mWorldBounds(0, 0, 5000, 5000)
	, mPlayer(mWorldBounds, mWindow, mSoundPlayer)
	, mCamera(window, &mPlayer, &mSurvivors, mWorldBounds)
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

	mMusicPlayer.loadTheme(Music::Ambient, "Assets/Music/Ambient.wav");
	mMusicPlayer.setVolume(35.f);
	mMusicPlayer.play(Music::Ambient);

	setupTexts();

	mMutex.lock();
	mZombies.clear();
	updateWave();
	mMutex.unlock();
}

void GameState::updateWave()
{
	if (mZombies.empty())
	{
		mWave++;
		for (int i = 0; i < mWave * 15; i++)
			mZombies.push_back(Zombie(&mPlayer, &mSurvivors, mTextures.get(Textures::Zombie), mWorldBounds));

		mPlayer.revive();
		for (auto& survivor : mSurvivors)
			survivor.revive();
	}
}

void GameState::updateWaveText()
{
	mWaveText.setString("Wave " + std::to_string(mWave));

	sf::Vector2f cameraCenter(mCamera.getCenter());
	sf::Vector2f cameraSize(mCamera.getSize());
	sf::FloatRect textBounds(mWaveText.getGlobalBounds());
	mWaveText.setPosition(cameraCenter.x + cameraSize.x / 2.f - textBounds.width - 10.f,
						  cameraCenter.y - cameraSize.y / 2.f);

	sf::Vector2f waveTextPos(mWaveText.getPosition());
	mZombiesRemaining.setString(std::to_string(mZombies.size()) + " remaining");
	mZombiesRemaining.setPosition(cameraCenter.x + cameraSize.x / 2.f - mZombiesRemaining.getGlobalBounds().width - 10.f,
								  waveTextPos.y + textBounds.height + 25.f);
}

void GameState::setupTexts()
{
	mFont.loadFromFile("Assets/Fonts/WaveFont.ttf");

	mWaveText.setFont(mFont);
	mWaveText.setColor(sf::Color::White);
	mWaveText.setCharacterSize(50);
	mWaveText.setStyle(sf::Text::Bold);
	mWaveText.centerOrigin();

	mZombiesRemaining.setFont(mFont);
	mZombiesRemaining.setColor(sf::Color::White);
	mZombiesRemaining.setCharacterSize(18);
	mZombiesRemaining.centerOrigin();
}

void GameState::setupResources()
{
	mTextures.load(Textures::Ground, "Assets/Textures/Ground.png");
	mTextures.load(Textures::Player, "Assets/Textures/Player.png");
	mTextures.load(Textures::Zombie, "Assets/Textures/Zombie.png");

	for (unsigned k = 0; k < static_cast<unsigned>(Textures::TotalTextures); k++)
	{
		sf::Image image = mTextures.get(static_cast<Textures>(k)).copyToImage();
		for (unsigned i = 0; i < image.getSize().x; i++)
			for (unsigned j = 0; j < image.getSize().y; j++)
			{
				sf::Color pxColor(image.getPixel(i, j));
				image.setPixel(i, j, sf::Color(pxColor.r * 0.6, pxColor.g * 0.6, pxColor.b * 0.6, pxColor.a));
			}
		mTextures.get(static_cast<Textures>(k)).update(image);
	}

	mSoundPlayer.loadEffect(Survivor::Sound::Gunshot, "Assets/Sounds/GunFire.wav");
}

bool GameState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			mNetwork.closeNetworkThread();
			requestStateClear();
			return false;
		}
	}

	mMutex.lock();
	mPlayer.handleEvent(event);
	mMutex.unlock();

	return false;
}

bool GameState::update(sf::Time dt)
{
	if (!mPlayer.isAlive())
	{
		bool allSurvivorsDead = true;
		for (const auto& survivor : mSurvivors)
			if (survivor.isAlive())
				allSurvivorsDead = false;

		if (allSurvivorsDead)
		{
			mNetwork.closeNetworkThread();
			requestStateClear();
			return false;
		}
	}

	mMutex.lock();
	if (mPlayer.isAlive())
		mPlayer.update(dt);

	for (unsigned i = mSurvivors.size(); i < mNetwork.getTotalSurvivors(); i++)
	{
		mSurvivors.push_back(Survivor(mSoundPlayer, mWindow));
		mSurvivors.back().setTexture(mTextures.get(Textures::Player));
		mSurvivors.back().setPosition(mWorldBounds.width / 2.f, mWorldBounds.height / 2.f);
	}
	for (auto& survivor : mSurvivors)
		survivor.update(dt);
	mMutex.unlock();

	mCamera.update(dt);

	updateWave();
	updateWaveText();

	mMutex.lock();
	for (auto& zombie : mZombies)
		zombie.update(dt);

	for (unsigned i = 0; i < mZombies.size(); i++)
		if (mPlayer.checkCollision(mZombies[i]).eraseZombie)
			mZombies.erase(mZombies.begin() + i);
		else
			for (unsigned j = 0; j < mSurvivors.size(); j++)
				if (mSurvivors[j].checkCollision(mZombies[i]).eraseZombie)
					mZombies.erase(mZombies.begin() + i);

	mMutex.unlock();

	return false;
}

void GameState::draw()
{
	mWindow.draw(mGround);

	mMutex.lock();

	if (mPlayer.isAlive())
		mWindow.draw(mPlayer);

	for (const auto& survivor : mSurvivors)
		mWindow.draw(survivor);

	for (const auto& zombie : mZombies)
		mWindow.draw(zombie);
	mMutex.unlock();

	mWindow.draw(mWaveText);
	mWindow.draw(mZombiesRemaining);
}