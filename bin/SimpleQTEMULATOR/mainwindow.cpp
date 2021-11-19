#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ramwindow.h"
#include <QTimer>

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
    InstructionDecoder();
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::ClockStart() {
    int freq = (1.00/ui->ClockEdit->text().toFloat() ) * (float)1000;
    ui->currentInstructionBox->setText( QString::number(currentCount));
    timer->start(freq);

}
void MainWindow::ClockStop() {
    timer->stop();
}
void MainWindow::AutoClock() {
    if(ROMLoaded == true) { // you can only run the code after the ROM is Loaded

        currentCount++;
        if (currentCount > 15) {
            currentCount = -1;
            if (current->next != NULL) {
                current = current->next;
            }
            else {
                 ROMLoaded = false;
            }
        }
        else if( currentCount > -1) { // -1 is used to initialize, but there is no -1 index of the ROM array
            //ui->currentInstructionBox->setText( QString::number(currentCount));
            //ui->currentInstructionBox->setText( QString::number(Ram[7]));
            InstructionDecoder();
        }

    }
    // TODO: add label that says to open a file if there is no rom loaded

}



void MainWindow::CLOCKButtonPressed() {
    if(ROMLoaded == true) { // you can only run the code after the ROM is Loaded

        currentCount++;
        if (currentCount > 15) {
            currentCount = -1;
            if (current->next != NULL) {
                current = current->next;
            }
            else {
                 ROMLoaded = false;
            }
        }
        else if( currentCount > -1) { // -1 is used to initialize, but there is no -1 index of the ROM array
            ui->currentInstructionBox->setText( QString::number(currentCount));
            //ui->currentInstructionBox->setText( QString::number(Ram[7]));

            InstructionDecoder();
        }

    }


}
void MainWindow::InstructionDecoder() {

    if (current != NULL) {
    opcode = current->Values[currentCount] >> 4;
    data = current->Values[currentCount] & 0b00001111;

   if ( (current->Values[currentCount - 1] >> 4) == 0b0000) {
        printstr = " Hello";  // clear string after HLT
   }
    switch(opcode) {
        case 0b0000: { // HLT: This effectively stops the clock
            ui->currentInstructionName->setText( "HLT");

            if (current->next != NULL) {
                currentCount = -1;
                current = current->next;
            }
            else {
                 ROMLoaded = false;
            }

            break;
        }

        case 0b0001: { // ADD: This adds whatever is in the specified RAM address to whatever is in the accumulator
            ui->currentInstructionName->setText( "ADD");
            accumulator = accumulator + Ram[data];
            break;
        }

        case 0b0010: { // SUB: This subtracts whatever is in the specified RAM address from whatever is in the accumulator
            ui->currentInstructionName->setText( "SUB");
            accumulator = accumulator - Ram[data];
            break;
        }

        case 0b0011: { // STO: this is the command used to write to RAM
            Ram[data] = accumulator;
            ui->currentInstructionName->setText( "STO");
            break;
        }

        case 0b0100: {// LD: this is the command used to read from RAM
            accumulator = Ram[data];
            ui->currentInstructionName->setText( "LD");
            break;
        }

        case 0b0101: { // B: this is an unconditional branch
            ui->currentInstructionName->setText( "B");
            currentCount = data -1; // unconditional jump -1 t0 get rid of the counter increment
            break;
        }

        case 0b0110: { // BZ: this is a conditional branch
            ui->currentInstructionName->setText( "BZ");
            if (accumulator == 0) {
                currentCount = data-1;
                }
            break;
        }

        case 0b0111: { // LDV: this is the command used to load a constant
            accumulator = data;
            ui->currentInstructionName->setText( "LDV");
            break;
        }

        case 0b1000: { // INP: Read input register into the accumulator, This is simulated with a QLineEdit to read data from. In hardware, the input register would be connected to input periphrials which would have to be emulated here as well
            ui->currentInstructionName->setText( "INP");
            QString displayVal = ui->INPUTREG->text();
            accumulator = displayVal.toInt();
            break;
        }

        case 0b1001: { // OUT: write the accumulator to the output register, This is simulated with a QLineEdit to write data to. In hardware, the output register would be connected to output periphrials which would have to be emulated here as well
            ui->currentInstructionName->setText( "OUT");
            ui->OUTPUTREG->setText(QString::number(accumulator));
            break;
        }

        case 0b1010: { // AND: Bitwise AND with whatever is in the accumulator and whatever is in the specified address
            ui->currentInstructionName->setText( "AND");
            accumulator = accumulator & Ram[data];
            break;
        }

        case 0b1011: { // OR: Bitwise OR with whatever is in the accumulator and whatever is in the specified address
            ui->currentInstructionName->setText( "OR");
            accumulator = accumulator | Ram[data];
            break;

        }

        case 0b1100: { // NOT: Bitwise NOT with whatever is in the accumulator
            ui->currentInstructionName->setText( "NOT");
            accumulator = !accumulator;
            break;
        }

        case 0b1101: { // This instruction is free
            ui->currentInstructionName->setText( "FREE");

            break;
        }

        case 0b1110: {
            ui->currentInstructionName->setText( "FREE");

            break;
        }
        case 0b1111: {
            ui->currentInstructionName->setText( "FREE");

            break;
        }
    }
    }
    printstr = printstr  + ui->currentInstructionName->text() + " " + QString("%1").arg(data, 8, 2, QChar('0')) +  "\n";
    ui->testbox->setText(printstr);
}




// Assembly code example:

/*
       This program will add 2 numbers and output the sum in an infinite loop
   PC ROM Value  ASM

   0  0b10000000 INP 0000   ; Input a value, 0000 because INP doesnt need an operand
   1  0b00110001 STO 0001   ; Store the value inputed to address 1
   2  0b10000000 INP 0000   ; Input another value
   3  0b00010001 ADD 0001   ; sum of 2 inputed values, the first value entered is in address 1 and the second is still in the accumulator
   4  0b10010000 OUT 0000   ; output the sum, the accumulator is written to the output register, 0000 because OUT doesnt need an operand
   5  0b01010000 B   0000   ; unconditional branch to set program counter to ROM address 0 to create infinite loop
   */
// The 4 most significant bits represent the MNEUMONIC EX: INP, STO, ADD, etc..
//  - this tells what instruction to do
// THe 4 least significant bits represent the DATA EX: 0000, 0001, etc..
//  - this gives data, it could be an address, constant, or unused depending on the instruction






void MainWindow::on_actionOpen_triggered()
{
      //Ram [16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // clear the ram
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");                            //This portion of the code opens and reads the code from assembly
        QFile file(filename);                                                                          //From the previous code, it will read individual lines to
        currentFile = filename;                                                                        //get the function, this is the first part of the test to see
        if(!file.open(QIODevice::ReadOnly | QFile::Text)){                                             //if we can get the lines, tested good
            QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        }
        setWindowTitle(filename);
        QTextStream in(&file);
       // int i = 0;
        int j = 0;

        while(!in.atEnd())
        {
            QString line = in.readLine();

            if(line.isEmpty() == false) { // ignore blank lines


                // here we are going to interpret the file and write appropriate data to rom

                QStringList list = line.split(" ");
                mnemonics[j] = list.at(0); // this is a QString array with all of the mneumonics for the instructions
                //
                InstructionEncoder(mnemonics[j], list.at(1), &ROM[j]);
                ROMLoaded = true; // now we can run the program because the rom has been loaded
                currentCount = -1; // reset to do the first instruction

                //i++; // keep track of the lines with code on them


                if ((mnemonics[j] == "HLT")) {
                  //  i = j;
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
            //i = j;
            //j = 0;
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




void MainWindow::InstructionEncoder(QString mnemonic, QString data, int* ROM) {
    if (mnemonic == "HLT") {
        *ROM = 0b00000000;
    }

    else if (mnemonic == "ADD") {
        *ROM = 0b00010000;
    }
    else if (mnemonic == "SUB") {
        *ROM = 0b00100000;
    }
    else if (mnemonic == "STO") {
        *ROM = 0b00110000;
    }
    else if (mnemonic == "LD") {
        *ROM = 0b01000000;
    }
    else if (mnemonic == "B") {
        *ROM = 0b01010000;
    }
    else if (mnemonic == "BZ") {
        *ROM = 0b01100000;
    }

    else if (mnemonic == "LDV") {
        *ROM = 0b01110000;
    }

    else if (mnemonic == "INP") {
        *ROM = 0b10000000;
    }
    else if (mnemonic == "OUT") {
        *ROM = 0b10010000;
    }
    else if (mnemonic == "AND") {
        *ROM = 0b10100000;
    }
    else if (mnemonic == "OR") {
        *ROM = 0b10110000;
    }
    else if (mnemonic == "NOT") {
        *ROM = 0b11000000;
    }

    // ADD the free instructions
    /*
    else if (mnemonic == "XXXX") {
        *ROM = 0b11010000;
    }
    else if (mnemonic == "XXXX") {
        *ROM = 0b11100000;
    }
    else if (mnemonic == "XXXX") {
        *ROM = 0b11110000;
    }
    */
    bool fOK;
    int dataINT = data.toInt(&fOK,2);
    // make sure only the first 4 bits are read

    *ROM =   *ROM | dataINT;
}

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
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_button_8bit_clicked()
{
    //
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_change_sim_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_change_sim_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::AppendROM( ROMS ** NodeHead, int ROM[16]) {
    ROMS* new_rom = new ROMS();
    ROMS* last = *NodeHead;
    for(int i = 0; i < 16; i++) {
        new_rom->Values[i] = ROM[i];
    }
    new_rom->next = NULL;
    if (*NodeHead == NULL) {
        *NodeHead = new_rom;
        return;
    }

    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_rom;
    return;
}
