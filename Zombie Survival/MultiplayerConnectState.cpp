#include "MultiplayerConnectState.h"

#include <SFML/Window/Event.hpp>

MultiplayerConnectState::MultiplayerConnectState(pyro::StateStack& stack, sf::RenderWindow& window)
	: State(stack, window)
	, mHostIpTextbox(sf::Vector2f(170.f, 30.f))
	, mHostIpTextboxActivated(false)
	, mHostPortTextbox(sf::Vector2f(170.f, 30.f))
	, mHostPortTextboxActivated(false)
	, mConnectTextbox(sf::Vector2f(120.f, 50.f))
{
	setupResources();

	setupTextboxes();
	setupTexts();
}

void MultiplayerConnectState::setupTextboxes()
{
	sf::Vector2f winSize(mWindow.getSize());

	// Host IP Textbox
	sf::FloatRect ipBounds(mHostIpTextbox.getLocalBounds());
	mHostIpTextbox.setOrigin(ipBounds.width / 2.f, ipBounds.height / 2.f);
	mHostIpTextbox.setPosition(winSize.x / 2.f, winSize.y / 2.f);
	mHostIpTextbox.setFillColor(sf::Color(143, 177, 189));

	// Host Port Textbox
	mHostPortTextbox = mHostIpTextbox;
	sf::Vector2f hostPortPos(mHostPortTextbox.getPosition());
	mHostPortTextbox.setPosition(hostPortPos.x, hostPortPos.y + mHostPortTextbox.getSize().y * 1.5f);

	// Connect Textbox
	sf::FloatRect connectBounds(mConnectTextbox.getLocalBounds());
	mConnectTextbox.setOrigin(connectBounds.width / 2.f, connectBounds.height / 2.f);
	mConnectTextbox.setPosition(hostPortPos.x + mHostPortTextbox.getSize().x - mConnectTextbox.getSize().x,
								hostPortPos.y * 1.5f);
	mConnectTextbox.setFillColor(sf::Color(143, 177, 189));
}

void MultiplayerConnectState::setupTexts()
{
	// Host IP Text
	mHostIp.setColor(sf::Color::White);
	mHostIp.setFont(mFont);
	mHostIp.centerOrigin();
	mHostIp.setCharacterSize(18);

	// Host Port Text
	mHostPort.setColor(sf::Color::White);
	mHostPort.setFont(mFont);
	mHostPort.centerOrigin();
	mHostPort.setCharacterSize(18);

	// Connect Text
	mConnect.setColor(sf::Color::White);
	mConnect.setFont(mFont);
	mConnect.centerOrigin();
	mConnect.setString("Connect");
	mConnect.setCharacterSize(25);

	sf::Vector2f connectTextboxPos(mConnectTextbox.getPosition());
	sf::FloatRect connectBounds(mConnect.getGlobalBounds());
	mConnect.setPosition(connectTextboxPos.x - connectBounds.width / 2.f - 3.f,
						 connectTextboxPos.y - connectBounds.height / 2.f - 5.f);
}

void MultiplayerConnectState::setupResources()
{
	mFont.loadFromFile("Assets/Fonts/WaveFont.ttf");
}

bool MultiplayerConnectState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::TextEntered)
	{
		char textChar = static_cast<char>(event.text.unicode);
	
		if (mHostIpTextboxActivated)
			mHostIp.setString(mHostIp.getString() + textChar);
		else if (mHostPortTextboxActivated)
			mHostPort.setString(mHostPort.getString() + textChar);
	}
	else if (event.type == sf::Event::MouseButtonPressed)
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow));
			if (mHostIpTextbox.getGlobalBounds().contains(mousePos))
			{
				mHostIpTextboxActivated = true;
				mHostPortTextboxActivated = false;
			}
			else if (mHostPortTextbox.getGlobalBounds().contains(mousePos))
			{
				mHostPortTextboxActivated = true;
				mHostIpTextboxActivated = false;
			}
			else if (mConnectTextbox.getGlobalBounds().contains(mousePos))
			{
				requestStatePush(pyro::StateID::Game);
				//requestStateClear();
				return false;
			}
		}

	return true;
}

bool MultiplayerConnectState::update(sf::Time dt)
{
	sf::Vector2f hostIpTextboxPos(mHostIpTextbox.getPosition());
	sf::FloatRect hostIpBounds(mHostIp.getGlobalBounds());
	mHostIp.setPosition(hostIpTextboxPos.x - hostIpBounds.width / 2.f,
						hostIpTextboxPos.y - hostIpBounds.height / 2.f);

	sf::Vector2f hostPortTextboxPos(mHostPortTextbox.getPosition());
	sf::FloatRect hostPortBounds(mHostPort.getGlobalBounds());
	mHostPort.setPosition(hostPortTextboxPos.x - hostPortBounds.width / 2.f,
						  hostPortTextboxPos.y - hostPortBounds.height / 2.f);

	return true;
}

void MultiplayerConnectState::draw()
{
	mWindow.draw(mHostIpTextbox);
	mWindow.draw(mHostIp);

	mWindow.draw(mHostPortTextbox);
	mWindow.draw(mHostPort);

	mWindow.draw(mConnectTextbox);
	mWindow.draw(mConnect);
}