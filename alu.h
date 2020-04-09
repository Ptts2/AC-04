#ifndef ALU_H
#define ALU_H

#include <string>

class Alu
{
public:

    struct Mantisa{
        unsigned long long parteEntera;
        std::string parteFraccionaria; //Seria un long long pero pierde ceros a la izquierda, trabajar con stoull
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
