#ifndef ALU_H
#define ALU_H


class Alu
{
public:
    struct IEEE754num{
        int mantisa : 23;
        int exponente : 8;
        int signo: 1;

    };
    Alu();
    ~Alu();
    float suma(float operador1, float operador2);
    float producto(float operador1, float operador2);
    float division(float operador1, float operador2);
    IEEE754num fromDecToIEEE754(float num);
    float fromIEEE754ToDec(IEEE754num);

};

#endif // ALU_H
