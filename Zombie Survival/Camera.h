#ifndef Camera_H_
#define Camera_H_

#include "Player.h"

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Camera : public sf::View
{
private:
	sf::RenderWindow&	   mWindow;
	Player*				   mPlayer;
	std::vector<Survivor>* mSurvivors;
	sf::IntRect			   mWorldBounds;

	int					   mFollowingCharacter;

public:
	Camera(sf::RenderWindow& window, Player* player,
		std::vector<Survivor>* survivors, sf::IntRect worldBounds);
public:
	void handleEvent(const sf::Event& event);
	void update(sf::Time dt);
};
#endif