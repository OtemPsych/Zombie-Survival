#include "Network.h"
#include "NetworkIdentifiers.h"

#include "MultiplayerConnectState.h"

#include <SFML/System/Sleep.hpp>

Network::Network(pyro::StateStack& stack, sf::Mutex& mutex, Player* player,
				std::vector<Survivor>* survivors, std::vector<Zombie>* zombies)
	: mHost(false)
	, mNetworkHost(nullptr)
	, mNetworkClient(nullptr)
{
	const auto* mpConnectState = dynamic_cast<const MultiplayerConnectState*>(stack.getState(pyro::StateID::PreGame1).get());
	if (mpConnectState != nullptr)
	{
		mHost = (mpConnectState->getHostIp().empty() && mpConnectState->getHostPort().empty());

		if (mHost)
			mNetworkHost = std::unique_ptr<NetworkHost>(new NetworkHost(stack, mutex, player, survivors, zombies));
		else
			mNetworkClient = std::unique_ptr<NetworkClient>(new NetworkClient(stack, mutex, player, survivors, zombies));
	}
}

unsigned Network::getTotalSurvivors() const
{
	if (mHost)
		return mNetworkHost->getTotalSurvivors();
	else
		return mNetworkClient->getTotalSurvivors();
}