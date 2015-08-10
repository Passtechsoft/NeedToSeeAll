#include "./Game/ntsa.h"
#define FULLSCREEN

using namespace std;

int main()
{
    affInDebug("Debugmode activated", DEBUG);
    TextureList::getGeneralTextureList()->loadTextures("texturelist");

    NtsaWindow window(sf::VideoMode(800, 600), "Need to see all!    v0.0.0" FULLSCREEN);

	Player player("SpaceCore", PRIORITY_CENTER+5, 30, window.getRelativePos(NtsaWindow::PosNames::Y, 3.6), "button");

    Button bouton("monbouton", PRIORITY_TOP, 200, 200, 200, 200, "button");
    bouton.setAction("close");

    window.setPlayer(player);
    window.addButton(bouton);

    // on fait tourner le programme tant que la fenêtre n'a pas été fermé
    while (window.isOpen())
    {
        //Il n'y a plus que cette fonction à utiliser: le programme tourne tout seul dans NtsaWindow
        window.actualize();
    }

    return 0;
}
