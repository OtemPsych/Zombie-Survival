//#ifndef Client_H_
//#define Client_H_
//
//#include "Player.h"
//
//#include <PYRO/StateStack.h>
//
//#include <SFML/System/Thread.hpp>
//#include <SFML/Network/IpAddress.hpp>
//#include <SFML/Network/UdpSocket.hpp>
////#include <SFML/Network/TcpSocket.hpp>
//
//class Client : private sf::NonCopyable
//{
//private:
//	pyro::StateStack&	   mStateStack;
//
//	//sf::TcpSocket		   mServerSocket;
//	sf::UdpSocket		   mSocket;
//	sf::IpAddress		   mServerIP;
//	unsigned short		   mServerPort;
//	unsigned			   mNbSurvivors;
//	sf::Thread			   mThread;
//
//	Player*				   mPlayer;
//	std::vector<Survivor>* mSurvivors;
//
//private:
//	void packetHandling();
//	void setup();
//public:
//	Client();
//	Client(pyro::StateStack& stack, Player& player,
//		   std::vector<Survivor>& survivors);
//public:
//	inline size_t getNbSurvivors() const { return mNbSurvivors; }
//};
//#endif