#include "NetworkHost.h"
#include "NetworkIdentifiers.h"

NetworkHost::NetworkHost(pyro::StateStack& stack, sf::Mutex& mutex, Player* player,
						 std::vector<Survivor>* survivors, std::vector<Zombie>* zombies)
	: NetworkABC(stack, mutex, player, survivors, zombies)
	, mThread(&NetworkHost::packetHandling, this)
{
	std::cout << "\nIP Address: " << sf::IpAddress::getPublicAddress().toString();
	std::cout << "\n      Port: " << std::to_string(mSocket.getLocalPort()) << std::endl << std::endl;

	mThread.launch();
}

void NetworkHost::sendNewClientInfo(sf::IpAddress ip, Port port)
{
	sf::Packet previousClientsPacket;
	assert(previousClientsPacket << static_cast<sf::Uint16>(NetworkID::NewClient));
	assert(previousClientsPacket << static_cast<sf::Uint16>(1));
	assert(previousClientsPacket << ip.toString() << port);

	sf::Packet newClientPacket;
	assert(newClientPacket << static_cast<sf::Uint16>(NetworkID::NewClient));
	assert(newClientPacket << static_cast<sf::Uint16>(mAddressList.size()));

	for (const auto& address : mAddressList)
	{
		mSocket.send(previousClientsPacket, address.first, address.second);
		assert(newClientPacket << address.first.toString() << address.second);
	}

	mSocket.send(newClientPacket, ip, port);
}

void NetworkHost::packetHandling()
{
	while (true)
	{
		handleReceiving();
		handleSending();

		NetworkABC::packetHandling();
	}
}

void NetworkHost::handleReceiving()
{
	sf::Packet	  clientPacket;
	sf::IpAddress clientIP;
	Port		  clientPort;
	if (mSocket.receive(clientPacket, clientIP, clientPort) == sf::Socket::Done)
	{
		bool found = false;
		for (unsigned i = 0; i < mAddressList.size(); i++)
			if (clientIP == mAddressList[i].first)
			{
				sf::Uint16 networkID;
				assert(clientPacket >> networkID);
				if (static_cast<NetworkID>(networkID) == NetworkID::PlayerInfo)
				{
					mMutex.lock();
					if (mSurvivors->size() > i)
						assert(clientPacket >> mSurvivors->at(i));
					mMutex.unlock();
				}
				found = true;
				break;
			}
		if (!found)
		{
			sendNewClientInfo(clientIP, clientPort);
			mAddressList.push_back(std::make_pair(clientIP, clientPort));
		}
	}
}

void NetworkHost::handleSending()
{
	sf::Packet clientPacket;
	assert(clientPacket << static_cast<sf::Uint16>(NetworkID::PlayerInfo));
	mMutex.lock();
	assert(clientPacket << *mPlayer);
	mMutex.unlock();

	for (const auto& address : mAddressList)
		mSocket.send(clientPacket, address.first, address.second);
}