#include "NetworkClient.h"
#include "NetworkIdentifiers.h"

#include "MultiplayerConnectState.h"

NetworkClient::NetworkClient(pyro::StateStack& stack, sf::Mutex& mutex, Player* player,
							 std::vector<Survivor>* survivors, std::vector<Zombie>* zombies)
	: NetworkABC(stack, mutex, player, survivors, zombies)
	, mThread(&NetworkClient::packetHandling, this)
{
	const MultiplayerConnectState* multiplayerConnectState = dynamic_cast<const MultiplayerConnectState*>(stack.getState(pyro::StateID::PreGame1).get());
	if (multiplayerConnectState != nullptr)
	{
		sf::IpAddress hostIp(multiplayerConnectState->getHostIp());
		Port hostPort(static_cast<Port>(std::stoi(multiplayerConnectState->getHostPort())));

		if (hostIp != sf::IpAddress::getPublicAddress() || hostPort != mSocket.getLocalPort())
			mAddressList.push_back(std::make_pair(hostIp, hostPort));

		mThread.launch();
	}

	////sf::IpAddress ipAddress;
	////std::cout << "\nHost's IP Address: ";
	////std::cin >> ipAddress;

	////Port port;
	////std::cout << "      Host's Port: ";
	////std::cin >> port;

	//sf::IpAddress hostIp("84.75.41.186");
	//Port hostPort(53000);
	//if (hostIp != sf::IpAddress::getPublicAddress() || hostPort != mSocket.getLocalPort())
	//{
	//	mAddressList.push_back(std::make_pair(hostIp, hostPort));
	//	std::cout << "Connected to " << hostIp.toString() << std::endl;
	//}
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
		std::cout << ipAddress << " connected!\n";
	}
}

void NetworkClient::setSurvivorInfo(sf::Packet& packet, sf::IpAddress ip, Port port)
{
	for (unsigned i = 0; i < mAddressList.size(); i++)
		if (ip == mAddressList[i].first && port == mAddressList[i].second)
		{
			mMutex.lock();
			if (mSurvivors->size() > i)
				assert(packet >> mSurvivors->at(i));
			mMutex.unlock();

			break;
		}

	if (!packet.endOfPacket())
	{
		sf::Uint16 networkID;
		assert(packet >> networkID);
		if (static_cast<NetworkID>(networkID) == NetworkID::ZombieInfo)
			setZombieInfo(packet);
	}
}

void NetworkClient::setZombieInfo(sf::Packet& packet)
{
	mMutex.lock();
	sf::Uint16 totalZombies;
	assert(packet >> totalZombies);
	if (totalZombies == mZombies->size())
	{
		for (unsigned i = 0; i < mZombies->size(); i++)
		{
			sf::Uint16 zombieIndex;
			assert(packet >> zombieIndex);
			assert(packet >> mZombies->at(zombieIndex));
		}
	}
	mMutex.unlock();
}

void NetworkClient::packetHandling()
{
	while (mPlaying)
	{
		if (mPlayer->isAlive())
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
		if (!packet.endOfPacket())
		{
			sf::Uint16 networkID;
			assert(packet >> networkID);
			switch (static_cast<NetworkID>(networkID))
			{
			case NetworkID::PlayerInfo:
				setSurvivorInfo(packet, ipAddress, port);
				break;
			case NetworkID::ZombieInfo:
				setZombieInfo(packet);
				break;
			case NetworkID::NewClient:
				addNewClient(packet);
			}
		}
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