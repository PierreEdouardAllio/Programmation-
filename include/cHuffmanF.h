/*****************************************************************************/
/*                          DEPENDENCIES                                     */
/*****************************************************************************/
#ifndef CHUFFMANF_H
#define CHUFFMANF_H
#include <iostream>
#include<vector>
#include<queue>
#include<stdio.h>
#include<string.h>

struct sNoeud {
/*****************************************************************************/
/*                          PRIVATE VARIABLES                                */
/*****************************************************************************/
    //! Donnée qui est codée
    double mdonnee;
    //! Frequence de la donnée
    double mfreq;
    //! Noeud gauche
    sNoeud *mgauche;
    //! Noeud droit
    sNoeud *mdroite;
/*****************************************************************************/
/*                         PUBLIC FUNCTIONS                                  */
/*****************************************************************************/

//! Constructeur de la structure
/**@brief
*   Cette fonction est le constructeur de la structure, elle permet de creer une structure sNoeud
*
*@param[in] d
*   char avec la valeur de la donnée
*@param[in] f
*   double avec la valeur de la fréquence de la donnée
*/
sNoeud(double d, double f)
{
mgauche=nullptr;
mdroite=nullptr;
this->mdonnee =d;
this->mfreq=f;
}
};
struct compare {
/*****************************************************************************/
/*                         PUBLIC FUNCTIONS                                  */
/*****************************************************************************/

//! Operateur ()
/**@brief
*   Cette fonction est une surdefinition du operateur () pour la structure sNoeud
*@param[in] Noeud gauche
*   sNoeud gauche
*@param[in] Noeud droite
*   sNoeud droite
*@retval sNoeud
*   La valeur la plus grande des sNoeud
*/
bool operator ()(sNoeud* gauche, sNoeud* droite)
{
    return gauche->mfreq > droite->mfreq;
}
};
class cHuffmanF
{
/*****************************************************************************/
/*                          PRIVATE VARIABLES                                */
/*****************************************************************************/
    //! Trame du codage
    double* mTrame;
    //! Longueur de la trame
    double mLongueur;
    //! Racine du sNoeud
    sNoeud* mRacine;
/*****************************************************************************/
/*                         PUBLIC FUNCTIONS                                  */
/*****************************************************************************/
    public:
//! Constructeur de la classe
/**@brief
*   Cette fonction est le constructeur de la classe, elle permet de creer un objet cHuffman à partir des parametres suivants
*
*@param[in] Trame
*   char* Trame du codage
*@param[in] Longueur
*   double Longueur de la trame
*@param[in] Racine
*   sNoeud Racine de la structure sNoeud
*/
cHuffmanF(double* Trame, double Longueur)
{
    mTrame=Trame;
    mLongueur=Longueur;
}
//! Destructeur de la classe
/**@brief
*   Cette fonction est le destructeur de la classe, elle permet de liberer la memoire utilisee par l'allocation dynamique
*/
virtual ~cHuffmanF()
{
    delete mTrame;
    delete mRacine;
}
//! Setteur de la trame de codage
/**@brief
*   Cette fonction est le setteur de la classe pour la trame
*
*@param[in] Trame
*   char* Trame de codage
*/
void SetDonnee(double *Trame)
{
    mTrame=Trame;
}
//! Setteur de la longeur de la trame
/**@brief
*   Cette fonction est le setteur de la classe pour la longeur de la trame de codage
*
*@param[in] Longeur
*   double longueur de la trame de codage
*/
void SetLongeur(double Longueur)
{
    mLongueur=Longueur;
}
//! Setteur de la racine du sNoeud
/**@brief
*   Cette fonction est le setteur de la classe pour la racine du sNoeud
*
*@param[in] Racine
*   sNoeud* Racine du sNoeud
*/
void SetRacine(sNoeud* Racine)
{
    mRacine=Racine;
}
//! Getteur de la trame de codage
/**@brief
*   Cette fonction est le getteur de la classe pour la variable privee mTrame
*
*@retval char* mTrame
*   Trame de codage
*/
double* GetDonnee(double *Trame)
{
    return mTrame;
}
//! Getteur de la longueur de la trame de codage
/**@brief
*   Cette fonction est le getteur de la classe pour la variable privee mLongueur
*
*@retval double mLongueur
*   Longueur de la trame de codage
*/
double GetLongeur(double Longueur)
{
    return mLongueur;
}
//! Getteur de la racine du sNoeud
/**@brief
*   Cette fonction est le getteur de la classe pour la variable privee mRacine
*
*@retval sNoeud* mRacine
*   Racine du sNoeud
*/
sNoeud* GetRacine(sNoeud* Racine)
{
    return mRacine;
}
//! Creation de l'arbre de Huffman
/**@brief
*   Cette fonction est le constructeur de l'arbre, elle permet de creer un arbre de cHuffman à partir des parametres suivants
*
*@param[in] Donnee
*   char* Donnees à coder
*@param[in] Frequence
*   double* Frequence des donnees
*@param[in] Taille
*   unsigned int Taille du tableau des donnees et frequences
*/
void HuffmanCodes(double* Donnee,double* Frequence, unsigned int Taille)
{
    sNoeud* Droite;
    sNoeud* Gauche;

    std::priority_queue<sNoeud*, std::vector<sNoeud*>, compare>queue;
    for (unsigned int i=0;i<Taille;i++)
    {
        sNoeud* Noeud=new sNoeud(Donnee[i], Frequence[i]);
        queue.push(Noeud);
    }
    for (unsigned int j=0;j<Taille-1;j++)
    {
         Gauche=queue.top();
         queue.pop();
         Droite=queue.top();
         queue.pop();
         sNoeud* NoeudN = new sNoeud(0, Gauche->mfreq + Droite->mfreq);
         NoeudN->mdroite = Droite;
         NoeudN->mgauche = Gauche;
         queue.push(NoeudN);
    }
    mRacine=queue.top();
    std::cout<<"Affichage Huffman"<<std::endl;
    unsigned ListeBinaire[5];
    HuffmanAffiche(mRacine,ListeBinaire,0);

}
//! Affichage de l'arbre de Huffman
/**@brief
*   Cette fonction affiche les valeurs issue du codage de huffman.
*
*@param[in] Leaf
*   sNoeud* Partie de l'arbre
*@param[out] binaire
*   unsigned Codage en binaire des donnees
*@param[in] profondeur
*   unsigned Profondeur dans l'arbre de huffman
*/
void HuffmanAffiche(struct sNoeud* Leaf,unsigned binaire[],unsigned profondeur)
{

    if(Leaf->mgauche !=nullptr)
    {
        binaire[profondeur]=0;
        HuffmanAffiche(Leaf->mgauche,binaire,profondeur+1);
    }
    if(Leaf->mdroite !=nullptr)
    {
        binaire[profondeur]=1;
        HuffmanAffiche(Leaf->mdroite,binaire,profondeur+1);
    }

    std::cout<<" D :"<<Leaf->mdonnee<<" F :"<<Leaf->mfreq<<std::endl;
    for (unsigned i=0;i<profondeur;i++)
    {
        std::cout<<binaire[i];
    }
    std::cout<<std::endl;
}


    protected:

    private:
};

#endif // CHUFFMANF_H
