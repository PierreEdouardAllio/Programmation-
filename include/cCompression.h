/*****************************************************************************/
/*                          DEPENDENCIES                                      */
/*****************************************************************************/

#ifndef CCOMPRESSION_H
#define CCOMPRESSION_H
#include <cmath>
#include <iostream>


class cCompression
{
/*****************************************************************************/
/*                          PRIVATE VARIABLES                                */
/*****************************************************************************/

    //! Largeur de l'image
    unsigned int mLargeur;
    //! Hauteur de l'image
    unsigned int mHauteur;
    //! Tableau repr�sentant l'image
    double **mBuffer;
    //! Facteur de qualit� de la conversion
    unsigned int mQualite=50;

    public:

/*****************************************************************************/
/*                         PUBLIC FUNCTIONS                                  */
/*****************************************************************************/

//! Constructeur de la classe
/**@brief
*   Cette fonction est le constructeur de la classe, elle permet de creer un objet cCompression a partir des parametres suivants
*
*@param[in] Largeur
*   unsigned int avec le valeur de la largeur de l'image en pixels
*@param[in] Hauteur
*   unsigned int avec le valeur de la hauteur de l'image en pixels
*@param[in] Image
*   tableau realise en allocation dynamique representant la valeur de chaque pixel de l'image
*@param[in] Qualite
*   unsigned int avec le valeur du taux de qualite de la compression
*/
cCompression(unsigned int Largeur, unsigned int Hauteur, double** Image, unsigned int Qualite)
{
    mLargeur=Largeur;
    mHauteur=Hauteur;
    mBuffer=Image;
    mQualite=Qualite;
}
//! Destructeur de la classe
/**@brief
*   Cette fonction est le destructeur de la classe, elle permet de liberer la memoire utilisee par l'allocation dynamique
*
*/
virtual ~cCompression()
{
    delete mBuffer;
}
//! Getteur de la largeur de l'image
/**@brief
*   Cette fonction est le getteur de la classe pour la variable privee mLargeur
*
*@retval unsigned int mLargeur
*   Largeur de l'image
*/
unsigned int GetLargeur()
{
    return mLargeur;
}
//! Getteur de la hauteur de l'image
//! Getteur de la largeur de l'image
/**@brief
*   Cette fonction est le getteur de la classe pour la variable privee mHauteur
*
*@retval unsigned int mHauteur
*   Hauteur de l'image
*/
unsigned int GetHauteur()
{
    return mHauteur;
}
//! Getteur de l'image
//! Getteur de la hauteur de l'image
//! Getteur de la largeur de l'image
/**@brief
*   Cette fonction est le getteur de la classe pour la variable privee mBuffer
*
*@retval double** mBuffer
*   Valeurs des pixels de l'image
*/
double** GetBuffer()
{
    return mBuffer;
}
//! Getteur de la qualite de l'image
//! Getteur de l'image
//! Getteur de la hauteur de l'image
//! Getteur de la largeur de l'image
/**@brief
*   Cette fonction est le getteur de la classe pour la variable privee mQualite
*
*@retval unsigned int mQualite
*   Qualite de la compression en pourcentage
*/
unsigned int GetQualite()
{
    return mQualite;
}
//! Setteur de la largeur de l'image
/**@brief
*   Cette fonction est le setteur de la classe pour la largeur
*
*@param[in] Largeur
*   unsigned int nouvelle valeur de la largeur de l'image en pixels
*/
void SetLargeur(unsigned int Largeur)
{
    mLargeur = Largeur;
}
//! Setteur de la hauteur de l'image
/**@brief
*   Cette fonction est le setteur de la classe pour la hauteur
*
*@param[in] Hauteur
*   unsigned int nouvelle valeur  de la hauteur de l'image en pixels
*/
void SetHauteur(unsigned int Hauteur)
{
    mHauteur = Hauteur;
}
//! Setteur de l'image
/**@brief
*   Cette fonction est le setteur de la classe pour le tableau representant l'image
*
*@param[in] Image
*   double** nouveau tableau avec les valeurs de chaque pixel pour une image donnee
*/
void SetBuffer(double** Image)
{
    mBuffer = Image;
}
//! Setteur de la qualite de l'image
/**@brief
*   Cette fonction est le setteur de la classe pour la qualite de la compression
*
*@param[in] Qualite
*   unsigned int nouvelle valeur de mQualite en pourcentage
*/
void SetQualite(unsigned int Qualite)
{
    mQualite = Qualite;
}
//! Calcul DCT du block 8x8
/**@brief
*   Cette fonction fait le calcul de la DCT pour un block8x8 venant de l'image
*
*@param[in] ImageInitiale
*    double** tableau avec les valeurs de chaque pixel pour un block8x8
*@param[out] ImageFinale
*    double** tableau avec les valeurs de chaque pixel apres la dct  pour un block8x8
*/
void Calcul_DCT_Block(double **ImageInitiale, double **ImageFinale)
{
    //Initialisation des variables
    double C[8]={(1/sqrt(2)),1,1,1,1,1,1,1}; //Tableau C(k)
    unsigned TailleBlock=8; //Taille du bloc
    double Somme;
    //Affichage de l'image initiale
    std::cout<<"DCT Input : "<<std::endl;
    for (unsigned i=0;i<TailleBlock;i++)
    {
        for(unsigned j=0;j<TailleBlock;j++)
        {
            std::cout<<" "<<ImageInitiale[i][j];
        }
        std::cout<<std::endl;
    }
    //Affichage de l'image transforme
    std::cout<<"DCT Transformation Valeurs(0->-128 | 255->127) : "<<std::endl;
    for (unsigned i=0;i<TailleBlock;i++)
    {
        for(unsigned j=0;j<TailleBlock;j++)
        {
            std::cout<<" "<<(ImageInitiale[i][j]-128);
        }
        std::cout<<std::endl;
    }
    for (unsigned  u=0; u<TailleBlock; u++)
    {
        for (unsigned  v=0; v<TailleBlock;v++)
        {
            for (unsigned  x=0; x<TailleBlock; x++) //Debut du calcul de la somme de x,y pour u,v donn�
            {
                for (unsigned y=0; y<TailleBlock; y++)
                {
                    Somme+=((ImageInitiale[x][y]-128)*cos(((2*x)+1)*M_PI*u/16)*cos(((2*y)+1)*M_PI*v/16));
                }
            } //Fin du calcul de somme x,y pour u,v donn�
            ImageFinale[u][v]=(C[u]*C[v]*Somme/4); //Calcul de P(u,v)
            Somme=0;
        }
    }
    //Affichage de l'image finale
    std::cout<<"DCT Output : "<<std::endl;
    for (unsigned i=0;i<TailleBlock;i++)
    {
        for(unsigned j=0;j<TailleBlock;j++)
        {
            std::cout<<" "<<ImageFinale[i][j];
        }
        std::cout<<std::endl;
    }
}
//! Calcul DCT inverse pour du block 8x8
/**@brief
*   Cette fonction fait le calcul de la DCT inverse pour un block8x8 apres DCT venant de l'image
*
*@param[in] ImageInitiale
*    double** tableau avec les valeurs de chaque pixel pour un block8x8 apres DCT
*@param[out] ImageFinale
*    double** tableau avec les valeurs de chaque pixel apres la DCT inverse pour un block8x8
*/
void Calcul_Inverse_DCT_Block(double **ImageInitiale, double **ImageFinale)
{
    //Initialisation de variables
    double C[8]={(1/sqrt(2)),1,1,1,1,1,1,1}; //Tableau C(k)
    unsigned TailleBlock=8; //Taille du bloc
    double Somme;
    //Affichage de l'image initiale
    std::cout<<"DCT Input : "<<std::endl;
    for (unsigned i=0;i<TailleBlock;i++)
    {
        for(unsigned j=0;j<TailleBlock;j++)
        {
            std::cout<<" "<<ImageInitiale[i][j];
        }
        std::cout<<std::endl;
    }
    for (unsigned  x=0; x<TailleBlock; x++)
    {
        for (unsigned  y=0; y<TailleBlock;y++)
        {
            for (unsigned  u=0; u<TailleBlock; u++) //Debut du calcul de la somme de u,v pour x,y donn�
            {
                for (unsigned v=0; v<TailleBlock; v++)
                {
                    Somme+=((ImageInitiale[u][v])*C[u]*C[v]*cos(((2*x)+1)*M_PI*u/16)*cos(((2*y)+1)*M_PI*v/16));
                }
            } //Fin du calcul de somme u,v pour x,y donn�
            ImageFinale[x][y]=round((Somme/4)+128); //Calcul de p(x,y)
            Somme=0;
        }
    }
    //Affichage de l'image finale
    std::cout<<"DCT Output : "<<std::endl;
    for (unsigned i=0;i<TailleBlock;i++)
    {
        for(unsigned j=0;j<TailleBlock;j++)
        {
            std::cout<<" "<<ImageFinale[i][j];
        }
        std::cout<<std::endl;
    }
}
//! Calcul de la quantification de l'image JPEG
/**@brief
*   Cette fonction fait le calcul de la quantification pour un block8x8 venant de l'image
*
*@param[in] ImageInitiale
*    double** tableau avec les valeurs de chaque pixel pour un block8x8
*@param[out] ImageFinale
*    double** tableau avec les valeurs de chaque pixel apres la quantification pour un block8x8
*/
void Calcul_Quant_JPEG(double** ImageInitiale, double**ImageFinale)
{
    //Intialisation des variables
    unsigned TailleBlock=8;
    unsigned int Lambda;
    //Creation de la matrice lambda
    if (mQualite<50)
    {
        Lambda=(5000/mQualite);
    }
    else
    {
        Lambda=(200-(2*mQualite));
    }
    //Creation du tableau de reference en allocation dynamique
    double Qx[8][8]={{16, 11, 10, 16, 24, 40, 51, 61},{12, 12, 14, 19, 26, 58, 60, 55}
    ,{14, 13, 16, 24, 40, 57, 69, 56},{14, 17, 22, 29, 51, 87, 80, 62},{18, 22, 37, 56, 68, 109, 103, 77}
    ,{24, 35, 55, 64, 81, 104, 113, 92},{49, 64, 78, 87, 103, 121, 120, 101},{72, 92, 95, 98, 112, 100, 103, 99}};
    double ** Q;
    Q=new double *[8];
    for (unsigned i=0;i<8;i++)
    {
        Q[i]=new double[8];
        for (unsigned j=0;j<8;j++)
        {
            Q[i][j]=Qx[i][j];
        }
    }
    //Creation du tableau de quantification en allocation dynamique
    double ** QTab;
    QTab=new double *[8];
    for (unsigned i=0;i<8;i++)
    {
        QTab[i]=new double[8];
        for (unsigned j=0;j<8;j++)
        {
            if ((((Q[i][j]*Lambda)+50)/100)<1)
            {
                QTab[i][j]=1;

            }
            else if ((((Q[i][j]*Lambda)+50)/100)>255)
            {
                QTab[i][j]=255;
            }
            else
            {
                QTab[i][j]=int(((Q[i][j]*Lambda)+50)/100);
            }

        }
    }
    //Affichage de l'image initiale
    std::cout<<"Quantification Input : "<<std::endl;
    for (unsigned i=0;i<TailleBlock;i++)
    {
        for(unsigned j=0;j<TailleBlock;j++)
        {
            std::cout<<" "<<ImageInitiale[i][j];
        }
        std::cout<<std::endl;
    }
    //Affichage du tableau de reference
    std::cout<<"Quantification Reference : "<<std::endl;
    for (unsigned i=0;i<TailleBlock;i++)
    {
        for(unsigned j=0;j<TailleBlock;j++)
        {
            std::cout<<" "<<Q[i][j];
        }
        std::cout<<std::endl;
    }
    //Affichage du tableau de quantification
    std::cout<<"Quantification Table : "<<std::endl;
    for (unsigned i=0;i<TailleBlock;i++)
    {
        for(unsigned j=0;j<TailleBlock;j++)
        {
            std::cout<<" "<<QTab[i][j];
        }
        std::cout<<std::endl;
    }
    //Calcul de l'image quantifie
    for (unsigned u=0;u<8;u++)
    {
        for(unsigned v=0;v<8;v++)
        {
            ImageFinale[u][v]=(round(ImageInitiale[u][v]/QTab[u][v]));
        }
    }
    //Affichage de l'image finale
    std::cout<<"Quantification Output : "<<std::endl;
    for (unsigned i=0;i<TailleBlock;i++)
    {
        for(unsigned j=0;j<TailleBlock;j++)
        {
            std::cout<<" "<<ImageFinale[i][j];
        }
        std::cout<<std::endl;
    }
}
//! Calcul de la quantification inverse de l'image JPEG
/**@brief
*   Cette fonction fait le calcul de la dequantification pour un block8x8 venant de l'image
*
*@param[in] ImageInitiale
*    double** tableau avec les valeurs de chaque pixel pour un block8x8 apres quantification
*@param[out] ImageFinale
*    double** tableau avec les valeurs de chaque pixel apres la dequantification pour un block8x8
*/
void Calcul_Inverse_Quant_JPEG(double** ImageInitiale, double** ImageFinale)
{
 //Intialisation des variables
    unsigned TailleBlock=8;
    unsigned int Lambda;
    //Creation de la matrice lambda
    if (mQualite<50)
    {
        Lambda=(5000/mQualite);
    }
    else
    {
        Lambda=(200-(2*mQualite));
    }
    //Creation du tableau de reference en allocation dynamique
    double Qx[8][8]={{16, 11, 10, 16, 24, 40, 51, 61},{12, 12, 14, 19, 26, 58, 60, 55}
    ,{14, 13, 16, 24, 40, 57, 69, 56},{14, 17, 22, 29, 51, 87, 80, 62},{18, 22, 37, 56, 68, 109, 103, 77}
    ,{24, 35, 55, 64, 81, 104, 113, 92},{49, 64, 78, 87, 103, 121, 120, 101},{72, 92, 95, 98, 112, 100, 103, 99}};
    double ** Q;
    Q=new double *[8];
    for (unsigned i=0;i<8;i++)
    {
        Q[i]=new double[8];
        for (unsigned j=0;j<8;j++)
        {
            Q[i][j]=Qx[i][j];
        }
    }
    //Creation du tableau de quantification en allocation dynamique
    double ** QTab;
    QTab=new double *[8];
    for (unsigned i=0;i<8;i++)
    {
        QTab[i]=new double[8];
        for (unsigned j=0;j<8;j++)
        {
            if ((((Q[i][j]*Lambda)+50)/100)<1)
            {
                QTab[i][j]=1;

            }
            else if ((((Q[i][j]*Lambda)+50)/100)>255)
            {
                QTab[i][j]=255;
            }
            else
            {
                QTab[i][j]=int(((Q[i][j]*Lambda)+50)/100);
            }

        }
    }
    //Affichage de l'image initiale
    std::cout<<"Dequantification Input : "<<std::endl;
    for (unsigned i=0;i<TailleBlock;i++)
    {
        for(unsigned j=0;j<TailleBlock;j++)
        {
            std::cout<<" "<<ImageInitiale[i][j];
        }
        std::cout<<std::endl;
    }
    //Affichage du tableau de reference
    std::cout<<"Quantification Reference : "<<std::endl;
    for (unsigned i=0;i<TailleBlock;i++)
    {
        for(unsigned j=0;j<TailleBlock;j++)
        {
            std::cout<<" "<<Q[i][j];
        }
        std::cout<<std::endl;
    }
    //Affichage du tableau de quantification
    std::cout<<"Quantification Table : "<<std::endl;
    for (unsigned i=0;i<TailleBlock;i++)
    {
        for(unsigned j=0;j<TailleBlock;j++)
        {
            std::cout<<" "<<QTab[i][j];
        }
        std::cout<<std::endl;
    }
    //Calcul de l'image dequantifie
    for (unsigned u=0;u<8;u++)
    {
        for(unsigned v=0;v<8;v++)
        {
            ImageFinale[u][v]=(round(ImageInitiale[u][v]*QTab[u][v]));
        }
    }
    //Affichage de l'image finale
    std::cout<<"Dequantification Output : "<<std::endl;
    for (unsigned i=0;i<TailleBlock;i++)
    {
        for(unsigned j=0;j<TailleBlock;j++)
        {
            std::cout<<" "<<ImageFinale[i][j];
        }
        std::cout<<std::endl;
    }
}
//! Calcul de l'erreur quadratique moyenne entre l'image initiale et l'image finale
/**@brief
*   Cette fonction fait le calcul du Ecart Quadratique Moyen entre une image apres la DCT inverse et une image avant la DCT
*
*@param[in] ImageInitiale
*    double** tableau avec les valeurs de chaque pixel apres DCT inverse pour un block8x8
*@retval ResultatEQM
*    double valeur du Ecart Quadratique Moyen
*/
double EQM (double **ImageInitiale)
{
//Initialisation des variables
double ResultatEQM;
double SommeEQM;
double N=64;
//Calcul de la somme de la difference (avant/apres)
for (unsigned i=0;i<8;i++)
{
    for (unsigned j=0;j<8;j++)
    {
        SommeEQM+=(((ImageInitiale[i][j])-(mBuffer[i][j]))*((ImageInitiale[i][j])-(mBuffer[i][j])));
    }
}
//Division de la somme par le nombre total des valeurs
ResultatEQM=round(SommeEQM/N);
return ResultatEQM;
}
//! Calcul du taux de compression entre l'image initiale et l'image finale
/**@brief
*   Cette fonction fait le calcul du taux de compression entre une image sans traitements et une image apres quantification
*
*@param[in] ImageInitiale
*    double** tableau avec les valeurs de chaque pixel pour un block8x8
*@retval ResultatTaux
*    double valeur du taux de compression
*/
double TauxCompression(double** ImageInitiale)
{
//Initialisation des variables
double CoeffsInit,CoeffsBuffer;
double ResultatTaux;
//Calcul du nombre de coefficients
for (unsigned x=0;x<8;x++)
{
    for (unsigned y=0;y<8;y++)
    {
        if (ImageInitiale[x][y]!=0)
        {
            CoeffsInit+=1;
        }
        if (mBuffer[x][y]!=0)
        {
            CoeffsBuffer+=1;
        }
    }
}
//Calcul du taux de compression
ResultatTaux=int(100-((CoeffsInit*100)/CoeffsBuffer));
return ResultatTaux;
}
//!Run-Lenght Encoding
/**@brief
*   Cette fonction rassemble en paquets les symboles d�un signal qui, tout � la fois se suivent et sont
identiques.
*
*@param[in] ImageInitiale
*    double** tableau avec les valeurs de chaque pixel pour un block8x8
*@param[in] DC_precedent
*    int valeur[0][0] du block8x8 quantifie precedent
*@param[out] ListeRLE
*    double* liste avec les resultats de la RLE
*/
void RLE_Block(double** ImageInitiale,int DC_precedent,double* ListeRLE)
{
//Variables
unsigned k=2;
unsigned i=0;
unsigned z=1;
unsigned zeros=0;
unsigned offset=0;
ListeRLE[0]=double(DC_precedent);
//Algorithme de deplacement en diagonale
for (k=2;k<=8;k++)
{
    for(i=0;i<k;i++)
    {
        if ((k%2)==0)
        {
            if(ImageInitiale[i][k-i-1]==0)
            {
                zeros++;
            }
            else
            {
                ListeRLE[z]=zeros;
                ListeRLE[z+1]=ImageInitiale[i][k-i-1];
                zeros=0;
                z=z+2;
            }
        }
        else
        {
            if(ImageInitiale[k-i-1][i]==0)
            {
                zeros++;
            }
            else
            {
                ListeRLE[z]=zeros;
                ListeRLE[z+1]=ImageInitiale[k-i-1][i];
                zeros=0;
                z=z+2;
            }
        }
    }
}
for (offset=1;offset<=7;offset++)
{
    for (i=offset;i<8;i++)
    {
        if ((offset%2)==0)
        {
            if(ImageInitiale[i][7-i+offset]==0)
            {
                zeros++;
            }
            else
            {
                ListeRLE[z]=zeros;
                ListeRLE[z+1]=ImageInitiale[i][7-i+offset];
                zeros=0;
                z=z+2;
            }
        }
        else
        {
            if(ImageInitiale[7-i+offset][i]==0)
            {
                zeros++;
            }
            else
            {
                ListeRLE[z]=zeros;
                ListeRLE[z+1]=ImageInitiale[7-i+offset][i];
                zeros=0;
                z=z+2;
            }
        }
    }
}
if(zeros>0)
{
ListeRLE[z]=0;
ListeRLE[z+1]=0;
z=z+2;
}

std::cout<<"RLE : "<<std::endl;
    for (unsigned a=0;a<8;a++)
    {
        for(unsigned b=0;b<8;b++)
        {
            std::cout<<" "<<(ImageInitiale[a][b]);
        }
        std::cout<<std::endl;
    }
std::cout<<"Liste RLE : "<<std::endl;
    for (unsigned a=0;a<z;a++)
    {
        std::cout<<ListeRLE[a]<<" ";
    }
    std::cout<<std::endl;
}
void RLE(double* ListeFinale)
{
    //Dynamic Allocation de blocs 8x8
    double *** Block8x8 = new double**[((mHauteur/8)*(mHauteur/8))];
    for (unsigned x=0;x<((mHauteur/8)*(mHauteur/8));x++)
    {
        Block8x8[x]=new double*[8];
        for (unsigned y=0;y<8;y++)
        {
            Block8x8[x][y]=new double[8];
        }
    }
    double ** Output;
    Output=new double *[8];
    for (unsigned i=0;i<8;i++)
    {
       Output[i]=new double[8];
       for (unsigned j=0;j<8;j++)
       {
           Output[i][j]=mBuffer[i][j];
       }
    }
    double ** ListeInter;
    ListeInter=new double *[8];
    unsigned decalagey=0;
    unsigned decalagez=0;
    unsigned decalageL=0;
    for (unsigned i=0;i<((mHauteur/8)*(mHauteur/8));i++)
    {
       ListeInter[i]=new double[100];
    }
    for (unsigned x=0;x<((mHauteur/8)*(mHauteur/8));x++)
    {
        for (unsigned y=decalagey;y<8+decalagey;y++)
        {
            for (unsigned z=decalagez;z<8+decalagez;z++)
            {
                Block8x8[x][y-decalagey][z-decalagez]=mBuffer[y][z];
            }
        }
        if (decalagey<mHauteur-8)
        {
            decalagey+=8;
        }
        if (decalagey==mHauteur-8)
        {
            decalagez+=8;
            decalagey=0;
        }
    }
    for (unsigned i=0;i<((mHauteur/8)*(mHauteur/8));i++)
    {
        Calcul_DCT_Block(Block8x8[i],Output);
        Calcul_Quant_JPEG(Output,Block8x8[i]);
        int DC_precedent=int(Block8x8[i][0][0]);
        RLE_Block(Block8x8[i],DC_precedent,ListeInter[i]);
    }
    for (unsigned i=0;i<((mHauteur/8)*(mHauteur/8));i++)
    {
        for (unsigned j=0;j<20;j++)
        {
            ListeFinale[j+decalageL]=ListeInter[i][j];
        }
        decalageL+=20;
    }
}







    protected:

    private:
};

#endif // CCOMPRESSION_H