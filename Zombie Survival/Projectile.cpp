//#include "Projectile.h"
//#include "Math.h"
//
//Projectile::Projectile(float speed, sf::Vector2f pos, float angle)
//	: RectangleShape(sf::Vector2f(5.f, 5.f))
//	, mSpeed(speed)
//	, mStartingPos(pos)
//{
//	setPosition(pos);
//	setRotation(angle);
//	setFillColor(sf::Color::Black);
//}
//
//bool Projectile::update(sf::Time dt)
//{
//	move(cos(math::degreesToRadians(getRotation())) * mSpeed * dt.asSeconds(),
//		 sin(math::degreesToRadians(getRotation())) * mSpeed * dt.asSeconds());
//
//	if (math::getMagnitude(mStartingPos - getPosition()) > 2000.f)
//		return false;
//	else
//		return true;
//}