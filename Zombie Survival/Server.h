#ifndef Server_H_
#define Server_H_

#include "Player.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Thread.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/UdpSocket.hpp>

class Server : private sf::NonCopyable
{
private:
	using Port = unsigned short;
	using AddressList = std::vector<std::pair<sf::IpAddress, Port>>;
private:
	AddressList			   mAddressList;
	sf::UdpSocket		   mSocket;
	sf::Thread			   mThread;
						   
	Player*				   mPlayer;
	std::vector<Survivor>* mSurvivors;

private:
	void packetHandling();
public:

};
#endif