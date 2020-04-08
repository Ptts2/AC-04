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

    float resultado = this->alu.suma(/*operadores*/);

    /*Ejemplo de resultado*/
    ui->resultado_dec->setText(QString::fromStdString(to_string(resultado)));
}

void MainWindow::on_boton_producto_pressed()
{

    float resultado = this->alu.producto(/*operadores*/);

    /*Ejemplo de resultado*/
    ui->resultado_dec->setText(QString::fromStdString(to_string(resultado)));
}


void MainWindow::on_boton_division_pressed()
{

    float resultado = this->alu.division(/*operadores*/);

    /*Ejemplo de resultado*/
    ui->resultado_dec->setText(QString::fromStdString(to_string(resultado)));

}
