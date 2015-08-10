#include "entity.h"
#include "../Game/ntsa.h"

#define PLAYER_STEP_MS 200

Player::Player() : WindowEntity()
{
	m_posX=200;
	m_timer.restart();
}

Player::Player(std::string name, unsigned int priority, std::string textureID)
	: WindowEntity(name, priority, textureID)
{
	m_posX=200;
	m_timer.restart();
}

Player::Player(std::string name, unsigned int priority, unsigned int width, int positionY, std::string textureID)
	: WindowEntity(name, priority, textureID)
{
	setZone(400, positionY, width, width);
	m_timer.restart();
}

void Player::actualiser(NtsaWindow* currentWindow)
{
	m_timer.start();
	int mstime=m_timer.getElapsedTime().asMilliseconds();

	while(mstime >= PLAYER_STEP_MS)
	{
		PIMP(mstime);
		m_posX+=m_currentSpeedFront;
		m_posY+=m_currentSpeedUpdown;

		if(m_posY<0)
			m_posY=0;
		else
		{
			int posLimit=currentWindow->getSize(NtsaWindow::PosNames::Y)-m_height;
			if(m_posY>posLimit)
				m_posY=posLimit;
		}
		mstime-=200;

		if(mstime < PLAYER_STEP_MS)//Si on a fini de faire le compte
			m_timer.restart();
	}
}

void Player::moveSomewere(Direction direction)
{
    if(direction==Direction::Up)
		m_currentSpeedUpdown+=2;
    else if(direction==Direction::Down)
		m_currentSpeedUpdown-=2;
}

void Player::stopMoving()
{
	m_currentSpeedUpdown=0;
	m_currentSpeedFront=0;
}

void Player::stabilize()
{
	m_currentSpeedUpdown=0;
}
