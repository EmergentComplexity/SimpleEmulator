#include "lcdwindow.h"
#include "ui_lcdwindow.h"

LCDwindow::LCDwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LCDwindow)
{
    ui->setupUi(this);
}

LCDwindow::~LCDwindow()
{
    delete ui;
}
