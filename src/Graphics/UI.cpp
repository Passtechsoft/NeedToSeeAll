#include "UI.h"

Button::Button(std::string name, unsigned int priority, std::string texture)
    : WindowEntity(name, priority, texture)
{}

Button::Button(std::string name, unsigned int priority, int x, int y, int w, int h, std::string texture)
    : WindowEntity(name, priority, texture)
{
    setZone(x, y, w, h);
}

bool Button::isPressed(sf::RenderWindow* currentWindow)
{
    //Bouton en mode "je reste appuyé, il envoie
    if(!sf::Event::MouseButtonReleased && m_pressed==true)
		return true;
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        int currentMousePosX = sf::Mouse::getPosition(*currentWindow).x;
        int currentMousePosY = sf::Mouse::getPosition(*currentWindow).y;

        if(currentMousePosX >= m_posX && currentMousePosX <= m_posX+m_width
            && currentMousePosY >= m_posY && currentMousePosY <= m_posY+m_height)
        {
            m_pressed=true;
            return true;
        }
    }
    return false;
}
