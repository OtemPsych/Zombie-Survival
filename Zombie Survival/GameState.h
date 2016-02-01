#ifndef GameState_H_
#define GameState_H_

#include "Zombie.h"
#include "Camera.h"
#include "Network.h"

#include <PYRO/State.h>
#include <PYRO/ResourceTypedefs.h>
#include <PYRO/SoundPlayer.h>
#include <PYRO/Text.h>

#include <SFML/System/Mutex.hpp>

class GameState : public pyro::State
{
private:
	enum class Textures { Ground, Player, Zombie };
private:
	sf::IntRect						   mWorldBounds;
	sf::Sprite						   mGround;
	pyro::SoundPlayer<Survivor::Sound> mSoundPlayer;
									   
	Player							   mPlayer;
	std::vector<Survivor>			   mSurvivors;
	std::vector<Zombie>				   mZombies;
									   
	Camera							   mCamera;
	pyro::TextureHolder<Textures>	   mTextures;
									   
	int								   mWave;
	pyro::Text						   mWaveText;
	sf::Font						   mFont;

	sf::Mutex						   mMutex;
	Network							   mNetwork;

private:
	void updateWaveText();
	virtual void setupResources();
public:
	GameState(pyro::StateStack& stack, sf::RenderWindow& window);
public:
	virtual bool handleEvent(const sf::Event& event);
	virtual bool update(sf::Time dt);
	virtual void draw();
};
#endif