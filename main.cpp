#include <iostream>
#include<fstream>
#include"cCompressionF.h"
#include"cHuffmanF.h"

using namespace std;

int main()
{
    void affichage1D(double* Element, unsigned Taille, string Titre);
    void affichage2D(double** Element, unsigned Taille, string Titre);
    void LectureImage (string Titre,double** Block,unsigned TailleB);
    unsigned TailleBlock = 8;
    unsigned TailleImage = 16;
    unsigned TailleFinal = 64;
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
           ImageRLE[i][j]=R[i][j];
       }
    }
    //Dynamic Allocation Liste RLE
    double* Liste1=new double[10000];
    double* Liste2=new double[10000];
    for (unsigned i=0;i<10000;i++)
    {
        Liste1[i]=0;
        Liste2[i]=0;
    }

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
    double** Image;
    Image=new double*[TailleFinal];
    for (unsigned i=0;i<TailleFinal;i++)
    {
       Image[i]=new double[TailleFinal];
       for (unsigned j=0;j<TailleFinal;j++)
       {
           Image[i][j]=0;
       }
    }
    //Essaies Compression
    unsigned TListe1=0;
    unsigned THisto1=0;
    unsigned TListe2=0;
    unsigned THisto2=0;
    string Titre1="Liste_RLE";
    string Titre2="Image_Initiale";
    double Frequence1[1000];
    double Donnee1[1000];
    double Frequence2[1000];
    double Donnee2[1000];
    /*
    cCompressionF F(TailleBlock,TailleBlock,ImageRLE,50);
    TListe1=F.RLE(Liste1);
    std::cout<<"Taille RLE : "<<TListe1<<std::endl;
    affichage2D(ImageInit,TailleBlock,Titre2);
    affichage1D(Liste1,TListe1,Titre1);
    //Essaies avec huffman
    double X[6]={5,3,7,1,10,2};
    double Y[6]={97,98,99,100,101,102};
    THisto1=F.Histogramme(Liste1,TListe1,Donnee1,Frequence1);
    std::cout<<"Taille Histo : "<<THisto1<<std::endl;
    affichage1D(Donnee1,THisto1,"Donnees");
    affichage1D(Frequence1,THisto1,"Frequence");
    cHuffmanF W(Liste1,THisto1);
    W.HuffmanCodes(Y,X,6);
    W.HuffmanCodes(Donnee1,Frequence1,THisto1);
    */
    //Donnees .dat
    string Titre3="lenna.dat";
    LectureImage(Titre3,Image,TailleFinal);
    affichage2D(Image,TailleFinal,"Block Image");
    cCompressionF L(TailleFinal,TailleFinal,Image,50);
    TListe2=L.RLE(Liste2);
    std::cout<<"Taille RLE : "<<TListe2<<std::endl;
    affichage1D(Liste2,TListe2,Titre1);
    THisto2=L.Histogramme(Liste2,TListe2,Donnee2,Frequence2);
    std::cout<<"Taille Histo : "<<THisto2<<std::endl;
    affichage1D(Donnee2,THisto2,"Donnees");
    affichage1D(Frequence2,THisto2,"Frequence");
    cHuffmanF V(Liste2,THisto2);
    V.HuffmanCodes(Donnee2,Frequence2,THisto2);
    return 0;
}
//! Affichage 2D
/**@brief
*   Cette fonction affiche une matrice carre
*
*@param[in] Element1
*    double** Array a 2 dimensions
*@param[in] Taille
*    unsigned Taille du array
*@param[in] Titre
*    string Titre du affichage
*/
void affichage2D(double** Element1, unsigned Taille, string Titre)
    {
        std::cout<<Titre<<std::endl;
        for(unsigned i=0;i<Taille;i++)
        {
            for(unsigned j=0;j<Taille;j++)
            {
                std::cout<<Element1[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
    }
//! Affichage 1D
/**@brief
*   Cette fonction affiche une liste
*
*@param[in] Element2
*    double* Array a 1 dimension
*@param[in] Taille
*    unsigned Taille du array
*@param[in] Titre
*    string Titre du affichage
*/
void affichage1D(double* Element2, unsigned Taille, string Titre)
{
     std::cout<<Titre<<std::endl;
    for(unsigned i=0;i<Taille;i++)
    {
        std::cout<<Element2[i]<<" ";
    }
    std::cout<<std::endl;
}
//! LectureImage
/**@brief
*   Cette fonction lit un fichier .dat et le transforme en une matrice
*
*@param[in] Block
*    double** Block a 2 dimensions qui recoit les valeurs du fichier
*@param[in] Titre
*    string Nom du fichier
*/
void LectureImage (string Titre,double** Block,unsigned TailleB)
{
    std::ifstream file;
    file.open(Titre);
    char buffer[20000];
    for (unsigned i=0;i<TailleB;i++)
    {
        for (unsigned j=0;j<TailleB;j++)
        {
            file.getline(buffer,20000,' ');
            Block[i][j]=stod(buffer);
        }
    }
}
