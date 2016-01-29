//#include "Camera.h"
//
//Camera::Camera(sf::RenderWindow& window, Player& player, sf::IntRect worldBounds)
//	: View(window.getDefaultView())
//	, mWindow(window)
//	, mPlayer(player)
//	, mWorldBounds(worldBounds)
//{
//}
//
//void Camera::update()
//{
//	sf::Vector2f center(mPlayer.getPosition());
//	sf::Vector2f halfViewSize = getSize() / 2.f;
//	sf::FloatRect visibleArea(center.x - halfViewSize.x, center.y - halfViewSize.y,
//							  center.x + halfViewSize.x, center.y + halfViewSize.y);
//
//	if (visibleArea.left >= mWorldBounds.left && visibleArea.width <= mWorldBounds.width)
//		setCenter(center.x, getCenter().y);
//
//	if (visibleArea.top >= mWorldBounds.top && visibleArea.height <= mWorldBounds.height)
//		setCenter(getCenter().x, center.y);
//
//	mWindow.setView(static_cast<sf::View>(*this));
//}