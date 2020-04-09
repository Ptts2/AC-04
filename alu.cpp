#include "alu.h"
#include <cmath>
#include <string>
#include <regex>

using namespace std;
Alu::Alu()
{

}

Alu::~Alu(){}

Alu::Mantisa Alu::decToBinary(float num){


    Mantisa mantisa;
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
    mantisa.parteEntera = stoull(parteEnteraString);

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

     parteFraccString = regex_replace(parteFraccString, std::regex(R"([\D])"), "");
     mantisa.parteFraccionaria = stoull(parteFraccString);
     return mantisa;

}

float Alu::fromIEEE754ToDec(Alu::IEEE754num){

    return 0.0;
}

Alu::NumSolucion Alu::suma(float operador1, float operador2)
{

    NumSolucion solucion;
    Mantisa mantisa = decToBinary(operador1);
    IEEE754num numero;
    numero.mantisa = mantisa;
    solucion.numIEEE = numero;

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

Alu::IEEE754num Alu::fromDecToIEEE754(float num){

    IEEE754num numeroConvertido;

    if(num<0)
        numeroConvertido.signo=1;
    else
        numeroConvertido.signo=0;

    return numeroConvertido;
}


