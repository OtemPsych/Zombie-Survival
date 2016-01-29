#include "Entity.h"

Entity::Entity(float speed)
	: mSpeed(speed)
{
}

Entity::~Entity()
{
}

//
//Entity::Entity(float speed)
//	: mSpeed(speed)
//{
//}
//
//void Entity::centerOrigin()
//{
//	sf::FloatRect bounds(getLocalBounds());
//	setOrigin(bounds.width / 2.f, bounds.height / 2.f);
//}
//
//sf::FloatRect Entity::getBounds() const
//{
//	sf::Vector2f fourthOfSize(getGlobalBounds().width / 4, getGlobalBounds().height / 4);
//	sf::Vector2f pos(getPosition());
//	return sf::FloatRect(pos.x - fourthOfSize.x, pos.y - fourthOfSize.y,
//						 fourthOfSize.x, fourthOfSize.y);
//}
//
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