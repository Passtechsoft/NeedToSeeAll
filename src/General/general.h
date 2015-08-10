#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED

#include "usualydefined.h"
#include "utilities.h"

#define PRIORITY_BACKGROUND0 1000000
#define PRIORITY_BACKGROUND1 500000
#define PRIORITY_BEFORECENTER 100000
#define PRIORITY_CENTER 50000
#define PRIORITY_TOP 10000
#define PRIORITY_TOTT 1000 //Top Of The Top

class WindowEntity
{
public:
    WindowEntity();
    WindowEntity(std::string name, unsigned int priority, std::string textureID="");
    void addTexture(std::string textureID);

    void setZone(int newPosX, int newPosY, int newWidth=0, int newHeight=0);
    void setWidthHeight(int newWidth, int newHeight);
    void setPosition(int newPosX, int newPosY);
    std::string getName(){return m_name;};

protected:
	void actuateSprite(unsigned int spriteLocation=0, unsigned int textureLocation=0);

    std::vector<sf::Sprite*> m_sprites;
    std::vector<sf::Texture*> m_textures;

    std::string m_name="Robert Paulson";
    unsigned int m_priority=PRIORITY_CENTER;

    int m_posX=23, m_posY=23;
    int m_height=23, m_width=23;
};

class Timer : public sf::Clock
{
public:
	Timer(){sf::Clock();};
	void start();
private:
	bool m_started=false;
};


class SpriteList
{
public:
    SpriteList(){};
    sf::Sprite* AddSprite(sf::Sprite sprite, std::string id, unsigned int priority);
    void RemoveSprite(std::string id);

    static SpriteList* getGeneralSpriteList();
    std::multimap<unsigned int, sf::Sprite*>* getPriorityMap(){return &priorityMap;};
private:

    std::map<std::string, sf::Sprite*> indexMap;
    std::multimap<unsigned int, sf::Sprite*> priorityMap;
};

class TextureList
{
public:
    TextureList(){};
    TextureList(std::string filePath);
    void loadTextures(std::string filePath);
    void showErrors(std::string outfilen="");

    sf::Texture* getTexture(std::string textureID);
    static TextureList* getGeneralTextureList();

private:
    std::string m_errors;
    std::map<std::string, sf::Texture> m_textureMap;
};

#endif // GENERAL_H_INCLUDED
