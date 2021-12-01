#include "ramwindow.h"
#include "ui_ramwindow.h"
#include "mainwindow.h"

RamWindow::RamWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RamWindow)
{
    ui->setupUi(this);
}

RamWindow::~RamWindow()
{
    delete ui;
}
