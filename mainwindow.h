#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <alu.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_boton_suma_pressed();

    void on_boton_producto_pressed();

    void on_boton_division_pressed();

    void setIEEEOperands();

private:
    Ui::MainWindow *ui;
    Alu alu;
};
#endif // MAINWINDOW_H
