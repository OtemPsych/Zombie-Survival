#include "Entity.h"

#include <cassert>

Entity::Entity(float speed)
	: mSpeed(speed)
{

}

Entity::~Entity()
{
}

sf::Packet& operator<<(sf::Packet& packet, const Entity& entity)
{
	assert(packet << static_cast<sf::Uint16>(entity.mSpeed));
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, Entity& entity)
{
	sf::Uint16 entitySpeed;
	assert(packet >> entitySpeed);

	entity.mSpeed = static_cast<float>(entitySpeed);
	return packet;
}