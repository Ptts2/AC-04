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

Alu::IEEE754num Alu::fromDecToIEEE754(float num){

    IEEE754num numeroConvertido;


    if(num<0){
        numeroConvertido.signo=1;
        numeroConvertido.mantisa = decToBinary(-num);
    }
    else{
        numeroConvertido.signo=0;
        numeroConvertido.mantisa = decToBinary(num);
    }

    std::cout << numeroConvertido.mantisa.parteEntera<<endl;
    int exponente = 127 + (int)(numeroConvertido.mantisa.parteEntera.size()) -1;

    while(numeroConvertido.mantisa.parteEntera.size()>1){

        numeroConvertido.mantisa.parteFraccionaria.pop_back();

        (numeroConvertido.mantisa.parteFraccionaria).insert(0, &numeroConvertido.mantisa.parteEntera.back());
        numeroConvertido.mantisa.parteEntera.pop_back();
    }

    Mantisa mantisa2 = decToBinary(float(exponente));
    numeroConvertido.exponente= mantisa2.parteEntera;


    return numeroConvertido;
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



