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
    float suma(/*Ver que incluir*/);
    float producto(/*Ver que incluir*/);
    float division(/*Ver que incluir*/);
    IEEE754num fromDecToIEEE754(float num);
    float fromIEEE754ToDec(IEEE754num);

};

#endif // ALU_H
