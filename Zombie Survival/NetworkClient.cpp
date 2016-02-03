#include "NetworkClient.h"
#include "NetworkIdentifiers.h"

NetworkClient::NetworkClient(pyro::StateStack& stack, sf::Mutex& mutex, Player* player,
							 std::vector<Survivor>* survivors, std::vector<Zombie>* zombies)
	: NetworkABC(stack, mutex, player, survivors, zombies)
	, mThread(&NetworkClient::packetHandling, this)
{
	sf::IpAddress ipAddress;
	std::cout << "\nHost's IP Address: ";
	std::cin >> ipAddress;

	Port port;
	std::cout << "      Host's Port: ";
	std::cin >> port;

	mAddressList.push_back(std::make_pair(ipAddress, port));

	mThread.launch();
}

void NetworkClient::addNewClient(sf::Packet& packet)
{
	sf::Uint16 totalClients;
	assert(packet >> totalClients);
	for (unsigned i = 0; i < totalClients; i++)
	{
		std::string ipAddress;
		Port		port;
		assert(packet >> ipAddress >> port);

		mAddressList.push_back(std::make_pair(sf::IpAddress(ipAddress), port));
	}
}

void NetworkClient::setSurvivorInfo(sf::Packet& packet, sf::IpAddress ip, Port port)
{
	for (unsigned i = 0; i < mAddressList.size(); i++)
		if (ip == mAddressList[i].first)
		{
			mMutex.lock();
			if (mSurvivors->size() > i)
				assert(packet >> mSurvivors->at(i));
			mMutex.unlock();

			return;
		}
}

void NetworkClient::packetHandling()
{
	while (true)
	{
		handleSending();
		handleReceiving();

		NetworkABC::packetHandling();
	}
}

void NetworkClient::handleReceiving()
{
	sf::Packet	  packet;
	sf::IpAddress ipAddress;
	Port		  port;
	if (mSocket.receive(packet, ipAddress, port) == sf::Socket::Done)
	{
		sf::Uint16 networkID;
		assert(packet >> networkID);
		if (static_cast<NetworkID>(networkID) == NetworkID::PlayerInfo)
			setSurvivorInfo(packet, ipAddress, port);
		else if (static_cast<NetworkID>(networkID) == NetworkID::NewClient)
			addNewClient(packet);
	}
}

void NetworkClient::handleSending()
{
	sf::Packet packet;
	assert(packet << static_cast<sf::Uint16>(NetworkID::PlayerInfo));
	mMutex.lock();
	assert(packet << *mPlayer);
	mMutex.unlock();

	for (const auto& address : mAddressList)
		mSocket.send(packet, address.first, address.second);
}