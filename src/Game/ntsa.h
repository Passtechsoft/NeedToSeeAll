#ifndef NTSA_H_INCLUDED
#define NTSA_H_INCLUDED

#include "../General/usualydefined.h"
#include "../General/general.h"
#include "../Graphics/UI.h"
#include "../Game/level.h"
#include "../Game/entity.h"

class NtsaWindow
{
public:
	enum PosNames{X, Y};

    NtsaWindow(Player player);
    NtsaWindow(sf::VideoMode mode, const sf::String &title, sf::Uint32 style=sf::Style::Default,
         const sf::ContextSettings &settings=sf::ContextSettings());
    NtsaWindow(sf::WindowHandle handle, const sf::ContextSettings &settings=sf::ContextSettings());
	float getRelativePos(PosNames, int factor);//va donner la position donné par la largeur ou hauteur de l'écran divisé par le facteur

    void setPlayer(Player& player);
    void addButton(Button);
    void actualize();
    void doAction(std::string action);
    int getSize(PosNames pos);
    sf::RenderWindow* getRenderWindow(){return m_window;};

    std::pair<int, int> getWidthHeight();

    //Fonctions normallement hérités de Renderwindow (grrr)
    void close(){m_window->close();};
    void draw(sf::Sprite* sprite){m_window->draw(*sprite);};
    bool isOpen(){return m_window->isOpen();};
private:
    sf::RenderWindow* m_window;
    Player m_player;
    std::map<std::string, Button> m_buttons;
};

#endif // NTSA_H_INCLUDED
