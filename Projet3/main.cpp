#include <iostream>
#include"cCompressionF.h"

using namespace std;

int main()
{
    void affichage1D(double* Element, unsigned Taille, string Titre);
    void affichage2D(double** Element, unsigned Taille, string Titre);
    unsigned TailleBlock = 8;
    unsigned TailleImage = 16;
    //Block8x8 exemple
    double B[TailleBlock][TailleBlock]={{139, 144, 149, 153, 155, 155, 155, 155},{144, 151, 153, 156, 159, 156, 156, 156},{150, 155, 160, 163, 158, 156, 156, 156}
    ,{159, 161, 162, 160, 160, 159, 159, 159},{159, 160, 161, 162, 162, 155, 155, 155},{161, 161, 161, 161, 160, 157, 157, 157}
    ,{162, 162, 161, 163, 162, 157, 157, 157},{162, 162, 161, 161, 163, 158, 158, 158}};
    //Block16x16 exemple
    double R[TailleImage][TailleImage]={{139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},{139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},
    {139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},{139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},
    {139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},{139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},
    {139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},{139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},
    {139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},{139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},
    {139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},{139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},
    {139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},{139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},
    {139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},{139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155}};
    //Dynamic Allocation Image Initiale
    double ** ImageInit;
    ImageInit=new double *[TailleBlock];
    for (unsigned i=0;i<TailleBlock;i++)
    {
       ImageInit[i]=new double[TailleBlock];
       for (unsigned j=0;j<TailleBlock;j++)
       {
           ImageInit[i][j]=B[i][j];
       }
    }
    //Dynamic Allocation Image DCT
    double ** ImageDCT;
    ImageDCT=new double *[TailleBlock];
    for (unsigned i=0;i<TailleBlock;i++)
    {
       ImageDCT[i]=new double[TailleBlock];
       for (unsigned j=0;j<TailleBlock;j++)
       {
           ImageDCT[i][j]=0;
       }
    }
    //Dynamic Allocation Image Quantification
    double ** ImageQUANT;
    ImageQUANT=new double *[TailleBlock];
    for (unsigned i=0;i<TailleBlock;i++)
    {
       ImageQUANT[i]=new double[TailleBlock];
       for (unsigned j=0;j<TailleBlock;j++)
       {
           ImageQUANT[i][j]=0;
       }
    }
    //Dynamic Allocation Image Dequantification
    double ** ImageDEQUANT;
    ImageDEQUANT=new double *[TailleBlock];
    for (unsigned i=0;i<TailleBlock;i++)
    {
       ImageDEQUANT[i]=new double[TailleBlock];
       for (unsigned j=0;j<TailleBlock;j++)
       {
           ImageDEQUANT[i][j]=0;
       }
    }
    //Dynamic Allocation Image DCT Inverse
    double ** ImageDEDCT;
    ImageDEDCT=new double *[TailleBlock];
    for (unsigned i=0;i<8;i++)
    {
       ImageDEDCT[i]=new double[TailleBlock];
       for (unsigned j=0;j<TailleBlock;j++)
       {
           ImageDEDCT[i][j]=0;
       }
    }
    //Dynamic Allocation Image RLE
    double ** ImageRLE;
    ImageRLE=new double *[TailleImage];
    for (unsigned i=0;i<TailleBlock;i++)
    {
       ImageRLE[i]=new double[TailleImage];
       for (unsigned j=0;j<TailleBlock;j++)
       {
           ImageRLE[i][j]=1;
       }
    }
    //Dynamic Allocation Liste RLE
    double* Liste=new double[500];

    //Fonctions de compression (I/O)
    /*
    cCompression A(8,8,ImageInit,50);
    A.Calcul_DCT_Block(ImageInit,ImageDCT);
    A.Calcul_Quant_JPEG(ImageDCT,ImageQUANT);
    A.Calcul_Inverse_Quant_JPEG(ImageQUANT,ImageDEQUANT);
    A.Calcul_Inverse_DCT_Block(ImageDEQUANT,ImageDEDCT);
    double X,Y;
    X=A.EQM(ImageDEDCT);
    std::cout<<"EQM : "<<X<<std::endl;
    Y=A.TauxCompression(ImageQUANT);
    std::cout<<"Taux de conversion : "<<Y<<" % "<<std::endl;
    int DC_Precedent = int(ImageQUANT[0][0]);
    A.RLE_Block(ImageQUANT,DC_Precedent, Liste);
    */

    unsigned TListe;
    string Titre1="Liste_RLE";
    string Titre2="Image_Initiale";
    cCompressionF A(8,8,ImageInit,50);
    cCompressionF F(TailleBlock,TailleBlock,ImageInit,50);
    TListe=F.RLE(Liste);
    affichage2D(ImageInit,TailleBlock,Titre2);
    affichage1D(Liste,TListe,Titre1);
    return 0;
}
void affichage2D(double** Element, unsigned Taille, string Titre)
    {
        std::cout<<Titre<<std::endl;
        for(unsigned i=0;i<Taille;i++)
        {
            for(unsigned j=0;j<Taille;j++)
            {
                std::cout<<Element[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
    }
void affichage1D(double* Element, unsigned Taille, string Titre)
{
     std::cout<<Titre<<std::endl;
    for(unsigned i=0;i<Taille;i++)
    {
        std::cout<<Element[i]<<" ";
    }
    std::cout<<std::endl;
}
