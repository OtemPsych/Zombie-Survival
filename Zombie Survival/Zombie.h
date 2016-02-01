#ifndef Zombie_H_
#define Zombie_H_

#include "Player.h"

class Zombie : public EntitySprite
{
private:
	Player*				   mPlayer;
	std::vector<Survivor>* mSurvivors;

private:
	void randomizeStartingPosition(sf::IntRect worldBounds);
public:
	Zombie(Player* player, std::vector<Survivor>* survivors,
		  const sf::Texture& texture, sf::IntRect worldBounds);
public:
	virtual void update(sf::Time dt);

	friend sf::Packet& operator<<(sf::Packet& packet, Zombie& zombie);
	friend sf::Packet& operator>>(sf::Packet& packet, Zombie& zombie);
};
#endif