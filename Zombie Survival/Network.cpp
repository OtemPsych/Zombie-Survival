#include "Network.h"
#include "NetworkIdentifiers.h"

#include <SFML/System/Sleep.hpp>

Network::Network(pyro::StateStack& stack, sf::Mutex& mutex, Player* player,
				std::vector<Survivor>* survivors, std::vector<Zombie>* zombies)
	: mHost(false)
	, mNetworkHost(nullptr)
	, mNetworkClient(nullptr)
{
	setup();
	if (mHost)
		mNetworkHost = std::unique_ptr<NetworkHost>(new NetworkHost(stack, mutex, player, survivors, zombies));
	else
		mNetworkClient = std::unique_ptr<NetworkClient>(new NetworkClient(stack, mutex, player, survivors, zombies));
}

void Network::setup()
{
	std::string response;
	std::cout << "1| Host\n"
			  << "2| Client\n\n";
	do {
		std::cin >> response;
	} while (response != "1" && response != "2");

	if (response == "1")
		mHost = true;
}

unsigned Network::getTotalSurvivors() const
{
	if (mNetworkHost != nullptr)
		return mNetworkHost->getTotalSurvivors();
	else
		return mNetworkClient->getTotalSurvivors();
}