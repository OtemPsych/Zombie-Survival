#include "Player.h"

#include <PYRO/Math.h>

Player::Player(sf::IntRect worldBounds, sf::RenderWindow& window,
	pyro::SoundPlayer<Sound>& soundPlayer)
	: Survivor(soundPlayer, window)
	, mWorldBounds(worldBounds)
	, mIsAlive(true)
{
	mMovement.up = mMovement.down = mMovement.left = mMovement.right = false;
}

void Player::handleWorldBoundsCollision()
{
	sf::FloatRect bounds(getGlobalBounds());

	if (bounds.left <= mWorldBounds.left)
		mMovement.left = false;
	else if (bounds.left + bounds.width >= mWorldBounds.left + mWorldBounds.width)
		mMovement.right = false;

	if (bounds.top <= mWorldBounds.top)
		mMovement.up = false;
	else if (bounds.top + bounds.height >= mWorldBounds.top + mWorldBounds.height)
		mMovement.down = false;
}

void Player::handleRotation()
{
	if (mWindow.hasFocus())
	{
		sf::Vector2f mousePos(mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow)));
		sf::Vector2f distanceVec(mousePos - getPosition());

		setRotation(pyro::math::toDegrees(atan2f(distanceVec.y, distanceVec.x)));
	}
}

void Player::handleMovement(const sf::Event& event)
{
	bool state;
	if (event.type == sf::Event::KeyPressed)
		state = true;
	else if (event.type == sf::Event::KeyReleased)
		state = false;
	else
		return;

	switch (event.key.code)
	{
	case sf::Keyboard::W:
		mMovement.up = state;
		break;
	case sf::Keyboard::S:
		mMovement.down = state;
		break;
	case sf::Keyboard::A:
		mMovement.left = state;
		break;
	case sf::Keyboard::D:
		mMovement.right = state;
		break;
	}
}

void Player::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed
		&& event.key.code == sf::Mouse::Left)
	{
		fireProjectile();
		return;
	}
	else
		handleMovement(event);
}

Player::CollisionChecker Player::checkCollision(const Zombie& zombie)
{
	CollisionChecker collisionChecker(Survivor::checkCollision(zombie));
	if (collisionChecker.erasePlayer)
		mIsAlive = false;

	return collisionChecker;
}

void Player::update(sf::Time dt)
{
	handleWorldBoundsCollision();
	handleRotation();

	sf::Vector2f movement(0.f, 0.f);
	if (mMovement.up)
		movement.y -= mSpeed;
	if (mMovement.down)
		movement.y += mSpeed;

	if (mMovement.left)
		movement.x -= mSpeed;
	if (mMovement.right)
		movement.x += mSpeed;

	move(movement * dt.asSeconds());
	Survivor::update(dt);
}

sf::Packet& operator<<(sf::Packet& packet, Player& player)
{
	assert(packet << *dynamic_cast<Survivor*>(&player));
	return packet;
}