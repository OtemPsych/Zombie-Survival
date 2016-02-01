#include "Projectile.h"

#include <PYRO/Math.h>

Projectile::Projectile(float speed, sf::Vector2f pos, float angle)
	: Entity(speed)
	, RectangleShape(sf::Vector2f(5.f, 5.f))
	, mStartingPosition(pos)
	, mDestroyable(false)
{
	setPosition(pos);
	setRotation(angle);
	setFillColor(sf::Color::Black);
}

void Projectile::update(sf::Time dt)
{
	using namespace pyro::math;

	float angle = getRotation();
	move(cos(toRadians(angle)) * mSpeed * dt.asSeconds(),
		 sin(toRadians(angle)) * mSpeed * dt.asSeconds());

	if (getMagnitude(mStartingPosition - getPosition()) > 2000.f)
		mDestroyable = true;
}