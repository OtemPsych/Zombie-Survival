#ifndef Network_H_
#define Network_H_

#include "Zombie.h"

#include <PYRO/StateStack.h>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Thread.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/UdpSocket.hpp>

class Network : private sf::NonCopyable
{
private:
	using Port = unsigned short;
	using AddressList = std::vector<std::pair<sf::IpAddress, Port>>;
private:
	pyro::StateStack&	   mStateStack;
	sf::Mutex&			   mMutex;

	AddressList			   mAddressList;
	sf::UdpSocket		   mSocket;
	sf::Thread			   mThread;
						   
	Player*				   mPlayer;
	std::vector<Survivor>* mSurvivors;
	std::vector<Zombie>*   mZombies;
	bool				   mHost;

private:
	void packetHandling();

	void host_handleSending();
	void host_sendNewClientInfo();

	void client_handleSending();
	void client_handleReceiving();
	void client_addNewClient(sf::Packet& packet);
	void client_setSurvivorInfo(sf::Packet& packet, sf::IpAddress ip, Port port);

	void setup();
	void handleConnectionTypes();
public:
	Network(pyro::StateStack& stack, sf::Mutex& mutex, Player* player,
			std::vector<Survivor>* survivors, std::vector<Zombie>* zombies);
public:
	inline unsigned getTotalSurvivors() const { return mAddressList.size(); }
};
#endif