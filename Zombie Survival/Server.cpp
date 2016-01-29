//#include "Server.h"
//
//#include <SFML/Network/TcpListener.hpp>
//
//Server::Server(GameState& gameState, pyro::StateStack& stack, Player& player,
//			   std::vector<Survivor>& survivors)
//	: mGameState(gameState)
//	, mStateStack(stack)
//	, mThread(&Server::packetHandling, this)
//	//, mPort(53000)
//	, mPlayer(&player)
//	, mSurvivors(&survivors)
//{
//	if (mSocket.bind(sf::Socket::AnyPort) == sf::Socket::Done)
//	{
//		std::cout << "\nServer listening to port " << mSocket.getLocalPort() << ", waiting for a message\n";
//		displayNetworkInformation();
//
//		//mConnectionListener.listen(mPort);
//		//mSocketSelector.add(mConnectionListener);
//
//		//mSocket.setBlocking(false);
//		mThread.launch();
//	}
//}
//
//void Server::packetHandling()
//{
//	while (!mStateStack.isEmpty())
//	{
//		sf::Packet clientPacket;
//		sf::IpAddress sender;
//		Port port;
//		if (mSocket.receive(clientPacket, sender, port) == sf::Socket::Done)
//		{
//			std::cout << "Server - clientPacket received\n";
//
//			bool newClient = true;
//			for (unsigned i = 0; i < mAddresses.size(); i++)
//				if (sender.toString() == mAddresses[i].first.toString())
//				{
//					if (mSurvivors->size() > i)
//						assert(clientPacket >> mSurvivors->at(i));
//
//					sf::Packet serverPacket;
//					serverPacket << 1 << *mPlayer;
//
//					sf::Packet serverClientPacket;
//					serverClientPacket << 2 << *mPlayer << i << clientPacket;
//
//					for (unsigned j = 0; j < mAddresses.size(); j++)
//						if (j != i)
//							mSocket.send(serverClientPacket, mAddresses[i].first, mAddresses[i].second);
//						else
//							mSocket.send(serverPacket, mAddresses[i].first, mAddresses[i].second);
//
//
//					newClient = false;
//				}
//
//			if (newClient)
//			{
//				mGameState.addSurvivor();
//				mAddresses.push_back(std::make_pair(sender, port));
//			}
//		}
//
//		std::cout << sender.toString() << " " << port << std::endl;
//	}
//
//	//while (!mStateStack.isEmpty())
//	//{
//	//	if (mSocketSelector.wait())
//	//	{
//	//		// Check for pending connection
//	//		if (mSocketSelector.isReady(mConnectionListener))
//	//		{
//	//			ClientSocket client(new sf::TcpSocket());
//	//			if (mConnectionListener.accept(*client) == sf::Socket::Done)
//	//			{
//	//				mClientSockets.push_back(std::move(client));
//	//				mSocketSelector.add(*mClientSockets.back());
//	//				std::cout << std::endl << mClientSockets.back()->getRemoteAddress().toString() << " Connected!\n";
//	//			}
//	//		}
//
//	//		sf::Packet playerPacket;
//	//		assert(playerPacket << 0 << *mPlayer);
//	//		for (unsigned i = 0; i < mClientSockets.size(); i++)
//	//			mClientSockets[i]->send(playerPacket);
//
//	//		// Receive info from client and send to the other clients
//	//		for (unsigned i = 0; i < mClientSockets.size(); i++)
//	//			if (mSocketSelector.isReady(*mClientSockets[i]))
//	//			{
//	//				sf::Packet clientPacket;
//	//				if (mClientSockets[i]->receive(clientPacket) == sf::Socket::Done)
//	//				{
//	//					if (mSurvivors->size() > i)
//	//						assert(clientPacket >> mSurvivors->at(i));
//
//	//					sf::Packet newPacketToSend;
//	//					newPacketToSend << i << clientPacket;
//
//	//					for (unsigned j = 0; j < mClientSockets.size(); j++)
//	//						if (j != i)
//	//							mClientSockets[j]->send(newPacketToSend);
//	//				}
//	//			}
//	//	}
//	//}
//}
//
//void Server::displayNetworkInformation()
//{
//	std::cout << "\nIP Address: " << sf::IpAddress::getPublicAddress().toString();
//	std::cout << "\n      Port: " << mSocket.getLocalPort() << std::endl << std::endl;
//}