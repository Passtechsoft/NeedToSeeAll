#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED
#include "../General/general.h"

class NtsaWindow;

class Player : public WindowEntity
{
    public:
        enum Direction{Up, Down, Front, Back};

        Player();
        Player(std::string name, unsigned int priority, std::string textureID="");
        Player(std::string name, unsigned int priority, unsigned int width, int positionY, std::string textureID="");
        void actualiser(NtsaWindow* window);
        void moveSomewere(Direction direction);
        void stabilize();
        void stopMoving();

        void setSpeedUpDown(int speed=3);
        void setSpeedFront(int speed=4);

    private:
		Timer m_timer;
        int m_lifepoints=100;
        int m_speedUpDown=2;
        int m_speedFront=0;

        int m_currentSpeedUpdown=0;
        int m_currentSpeedFront=0;
};

#endif // ENTITY_H_INCLUDED
