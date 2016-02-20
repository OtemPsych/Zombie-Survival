#ifndef NetworkABC_H_
#define NetworkABC_H_

#include "Zombie.h"

#include <PYRO/StateStack.h>

#include <SFML/System/Mutex.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/UdpSocket.hpp>

class NetworkABC : private sf::NonCopyable
{
protected:
	using Port = sf::Uint16;
	using AddressList = std::vector<std::pair<sf::IpAddress, Port>>;
protected:
	pyro::StateStack&	   mStateStack;
	sf::Mutex&			   mMutex;
						   
	AddressList			   mAddressList;
	sf::UdpSocket		   mSocket;
						   
	Player*				   mPlayer;
	std::vector<Survivor>* mSurvivors;
	std::vector<Zombie>*   mZombies;

	bool				   mPlaying;
	unsigned			   mTotalZombies;

protected:
	virtual void packetHandling() = 0;
private:
	virtual void handleReceiving() = 0;
	virtual void handleSending() = 0;
public:
	NetworkABC(pyro::StateStack& stack, sf::Mutex& mutex, Player* player,
			   std::vector<Survivor>* survivors, std::vector<Zombie>* zombies);
	virtual ~NetworkABC();
public:
	inline unsigned getTotalSurvivors() const { return mAddressList.size(); }
	inline void closeNetworkThread() { mPlaying = false; }

	inline unsigned getTotalZombies() const { return mTotalZombies; }
	inline void setTotalZombies(unsigned totalZombies) { mTotalZombies = totalZombies; }
};
#endif