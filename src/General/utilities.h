#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

//Mettez cette ligne en commentaire si vous ne voulez pas voir affichés les messages de debug
#define DEBUGMOD


#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <sys/time.h>

#include <iostream>
#include <string>
#include <fstream>
#include <ostream>

#include <array>
#include <vector>
#include <map>
#include <queue>
#include <list>


#define PR_WHITE 30 //#seriouslybro
#define PR_RED 31
#define PR_GREEN 32
#define PR_YELLOW 33
#define PR_BLUE 34
#define PR_PURPLE 35
#define PR_LIGHTBLUE 36
#define PR_GREY 37

#define COLORED_PRINT(param1, param) std::cout<<"\033["<<param<<"m"<<param1<<"\033[30m"<<std::endl

#define PIMP(txt) COLORED_PRINT("/!\\PIMP SPOTTED/!\\: "<<txt, PR_LIGHTBLUE)
#define DEBUG(txt) COLORED_PRINT("DEBUG: "<<txt, PR_BLUE)
#define INFO(txt) COLORED_PRINT("INFO: "<<txt, PR_GREY)
#define WARNING(txt) COLORED_PRINT("WARNING: "<<txt, PR_YELLOW)
#define ERROR(txt) COLORED_PRINT("ERROR: "<<txt, PR_RED)
#define CRITIC_ERROR(txt) COLORED_PRINT("/!\\CRITIC ERROR/!\\: "<<txt, PR_PURPLE);std::cout<<1/0<<std::endl

#ifdef DEBUGMOD
#define affInDebug(message, entree) entree(message)
#else
#define affDebug(message, entree) ;
#endif // DEBUGMOD

//Génère un pitit nbre aléatoire
#define RAND(min, max) ( (rand() % (max-min+1))+min )

//Une simple fonction ²
#define CARRE(var) (var*var)

//Retourne true si le chiffre est entier
#define ISINTEGRER(result) (result==(int)result)

#define DIVISIBLE_PAR(nbre, diviseur) (nbre/((float)diviseur)==(short)nbre/diviseur)
//Utile dans les cas de tests ou on aimerait obtenir un int tel que jamais un utilisateur n'oserais le taper
#define INT_IMPROBABLE 4294967295

typedef unsigned char oct_e;//Reast In Pieces `(
typedef unsigned char uchar;
typedef unsigned short ushort;

///Permet de tester une certaine probabilité
bool probability(int prob, int sur);
///Renvoie le nombre en positif
float positif(int a);
///Cette fonction ne garde que les chiffres des unitées
long cutDizL(const long& l);
///Donne un mot dans une chaine
std::string getWord(ushort word_num, std::string &chaine);

///Uchronia noise namespace
namespace Unoise
{
    typedef std::array<unsigned short, 256> PermTable;

    ///Stocke une table de permutation "Diamond"
    struct DiamondPermTable
    {
        PermTable permTable;
        PermTable permPermTable;
    };

    ///Pas obligatoire, cette fonction permet de changer lambdaPermTable
    void setPermTable(PermTable* perm);

    void setSeed(int);

    ///On génère la table de permutation à partir d'un seed
    void genPermTable(PermTable*, int);

    ///Fonction du bruit de perlin (float x, float z, float resolution, table de permutation):
    float perlinNoise(float x, float z, float res, PermTable* perm=nullptr);

    ///Midpoint displacement noise, ou Diamond square noise (nom latin: carrus diamus)
    std::vector<std::vector<float>> DiamondSquareNoiseChunk(float x, float z, float res, ushort tailleArray=10, DiamondPermTable* perm=nullptr);
}


#endif // UTILITIES_H_INCLUDED
