#include "ntsa.h"

NtsaWindow::NtsaWindow(Player player) : m_player(player)
{
    m_window=new sf::RenderWindow();
}

NtsaWindow::NtsaWindow(sf::VideoMode mode, const sf::String &title,
        sf::Uint32 style, const sf::ContextSettings &settings)
{
    m_window=new sf::RenderWindow(mode, title, style, settings);
}

NtsaWindow::NtsaWindow(sf::WindowHandle handle, const sf::ContextSettings &settings)
{
    m_window=new sf::RenderWindow(handle, settings);
}

void NtsaWindow::setPlayer(Player& player)
{
    m_player = player;
}

void NtsaWindow::addButton(Button button)
{
    m_buttons[button.getName()]=button;
}

void NtsaWindow::doAction(std::string action)
{
    if(action=="close")
        m_window->close();
}

float NtsaWindow::getRelativePos(PosNames pos, int factor)
{
	if(pos==PosNames::X)
		return m_window->getSize().x/factor;
	return m_window->getSize().y/factor;
}

int NtsaWindow::getSize(PosNames pos)
{
	if(pos==PosNames::X)
		return m_window->getSize().x;
	return m_window->getSize().y;
}

void NtsaWindow::actualize()
{
    sf::Event event;
    while (m_window->pollEvent(event))
    {
        // on regarde le type de l'évènement...
        switch (event.type)
        {
            // fenêtre fermée
            case sf::Event::Closed:
                m_window->close();
            break;

            // touche pressée
            case sf::Event::KeyPressed:
                if (event.key.code == (sf::Keyboard::Z))
                    m_player.moveSomewere(Player::Direction::Up);
                else if(event.key.code == (sf::Keyboard::S))
                    m_player.moveSomewere(Player::Direction::Up);
                else if(event.key.code == sf::Keyboard::Escape)
                    m_window->close();

            break;

            case sf::Event::KeyReleased:
                if (event.key.code == (sf::Keyboard::Space))
                    m_player.stabilize();
            break;

            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    for(std::map<std::string, Button>::iterator it=m_buttons.begin(); it!=m_buttons.end();it++)
                    {
                        if(it->second.isPressed(m_window))
                            doAction(it->second.getAction());
                    }
                }
            break;
            default:
            break;
        }
    }
	m_player.actualiser(this);
    // effacement de la fenêtre en noir
    m_window->clear(sf::Color::Black);

    //Dessin de tous les éléments graphiques:
    SpriteList* theSpriteList=SpriteList::getGeneralSpriteList();

    //On parcours le tableau de sprite général trié par priorité:
    for(std::map<unsigned int, sf::Sprite*>::iterator it=
        theSpriteList->getPriorityMap()->begin(); it!=theSpriteList->getPriorityMap()->end(); it++)
    {
        //std::cout<<"La version qui va s'afficher: "<<it->second<<std::endl;
        m_window->draw(*it->second);//tout ce beau code qui s'affiche correctement, ç'est beau :_)
    }
    // fin de la frame courante, affichage de tout ce qu'on a dessiné
    m_window->display();
}
