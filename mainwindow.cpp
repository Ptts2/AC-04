#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <alu.h>
#include <string.h>


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

    Alu::NumSolucion resultado = this->alu.suma(6.3,0);

    /*Ejemplo de resultado*/
    ui->resultado_dec->setText(QString::fromStdString(to_string(resultado.numDec)));

    //Por ahora solo pasa a binario
    ui->resultado_IEEE->setText(QString::fromStdString(to_string(resultado.numIEEE.mantisa.parteEntera)+", "+to_string(resultado.numIEEE.mantisa.parteFraccionaria)));

    ui->resultado_hex->setText(QString::fromStdString(to_string(resultado.numHex)));
}

void MainWindow::on_boton_producto_pressed()
{

    Alu::NumSolucion resultado = this->alu.suma(0,0);

    /*Ejemplo de resultado*/
    ui->resultado_dec->setText(QString::fromStdString(to_string(resultado.numDec)));
    ui->resultado_IEEE->setText(QString::fromStdString(to_string(resultado.numIEEE.mantisa.parteEntera)+to_string(resultado.numIEEE.mantisa.parteFraccionaria)));
    ui->resultado_hex->setText(QString::fromStdString(to_string(resultado.numHex)));
}


void MainWindow::on_boton_division_pressed()
{

    Alu::NumSolucion resultado = this->alu.suma(0,0);

    /*Ejemplo de resultado*/
    ui->resultado_dec->setText(QString::fromStdString(to_string(resultado.numDec)));
    ui->resultado_IEEE->setText(QString::fromStdString(to_string(resultado.numIEEE.mantisa.parteEntera)+to_string(resultado.numIEEE.mantisa.parteFraccionaria)));
    ui->resultado_hex->setText(QString::fromStdString(to_string(resultado.numHex)));
}
