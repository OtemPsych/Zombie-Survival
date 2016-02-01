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

//sf::Packet& operator<<(sf::Packet& packet, const Entity& entity)
//{
//	sf::Vector2f entityPos(entity.getPosition());
//	return packet << entity.mSpeed << entityPos.x << entityPos.y << entity.getRotation();
//}
//
//sf::Packet& operator>>(sf::Packet& packet, Entity& entity)
//{
//	sf::Vector2f entityPos;
//	float entityAngle;
//	packet >> entity.mSpeed >> entityPos.x >> entityPos.y >> entityAngle;
//
//	entity.setPosition(entityPos);
//	entity.setRotation(entityAngle);
//
//	return packet;
//}