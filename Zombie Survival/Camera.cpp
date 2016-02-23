#include "Camera.h"

#include <PYRO/Math.h>

Camera::Camera(sf::RenderWindow& window, Player* player,
			  std::vector<Survivor>* survivors, sf::IntRect worldBounds)
	: View(window.getDefaultView())
	, mWindow(window)
	, mPlayer(player)
	, mSurvivors(survivors)
	, mWorldBounds(worldBounds)
	, mCharacterFollowing(-1)
{
}

void Camera::handleEvent(const sf::Event& event)
{
	if (!mPlayer->isAlive())
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Left)
			{
				if (mCharacterFollowing - 1 >= 0)
					mCharacterFollowing -= 1;
			}
			else if (event.key.code == sf::Keyboard::Right)
				if (mCharacterFollowing + 1u < mSurvivors->size())
					mCharacterFollowing += 1;
		}
	}
}

void Camera::update(sf::Time dt)
{
	// Change Survivor Being Followed
	bool characterFollowingDead = false;
	if (mCharacterFollowing == -1) {
		if (!mPlayer->isAlive())
			characterFollowingDead = true;
	}
	else if (!mSurvivors->at(mCharacterFollowing).isAlive())
		characterFollowingDead = true;
	else if (mPlayer->isAlive())
		mCharacterFollowing = -1;

	if (characterFollowingDead)
		for (unsigned i = 0; i < mSurvivors->size(); i++)
			if (mSurvivors->at(i).isAlive())
				mCharacterFollowing = i;

	// Update Camera Position
	sf::Vector2f center;
	if (mCharacterFollowing == -1)
		center = mPlayer->getPosition();
	else
		center = mSurvivors->at(mCharacterFollowing).getPosition();

	sf::Vector2f halfViewSize(getSize() / 2.f);
	sf::FloatRect visibleArea(center.x - halfViewSize.x, center.y - halfViewSize.y,
							  center.x + halfViewSize.x, center.y + halfViewSize.y);

	if (visibleArea.left >= mWorldBounds.left && visibleArea.width <= mWorldBounds.width)
		setCenter(center.x, getCenter().y);

	if (visibleArea.top >= mWorldBounds.top && visibleArea.height <= mWorldBounds.height)
		setCenter(getCenter().x, center.y);

	mWindow.setView(*dynamic_cast<sf::View*>(this));
}