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

std::string MainWindow::getHexString(unsigned int hex){

    string representacionHex = "0x";
    std::ostringstream numeroHex;
    numeroHex<<std::hex<<std::uppercase<< hex;
    representacionHex+= numeroHex.str();

    return representacionHex;

}

void MainWindow::setIEEEOperands(){
    float op1 = atof(ui->operando1->text().toStdString().c_str());
    float op2 = atof(ui->operando2->text().toStdString().c_str());

    Alu::Code op1IEEE = alu.fromDecToIEEE754(op1);
    Alu::Code op2IEEE = alu.fromDecToIEEE754(op2);


    if(op1IEEE.bitfield.expo-127 > 127){
        ui->op1_IEEE->setText(QString::fromStdString("inf"));
        ui->op1_hex->setText(QString::fromStdString("inf"));
    }else{
        ui->op1_IEEE->setText(QString::fromStdString(to_string( op1IEEE.bitfield.sign ) + " " + alu.decToBinaryIEEE(op1IEEE.bitfield.expo, 8).parteEntera + " " + alu.decToBinaryIEEE( op1IEEE.bitfield.partFrac).parteEntera));
        ui->op1_hex->setText( QString::fromStdString(getHexString(op1IEEE.numerox)) );
    }

    if(op2IEEE.bitfield.expo-127 > 127){
        ui->op2_IEEE->setText(QString::fromStdString("inf"));
        ui->op2_hex->setText(QString::fromStdString("inf"));
    }else{
        ui->op2_IEEE->setText(QString::fromStdString(to_string( op2IEEE.bitfield.sign ) + " " + alu.decToBinaryIEEE(op2IEEE.bitfield.expo, 8).parteEntera + " " + alu.decToBinaryIEEE( op2IEEE.bitfield.partFrac).parteEntera));
        ui->op2_hex->setText( QString::fromStdString(getHexString(op2IEEE.numerox)) );
    }


}
void MainWindow::on_boton_suma_pressed()
{

    float op1 = atof(ui->operando1->text().toStdString().c_str());
    float op2 = atof(ui->operando2->text().toStdString().c_str());

    //Poner hexadecimal y IEEE754 operadores

    this->setIEEEOperands();

    //Operacion

    Alu::Code resultado = this->alu.suma(op1, op2);

    Alu::Binario op1bin =alu.decToBinaryNormal(op1);
    Alu::Binario compA2 = alu.complementoA2(op1bin);

    ui->resultado_dec->setText( QString::fromStdString( to_string(resultado.numero) ));
    ui->resultado_IEEE->setText(QString::fromStdString(to_string( resultado.bitfield.sign ) + " " + alu.decToBinaryIEEE(resultado.bitfield.expo, 8).parteEntera + " " + alu.decToBinaryIEEE( resultado.bitfield.partFrac).parteEntera));
    ui->resultado_hex->setText( QString::fromStdString(getHexString(resultado.numerox)) );

}


void MainWindow::on_boton_producto_pressed()
{

    this->setIEEEOperands();
    float op1 = atof(ui->operando1->text().toStdString().c_str());
    float op2 = atof(ui->operando2->text().toStdString().c_str());

    Alu::Code resultado = this->alu.producto(op1, op2);

    if(resultado.nan)
    {
        ui->resultado_dec->setText( QString::fromStdString( "NaN" ));
        ui->resultado_IEEE->setText(QString::fromStdString( "NaN" ));
        ui->resultado_hex->setText( QString::fromStdString( "NaN" ));
    }else
    {
        ui->resultado_dec->setText( QString::fromStdString( to_string(resultado.numero) ));
        ui->resultado_IEEE->setText(QString::fromStdString(to_string( resultado.bitfield.sign ) + " " + alu.decToBinaryIEEE(resultado.bitfield.expo, 8).parteEntera + " " + alu.decToBinaryIEEE( resultado.bitfield.partFrac).parteEntera));
        ui->resultado_hex->setText( QString::fromStdString(getHexString(resultado.numerox)) );
    }
}


void MainWindow::on_boton_division_pressed()
{


    this->setIEEEOperands();
    float op1 = atof(ui->operando1->text().toStdString().c_str());
    float op2 = atof(ui->operando2->text().toStdString().c_str());

    Alu::Code resultado = this->alu.division(op1, op2);

    if(resultado.nan)
    {
        ui->resultado_dec->setText( QString::fromStdString( "NaN" ));
        ui->resultado_IEEE->setText(QString::fromStdString( "NaN" ));
        ui->resultado_hex->setText( QString::fromStdString( "NaN" ));
    }else
    {
        ui->resultado_dec->setText( QString::fromStdString( to_string(resultado.numero) ));
        ui->resultado_IEEE->setText(QString::fromStdString(to_string( resultado.bitfield.sign ) + " " + alu.decToBinaryIEEE(resultado.bitfield.expo, 8).parteEntera + " " + alu.decToBinaryIEEE( resultado.bitfield.partFrac).parteEntera));
        ui->resultado_hex->setText( QString::fromStdString(getHexString(resultado.numerox)) );
    }

}
