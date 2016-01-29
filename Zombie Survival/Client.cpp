//#include "Client.h"
//
//Client::Client(pyro::StateStack& stack, Player& player,
//			   std::vector<Survivor>& survivors)
//	: mGameState(gameState)
//	, mStateStack(stack)
//	, mThread(&Client::packetHandling, this)
//	, mPlayer(&player)
//	, mSurvivors(&survivors)
//{
//	setup();
//	//mSocket.setBlocking(false);
//	mThread.launch();
//
//	//mServerSocket.setBlocking(false);
//}
//
//void Client::packetHandling()
//{
//	while (!mStateStack.isEmpty())
//	{
//		sf::Packet clientPacket;
//		assert(clientPacket << *mPlayer);
//		std::cout << "Before sending first client packet\n";
//		std::cout << "Server IP: " << mServerIP.toString() << "\nServer Port: " << mServerPort << std::endl;
//		if (mSocket.send(clientPacket, mServerIP, mServerPort) == sf::Socket::Done)
//			std::cout << "Client - clientPacket sent\n";
//
//		std::cout << "After sending first client packet\n";
//		std::cout << "Server IP: " << mServerIP.toString() << "\nServer Port: " << mServerPort << std::endl;
//
//		sf::Packet serverPacket;
//		if (mSocket.receive(serverPacket, mServerIP, mServerPort) == sf::Socket::Done)
//		{
//			unsigned short identifier;
//			assert(serverPacket >> identifier);
//			if (identifier == 1)
//			{
//				if (!mSurvivors->empty())
//					assert(serverPacket >> mSurvivors->at(0));
//				else
//					mGameState.addSurvivor();
//			}
//			else if (identifier == 2)
//			{
//				bool safeToContinue = true;
//
//				if (!mSurvivors->empty())
//					assert(serverPacket >> mSurvivors->at(0));
//				else
//				{
//					mGameState.addSurvivor();
//					safeToContinue = false;
//				}
//
//				if (safeToContinue)
//				{
//					unsigned short survivorPos;
//					assert(serverPacket >> survivorPos);
//
//					if (mSurvivors->size() > survivorPos)
//						assert(serverPacket >> mSurvivors->at(survivorPos));
//					else
//						mGameState.addSurvivor();
//				}
//			}
//		}
//		else
//			std::cout << "Unable to send client packet to server\n";
//
//		std::cout << "After receiving first server packet\n";
//		std::cout << "Server IP: " << mServerIP.toString() << "\nServer Port: " << mServerPort << std::endl;
//	}
//
//	//while (!mStateStack.isEmpty())
//	//{
//	//	sf::Packet serverPacket;
//	//	if (mServerSocket.receive(serverPacket) == sf::Socket::Done)
//	//	{
//	//		unsigned survivorPos;
//	//		assert(serverPacket >> survivorPos);
//	//		if (survivorPos < mSurvivors->size())
//	//			assert(serverPacket >> mSurvivors->at(survivorPos));
//	//		else
//	//			mNbSurvivors++;
//	//	}
//
//	//	sf::Packet clientPacket;
//	//	assert(clientPacket << *mPlayer);
//	//	mServerSocket.send(clientPacket);
//	//}
//}
//
//void Client::setup()
//{
//	std::cout << "\nEnter host's IP Address and Port\n";
//	std::cout << "Host's IP Address: ";
//	std::cin >> mServerIP;
//
//	std::cout << "      Host's Port: ";
//	std::cin >> mServerPort;
//
//	//if (mServerSocket.connect(ip, std::stoi(portResponse)) == sf::Socket::Done)
//	//{
//	//	std::cout << "\nSuccessfuly connected!\n";
//	//	mNbSurvivors++;
//	//}
//
//	if (mSocket.bind(sf::Socket::AnyPort) == sf::Socket::Done)
//		std::cout << "\nSuccessfully bound UDP Socket to port " << mSocket.getLocalPort() << "\n";
//}