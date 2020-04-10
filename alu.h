#ifndef ALU_H
#define ALU_H

#include <string>

class Alu
{
public:

    struct Binario{
        std::string parteEntera;
        std::string parteFraccionaria; //Seria un long long pero pierde ceros a la izquierda, trabajar con stoull
    };

    union Code {

        struct{
            unsigned int partFrac : 23;
            unsigned int expo : 8;
            unsigned int sign : 1;
        }bitfield;

        float numero;
        unsigned int numerox;
    };

    struct NumSolucion{
        float numDec;
        Code numIEEE;
        int numHex;
    };

    Alu();
    ~Alu();
    NumSolucion suma(float operador1, float operador2);
    NumSolucion producto(float operador1, float operador2);
    NumSolucion division(float operador1, float operador2);
    Code fromDecToIEEE754(float num);
    Binario decToBinaryIEEE(float num, int nBits = 23);
    Binario decToBinaryNormal(float num);

private:


    float binaryToDec(Binario bin);

};

#endif // ALU_H
