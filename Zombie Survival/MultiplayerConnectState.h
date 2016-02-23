#ifndef MultiplayerConnectState_H_
#define MultiplayerConnectState_H_

#include <PYRO/State.h>
#include <PYRO/Text.h>

#include <SFML/Graphics/RectangleShape.hpp>

class MultiplayerConnectState : public pyro::State
{
private:
	sf::Font		   mFont;

	pyro::Text		   mHostIp;
	sf::RectangleShape mHostIpTextbox;
	bool			   mHostIpTextboxActivated;

	pyro::Text		   mHostPort;
	sf::RectangleShape mHostPortTextbox;
	bool			   mHostPortTextboxActivated;

	pyro::Text		   mConnect;
	sf::RectangleShape mConnectTextbox;

private:
	void setupTextboxes();
	void setupTexts();
	virtual void setupResources();
public:
	MultiplayerConnectState(pyro::StateStack& stack, sf::RenderWindow& window);
public:
	inline std::string getHostIp() const { return mHostIp.getString(); }
	inline std::string getHostPort() const { return mHostPort.getString(); }

	virtual bool handleEvent(const sf::Event& event);
	virtual bool update(sf::Time dt);
	virtual void draw();
};
#endif