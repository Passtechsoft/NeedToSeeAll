#include "../General/general.h"

SpriteList generalSpriteList;
TextureList generalTextureList;

SpriteList* SpriteList::getGeneralSpriteList()
{
    return &generalSpriteList;
}

TextureList* TextureList::getGeneralTextureList()
{
    return &generalTextureList;
}

/*     ***************************      *\
            Classe SpriteList
\*     ***************************      */

sf::Sprite* SpriteList::AddSprite(sf::Sprite sprite, std::string id, unsigned int priority)
{
	sf::Sprite* referenceSprite=nullptr;
    if(indexMap.find(id)!=indexMap.end())
    {
		affInDebug(":4:: Le sprite "<<id<<" sera reset sans changer d'adresse.", INFO);
		referenceSprite=indexMap[id];
		*referenceSprite=sf::Sprite();
		return referenceSprite;
    }


	affInDebug(":4:: Création d'un nouveau sprite nommé "<<id, INFO);
	referenceSprite=new sf::Sprite;
	//On ajoute à la pioritymap le sprite nouvellement créé
	priorityMap.insert( priorityMap.begin(), std::pair<unsigned int, sf::Sprite*>(priority, referenceSprite) );
	indexMap[id] = referenceSprite;
	affInDebug(":4:: Le sprite \""<<id<<"\" a été ajouté aux tableaux de tri.", INFO);

	if(indexMap.size() == priorityMap.size())
		affInDebug(":4:: Il y a donc désormait "<<priorityMap.size()<<" sprites dans indexmap et prioritymap", DEBUG);
	else
		ERROR("Il n'y a pas le même nombre de sprites dans priorityMap et indexMap, c'est un bug dangeureux.");

    return referenceSprite;
}

///\note check 1
void SpriteList::RemoveSprite(std::string id)
{
    sf::Sprite* supress=indexMap[id];
    std::map<std::string, sf::Sprite*>::iterator itsupression=indexMap.find(id);
    if(itsupression!=indexMap.end())
        indexMap.erase(itsupression);

    //On purge la map:
    bool finish=false;
    for(std::multimap<unsigned int, sf::Sprite*>::iterator it=priorityMap.begin();
        it!=priorityMap.end() && !finish; it++)
    {
        if(it->second==supress){
            priorityMap.erase(it);
            finish=true;
        }
    }
    affInDebug(":5:: Le sprite \""<<id<<"\" a été supprimé.", DEBUG);
}

/*     ***************************      *\
            Classe TextureList
\*     ***************************      */
///\note check 1
TextureList::TextureList(std::string filePath)
{
    loadTextures(filePath);
}
///\note check 1
void TextureList::showErrors(std::string outfilen)
{
    if(!outfilen.empty())
    {
        std::ofstream outFile(outfilen);
        if(outFile)
            outFile<<m_errors<<std::endl<<":0::    Rien que ça! Dur!";
    }
    if(!m_errors.empty())
        std::cout<<std::endl<<m_errors<<":0::    Rien que ça! Dur!"<<std::endl;
    else
        std::cout<<std::endl<<":0::   Aucune erreur n'a été décelée durant le chargement des textures"<<std::endl;
}

///\note check 1
void TextureList::loadTextures(std::string filePath)
{
    std::ifstream infile(filePath);
    if(!infile){
        m_errors+=":1:: Erreur: Impossible de lire le fichier \""+filePath+"\". Les textures seront immanquablement manquantes.\n";
        showErrors();
        return;
    }

    std::string id, chemin;
    while(id!=";eof;")
    {
        infile>>id;
        infile>>chemin;
        if(m_textureMap.find(id)!=m_textureMap.end())
            ERROR(":6:: Il semble qu'une Texture existe déjà à cet ID. Résolvez ce conflit SVP");

        m_textureMap[id]=sf::Texture();
        if(!m_textureMap[id].loadFromFile(chemin)){
            affInDebug("La texture "+chemin+" est inaccessible, enfin c'kon peut pas la charger, alors chargez vous-en didiou.", WARNING);
            m_errors+="La texture "+chemin+" est inaccessible, enfin c'kon peut pas la charger, alors chargez vous-en didiou.\n";
        }
        else{
            affInDebug(":1:: La texture \""<<id<<"\" s'est probablement chargée sans accrocs", INFO);
            affInDebug(":1:: Il y a "<<m_textureMap.size()<<" texture(s) chargée(s) désormait.", DEBUG);
            m_textureMap[id].setSmooth(true);
        }

        infile>>id;
        if(id!=";"||id!=";eof;")
            m_errors+="erreur critique: synthaxe incorrecte! la liste est fichue, soignez vos fichiers de conf sacrebleu!\n";
    }

}

sf::Texture* TextureList::getTexture(std::string textureID)
{
    return &m_textureMap[textureID];
}


/*     ***************************      *\
            Classe WindowEntity
\*     ***************************      */

WindowEntity::WindowEntity()
{
	affInDebug(":7:: constructor", DEBUG);
}

WindowEntity::WindowEntity(std::string name, unsigned int priority, std::string textureID)
	: m_name(name), m_priority(priority)
{
	INFO(std::endl<<std::endl<<":7:: Création d'un WindowEntity le biennommé \""<<name<<" =====================");
	if(textureID!="")
		addTexture(textureID);
}

///\note check 1
void WindowEntity::actuateSprite(unsigned int spriteLocation, unsigned int textureLocation)
{
    affInDebug(":3:: Actualisation du sprite "<<m_name<<"_sprite", DEBUG);
    //On vérifie si m_sprites contient assez de cases
    if(m_sprites.size() < spriteLocation+1)
    {
        for(unsigned int c=m_sprites.size(); c<spriteLocation+1; c++)
            m_sprites.push_back(nullptr);
    }
    //On vérifie si m_textures contient assez de cases
    if(m_textures.size() < textureLocation+1)
    {
        for(unsigned int c=m_textures.size(); c<textureLocation+1; c++)
            m_textures.push_back(new sf::Texture);
    }

    if(m_sprites[spriteLocation] != nullptr){
        affInDebug(":3:: Un sprite \""<<m_name+"_sprite"<<"\" existe déjà, il sera normallement reset en :4", INFO);
        m_sprites[spriteLocation]=0;
    }

    sf::Sprite* sprite = SpriteList::getGeneralSpriteList()->AddSprite(sf::Sprite(), m_name+"_sprite", m_priority);
    m_sprites[spriteLocation]=sprite;
    DEBUG(m_sprites[spriteLocation]);

    if(m_textures[textureLocation]!=0){
        sprite->setTexture(*m_textures[textureLocation], true);
        affInDebug(":3:: "<<m_name<<" a reçu une texture", INFO);
    }
    else
        affInDebug("Rappele toi le segfault. Pas bon les sprites sans textures, pas bon...", ERROR);
    sprite->setPosition(m_posX, m_posY);
    //Cette ligne donne au sprite la largeur et hauteur voulue
    sprite->setScale(sf::Vector2f(m_width/sprite->getLocalBounds().width, m_height/sprite->getLocalBounds().height));
}

void WindowEntity::addTexture(std::string textureID)
{
    affInDebug(":2:: Ajout de la texture \""<<textureID<<"\" dans "<<m_name<<".", INFO);
    sf::Texture* text=TextureList::getGeneralTextureList()->getTexture(textureID);
    if(text!=nullptr){
        m_textures.push_back(text);
        actuateSprite();
    }
    else
        WARNING(":2:: La texture \""<<textureID<<"\" n'est pas dans la generalTextureList");
}

///\note Check 1
void WindowEntity::setZone(int newPosX, int newPosY, int newWidth, int newHeight)
{
    m_posX=newPosX;
    m_posY=newPosY;
    if(newWidth)
        m_width=newWidth;
    if(newHeight)
        m_height=newHeight;
    if(m_textures.size()!=0)
        actuateSprite();
}

void WindowEntity::setPosition(int newPosX, int newPosY)
{
    m_posX=newPosX;
    m_posY=newPosY;
}

void WindowEntity::setWidthHeight(int newWidth, int newHeight)
{
    m_width=newWidth;
    m_height=newHeight;
}

/*     ***************************      *\
              Classe Timer
\*     ***************************      */

void Timer::start()
{
	if(!m_started)
	{
		restart();
		m_started=true;
	}
}
