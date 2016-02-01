#include "EntitySprite.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <cassert>

EntitySprite::EntitySprite(float speed)
	: Entity(speed)
{
}

EntitySprite::~EntitySprite()
{
}

EntitySprite::EntitySprite(float speed, const sf::Texture& texture)
	: Entity(speed)
	, Sprite(texture)
{
	centerOrigin();
}

void EntitySprite::centerOrigin()
{
	sf::FloatRect bounds(getLocalBounds());
	setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void EntitySprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(static_cast<Sprite>(*this), states);
}

sf::FloatRect EntitySprite::getQuarterBounds() const
{
	sf::Vector2f pos(getPosition());
	sf::FloatRect globalBounds(getGlobalBounds());

	sf::Vector2f quarterSize(globalBounds.width / 4.f, globalBounds.height / 4.f);
	return sf::FloatRect(pos.x - quarterSize.x, pos.y - quarterSize.y,
						 quarterSize.x, quarterSize.y);
}

void EntitySprite::setTexture(const sf::Texture& texture)
{
	Sprite::setTexture(texture);
	centerOrigin();
}

sf::Packet& operator<<(sf::Packet& packet, EntitySprite& entitySprite)
{
	sf::Vector2f entitySpritePos(entitySprite.getPosition());
	assert(packet << static_cast<sf::Int32>(entitySpritePos.x));
	assert(packet << static_cast<sf::Int32>(entitySpritePos.y));
	assert(packet << static_cast<sf::Int16>(entitySprite.getRotation()));

	assert(packet << *dynamic_cast<Entity*>(&entitySprite));
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, EntitySprite& entitySprite)
{
	sf::Int32 entitySpritePosX;
	sf::Int32 entitySpritePosY;
	sf::Int16 entitySpriteRotation;
	assert(packet >> entitySpritePosX >> entitySpritePosY >> entitySpriteRotation);

	entitySprite.setPosition(static_cast<float>(entitySpritePosX),
							 static_cast<float>(entitySpritePosY));
	entitySprite.setRotation(static_cast<float>(entitySpriteRotation));

	assert(packet >> *dynamic_cast<Entity*>(&entitySprite));
	return packet;
}