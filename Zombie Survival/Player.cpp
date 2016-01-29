//#include "Player.h"
//#include "Math.h"
//
//Player::Player(sf::IntRect worldBounds, sf::RenderWindow& window,
//			   pyro::SoundPlayer<Sound>& soundPlayer)
//	: Survivor(window, soundPlayer)
//	, mWorldBounds(worldBounds)
//{
//	mMovement.up = mMovement.down = mMovement.left = mMovement.right = false;
//}
//
//void Player::handleWorldBoundsCollision()
//{
//	sf::FloatRect bounds(getGlobalBounds());
//
//	if (bounds.left <= mWorldBounds.left)
//		mMovement.left = false;
//	else if (bounds.left + bounds.width >= mWorldBounds.left + mWorldBounds.width)
//		mMovement.right = false;
//
//	if (bounds.top <= mWorldBounds.top)
//		mMovement.up = false;
//	else if (bounds.top + bounds.height >= mWorldBounds.top + mWorldBounds.height)
//		mMovement.down = false;
//}
//
//void Player::handleRotation()
//{
//	if (mWindow.hasFocus())
//	{
//		sf::Vector2f mousePos = mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow));
//		sf::Vector2f distanceVector(mousePos - getPosition());
//
//		setRotation(math::radiansToDegrees(std::atan2f(distanceVector.y, distanceVector.x)));
//	}
//}
//
//void Player::handleEvent(const sf::Event& event)
//{
//	if (event.type == sf::Event::MouseButtonPressed
//		&& event.key.code == sf::Mouse::Left)
//	{
//		firedProjectile(true);
//		return;
//	}
//
//	bool state;
//	if (event.type == sf::Event::KeyPressed)
//		state = true;
//	else if (event.type == sf::Event::KeyReleased)
//		state = false;
//	else
//		return;
//
//	if (event.key.code == sf::Keyboard::W) 
//		mMovement.up = state;
//	else if (event.key.code == sf::Keyboard::S)
//		mMovement.down = state;
//	else if (event.key.code == sf::Keyboard::A)
//		mMovement.left = state;
//	else if (event.key.code == sf::Keyboard::D)
//		mMovement.right = state;
//}
//
//void Player::update(sf::Time dt)
//{
//	handleWorldBoundsCollision();
//	handleRotation();
//
//	sf::Vector2f movement(0.f, 0.f);
//	if (mMovement.up)
//		movement.y -= mSpeed;
//	if (mMovement.down)
//		movement.y += mSpeed;
//	if (mMovement.left)
//		movement.x -= mSpeed;
//	if (mMovement.right)
//		movement.x += mSpeed;
//
//	move(movement * dt.asSeconds());
//
//	Survivor::update(dt);
//}
//
//sf::Packet& operator<<(sf::Packet& packet, Player& player)
//{
//	return packet << *dynamic_cast<Survivor*>(&player);
//}