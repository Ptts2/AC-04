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

Alu::Binario Alu::decToBinaryIEEE(float num, int nBits){


    Binario mantisa;
    float parteEntera, parteFraccionaria;

    parteFraccionaria = modf(num, &parteEntera);

    int parteEnteraInt = (int)parteEntera;

    //Convertir la parte entera a binario
    string parteEnteraString = "";
    int contPartEntera = 0;
    while(parteEnteraInt>0 && contPartEntera<=23){
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

    while(parteFraccionaria!=0 && (contPartEntera+contPartFrac) <=nBits){

        float parteEnteraDec;
        parteFraccionaria *=2;

        parteFraccionaria = modf(parteFraccionaria, &parteEnteraDec);

        parteFraccString += std::to_string((int)parteEnteraDec);

        contPartFrac++;
    }

     if((contPartEntera+contPartFrac) < nBits){

         while((contPartEntera+contPartFrac) <=nBits){
             parteFraccString += "0";
             contPartFrac++;
         }
     }
     parteFraccString = regex_replace(parteFraccString, std::regex(R"([\D])"), "");
     mantisa.parteFraccionaria = parteFraccString;



     while((int)mantisa.parteEntera.size()<nBits){

         mantisa.parteEntera.insert(0, "0");
     }
     return mantisa;

}

Alu::Binario Alu::decToBinaryNormal(float num){


    Binario mantisa;
    float parteEntera, parteFraccionaria;

    parteFraccionaria = modf(num, &parteEntera);

    int parteEnteraInt = (int)parteEntera;

    //Convertir la parte entera a binario
    string parteEnteraString = "";
    int contPartEntera = 0;
    while(parteEnteraInt>0 && contPartEntera<=23){
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

    while(parteFraccionaria!=0 && (contPartEntera+contPartFrac) <=23){

        float parteEnteraDec;
        parteFraccionaria *=2;

        parteFraccionaria = modf(parteFraccionaria, &parteEnteraDec);

        parteFraccString += std::to_string((int)parteEnteraDec);

        contPartFrac++;
    }

     if((contPartEntera+contPartFrac) < 23){

         while((contPartEntera+contPartFrac) <=23){
             parteFraccString += "0";
             contPartFrac++;
         }
     }
     parteFraccString = regex_replace(parteFraccString, std::regex(R"([\D])"), "");
     mantisa.parteFraccionaria = parteFraccString;

     return mantisa;

}

Alu::Binario Alu::complementoA2(Alu::Binario num){

   Alu::Binario binarioCompA2;


   string binario = num.parteEntera+num.parteFraccionaria;
   int posPrimer1 = binario.size()-1;
   string binarioA2 ="";

   while( strncmp(&binario[posPrimer1], "1", 1) != 0 && posPrimer1 > 0){
       binarioA2 += binario.at(posPrimer1);
       posPrimer1--;
   }

   binarioA2 +="1";
   int i = posPrimer1-1;

   while(i>=0){

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

Alu::Code Alu::fromDecToIEEE754(float num){

    Code a;
    a.numero = num;
    return a;

}

Alu::NumSolucion Alu::suma(float operador1, float operador2)
{

    NumSolucion solucion;

    int g = 0, r = 0, st = 0, n = 24;
    bool operandosIntercambiados = false, complementadoP = false;
    string mantisaA, mantisaB;

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
        mantisa.parteFraccionaria = decToBinaryNormal(operB.bitfield.partFrac).parteEntera;

        Binario mantisaA2 = complementoA2(mantisa);
        mantisaB = mantisaA2.parteEntera+mantisaA2.parteFraccionaria;
    }else{
        mantisaB = "1"+decToBinaryNormal(operB.bitfield.partFrac).parteEntera;
    }

    string P = mantisaB;

    if(d<0 && d-1< (int)P.size() )
        g = stoi(&P[d-1]);
    if(d<1 && d-2< (int)P.size())
        r = stoi(&P[d-2]);

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

    return solucion;
}

Alu::NumSolucion Alu::producto(float operador1, float operador2)
{

    NumSolucion solucion;
    return solucion;
}

Alu::NumSolucion Alu::division(float operador1, float operador2)
{

    NumSolucion solucion;
    return solucion;
}



