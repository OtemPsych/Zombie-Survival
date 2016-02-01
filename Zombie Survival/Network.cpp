#include "Network.h"
#include "NetworkIdentifiers.h"

#include <SFML/System/Sleep.hpp>

Network::Network(pyro::StateStack& stack, sf::Mutex& mutex, Player* player,
				std::vector<Survivor>* survivors, std::vector<Zombie>* zombies)
	: mStateStack(stack)
	, mMutex(mutex)
	, mThread(&Network::packetHandling, this)
	, mPlayer(player)
	, mSurvivors(survivors)
	, mZombies(zombies)
	, mHost(false)
{
	if (mSocket.bind(53000) != sf::Socket::Done)
		if (mSocket.bind(53001) == sf::Socket::Done)
			std::cout << "\nSocket successfully bound to port 53001\n";
	else
		std::cout << "\nSocket successfully bound to port 53000\n";

	setup();
	mSocket.setBlocking(false);
	mThread.launch();
}

void Network::packetHandling()
{
	while (true)
	{
		if (mHost)
		{
			// Receive client packet from client
			sf::Packet clientPacket;
			sf::IpAddress clientIP;
			Port		  clientPort;
			if (mSocket.receive(clientPacket, clientIP, clientPort) == sf::Socket::Done)
			{
				// Check if packet sent from new client
				bool found = false;
				for (unsigned i = 0; i < mAddressList.size(); i++)
					if (clientIP == mAddressList[i].first)
					{
						// Distribute packet to self
						mMutex.lock();
						if (mSurvivors->size() > i)
							assert(clientPacket >> mSurvivors->at(i));
						mMutex.unlock();
						 
						found = true;
						break;
					}
				if (!found)
				{
					mAddressList.push_back(std::make_pair(clientIP, clientPort));
					host_sendNewClientInfo();
				}
			}

			// Send packet to client
			host_handleSending();
		}
		else
		{
			// Send own packet to all addresses
			client_handleSending();

			// Receive packet from host/client | new client info/player info
			client_handleReceiving();
		}

		sf::sleep(sf::milliseconds(40));
	}
}

void Network::host_handleSending()
{
	sf::Packet packet;
	assert(packet << static_cast<sf::Int16>(NetworkID::PlayerInfo));
	mMutex.lock();
	assert(packet << *mPlayer);
	mMutex.unlock();
	for (unsigned i = 0; i < mSurvivors->size(); i++)
		mSocket.send(packet, mAddressList[i].first, mAddressList[i].second);
}

void Network::host_sendNewClientInfo()
{
	sf::Packet packet;
	assert(packet << mAddressList.back().first.toString() << mAddressList.back().second);
	for (unsigned i = 0; i < mAddressList.size() - 1; i++)
		mSocket.send(packet, mAddressList[i].first, mAddressList[i].second);
}

void Network::client_handleSending()
{
	sf::Packet clientPacket;
	assert(clientPacket << static_cast<sf::Uint16>(NetworkID::PlayerInfo));
	mMutex.lock();
	assert(clientPacket << *mPlayer);
	mMutex.unlock();

	for (const auto& address : mAddressList)
		mSocket.send(clientPacket, address.first, address.second);
}

void Network::client_handleReceiving()
{
	sf::Packet packet;
	sf::IpAddress IPAddress;
	Port		  Port;
	if (mSocket.receive(packet, IPAddress, Port) == sf::Socket::Done)
	{
		sf::Int16 networkID;
		assert(packet >> networkID);
		if (static_cast<NetworkID>(networkID) == NetworkID::NewClient)
			client_addNewClient(packet);
		if (static_cast<NetworkID>(networkID) == NetworkID::PlayerInfo)
			client_setSurvivorInfo(packet, IPAddress, Port);
	}
}

void Network::client_addNewClient(sf::Packet& packet)
{
	std::string ipAddress;
	Port	    port;
	assert(packet >> ipAddress >> port);

	mAddressList.push_back(std::make_pair(sf::IpAddress(ipAddress), port));
}

void Network::client_setSurvivorInfo(sf::Packet& packet, sf::IpAddress ip, Port port)
{
	for (unsigned i = 0; i < mAddressList.size(); i++)
		if (ip == mAddressList[i].first)
		{
			mMutex.lock();
			if (mSurvivors->size() > i)
				assert(packet >> mSurvivors->at(i));
			mMutex.lock();

			break;
		}
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

	handleConnectionTypes();
}

void Network::handleConnectionTypes()
{
	if (mHost)
	{
		std::cout << "\nIP Address: " << sf::IpAddress::getPublicAddress().toString();
		std::cout << "\n      Port: " << std::to_string(mSocket.getLocalPort()) << std::endl << std::endl;
	}
	else
	{
		sf::IpAddress ipAddress;
		std::cout << "\nHost's IP Address: ";
		std::cin >> ipAddress;

		Port port;
		std::cout << "      Host's Port: ";
		std::cin >> port;

		mAddressList.push_back(std::make_pair(ipAddress, port));
	}
}