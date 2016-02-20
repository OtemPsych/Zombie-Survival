#include "Zombie.h"

#include <PYRO/Math.h>

Zombie::Zombie(Player* player, std::vector<Survivor>* survivors,
			   const sf::Texture& texture, sf::IntRect worldBounds)
	: EntitySprite(rand() / (RAND_MAX / (200.f - 80.f)) + 80.f, texture)
	, mPlayer(player)
	, mSurvivors(survivors)
{
	randomizeStartingPosition(worldBounds);
}

void Zombie::randomizeStartingPosition(sf::IntRect worldBounds)
{
	sf::FloatRect globalBounds(getGlobalBounds());
	enum POS { up, down, left, right };

	POS pos = static_cast<POS>(rand() % 4);
	switch (pos)
	{
	case up:
		setPosition(static_cast<float>(rand() / (RAND_MAX / worldBounds.width)), worldBounds.top - globalBounds.height);
		break;
	case down:
		setPosition(static_cast<float>(rand() / (RAND_MAX / worldBounds.width)), worldBounds.height + globalBounds.height);
		break;
	case left:
		setPosition(worldBounds.left - globalBounds.width, static_cast<float>(rand() / (RAND_MAX / worldBounds.height)));
		break;
	case right:
		setPosition(worldBounds.width + globalBounds.width, static_cast<float>(rand() / (RAND_MAX / worldBounds.height)));
		break;
	}
}

void Zombie::update(sf::Time dt)
{
	sf::Vector2f zombiePos(getPosition());

	sf::Vector2f distanceVec;
	int startingSurvivor = 0;

	if (mPlayer->isAlive())
		distanceVec = mPlayer->getPosition() - zombiePos;
	else
	{
		bool found = false;
		for (unsigned i = 0; i < mSurvivors->size(); i++)
			if (mSurvivors->at(i).isAlive())
			{
				distanceVec = mSurvivors->at(i).getPosition() - zombiePos;
				startingSurvivor = i;
				found = true;
			}
		if (!found)
			return;
	}

	float magnitude = pyro::math::getMagnitude(distanceVec);

	for (unsigned i = startingSurvivor; i < mSurvivors->size(); i++)
	{
		if (mSurvivors->at(i).isAlive())
		{
			sf::Vector2f newDistanceVec(mSurvivors->at(i).getPosition() - zombiePos);
			float newMagnitude = pyro::math::getMagnitude(newDistanceVec);
			if (std::min(std::abs(magnitude), std::abs(newMagnitude)) == newMagnitude)
			{
				distanceVec = newDistanceVec;
				magnitude = newMagnitude;
			}
		}
	}
	distanceVec = pyro::math::normalizeVector(distanceVec);
	setRotation(pyro::math::toDegrees(std::atan2f(distanceVec.y, distanceVec.x)));

	move(distanceVec * mSpeed * dt.asSeconds());
}

sf::Packet& operator<<(sf::Packet& packet, Zombie& zombie)
{
	assert(packet << *dynamic_cast<EntitySprite*>(&zombie));
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, Zombie& zombie)
{
	assert(packet >> *dynamic_cast<EntitySprite*>(&zombie));
	return packet;
}