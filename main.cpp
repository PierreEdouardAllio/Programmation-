#include <iostream>
#include"cCompression.h"
using namespace std;

int main()
{
    //Block8x8 exemple
    double B[8][8]={{139, 144, 149, 153, 155, 155, 155, 155},{144, 151, 153, 156, 159, 156, 156, 156},{150, 155, 160, 163, 158, 156, 156, 156}
    ,{159, 161, 162, 160, 160, 159, 159, 159},{159, 160, 161, 162, 162, 155, 155, 155},{161, 161, 161, 161, 160, 157, 157, 157}
    ,{162, 162, 161, 163, 162, 157, 157, 157},{162, 162, 161, 161, 163, 158, 158, 158}};

    //Dynamic Allocation Image Initiale
    double ** ImageInit;
    ImageInit=new double *[8];
    for (unsigned i=0;i<8;i++)
    {
       ImageInit[i]=new double[8];
       for (unsigned j=0;j<8;j++)
       {
           ImageInit[i][j]=B[i][j];
       }
    }
    //Dynamic Allocation Image DCT
    double ** ImageDCT;
    ImageDCT=new double *[8];
    for (unsigned i=0;i<8;i++)
    {
       ImageDCT[i]=new double[8];
       for (unsigned j=0;j<8;j++)
       {
           ImageDCT[i][j]=0;
       }
    }
    //Dynamic Allocation Image Quantification
    double ** ImageQUANT;
    ImageQUANT=new double *[8];
    for (unsigned i=0;i<8;i++)
    {
       ImageQUANT[i]=new double[8];
       for (unsigned j=0;j<8;j++)
       {
           ImageQUANT[i][j]=0;
       }
    }
    //Dynamic Allocation Image Dequantification
    double ** ImageDEQUANT;
    ImageDEQUANT=new double *[8];
    for (unsigned i=0;i<8;i++)
    {
       ImageDEQUANT[i]=new double[8];
       for (unsigned j=0;j<8;j++)
       {
           ImageDEQUANT[i][j]=0;
       }
    }
    //Dynamic Allocation Image DCT Inverse
    double ** ImageDEDCT;
    ImageDEDCT=new double *[8];
    for (unsigned i=0;i<8;i++)
    {
       ImageDEDCT[i]=new double[8];
       for (unsigned j=0;j<8;j++)
       {
           ImageDEDCT[i][j]=0;
       }
    }
    //Dynamic Allocation Liste RLE
    double* Liste=new double[100];

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
    //Block16x16 exemple
    double R[16][16]={{139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},{139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},
    {139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},{139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},
    {139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},{139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},
    {139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},{139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},
    {139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},{139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},
    {139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},{139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},
    {139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},{139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},
    {139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155},{139, 144, 149, 153, 155, 155, 155, 155,139, 144, 149, 153, 155, 155, 155, 155}};
        //Dynamic Allocation Image Initiale
    double ** ImageRLE;
    ImageRLE=new double *[16];
    for (unsigned i=0;i<8;i++)
    {
       ImageRLE[i]=new double[16];
       for (unsigned j=0;j<8;j++)
       {
           ImageRLE[i][j]=R[i][j];
       }
    }
    cCompression F(16,16,ImageRLE,50);
    F.RLE(Liste);
    std::cout<<"LISTE RLE"<<std::endl;
    for (unsigned i=0;i<100;i++)
    {
        std::cout<<Liste[i]<<" ";
    }
    std::cout<<std::endl;
    return 0;
}
