#include "numpadwindow.h"
#include "ui_numpadwindow.h"

NumPadWindow::NumPadWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NumPadWindow)
{
    ui->setupUi(this);
}

NumPadWindow::~NumPadWindow()
{
    delete ui;
}
