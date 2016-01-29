//#ifndef GameState_H_
//#define GameState_H_
//
//#include "Zombie.h"
//#include "Camera.h"
//
//#include <PYRO/State.h>
//#include <PYRO/ResourceTypedefs.h>
//#include <PYRO/SoundPlayer.h>
//#include <PYRO/Text.h>
//
//class GameState : public pyro::State
//{
//private:
//	enum class Textures { Ground, Player, Zombie1, Zombie2 };
//private:
//	sf::IntRect						   mWorldBounds;
//	sf::Sprite						   mGround;
//	pyro::SoundPlayer<Survivor::Sound> mSoundPlayer;
//									   
//	Player							   mPlayer;
//	std::vector<Survivor>			   mSurvivors;
//	std::vector<Zombie>				   mZombies;
//									   
//	Camera							   mCamera;
//	pyro::TextureHolder<Textures>	   mTextures;
//									   
//	int								   mWave;
//	pyro::Text						   mWaveText;
//	sf::Font						   mFont;
//
//	std::unique_ptr<Server>			   mServer;
//	std::unique_ptr<Client>			   mClient;
//
//private:
//	void setupNetworkConnectionType();
//
//	void handleWaves();
//	void updateWaveText();
//	void handleCollisions();
//	virtual void setupResources();
//public:
//	GameState(pyro::StateStack& stack, sf::RenderWindow& window);
//public:
//	void addSurvivor();
//
//	virtual bool handleEvent(const sf::Event& event);
//	virtual bool update(sf::Time dt);
//	virtual void draw();
//};
//#endif