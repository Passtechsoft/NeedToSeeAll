#include "utilities.h"
#include <math.h>
#include <cstdlib>

long cutDizL(const long& l){
    return l/(10*(long)(l/10));
}

namespace Uchronia{class ZChunk;}

using namespace std;

bool probability(int prob, int sur)
{
    return RAND(0, sur)<=prob;
}

string getWord(ushort word_num, string &chaine)
{
        string word;
        int compteur=0;
        for(unsigned int c=0; c!=chaine.size(); c++)
        {
                if(compteur==word_num-1)
                        word.push_back(chaine[c]);
                else if(compteur>=word_num)
                        break;

                if(chaine[c]==' ')
                        compteur++;
        }
        if(word.empty())
                WARNING("10::: le mot demandé (n°"<<word_num<<") est introuvable.");
        return word;
}

float positif(int a)
{
    if(a<0)
        return a*-1;
    return a;
}

namespace Unoise
{
    PermTable* lambdaPermTable=nullptr;//La table de permutation de base
    DiamondPermTable* lambdaDiamsPermTable=nullptr;
    int seed=0;//Le seed!!!

    void setSeed(int graine)
    {
        seed=graine;
        srand(seed);
    }

    void setPermTable(PermTable* perm)
        {lambdaPermTable=perm;}


    /// \param pttable pointeur via une table de permutation qui sera générée avec le seed
    /// \param seed le seed
    void genPermTable(PermTable* pttable, int seed)
    {
        cout<<"9:::      Génération d'une table de permutation"<<endl;
        srand(seed);//on utilise un seed avec la méthode srand

        unsigned short buffer;
        bool finish=false;
        //On crée toutes les 256 cases de la table de permutation
        for(unsigned short c=0;c!=256;c++)
        {
            //Tant qu'on a pas trouvé un nombre qui n'est pas dans la liste
            while(!finish)
            {
                finish = true;//Alors on a pas fini
                buffer = rand() % (255 + 1);//On calcul un nouveau nombre

                //Tant qu'on est pas arrivé au nombre qu'on est sensé calculer actuellement:
                for(unsigned short d=0; d!=c; d++){
                    if(buffer == pttable->at(d))//Si par malheur on a déjà généré ce nombre
                        finish = false;//On recommence
                }

                if(finish == true)//En revanche si tout va au mieux
                    pttable->at(c) = buffer;//On donne la valeur générée à la case du tableau qu'on cherchait à remplir
            }
            finish=false;
        }
    }

    /*//s'appuyant sur le bruit de perlin, cet algo va génerer sur une zone memoire donnée un bruit du modpoint displacement
    std::vector<std::vector<float>> DiamondSquareNoiseChunk(float x, float z, float res, ushort tailleArray, DiamondPermTable* perm)
    {
        if(perm==nullptr)
        {
            if(lambdaDiamsPermTable==nullptr){
                lambdaDiamsPermTable=new DiamondPermTable;
                genPermTable(&lambdaDiamsPermTable->permPermTable, seed);
                genPermTable(&lambdaDiamsPermTable->permTable, seed);
            }
            perm=lambdaDiamsPermTable;
        }

        if(!DIVISIBLE_PAR(tailleArray, 2.f))
                CRITIC_ERROR("7::: Diamond square noise: vouss nous avez donné une taille  on multiple de 2! chalauds!");

        for(int c=0; c!=tailleArray; c++)
        {

        }
        //return 0;
    }*/

    /**
    * \param x La position X
    * \param y La position Z
    * \param res La douceur du terrain
    * \param perm Le pointeur vers la table de permutation
    * \warning La fonction est défective
    */
    float perlinNoise(float x, float y, float res, PermTable *perm)
    {
        if(perm==nullptr)
        {
            if(lambdaPermTable==nullptr){
                lambdaPermTable=new PermTable;
                genPermTable(lambdaPermTable, seed);
            }
            perm=lambdaPermTable;
        }

        float tempX,tempY;
        int x0,y0,ii,jj,gi0,gi1,gi2,gi3;
        float unit = 1.0f/sqrt(2);
        float tmp,s,t,u,v,Cx,Cy,Li1,Li2;
        float gradient2[][2] = {{unit,unit},{-unit,unit},{unit,-unit},{-unit,-unit},{1,0},{-1,0},{0,1},{0,-1}};

        //Adapter pour la résolution
        x /= res;
        y /= res;

        //On récupère les positions de la grille associée à (x,y)
        x0 = (int)(x);
        y0 = (int)(y);

        //Masquage
        ii = x0 & 255;
        jj = y0 & 255;

        //Pour récupérer les vecteurs
        gi0 = perm->at(ii + perm->at(jj)) % 8;
        gi1 = perm->at(ii + 1 + perm->at(jj)) % 8;
        gi2 = perm->at(ii + perm->at(jj + 1)) % 8;
        gi3 = perm->at(ii + 1 + perm->at(jj + 1)) % 8;

        //on récupère les vecteurs et on pondère
        tempX = x-x0;
        tempY = y-y0;
        s = gradient2[gi0][0]*tempX + gradient2[gi0][1]*tempY;

        tempX = x-(x0+1);
        tempY = y-y0;
        t = gradient2[gi1][0]*tempX + gradient2[gi1][1]*tempY;

        tempX = x-x0;
        tempY = y-(y0+1);
        u = gradient2[gi2][0]*tempX + gradient2[gi2][1]*tempY;

        tempX = x-(x0+1);
        tempY = y-(y0+1);
        v = gradient2[gi3][0]*tempX + gradient2[gi3][1]*tempY;


        //Lissage
        tmp = x-x0;
        Cx = 3 * tmp * tmp - 2 * tmp * tmp * tmp;

        Li1 = s + Cx*(t-s);
        Li2 = u + Cx*(v-u);

        tmp = y - y0;
        Cy = 3 * tmp * tmp - 2 * tmp * tmp * tmp;

        return Li1 + Cy*(Li2-Li1);
    }
}


