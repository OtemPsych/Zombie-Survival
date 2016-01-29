//#include "Survivor.h"
//
//Survivor::Survivor(sf::RenderWindow& window, pyro::SoundPlayer<Sound>& soundPlayer)
//	: Entity(280.f)
//	, mShot(false)
//	, mWindow(window)
//	, mSoundPlayer(soundPlayer)
//{
//}
//
//void Survivor::draw(sf::RenderTarget& target, sf::RenderStates states) const
//{
//	for (const auto& projectile : mProjectiles)
//		target.draw(projectile, states);
//	target.draw(static_cast<sf::Sprite>(*this), states);
//}
//
//void Survivor::update(sf::Time dt)
//{
//	if (mShot)
//	{
//		mProjectiles.push_back(Projectile(1000.f, getPosition(), getRotation()));
//		mSoundPlayer.play(Sound::GunFire, getPosition(), 5.f);
//		mShot = false;
//	}
//
//	for (unsigned i = 0; i < mProjectiles.size(); i++)
//		if (!mProjectiles[i].update(dt))
//			mProjectiles.erase(mProjectiles.begin() + i);
//}
//
//sf::Packet& operator<<(sf::Packet& packet, Survivor& survivor)
//{
//	return packet << *dynamic_cast<Entity*>(&survivor) << survivor.mShot;
//}
//
//sf::Packet& operator>>(sf::Packet& packet, Survivor& survivor)
//{
//	return packet >> *dynamic_cast<Entity*>(&survivor) >> survivor.mShot;
//}