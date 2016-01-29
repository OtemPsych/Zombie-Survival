//#include "Zombie.h"
//#include "Math.h"
//
//Zombie::Zombie(Player* player, std::vector<Survivor>* survivors, sf::IntRect worldBounds)
//	: Entity(rand() / (RAND_MAX / (250.f - 100.f)) + 100.f)
//	, mPlayer(player)
//	, mSurvivors(survivors)
//{
//	randomizeStartingPosition(worldBounds);
//}
//
//void Zombie::randomizeStartingPosition(sf::IntRect worldBounds)
//{
//	sf::FloatRect globalBounds(getGlobalBounds());
//	enum POS { Up, Down, Left, Right };
//
//	POS pos = static_cast<POS>(rand() % 4);
//	if (pos == Up)
//		setPosition(rand() / (RAND_MAX / worldBounds.width), worldBounds.top - globalBounds.height);
//	else if (pos == Down)
//		setPosition(rand() / (RAND_MAX / worldBounds.width), worldBounds.height + globalBounds.height);
//	else if (pos == Left)
//		setPosition(worldBounds.left - globalBounds.width, rand() / (RAND_MAX / worldBounds.height));
//	else if (pos == Right)
//		setPosition(worldBounds.width + globalBounds.width, rand() / (RAND_MAX / worldBounds.height));
//}
//
//void Zombie::update(sf::Time dt)
//{
//	sf::Vector2f distanceVec(mPlayer->getPosition() - getPosition());
//	float magnitude = math::getMagnitude(distanceVec);
//
//	for (unsigned i = 0; i < mSurvivors->size(); i++)
//	{
//		sf::Vector2f newDistanceVec(mSurvivors->at(i).getPosition() - getPosition());
//		float newMagnitude = math::getMagnitude(newDistanceVec);
//		if (std::min(std::abs(magnitude), std::abs(newMagnitude)) == newMagnitude)
//		{
//			distanceVec = newDistanceVec;
//			magnitude = newMagnitude;
//		}
//	}
//	distanceVec = math::normalizeVector(distanceVec);
//	setRotation(math::radiansToDegrees(std::atan2f(distanceVec.y, distanceVec.x)));
//
//	move(distanceVec * mSpeed * dt.asSeconds());
//}