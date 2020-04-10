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

    Alu::Code op1IEEE = alu.fromDecToIEEE754(op1);
    Alu::Code op2IEEE = alu.fromDecToIEEE754(op2);

    ui->op1_IEEE->setText(QString::fromStdString(to_string( op1IEEE.bitfield.sign ) + " " + alu.decToBinary(op1IEEE.bitfield.expo).parteEntera + " " + alu.decToBinary( op1IEEE.bitfield.partFrac).parteEntera));
    ui->op2_IEEE->setText(QString::fromStdString(to_string( op2IEEE.bitfield.sign ) + " " + alu.decToBinary(op2IEEE.bitfield.expo).parteEntera + " " + alu.decToBinary( op2IEEE.bitfield.partFrac).parteEntera));
}
void MainWindow::on_boton_suma_pressed()
{

    float op1 = atof(ui->operando1->text().toStdString().c_str());
    float op2 = atof(ui->operando2->text().toStdString().c_str());

    //Poner hexadecimal y IEEE754 operadores

    this->setIEEEOperands();

    //Operacion

    Alu::NumSolucion resultado = this->alu.suma(op1, op2);
}

void MainWindow::on_boton_producto_pressed()
{

    this->setIEEEOperands();
    float op1 = atof(ui->operando1->text().toStdString().c_str());
    float op2 = atof(ui->operando2->text().toStdString().c_str());

    Alu::NumSolucion resultado = this->alu.producto(0,0);

}


void MainWindow::on_boton_division_pressed()
{


    this->setIEEEOperands();
    float op1 = atof(ui->operando1->text().toStdString().c_str());
    float op2 = atof(ui->operando2->text().toStdString().c_str());

    Alu::NumSolucion resultado = this->alu.division(0,0);


}
