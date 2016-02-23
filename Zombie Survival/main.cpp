#include "MultiplayerConnectState.h"
#include "GameState.h"

#include <PYRO/Application.h>

int main()
{
	std::srand(static_cast<unsigned>(std::time(0)));

	pyro::Application app(sf::VideoMode(1280, 720), "League of Zombies",
						  sf::Style::Default);
	app.setClearScreen(true);
	app.setFPS(60);

	app.registerState<MultiplayerConnectState>(pyro::StateID::PreGame1);
	app.registerState<GameState>(pyro::StateID::Game);
	app.pushState(pyro::StateID::PreGame1);
	app.run();

	return 0;
}
