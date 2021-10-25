#include "mainwindow.h"
#include "ui_mainwindow.h"


//void SetAButtonPressed();
//void SetDButtonPressed();
void RamOperations();
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->SetAButton, SIGNAL(released()), this, SLOT(SetAButtonPressed()));
    connect(ui->SetDButton, SIGNAL(released()), this, SLOT(SetDButtonPressed()));
    connect(ui->MECheckbox, SIGNAL(clicked()), this, SLOT(MECheckboxClicked()));
    connect(ui->WECheckbox, SIGNAL(clicked()), this, SLOT(WECheckboxClicked()));
    for(int i = 0; i<16;i++) {
        data[i] = 0;
    }
    ui->MECheckbox->setChecked(1);
    ui->MECheckbox->isChecked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetAButtonPressed() {
    QString displayVal = ui->AddressField->text();
    A = displayVal.toInt();
    RamOperations();
}
void MainWindow::SetDButtonPressed() {
    QString displayVal = ui->DatainFIeld->text();
    D = displayVal.toInt();
    RamOperations();


}

void MainWindow::MECheckboxClicked(){
    RamOperations();
}
void MainWindow::WECheckboxClicked() {
    RamOperations();
}

void MainWindow::RamOperations() {
    if ( ui->MECheckbox->isChecked() == false && ui->WECheckbox->isChecked() == false) { // write
        data[A] = D; // write operation
        ui->DataOutField->setText( QString::number(data[A]));
    }
    else if ( ui->MECheckbox->isChecked() == false && ui->WECheckbox->isChecked() == true) { // read
         ui->DataOutField->setText( QString::number(data[A]));
    }
    else { // hold
        ui->DataOutField->setText( QString::number(0));
   }

}
