#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "alu.h"
#include <string>
#include <regex>


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


void MainWindow::on_boton_suma_pressed()
{

    float op1 = atof(ui->operando1->text().toStdString().c_str());
    float op2 = atof(ui->operando2->text().toStdString().c_str());
    Alu::NumSolucion resultado = this->alu.suma(op1, op2);

    /*Ejemplo de resultado*/
    ui->resultado_dec->setText(QString::fromStdString(to_string(resultado.numDec)));

    //Por ahora solo pasa a binario
    ui->resultado_IEEE->setText(QString::fromStdString(to_string(resultado.numIEEE.mantisa.parteEntera)+", "+resultado.numIEEE.mantisa.parteFraccionaria));

    ui->resultado_hex->setText(QString::fromStdString(to_string(resultado.numHex)));
}

void MainWindow::on_boton_producto_pressed()
{

    Alu::NumSolucion resultado = this->alu.suma(0,0);

    /*Ejemplo de resultado*/
    ui->resultado_dec->setText(QString::fromStdString(to_string(resultado.numDec)));
    ui->resultado_IEEE->setText(QString::fromStdString(to_string(resultado.numIEEE.mantisa.parteEntera)+", "+resultado.numIEEE.mantisa.parteFraccionaria));
    ui->resultado_hex->setText(QString::fromStdString(to_string(resultado.numHex)));
}


void MainWindow::on_boton_division_pressed()
{

    Alu::NumSolucion resultado = this->alu.suma(0,0);

    /*Ejemplo de resultado*/
    ui->resultado_dec->setText(QString::fromStdString(to_string(resultado.numDec)));
    ui->resultado_IEEE->setText(QString::fromStdString(to_string(resultado.numIEEE.mantisa.parteEntera)+", "+resultado.numIEEE.mantisa.parteFraccionaria));
    ui->resultado_hex->setText(QString::fromStdString(to_string(resultado.numHex)));
}
