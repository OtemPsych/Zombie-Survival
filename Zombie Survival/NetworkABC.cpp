#include "NetworkABC.h"

#include <SFML/System/Sleep.hpp>

NetworkABC::NetworkABC(pyro::StateStack& stack, sf::Mutex& mutex, Player* player,
	std::vector<Survivor>* survivors, std::vector<Zombie>* zombies)
	: mStateStack(stack)
	, mMutex(mutex)
	, mPlayer(player)
	, mSurvivors(survivors)
	, mZombies(zombies)
{
	if (mSocket.bind(53000) != sf::Socket::Done)
		if (mSocket.bind(53001) != sf::Socket::Done)
			mSocket.bind(53002);

	mSocket.setBlocking(false);
}

NetworkABC::~NetworkABC()
{
}

void NetworkABC::packetHandling()
{
	sf::sleep(sf::milliseconds(40));
}