#ifndef EntitySprite_H_
#define EntitySprite_H_

#include "Entity.h"

#include <SFML/Graphics/Sprite.hpp>

class EntitySprite : public Entity, public sf::Sprite
{
private:
	void centerOrigin();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	explicit EntitySprite(float speed);
			 EntitySprite(float speed, const sf::Texture& texture);

	virtual ~EntitySprite();
public:
	sf::FloatRect getQuarterBounds() const;
	void setTexture(const sf::Texture& texture);

	virtual void update(sf::Time dt) = 0;

	friend sf::Packet& operator<<(sf::Packet& packet, EntitySprite& entitySprite);
	friend sf::Packet& operator>>(sf::Packet& packet, EntitySprite& entitySprite);
};
#endif