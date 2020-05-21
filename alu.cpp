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

Alu::Binario Alu::decToBinaryIEEE(float num, int nBits)
{


    Binario mantisa;
    float parteEntera, parteFraccionaria;

    parteFraccionaria = modf(num, &parteEntera);

    int parteEnteraInt = (int)parteEntera;

    //Convertir la parte entera a binario
    string parteEnteraString = "";
    int contPartEntera = 0;
    while(parteEnteraInt>0 && contPartEntera<=23)
    {
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

    while(parteFraccionaria!=0 && (contPartEntera+contPartFrac) <=nBits)
    {

        float parteEnteraDec;
        parteFraccionaria *=2;

        parteFraccionaria = modf(parteFraccionaria, &parteEnteraDec);

        parteFraccString += std::to_string((int)parteEnteraDec);

        contPartFrac++;
    }

     if((contPartEntera+contPartFrac) < nBits)
     {

         while((contPartEntera+contPartFrac) <=nBits)
         {
             parteFraccString += "0";
             contPartFrac++;
         }
     }
     parteFraccString = regex_replace(parteFraccString, std::regex(R"([\D])"), "");
     mantisa.parteFraccionaria = parteFraccString;



     while((int)mantisa.parteEntera.size()<nBits)
     {

         mantisa.parteEntera.insert(0, "0");
     }
     return mantisa;

}

Alu::Binario Alu::decToBinaryNormal(float num)
{


    Binario mantisa;
    float parteEntera, parteFraccionaria;

    parteFraccionaria = modf(num, &parteEntera);

    int parteEnteraInt = (int)parteEntera;

    //Convertir la parte entera a binario
    string parteEnteraString = "";
    int contPartEntera = 0;
    while(parteEnteraInt>0 && contPartEntera<=23)
    {
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

    while(parteFraccionaria!=0 && (contPartEntera+contPartFrac) <=23)
    {

        float parteEnteraDec;
        parteFraccionaria *=2;

        parteFraccionaria = modf(parteFraccionaria, &parteEnteraDec);

        parteFraccString += std::to_string((int)parteEnteraDec);

        contPartFrac++;
    }

     if((contPartEntera+contPartFrac) < 23)
     {

         while((contPartEntera+contPartFrac) <=23)
         {
             parteFraccString += "0";
             contPartFrac++;
         }
     }
     parteFraccString = regex_replace(parteFraccString, std::regex(R"([\D])"), "");
     mantisa.parteFraccionaria = parteFraccString;

     return mantisa;

}

Alu::Binario Alu::complementoA2(Alu::Binario num)
{

   Alu::Binario binarioCompA2;


   string binario = num.parteEntera+num.parteFraccionaria;
   int posPrimer1 = binario.size()-1;
   string binarioA2 ="";

   while( strncmp(&binario[posPrimer1], "1", 1) != 0 && posPrimer1 > 0)
   {
       binarioA2 += binario.at(posPrimer1);
       posPrimer1--;
   }

   binarioA2 +="1";
   int i = posPrimer1-1;

   while(i>=0)
   {

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

Alu::Code Alu::fromDecToIEEE754(float num)
{

    Code a;
    a.numero = num;
    return a;

}
unsigned int Alu::binaryToDec(string bin)
{

    unsigned int resultado = 0;

    int i = bin.size()-1;
    int j = 0;

    while(i>=0)
    {
        if(strncmp(&bin[i], "1", 1) == 0)
        {

            resultado += pow(2,j);

        }

        i--;
        j++;
    }

    return resultado;
}

bool Alu::denormal(Code operando)
{
   return operando.bitfield.expo-127 < -126;
}

string Alu::escalar(Binario operador)
{
    string entera = operador.parteEntera, fraccionaria = operador.parteFraccionaria, enteraNueva, fraccionariaNueva;
    while(strncmp(&entera[0], "0", 1) == 0)
    {
        entera.erase(0,1);
    }
        enteraNueva = "1";
    entera.erase(0,1);
    fraccionariaNueva = entera+fraccionaria;
    return enteraNueva +","+ fraccionariaNueva;
}

float Alu::fraccionarBinaryToDec(string binario)
{
    string parteEntera, parteFraccionaria;
    float solucion = 0.0;
    parteEntera = binario.substr(0,binario.find(","));
    parteFraccionaria = binario.substr(binario.find(",")+1, binario.size());
    solucion += binaryToDec(parteEntera);

    for(int i = 0; i<(int)parteFraccionaria.size(); i++){
        if(strncmp(&parteFraccionaria[i], "1", 1) == 0)
            solucion += 1/pow(2,i+1);
    }
    return solucion;
}
Alu::BinYAcarreo Alu::sumaNumerosBinarios(std::string Operador1, std::string Operador2, int C) {


    BinYAcarreo solucion;

    string aux ="";
    int i = Operador1.size()-1;

    while(i>=0){

        if( (strncmp(&Operador1[i], "1", 1) == 0) && (strncmp(&Operador2[i], "1", 1) == 0) )
        {
            //Si son ambos 1

            if(C==0){
               //Si no hay acarreo
               aux += "0";
               C=1;
            }else{
                //Si hay acarreo
                aux +="1";
            }
        }else if( (strncmp(&Operador1[i], "0", 1) == 0) && (strncmp(&Operador2[i], "0", 1) == 0) )
        {
            //Si son ambos 0
            if(C==0){
               aux += "0";
            }else{
               aux += "1";
               C=0;
            }
        }else
        {
            //Si son 0+1 o 1+0
            if(C==0){
               aux += "1";
            }else{
                aux +="0";
            }
        }

        i--;
    }
    reverse(aux.begin(), aux.end());

    solucion.binario = aux;
    solucion.acarreo = C;
    return solucion;
}

Alu::Code Alu::suma(float operador1, float operador2)
{

    Code solucion;

    int g = 0, r = 0, st = 0, n = 24;
    bool operandosIntercambiados = false, complementadoP = false;
    string mantisaA, mantisaB, mantisaSuma;

    Code operA, operB;
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

    if(operA.bitfield.sign != operB.bitfield.sign){

        Binario mantisa;
        mantisa.parteEntera = "1";
        mantisa.parteFraccionaria = decToBinaryIEEE(operB.bitfield.partFrac).parteEntera;

        Binario mantisaA2 = complementoA2(mantisa);
        mantisaB = mantisaA2.parteEntera+mantisaA2.parteFraccionaria;
    }else{
        mantisaB = "1"+decToBinaryIEEE(operB.bitfield.partFrac).parteEntera;
    }

    mantisaA = "1"+decToBinaryIEEE(operA.bitfield.partFrac).parteEntera;

    string P = mantisaB;

    if(d>0 && d-1< (int)P.size() ){
        if((strncmp(&P[(n-1)-(d-1)], "1", 1) == 0))
            g = 1;
        else
            g = 0;
    }if(d>1 && d-2< (int)P.size()){
        if((strncmp(&P[(n-1)-(d-2)], "1", 1) == 0))
            r = 1;
        else
            r = 0;
    }


   int i = 0;
   while(i<=d-2 && st == 0){

        if(strncmp(&P[(n-1)-i], "1", 1) == 0)
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

    int C = 0; //acarreo

    BinYAcarreo suma = sumaNumerosBinarios(mantisaA, P, C);
    P = suma.binario;
    C = suma.acarreo;

    if( (operA.bitfield.sign!=operB.bitfield.sign) && (strncmp(&P[0], "1", 1) == 0) && (C == 0) )
    {

        Binario p;
        p.parteEntera = P;
        P = complementoA2(p).parteEntera;
        complementadoP = true;
    }


    if( (operA.bitfield.sign==operB.bitfield.sign) && (C==1) )
    {
        st = (g||r||st);
        (strncmp(&P[n-1], "1", 1) == 0)? r=1:r=0;
        P.pop_back();
        P.insert(0,"1");

        exponenteSuma++;
    }else
    {

        int K = 0;
        while( (strncmp(&P[K], "1", 1) != 0) )
            K++;

        if(K==0)
        {
          st=(r||st);
          r = g;
        }
        if(K>1)
        {
            r = 0;
            st = 0;
        }

        i=K;
        while(i>0)
        {
            P.erase(0,1);
            if(g==0)
                P += "0";
            else
                P += "1";
            i--;
        }

        exponenteSuma -= K;
    }

    int C2 = 0; //Acarreo 2

    if( (r==1 && st==1) || (r==1 && st == 0 && (strncmp(&P[n-1], "1", 1) == 0)) )
    {

        string uno ="000000000000000000000001";
        BinYAcarreo suma2 = sumaNumerosBinarios(P, uno, C2);
        P=suma2.binario;
        C2=suma2.acarreo;

        if(C2==1)
        {
            P.pop_back();
            P.insert(0,"1");
            exponenteSuma++;
        }
    }

    mantisaSuma = P;
    int signoSuma;

    if( !operandosIntercambiados && complementadoP)
        signoSuma = operB.bitfield.sign;
    else
        signoSuma = operA.bitfield.sign;

    mantisaSuma.erase(0,1);

    solucion.bitfield.sign = signoSuma;
    solucion.bitfield.expo = exponenteSuma;
    solucion.bitfield.partFrac = binaryToDec(mantisaSuma);

    return solucion;
}

Alu::Code Alu::producto(float operador1, float operador2)
{

    Code solucion;
    if(operador1 == 0 || operador2 == 0)
    {
        solucion.bitfield.expo = 0;
        solucion.bitfield.sign = 0;
        solucion.bitfield.partFrac = 0;
        return solucion;
    }
    Code operA, operB;
    int st, r;

    operA.numero=operador1;
    operB.numero=operador2;

    if( (operA.bitfield.sign==1) ^ (operB.bitfield.sign==1) )
    {
        solucion.bitfield.sign=1;
    }else
    {
        solucion.bitfield.sign=0;
    }

    solucion.bitfield.expo = (operA.bitfield.expo)+(operB.bitfield.expo)-127;

    string mantisaA = "1"+decToBinaryIEEE(operA.bitfield.partFrac).parteEntera;
    string mantisaB = "1"+decToBinaryIEEE(operB.bitfield.partFrac).parteEntera;

    string *PA =  multiplicacionBinariaSinSigno(mantisaA, mantisaB); //24 bits P + 24 bits A

    if(strncmp(&PA[0][0], "0", 1) == 0) {

       for(int i=0;i<(int)PA[0].size()-1;i++)
           PA[0][i] = PA[0][i+1];
       PA[0][PA[0].size()-1] = PA[1][0];
       for(int i=0;i<(int)PA[1].size()-1;i++)
           PA[1][i] = PA[1][i+1];
        PA[1][PA[1].size()-1] = 0x30;

      } else {
        solucion.bitfield.expo = solucion.bitfield.expo + 1;
     }

    if(strncmp(&PA[1][23], "0", 1) == 0)
        r = 0;
    else
        r = 1;

    int n = 0;
    st = 0;

    while(st == 0 && n<23){

        if(strncmp(&PA[1][n], "1", 1) == 0)
            st = 1;
        n++;
    }


    if( (r == 1 && st == 1)  || (r == 1 && st == 0 && (strncmp(&PA[0][23], "1", 1) == 0) ) ) {

         string uno ="000000000000000000000001";
         PA[0] = sumaNumerosBinarios(PA[0], uno).binario;

    }

    //comprobacion desbordamientos

    int t;
    if(solucion.bitfield.expo - 127 > 127){
        solucion.nan = true;
        return solucion; //Devolver infinito
    }else if(solucion.bitfield.expo - 127 < -126){

         t = -126 - (solucion.bitfield.expo - 127);

         if(t>=24){
             solucion.nan = true;
             return solucion; //Devolver underflow (NaN, ind...)

         }else{
             for(int j = 0; j<t ; j++)
             {

                for(int i=(int)PA[1].size()-1;i>0;i--)
                    PA[1][i] = PA[1][i-1];

                PA[1][0] = PA[0][PA[0].size()-1];

                for(int i=PA[0].size()-1;i>0;i--)
                    PA[0][i] = PA[0][i-1];
                PA[0][0] = 0x30;
             }
            solucion.bitfield.expo = -126 + 127;
         }
    }

    //Operandos denormales
    if(denormal(operA) || denormal(operB))
    {
        if(solucion.bitfield.expo -127 < -126)
        {
            solucion.nan = true;
            return solucion; //Devolver underflow (NaN, ind...)
        }else if(solucion.bitfield.expo -127 > -126)
        {
            int t1 = 0, t2= 0, t = 0;
            string PA2= PA[0]+PA[1];
            t1 = solucion.bitfield.expo - (-126);
            while(strncmp(&PA2[t2], "0", 1) == 0 && t2<(int) PA2.size())
                t2++;
            if(t1 < t2)
                t = t1;
            else
                t = t2;

            solucion.bitfield.expo = solucion.bitfield.expo - t;
            for(int j = 0; j<t ; j++)
            {

            for(int i=0;i<(int)PA[0].size()-1;i++)
                PA[0][i] = PA[0][i+1];

            PA[0][PA[0].size()-1] = PA[1][0];

            for(int i=0;i<(int)PA[1].size()-1;i++)
                PA[1][i] = PA[1][i+1];
            PA[1][PA[1].size()-1] = 0x30;
            }

        }else
        {
            //resultado denormal
        }
    }
    string mantisaMultiplicacion = PA[0];
    mantisaMultiplicacion.erase(0,1);
    solucion.bitfield.partFrac = binaryToDec(mantisaMultiplicacion);
    solucion.nan = false;
    return solucion;
}

string *Alu::multiplicacionBinariaSinSigno(string A, string B)
{
    string P = "000000000000000000000000";
    string A2 = A;
    int n = 24;
    int C = 0; //acarreo

    for(int j=0; j<n;j++)
    {
        C=0;
        if(strncmp(&A2[23], "1", 1) == 0){
            BinYAcarreo suma =  sumaNumerosBinarios(P, B);
            P = suma.binario;
            C = suma.acarreo;
           }
        for(int k=23;k>0;k--)
            A2[k] = A2[k-1];

        A2[0] = P[23];

        for(int k=23;k>0;k--)
           P[k] = P[k-1];

        if(C==0)
        P[0] = 0x30; // cero
        else
        P[0] = 0x31; // uno
    }

    string *PA = new string[3];
    PA[0] = P;
    PA[1] = A2;

    return PA;
}

Alu::Code Alu::division(float operador1, float operador2)
{

    Code solucion;

    //Casos especiales

    if(operador2==0){
        solucion.nan = true;
        return solucion;
    }
    /*if(operador1 == 0){
        solucion.bitfield.expo=0;
        solucion.bitfield.sign=0;
        solucion.bitfield.partFrac=0;
        return solucion;
    }*/


    string Aesc = escalar(decToBinaryIEEE(operador1)), Besc = escalar(decToBinaryIEEE(operador2));
    Code operador1C, operador2C;

    operador1C.numero = operador1;
    operador2C.numero = operador2;

    float X0, Y0, X1, Y1, r;
    float Af = fraccionarBinaryToDec(Aesc), Bf = fraccionarBinaryToDec(Besc), Bp=0.00;

    if(Bf>=1 && Bf<1.25)
        Bp=1.00;
    else if(Bf>= 1.25 && Bf<2)
        Bp=0.8;

    if(operador1C.bitfield.sign==1 ^ operador2C.bitfield.sign==1)
        solucion.bitfield.sign=1;
    else
        solucion.bitfield.sign=0;

    X0 = producto(Af, Bp).numero;
    Y0 = producto(Bf, Bp).numero;
    bool bucle = true;

    do{
       r = suma(2, -Y0).numero;
       Y1 = producto(Y0,r).numero;
       X1 = producto(X0,r).numero;

       if(X1 - X0 >= 0.0001){
           bucle = false;
       }else{
           X0 = X1;
           Y0 = Y1;
        }
    }while(bucle);

    Code division;
    division.numero = X1;

    solucion.bitfield.expo = suma(suma(operador1C.bitfield.expo, -operador1C.bitfield.expo).numero, division.bitfield.expo).numero;
    solucion.bitfield.partFrac = division.bitfield.partFrac;

    return solucion;
}







