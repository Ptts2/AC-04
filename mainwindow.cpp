#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "alu.h"
#include <string>
#include <regex>
#include <iostream>


using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: setIEEEOperands(){
    float op1 = atof(ui->operando1->text().toStdString().c_str());
    float op2 = atof(ui->operando2->text().toStdString().c_str());

    Alu::IEEE754num op1IEEE = alu.fromDecToIEEE754(op1);
    Alu::IEEE754num op2IEEE = alu.fromDecToIEEE754(op2);

    ui->op1_IEEE->setText(QString::fromStdString(to_string(op1IEEE.signo) + " " + op1IEEE.exponente + " " + op1IEEE.mantisa.parteFraccionaria));
    ui->op2_IEEE->setText(QString::fromStdString(to_string(op2IEEE.signo) + " " + op2IEEE.exponente + " " + op2IEEE.mantisa.parteFraccionaria));
}
void MainWindow::on_boton_suma_pressed()
{

    float op1 = atof(ui->operando1->text().toStdString().c_str());
    float op2 = atof(ui->operando2->text().toStdString().c_str());

    //Poner hexadecimal y IEEE754 operadores

    this->setIEEEOperands();

    //Operacion
    Alu::NumSolucion resultado = this->alu.suma(op1, op2);

    /*Ejemplo de resultado*/
    ui->resultado_dec->setText(QString::fromStdString(to_string(resultado.numDec)));

    //Por ahora solo pasa a binario
    ui->resultado_IEEE->setText(QString::fromStdString(resultado.numIEEE.mantisa.parteEntera+", "+resultado.numIEEE.mantisa.parteFraccionaria));

    ui->resultado_hex->setText(QString::fromStdString(to_string(resultado.numHex)));
}

void MainWindow::on_boton_producto_pressed()
{



    this->setIEEEOperands();

    Alu::NumSolucion resultado = this->alu.producto(0,0);

    //Ejemplo de resultado
    ui->resultado_dec->setText(QString::fromStdString(to_string(resultado.numDec)));
    ui->resultado_IEEE->setText(QString::fromStdString(resultado.numIEEE.mantisa.parteEntera+", "+resultado.numIEEE.mantisa.parteFraccionaria));
    ui->resultado_hex->setText(QString::fromStdString(to_string(resultado.numHex)));

}


void MainWindow::on_boton_division_pressed()
{


    this->setIEEEOperands();
    Alu::NumSolucion resultado = this->alu.division(0,0);

    /*Ejemplo de resultado*/
    ui->resultado_dec->setText(QString::fromStdString(to_string(resultado.numDec)));
    ui->resultado_IEEE->setText(QString::fromStdString(resultado.numIEEE.mantisa.parteEntera+", "+resultado.numIEEE.mantisa.parteFraccionaria));
    ui->resultado_hex->setText(QString::fromStdString(to_string(resultado.numHex)));
}
