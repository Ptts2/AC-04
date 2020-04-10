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

Alu::Binario Alu::decToBinary(float num){


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

Alu::Code Alu::fromDecToIEEE754(float num){

    Code a;
    a.numero = num;
    return a;

}

Alu::NumSolucion Alu::suma(float operador1, float operador2)
{

    NumSolucion solucion;
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



