//#include "GameState.h"
//#include "Math.h"
//
//GameState::GameState(pyro::StateStack& stack, sf::RenderWindow& window)
//	: State(stack, window)
//	, mWorldBounds(0, 0, 5000, 5000)
//	, mPlayer(mWorldBounds, mWindow, mSoundPlayer)
//	, mCamera(mWindow, mPlayer, mWorldBounds)
//	, mWave(0)
//	, mServer(nullptr)
//	, mClient(nullptr)
//{
//	mWindow.setFramerateLimit(60);
//
//	setupResources();
//
//	sf::Texture& groundTexture = mTextures.get(Textures::Ground);
//	groundTexture.setRepeated(true);
//	mGround.setTexture(mTextures.get(Textures::Ground));
//	mGround.setTextureRect(mWorldBounds);
//
//	mPlayer.setTexture(mTextures.get(Textures::Player));
//	mPlayer.centerOrigin();
//	mPlayer.setPosition(mWorldBounds.width / 2.f, mWorldBounds.height / 2.f);
//
//	mFont.loadFromFile("Assets/Fonts/WaveFont.ttf");
//	mWaveText.setFont(mFont);
//	mWaveText.setColor(sf::Color::Black);
//	mWaveText.setCharacterSize(40);
//	mWaveText.setStyle(sf::Text::Bold);
//
//	setupNetworkConnectionType();
//}
//
//void GameState::setupNetworkConnectionType()
//{
//	std::cout << "1| Server\n"
//			  << "2| Client\n\n";
//	std::string hostResponse;
//	do {
//		std::cin >> hostResponse;
//	} while (hostResponse != "1" && hostResponse != "2");
//
//	if (hostResponse == "1")
//		mServer = std::unique_ptr<Server>(new Server(*this, mStack, mPlayer, mSurvivors));
//	else
//		mClient = std::unique_ptr<Client>(new Client(*this, mStack, mPlayer, mSurvivors));
//}
//
//void GameState::handleWaves()
//{
//	if (mZombies.empty()) {
//		mWave++;
//		for (int i = 0; i < mWave * 10; i++)
//		{
//			mZombies.push_back(Zombie(&mPlayer, &mSurvivors, mWorldBounds));
//			mZombies.back().setTexture(mTextures.get(Textures::Zombie1));
//			mZombies.back().centerOrigin();
//		}
//	}
//}
//
//void GameState::handleCollisions()
//{
//	auto& projectiles = mPlayer.getProjectiles();
//	for (unsigned i = 0; i < mZombies.size(); i++)
//	{
//		//if (mPlayer.getBounds().intersects(mZombies[i].getBounds()))
//		//	requestStateClear();
//
//		for (auto proj = projectiles.begin(); proj != projectiles.end(); proj++)
//			if (mZombies[i].getGlobalBounds().intersects(proj->getGlobalBounds()))
//			{
//				mZombies.erase(mZombies.begin() + i);
//				projectiles.erase(proj);
//				break;
//			}
//	}
//}
//
//void GameState::updateWaveText()
//{
//	mWaveText.setString("Wave " + std::to_string(mWave));
//
//	sf::Vector2f cameraCenter(mCamera.getCenter());
//	sf::Vector2f cameraSize(mCamera.getSize());
//	sf::FloatRect textBounds(mWaveText.getGlobalBounds());
//	mWaveText.setPosition(cameraCenter.x + cameraSize.x / 2.f - textBounds.width - 10.f,
//						  cameraCenter.y - cameraSize.y / 2.f);
//}
//
//void GameState::setupResources()
//{
//	mTextures.load(Textures::Ground, "Assets/Textures/Ground.png");
//	mTextures.load(Textures::Player, "Assets/Textures/Player.png");
//	mTextures.load(Textures::Zombie1, "Assets/Textures/Zombie.png");
//	mTextures.load(Textures::Zombie2, "Assets/Textures/ZombieFilippos.png");
//
//	mSoundPlayer.loadEffect(Survivor::Sound::GunFire, "Assets/Sounds/GunFire.wav");
//}
//
//void GameState::addSurvivor()
//{
//	mSurvivors.push_back(Survivor(mWindow, mSoundPlayer));
//	mSurvivors.back().setTexture(mTextures.get(Textures::Player));
//	mSurvivors.back().centerOrigin();
//}
//
//bool GameState::handleEvent(const sf::Event& event)
//{
//	if (event.type == sf::Event::KeyPressed
//		&& event.key.code == sf::Keyboard::Escape)
//		requestStateClear();
//
//	mPlayer.handleEvent(event);
//	return true;
//}
//
//bool GameState::update(sf::Time dt)
//{
//	handleWaves();
//
//	mPlayer.update(dt);
//	//for (auto& zombie : mZombies)
//	//	zombie.update(dt);
//	for (auto& survivor : mSurvivors)
//		survivor.update(dt);
//
//	mCamera.update();
//	handleCollisions();
//	updateWaveText();
//
//	return true;
//}
//
//void GameState::draw()
//{
//	mWindow.draw(mGround);
//	mWindow.draw(mPlayer);
//	for (const auto& zombie : mZombies)
//		mWindow.draw(zombie);
//	for (const auto& survivor : mSurvivors)
//		mWindow.draw(survivor);
//
//	mWindow.draw(mWaveText);
//}