#ifndef Player_H_
#define Player_H_

#include "Survivor.h"

#include <SFML/Window/Event.hpp>

class Player : public Survivor
{
private:
	struct Movement {
		bool up, down, left, right;
	};
private:
	Movement	mMovement;
	sf::IntRect mWorldBounds;
	bool		mIsAlive;

private:
	void handleWorldBoundsCollision();
	void handleRotation();

	void handleMovement(const sf::Event& event);
public:
	Player(sf::IntRect worldBounds, sf::RenderWindow& window,
		   pyro::SoundPlayer<Sound>& soundPlayer);
public:
	void handleEvent(const sf::Event& event);
	virtual CollisionChecker checkCollision(const Zombie& zombie);
	virtual void update(sf::Time dt);

	friend sf::Packet& operator<<(sf::Packet& packet, Player& player);

	inline bool isAlive() const { return mIsAlive; }
};
#endif

//#ifndef Player_H_
//#define Player_H_
//
//#include "Survivor.h"
//#include "Projectile.h"
//
//#include <PYRO/SoundPlayer.h>
//
//#include <SFML/Window/Event.hpp>
//#include <SFML/Graphics/RenderWindow.hpp>
//
//class Player : public Survivor
//{
//private:
//	struct Movement {
//		bool up, down, left, right;
//	};
//private:
//	Movement    mMovement;
//	sf::IntRect mWorldBounds;
//
//private:
//	void handleWorldBoundsCollision();
//	void handleRotation();
//public:
//	Player(sf::IntRect worldBounds, sf::RenderWindow& window,
//		   pyro::SoundPlayer<Sound>& soundPlayer);
//public:
//	void handleEvent(const sf::Event& event);
//	virtual void update(sf::Time dt);
//
//	friend sf::Packet& operator<<(sf::Packet& packet, Player& player);
//};
//#endif