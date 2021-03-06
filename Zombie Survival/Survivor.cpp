#include "Survivor.h"
#include "Zombie.h"

#include <cassert>

Survivor::Survivor(pyro::SoundPlayer<Sound>& soundPlayer, sf::RenderWindow& window)
	: EntitySprite(280.f)
	, mGunFired(false)
	, mSoundPlayer(&soundPlayer)
	, mWindow(&window)
	, mIsAlive(true)
{
}

Survivor::~Survivor()
{
}

void Survivor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& projectile : mProjectiles)
		target.draw(projectile, states);

	if (mIsAlive)
		target.draw(static_cast<Sprite>(*this), states);
}

Survivor::CollisionChecker Survivor::checkCollision(const Zombie& zombie)
{
	// Zombie & Survivor
	if (mIsAlive)
		if (getQuarterBounds().intersects(zombie.getQuarterBounds()))
		{
			mIsAlive = false;
			return CollisionChecker(false, true);
		}

	//  Zombie & Projectile
	for (unsigned i = 0; i < mProjectiles.size(); i++)
		if (mProjectiles[i].getGlobalBounds().intersects(zombie.getGlobalBounds()))
		{
			mProjectiles.erase(mProjectiles.begin() + i);
			return CollisionChecker(true, false);
		}

	return CollisionChecker(false, false);
}

void Survivor::update(sf::Time dt)
{
	for (unsigned i = 0; i < mProjectiles.size(); i++)
	{
		mProjectiles[i].update(dt);
		if (mProjectiles[i].isDestroyable())
			mProjectiles.erase(mProjectiles.begin() + i);
	}
}

void Survivor::fireProjectile()
{
	mProjectiles.push_back(Projectile(1000.f, getPosition(), getRotation()));
	mSoundPlayer->play(Sound::Gunshot, getPosition(), 5.f);
	mGunFired = true;
}

sf::Packet& operator<<(sf::Packet& packet, Survivor& survivor)
{
	assert(packet << survivor.mGunFired);
	survivor.mGunFired = false;
	assert(packet << static_cast<sf::Int16>(survivor.getRotation()));
	assert(packet << *dynamic_cast<EntitySprite*>(&survivor));
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, Survivor& survivor)
{
	assert(packet >> survivor.mGunFired);
	if (survivor.mGunFired)
	{
		survivor.fireProjectile();
		survivor.mGunFired = false;
	}
	sf::Int16 survivorRotation;
	assert(packet >> survivorRotation);
	survivor.setRotation(static_cast<float>(survivorRotation));

	assert(packet >> *dynamic_cast<EntitySprite*>(&survivor));
	return packet;
}

Survivor::CollisionChecker::CollisionChecker(bool zombie, bool player)
	: eraseZombie(zombie)
	, erasePlayer(player)
{
}