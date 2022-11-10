#ifndef CCOMPRESSION_H
#define CCOMPRESSION_H
#include <cmath>
#include <iostream>


class cCompression
{
    //! Largeur de l'image
    unsigned int mLargeur;
    //! Hauteur de l'image
    unsigned int mHauteur;
    //! Tableau représentant l'image
    double **mBuffer;
    //! Facteur de qualité de la conversion
    unsigned int mQualite=50;

    public:
        //! Constructeur de la classe
        cCompression(unsigned int Largeur, unsigned int Hauteur, double** Image, unsigned int Qualite)
        {
            mLargeur=Largeur;
            mHauteur=Hauteur;
            mBuffer=Image;
            mQualite=Qualite;
        }
        //! Destructeur de la classe
        virtual ~cCompression()
        {
            delete mBuffer;
        }
        //! Getteur de la largeur de l'image
        unsigned int GetLargeur()
        {
            return mLargeur;
        }
        //! Getteur de la hauteur de l'image
        unsigned int GetHauteur()
        {
            return mHauteur;
        }
        //! Getteur de l'image
        double** GetBuffer()
        {
            return mBuffer;
        }
        //! Getteur de la qualite de l'image
        unsigned int GetQualite()
        {
            return mQualite;
        }
        //! Setteur de la largeur de l'image
        void SetLargeur(unsigned int Largeur)
        {
            mLargeur = Largeur;
        }
        //! Setteur de la hauteur de l'image
        void SetHauteur(unsigned int Hauteur)
        {
            mHauteur = Hauteur;
        }
        //! Setteur de l'image
        void SetBuffer(double** Image)
        {
            mBuffer = Image;
        }
        //! Setteur de la qualite de l'image
        void SetQualite(unsigned int Qualite)
        {
            mQualite = Qualite;
        }
        //! Calcul DCT du block 8x8
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
                    for (unsigned  x=0; x<TailleBlock; x++) //Debut du calcul de la somme de x,y pour u,v donné
                    {
                        for (unsigned y=0; y<TailleBlock; y++)
                        {
                            Somme+=((ImageInitiale[x][y]-128)*cos(((2*x)+1)*M_PI*u/16)*cos(((2*y)+1)*M_PI*v/16));
                        }
                    } //Fin du calcul de somme x,y pour u,v donné
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
                    for (unsigned  u=0; u<TailleBlock; u++) //Debut du calcul de la somme de u,v pour x,y donné
                    {
                        for (unsigned v=0; v<TailleBlock; v++)
                        {
                            Somme+=((ImageInitiale[u][v])*C[u]*C[v]*cos(((2*x)+1)*M_PI*u/16)*cos(((2*y)+1)*M_PI*v/16));
                        }
                    } //Fin du calcul de somme u,v pour x,y donné
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
    void RLE_Block(double** ImageInitiale)
    {
        int a=0;
        int b=0;
        for (int i=0;i<3;i++)
            {
            if (a==0)
                {
                std::cout<<"C0"<<std::endl;
                for (int x=a;x<=a+b+1;x++)
                {

                    for (int y=a+b+1;y>=a;y--)
                    {
                        std::cout<<x<<y<<std::endl;
                    }
                }
                a=1;
                }
            if (a==1)
                {
                    std::cout<<"C1"<<std::endl;
                    a=2;
                }
            if (a==2)
                {
                    std::cout<<"C2"<<std::endl;
                    for (int x=a+b;x>=0;x--)
                    {

                        for (int y=0;y<=a+b;y++)
                        {

                        }
                    }
                    a=3;
                }
            if (a==3)
                {
                    std::cout<<"C3"<<std::endl;
                    b+=2;
                    a=0;
                }
            }
    }





    protected:

    private:
};

#endif // CCOMPRESSION_H
