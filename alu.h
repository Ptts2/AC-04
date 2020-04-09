#ifndef ALU_H
#define ALU_H

#include <iostream>

class Alu
{
public:

    struct Mantisa{
        unsigned long long parteEntera;
        unsigned long long parteFraccionaria;
    };
    struct IEEE754num{
        Mantisa mantisa;
       unsigned long long exponente : 8;
       unsigned int signo: 1;
    };
    struct NumSolucion{
        float numDec;
        IEEE754num numIEEE;
        int numHex;
    };

    Alu();
    ~Alu();
    NumSolucion suma(float operador1, float operador2);
    NumSolucion producto(float operador1, float operador2);
    NumSolucion division(float operador1, float operador2);
    IEEE754num fromDecToIEEE754(float num);
    float fromIEEE754ToDec(IEEE754num);

private:

    Mantisa decToBinary(float num);
    float binaryToDec(Mantisa bin);

};

#endif // ALU_H
