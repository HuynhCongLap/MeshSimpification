#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(onButton()));
}

void MainWindow::onButton()
{

        ui->widget->wireFrame = true ;

}

MainWindow::~MainWindow()
{
    delete ui;
}
