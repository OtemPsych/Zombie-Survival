#ifndef Entity_H_
#define Entity_H_

#include <SFML/System/Time.hpp>
#include <SFML/Network/Packet.hpp>

class Entity
{
protected:
	float mSpeed;

public:
	explicit Entity(float speed);
	virtual ~Entity();
public:
	virtual void update(sf::Time dt) = 0;

	friend sf::Packet& operator<<(sf::Packet& packet, const Entity& entity);
	friend sf::Packet& operator>>(sf::Packet& packet, Entity& entity);
};
#endif

//#ifndef Entity_H_
//#define Entity_H_
//
//#include <SFML/System/Time.hpp>
//#include <SFML/Network/Packet.hpp>
//#include <SFML/Graphics/Sprite.hpp>
//
//class Entity : public sf::Sprite
//{
//protected:
//	float mSpeed;
//
//public:
//	Entity(float speed);
//public:
//	virtual void update(sf::Time dt) = 0;
//
//	void centerOrigin();
//	sf::FloatRect getBounds() const;
//
//	friend sf::Packet& operator<<(sf::Packet& packet, const Entity& entity);
//	friend sf::Packet& operator>>(sf::Packet& packet, Entity& entity);
//};
//#endif