#include "alu.h"
#include <cmath>
#include <string>
#include <regex>
#include <iostream>

using namespace std;
Alu::Alu()
{

}

Alu::~Alu(){}

Alu::Binario Alu::decToBinaryIEEE(float num, int nBits)
{


    Binario mantisa;
    float parteEntera, parteFraccionaria;

    parteFraccionaria = modf(num, &parteEntera);

    int parteEnteraInt = (int)parteEntera;

    //Convertir la parte entera a binario
    string parteEnteraString = "";
    int contPartEntera = 0;
    while(parteEnteraInt>0 && contPartEntera<=23)
    {
        parteEnteraString += std::to_string(parteEnteraInt%2);
        parteEnteraInt = parteEnteraInt/2;
        contPartEntera++;
    }

    reverse(parteEnteraString.begin(), parteEnteraString.end());

    parteEnteraString = regex_replace(parteEnteraString, std::regex(R"([\D])"), "");
    mantisa.parteEntera = parteEnteraString;

    //Convertir la parte fraccionaria a binario
    string parteFraccString;
    int contPartFrac = 0;

    while(parteFraccionaria!=0 && (contPartEntera+contPartFrac) <=nBits)
    {

        float parteEnteraDec;
        parteFraccionaria *=2;

        parteFraccionaria = modf(parteFraccionaria, &parteEnteraDec);

        parteFraccString += std::to_string((int)parteEnteraDec);

        contPartFrac++;
    }

     if((contPartEntera+contPartFrac) < nBits)
     {

         while((contPartEntera+contPartFrac) <=nBits)
         {
             parteFraccString += "0";
             contPartFrac++;
         }
     }
     parteFraccString = regex_replace(parteFraccString, std::regex(R"([\D])"), "");
     mantisa.parteFraccionaria = parteFraccString;



     while((int)mantisa.parteEntera.size()<nBits)
     {

         mantisa.parteEntera.insert(0, "0");
     }
     return mantisa;

}

Alu::Binario Alu::decToBinaryNormal(float num)
{


    Binario mantisa;
    float parteEntera, parteFraccionaria;

    parteFraccionaria = modf(num, &parteEntera);

    int parteEnteraInt = (int)parteEntera;

    //Convertir la parte entera a binario
    string parteEnteraString = "";
    int contPartEntera = 0;
    while(parteEnteraInt>0 && contPartEntera<=23)
    {
        parteEnteraString += std::to_string(parteEnteraInt%2);
        parteEnteraInt = parteEnteraInt/2;
        contPartEntera++;
    }

    reverse(parteEnteraString.begin(), parteEnteraString.end());

    parteEnteraString = regex_replace(parteEnteraString, std::regex(R"([\D])"), "");
    mantisa.parteEntera = parteEnteraString;

    //Convertir la parte fraccionaria a binario
    string parteFraccString;
    int contPartFrac = 0;

    while(parteFraccionaria!=0 && (contPartEntera+contPartFrac) <=23)
    {

        float parteEnteraDec;
        parteFraccionaria *=2;

        parteFraccionaria = modf(parteFraccionaria, &parteEnteraDec);

        parteFraccString += std::to_string((int)parteEnteraDec);

        contPartFrac++;
    }

     if((contPartEntera+contPartFrac) < 23)
     {

         while((contPartEntera+contPartFrac) <=23)
         {
             parteFraccString += "0";
             contPartFrac++;
         }
     }
     parteFraccString = regex_replace(parteFraccString, std::regex(R"([\D])"), "");
     mantisa.parteFraccionaria = parteFraccString;

     return mantisa;

}

Alu::Binario Alu::complementoA2(Alu::Binario num)
{

   Alu::Binario binarioCompA2;


   string binario = num.parteEntera+num.parteFraccionaria;
   int posPrimer1 = binario.size()-1;
   string binarioA2 ="";

   while( strncmp(&binario[posPrimer1], "1", 1) != 0 && posPrimer1 > 0)
   {
       binarioA2 += binario.at(posPrimer1);
       posPrimer1--;
   }

   binarioA2 +="1";
   int i = posPrimer1-1;

   while(i>=0)
   {

       if( strncmp(&binario[i], "1", 1) == 0)
           binarioA2 += "0";
       else
           binarioA2 += "1";

       i--;
   }


   reverse(binarioA2.begin(), binarioA2.end());

   binarioCompA2.parteEntera = binarioA2.substr(0,num.parteEntera.size());
   binarioCompA2.parteFraccionaria = binarioA2.substr(num.parteEntera.size());

   return binarioCompA2;
}

Alu::Code Alu::fromDecToIEEE754(float num)
{

    Code a;
    a.numero = num;
    return a;

}
unsigned int Alu::binaryToDec(string bin)
{

    unsigned int resultado = 0;

    int i = bin.size()-1;
    int j = 0;

    while(i>=0)
    {
        if(strncmp(&bin[i], "1", 1) == 0)
        {

            resultado += pow(2,j);

        }

        i--;
        j++;
    }

    return resultado;
}

Alu::Code Alu::suma(float operador1, float operador2)
{

    Code solucion;

    int g = 0, r = 0, st = 0, n = 24;
    bool operandosIntercambiados = false, complementadoP = false;
    string mantisaA, mantisaB, mantisaSuma;

    Code numSuma, operA, operB;
    operA.numero=operador1;
    operB.numero=operador2;

    //Si el exponente de 1 es menor que el de 2 los intercambio
    if(operA.bitfield.expo < operB.bitfield.expo)
    {
        Code aux = operA;
        operA = operB;
        operB = aux;
        operandosIntercambiados = true;
    }


    int exponenteSuma = operA.bitfield.expo;
    int d = operA.bitfield.expo - operB.bitfield.expo;

    if(operA.bitfield.expo != operB.bitfield.expo){

        Binario mantisa;
        mantisa.parteEntera = "1";
        mantisa.parteFraccionaria = decToBinaryIEEE(operB.bitfield.partFrac).parteEntera;

        Binario mantisaA2 = complementoA2(mantisa);
        mantisaB = mantisaA2.parteEntera+mantisaA2.parteFraccionaria;
    }else{
        mantisaB = "1"+decToBinaryIEEE(operB.bitfield.partFrac).parteEntera;
    }

    mantisaA = "1"+decToBinaryIEEE(operA.bitfield.partFrac).parteEntera;

    string P = mantisaB;

    if(d<0 && d-1< (int)P.size() ){
        if((strncmp(&P[d-1], "1", 1) == 0))
            g = 1;
        else
            g = 0;
    }if(d<1 && d-2< (int)P.size()){
        if((strncmp(&P[d-2], "1", 1) == 0))
            r = 1;
        else
            r = 0;
    }


   int i = 0;
    while(i<d-2 && st == 0){

        if(strncmp(&P[i], "1", 1) == 0)
            st = 1;
        i++;
    }

    if(operA.bitfield.sign!=operB.bitfield.sign){

        for(i = 0; i<d; i++){
            P.insert(0,"1");
            P.pop_back();
        }

    }else{

        for(i = 0; i<d; i++){
            P.insert(0,"0");
            P.pop_back();
        }
    }

    int C = 0; //acarreo
    string aux ="";
    i = P.size()-1;

    while(i>=0){

        if( (strncmp(&mantisaA[i], "1", 1) == 0) && (strncmp(&P[i], "1", 1) == 0) )
        {
            //Si son ambos 1

            if(C==0){
               //Si no hay acarreo
               aux += "0";
               C=1;
            }else{
                //Si hay acarreo
                aux +="1";
            }
        }else if( (strncmp(&mantisaA[i], "0", 1) == 0) && (strncmp(&P[i], "0", 1) == 0) )
        {
            //Si son ambos 0
            if(C==0){
               aux += "0";
            }else{
               aux += "1";
               C=0;
            }
        }else
        {
            //Si son 0+1 o 1+0
            if(C==0){
               aux += "1";
            }else{
                aux +="0";
            }
        }

        i--;
    }
    reverse(aux.begin(), aux.end());
    P = aux;

    if( (operA.bitfield.sign!=operB.bitfield.sign) && (strncmp(&P[n-1], "1", 1) == 0) && (C == 0) )
    {

        Binario p;
        p.parteEntera = P;
        P = complementoA2(p).parteEntera;
        complementadoP = true;
    }


    if( (operA.bitfield.sign==operB.bitfield.sign) && (C==1) )
    {
        st = (g||r||st);
        (strncmp(&P[0], "1", 1) == 0)? r=1:r=0;
        P.pop_back();
        P.insert(0,"1");

        exponenteSuma++;
    }else
    {

        int K = 0;
        while( (strncmp(&P[K], "1", 1) != 0) )
            K++;

        if(K==0)
        {
          st=(r||st);
          r = g;
        }
        if(K>1)
        {
            r = 0;
            st = 0;
        }

        i=K;
        while(i>0)
        {
            P.erase(0,1);
            if(g==0)
                P += "0";
            else
                P += "1";
            i--;
        }

        exponenteSuma -= K;
    }

    int C2 = 0; //Acarreo 2

    if( (r==1 && st==1) || (r==1 && st == 0 && (strncmp(&P[0], "1", 1) == 0)) )
    {

        i = P.size()-1;
        string uno ="000000000000000000000001";
        string aux2 ="";
        while(i>=0){

            if( (strncmp(&uno[i], "1", 1) == 0) && (strncmp(&P[i], "1", 1) == 0) )
            {
                //Si son ambos 1

                if(C2==0){
                   //Si no hay acarreo
                   aux2 += "0";
                   C2=1;
                }else{
                    //Si hay acarreo
                    aux2 +="1";
                }
            }else if( (strncmp(&uno[i], "0", 1) == 0) && (strncmp(&P[i], "0", 1) == 0) )
            {
                //Si son ambos 0
                if(C2==0){
                   aux2 += "0";
                }else{
                   aux2 += "1";
                   C2=0;
                }
            }else
            {
                //Si son 0+1 o 1+0
                if(C2==0){
                   aux2 += "1";
                }else{
                    aux2 +="0";
                }
            }

            i--;
        }
        reverse(aux2.begin(), aux2.end());
        P = aux2;

        if(C2==1)
        {
            P.pop_back();
            P.insert(0,"1");
            exponenteSuma++;
        }
    }

    mantisaSuma = P;
    int signoSuma;

    if( !operandosIntercambiados && complementadoP)
        signoSuma = operB.bitfield.sign;
    else
        signoSuma = operA.bitfield.sign;

    mantisaSuma.erase(0,1);

    solucion.bitfield.sign = signoSuma;
    solucion.bitfield.expo = exponenteSuma;
    solucion.bitfield.partFrac = binaryToDec(mantisaSuma);

    return solucion;
}

Alu::Code Alu::producto(float operador1, float operador2)
{

    Code solucion;
    return solucion;
}

Alu::Code Alu::division(float operador1, float operador2)
{

    Code solucion;
    return solucion;
}



