#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ramwindow.h"
#include <QTimer>
#include "4_Bit_Low_Level.cpp"
#include "4_Bit_High_Level.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->clockbutton, SIGNAL(clicked()), this, SLOT(CLOCKButtonPressed()));
    ui->currentInstructionBox->setText( QString::number(currentCount));
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::AutoClock));
    connect(ui->ClockStart, SIGNAL(clicked()), this, SLOT(ClockStart()));
    connect(ui->ClockStop, SIGNAL(clicked()), this, SLOT(ClockStop()));

    // low level emu clk
    connect(timer2, &QTimer::timeout, this, QOverload<>::of(&MainWindow::AutoClock2));
    connect(ui->ClockStart_2, SIGNAL(clicked()), this, SLOT(ClockStart2()));
    connect(ui->ClockStop_2, SIGNAL(clicked()), this, SLOT(ClockStop2()));

    // 8 Bit emu clk
    connect(timer3, &QTimer::timeout, this, QOverload<>::of(&MainWindow::AutoClock8B));
    connect(ui->ClockStart8, SIGNAL(clicked()), this, SLOT(ClockStart8B()));
    connect(ui->ClockStop8, SIGNAL(clicked()), this, SLOT(ClockStop8B()));
    InstructionDecoder();
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


// When a file is opened
void MainWindow::on_actionOpen_triggered() {
    if(isHL4 == true) {
        QString filename = QFileDialog::getOpenFileName(this, "Open the file");                        //This portion of the code opens and reads the code from assembly
        QFile file(filename);                                                                          //From the previous code, it will read individual lines to
        currentFile = filename;                                                                        //get the function, this is the first part of the test to see
        if(!file.open(QIODevice::ReadOnly | QFile::Text)){                                             //if we can get the lines, tested good
            QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        }
        setWindowTitle(filename);
        QTextStream in(&file);
        int j = 0;
        while(!in.atEnd()) {
            QString line = in.readLine();
            if(line.isEmpty() == false) { // ignore blank lines
                // here we are going to interpret the file and write appropriate data to rom
                QStringList list = line.split(" ");
                mnemonics[j] = list.at(0); // this is a QString array with all of the mneumonics for the instructions
                InstructionEncoder(mnemonics[j], list.at(1), &ROM[j]);
                ROMLoaded = true; // now we can run the program because the rom has been loaded
                currentCount = -1; // reset to do the first instruction
                if ((mnemonics[j] == "HLT")) {
                    j = 0;
                    AppendROM( &head, ROM);

                    // now clear rom array
                    for(int i = 0; i < 16; i++) {
                        ROM[i] = 0;
                    }
                }
                else {
                    j++;
                }
            }
       }

        // if there was no HLT in the program file, still add the file to the list
        if ((mnemonics[j-1] != "HLT")) {
            AppendROM( &head, ROM);
            // now clear rom array
            for(int i = 0; i < 16; i++) {
                ROM[i] = 0;
            }
        }
        current = head;
        file.seek(0);
        QString text = in.readAll();
        ui->textEdit->setText((text));
   }


   else if(isLL4 == true) {
        QString filename = QFileDialog::getOpenFileName(this, "Open the file");                        //This portion of the code opens and reads the code from assembly
        QFile file(filename);                                                                          //From the previous code, it will read individual lines to
        currentFile = filename;                                                                        //get the function, this is the first part of the test to see
        if(!file.open(QIODevice::ReadOnly | QFile::Text)){                                             //if we can get the lines, tested good
            QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        }
        setWindowTitle(filename);
        QTextStream in(&file);
        int j = 0;
        while(!in.atEnd()) {
            QString line = in.readLine();
            if(line.isEmpty() == false) { // ignore blank lines
                // here we are going to interpret the file and write appropriate data to rom
                QStringList list = line.split(" ");
                mnemonics[j] = list.at(0); // this is a QString array with all of the mneumonics for the instructions
                InstructionEncoder(mnemonics[j], list.at(1), &ROM[j]);
                ROMLoaded = true; // now we can run the program because the rom has been loaded
                currentCount = -1; // reset to do the first instruction
                if ((mnemonics[j] == "HLT")) {
                    j = 0;
                    AppendROM( &head, ROM);

                    // now clear rom array
                    for(int i = 0; i < 16; i++) {
                        ROM[i] = 0;
                    }
                }
                else {
                    j++;
                }
            }
       }

        // if there was no HLT in the program file, still add the file to the list
        if ((mnemonics[j-1] != "HLT")) {
            AppendROM( &head, ROM);
            // now clear rom array
            for(int i = 0; i < 16; i++) {
                ROM[i] = 0;
            }
        }
        current = head;
        file.seek(0);
        QString text = in.readAll();
        ui->textEdit_2->setText((text));
        // fill simulated rom chips
        for( int i = 0; i < 16; i++) {
            InstructionRom.Update(0,0, i, ((current->Values[i] & 0b11110000) >> 4));
            DataRom.Update(0,0, i,(current->Values[i] & 0b00001111));
        }
    }

   else if(isHL8 == true) {
        QString filename = QFileDialog::getOpenFileName(this, "Open the file");                        //This portion of the code opens and reads the code from assembly
        QFile file(filename);                                                                          //From the previous code, it will read individual lines to
        currentFile = filename;                                                                        //get the function, this is the first part of the test to see
        if(!file.open(QIODevice::ReadOnly | QFile::Text)){                                             //if we can get the lines, tested good
            QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        }
        setWindowTitle(filename);
        QTextStream in(&file);
        int j = 0;
        while(!in.atEnd()) {
            QString line = in.readLine();
            if(line.isEmpty() == false) { // ignore blank lines
                // here we are going to interpret the file and write appropriate data to rom
                QStringList list = line.split(" ");
                mnemonics[j] = list.at(0); // this is a QString array with all of the mneumonics for the instructions
                InstructionEncoder8(mnemonics[j], list.at(1), &ROM[j]);
                ROMLoaded = true; // now we can run the program because the rom has been loaded
                currentCount = -1; // reset to do the first instruction
                if ((mnemonics[j] == "HLT")) {
                    j = 0;
                    AppendROM8B( &head8, ROM);

                    // now clear rom array
                    for(int i = 0; i < 256; i++) {
                        ROM[i] = 0;
                    }
                }
                else {
                    j++;
                }
            }
       }

        // if there was no HLT in the program file, still add the file to the list
        if ((mnemonics[j-1] != "HLT")) {
            AppendROM8B( &head8, ROM);
            // now clear rom array
            for(int i = 0; i < 256; i++) {
                ROM[i] = 0;
            }
        }
        current8 = head8;
        file.seek(0);
        QString text = in.readAll();
        ui->textEdit8->setText((text));
    }


}




// When you execute the 4 bit high level emulator from the home page
void MainWindow::on_button_4bit_clicked()
{

    // clear ram
    for(int i = 0; i < 16; i++) {
        Ram[i] = 0;
    }

    // clear list
    while (current != NULL)
      {
          ROMS *next = current->next;
          free(current);
          current = next;
      }

      head = NULL;
      // reset values
      printstr.clear();
      timer->stop();
      ui->textEdit->clear();
      ui->AccumulatorBox->clear();
      ui->AddressField->clear();
      ui->INPUTREG->clear();
      ui->OUTPUTREG->clear();
      ui->testbox->clear();
      isHL4 = true;
    ui->stackedWidget->setCurrentIndex(1);
}

// When you execute the 4 bit low level emulator from the home page
void MainWindow::on_button_4bit_LowLevel_clicked()
{
    //
    ui->stackedWidget->setCurrentIndex(2);
   // int ROM [16] = {0b10000000, 0b00110001, 0b10000000, 0b00010001,0b10010000,0b01010000,0,0,0,0,0,0,0,0,0,0}; // this is the program being run

    // fill simulated rom chips
    for( int i = 0; i < 16; i++) {
        InstructionRom.Update(0,0, i, ((0 & 0b11110000) >> 4));
        DataRom.Update(0,0, i,(0 & 0b00001111));
    }
    isLL4 = true;
}

// When you execute the 8 bit high level emulator from the home page
void MainWindow::on_button_8bit_clicked()
{
    isHL8 = true;
    ui->stackedWidget->setCurrentIndex(3);
}






// go back to the home page
void MainWindow::on_change_sim_clicked() {
    isHL4 = false;
    isLL4 = false;
    isHL8 = false;
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_change_sim_2_clicked() {
    isHL4 = false;
    isLL4 = false;
    isHL8 = false;
    ui->stackedWidget->setCurrentIndex(0);
}

// go back homme from 8-bit emu
void MainWindow::on_change_sim_5_clicked() {
    isHL4 = false;
    isLL4 = false;
    isHL8 = false;
    ui->stackedWidget->setCurrentIndex(0);
}

