#ifndef Network_H_
#define Network_H_

#include "Zombie.h"
#include "NetworkHost.h"
#include "NetworkClient.h"

#include <PYRO/StateStack.h>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Thread.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/UdpSocket.hpp>

class Network : private sf::NonCopyable
{
private:
	bool						   mHost;
	std::unique_ptr<NetworkHost>   mNetworkHost;
	std::unique_ptr<NetworkClient> mNetworkClient;

public:
	Network(pyro::StateStack& stack, sf::Mutex& mutex, Player* player,
			std::vector<Survivor>* survivors, std::vector<Zombie>* zombies);
public:
	unsigned getTotalSurvivors() const;
	inline bool isHost() const { return mHost; }
	inline void closeNetworkThread() { mHost ? mNetworkHost->closeNetworkThread() : mNetworkClient->closeNetworkThread(); }
};
#endif