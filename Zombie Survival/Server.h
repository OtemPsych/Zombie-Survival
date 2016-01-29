//#ifndef Server_H_
//#define Server_H_
//
//#include "GameState.h"
//
//#include <PYRO/StateStack.h>
//
//#include <SFML/System/Thread.hpp>
//#include <SFML/Network/IpAddress.hpp>
//#include <SFML/Network/UdpSocket.hpp>
////#include <SFML/Network/TcpSocket.hpp>
////#include <SFML/Network/TcpListener.hpp>
////#include <SFML/Network/SocketSelector.hpp>
//
//class Server
//{
//private:
//	using Port = unsigned short;
//	using AddressList = std::vector<std::pair<sf::IpAddress, Port>>;
////	using ClientSocket = std::unique_ptr<sf::TcpSocket>;
//private:
//	GameState&				  mGameState;
//	pyro::StateStack&		  mStateStack;
//							  
//	//std::vector<ClientSocket> mClientSockets;
//	//sf::TcpListener			  mConnectionListener;
//	//sf::SocketSelector		  mSocketSelector;
//	AddressList				  mAddresses;
//	sf::UdpSocket			  mSocket;
//	sf::Thread				  mThread;
//							  
//	//unsigned short			  mPort;
//							  
//	Player*					  mPlayer;
//	std::vector<Survivor>*	  mSurvivors;
//
//private:
//	void packetHandling();
//
//	void displayNetworkInformation();
//public:
//	Server();
//	Server(GameState& gameState, pyro::StateStack& stack, Player& player,
//		   std::vector<Survivor>& survivors);
//public:
//	//inline size_t getNbSurvivors() const { return mClientSockets.size(); }
//	inline size_t getNbSurvivors() const { return mAddresses.size(); }
//};
//#endif