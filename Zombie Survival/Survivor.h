#ifndef Survivor_H_
#define Survivor_H_

#include "EntitySprite.h"
#include "Projectile.h"

#include <PYRO/SoundPlayer.h>

#include <SFML/Graphics/RenderWindow.hpp>

class Zombie;
class Survivor : public EntitySprite
{
public:
	struct CollisionChecker
	{
		bool eraseZombie;
		bool erasePlayer;

		CollisionChecker(bool zombie, bool player);
	};
public:
	enum class Sound { Gunshot };
private:
	bool					  mGunFired;
	std::vector<Projectile>	  mProjectiles;
	pyro::SoundPlayer<Sound>* mSoundPlayer;
protected:
	sf::RenderWindow*		  mWindow;
	bool					  mIsAlive;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Survivor(pyro::SoundPlayer<Sound>& soundPlayer, sf::RenderWindow& window);
	virtual ~Survivor();
public:
	virtual CollisionChecker checkCollision(const Zombie& zombie);
	virtual void update(sf::Time dt);

	void fireProjectile();
	inline bool isAlive() const { return mIsAlive; }
	inline void revive() { mIsAlive = true; }

	friend sf::Packet& operator<<(sf::Packet& packet, Survivor& survivor);
	friend sf::Packet& operator>>(sf::Packet& packet, Survivor& survivor);
};
#endif