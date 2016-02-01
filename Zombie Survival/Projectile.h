#ifndef Projectile_H_
#define Projectile_H_

#include "Entity.h"

#include <SFML/Graphics/RectangleShape.hpp>

class Projectile : public Entity, public sf::RectangleShape
{
private:
	sf::Vector2f mStartingPosition;
	bool		 mDestroyable;

public:
	Projectile(float speed, sf::Vector2f pos, float angle);
public:
	virtual void update(sf::Time dt);
	inline bool isDestroyable() const { return mDestroyable; }
};
#endif