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

        struct{
            bool nan;
            bool inf;
        }denormals;
    };

    struct BinYAcarreo{
        std::string binario;
        int acarreo;
    };

    Alu();
    ~Alu();
    Code suma(float operador1, float operador2);
    Code producto(float operador1, float operador2);
    Code division(float operador1, float operador2);
    Code fromDecToIEEE754(float num);
    Binario decToBinaryIEEE(float num, int nBits = 23);
    Binario decToBinaryNormal(float num);
    Binario complementoA2(Alu::Binario num);

private:

    unsigned int binaryToDec(std::string bin);
    std::string *multiplicacionBinariaSinSigno(std::string a, std::string b);
    BinYAcarreo sumaNumerosBinarios(std::string Operador1, std::string Operador2, int C=0);
    bool denormal(Code operando);
    std::string escalar(Binario operador);
    float fraccionarBinaryToDec(std::string binario);

};

#endif // ALU_H
