#ifndef NetworkClient_H_
#define NetworkClient_H_

#include "NetworkABC.h"

#include <SFML/System/Thread.hpp>

class NetworkClient : public NetworkABC
{
private:
	sf::Thread mThread;

private:
	void addNewClient(sf::Packet& packet);
	void setSurvivorInfo(sf::Packet& packet, sf::IpAddress ip, Port port);
	void setZombieInfo(sf::Packet& packet);

	virtual void packetHandling();
	virtual void handleReceiving();
	virtual void handleSending();
public:
	NetworkClient(pyro::StateStack& stack, sf::Mutex& mutex, Player* player,
				  std::vector<Survivor>* survivors, std::vector<Zombie>* zombies);
};
#endif