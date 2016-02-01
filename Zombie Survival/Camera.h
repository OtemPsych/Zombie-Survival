#ifndef Camera_H_
#define Camera_H_

#include "Survivor.h"

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Camera : public sf::View
{
private:
	sf::RenderWindow& mWindow;
	Survivor*		  mSurvivor;
	sf::IntRect		  mWorldBounds;

public:
	Camera(sf::RenderWindow& window, Survivor* survivor, sf::IntRect worldBounds);
public:
	void update();
};
#endif