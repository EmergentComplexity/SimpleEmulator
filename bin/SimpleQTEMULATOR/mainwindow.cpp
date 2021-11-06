#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->clockbutton, SIGNAL(clicked()), this, SLOT(CLOCKButtonPressed()));
    ui->currentInstructionBox->setText( QString::number(currentCount));
    InstructionDecoder();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CLOCKButtonPressed() {

    ui->currentInstructionBox->setText( QString::number(currentCount));
    currentCount++;
    if (currentCount > 15) {
        currentCount = 0;
    }
     ui->currentInstructionBox->setText( QString::number(currentCount));
   InstructionDecoder();


}
void MainWindow::InstructionDecoder() {
    opcode = ROM[currentCount] >> 4;
    data = ROM[currentCount] & 0b00001111;
    switch(opcode) {
    case 0b0000:{
        ui->currentInstructionName->setText( "HLT");
            break;

    } // HLT: THis effectively stops the clock

               case 0b0001:{
        ui->currentInstructionName->setText( "ADD");
        accumulator = accumulator + Ram[data];
         break;
    } // ADD

               case 0b0010: {
        ui->currentInstructionName->setText( "SUB");
        accumulator = accumulator - Ram[data];
        break;
    }

        // SUB

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
                   currentCount = data -1; // unconditional jump -1 tp get rid of the counter increment
                   break;
               }
               case 0b0110: { // BZ: this is a conditional branch
                   ui->currentInstructionName->setText( "BZ");
                   if(accumulator == 0) {
                      currentCount = data-1;
                    }
                   break;
                  }
                case 0b0111: {
                    // pos
                        break;
                }

               case 0b1000: { // INP: Read input register into the accumulator, this  is simulated with scanf, whereas in actual hardware, you can change what is in the input register at any time, INP only controls when it is read
                   ui->currentInstructionName->setText( "INP");
                   QString displayVal = ui->INPUTREG->text();
                   accumulator = displayVal.toInt();
                   break;
               }


               case 0b1001: {// OUT: write the accumulator to the output register, this is simulated with printf, wheras in actual hardware, the output register always outputs its value, OUT only controls when the output value is changed
                   ui->currentInstructionName->setText( "OUT");
                   ui->OUTPUTREG->setText(QString::number(accumulator));
                   break;
                  }
               case 0b1010: {// AND
                   ui->currentInstructionName->setText( "AND");
                    break;
                    }
                    case 0b1100: {
                        //xor
                            break;

                    }

               case 0b1101: {// NOT

                   break;
                 }
           }
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
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");                            //This portion of the code opens and reads the code from assembly
        QFile file(filename);                                                                          //From the previous code, it will read individual lines to
        currentFile = filename;                                                                        //get the function, this is the first part of the test to see
        if(!file.open(QIODevice::ReadOnly | QFile::Text)){                                             //if we can get the lines, tested good
            QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        }
        setWindowTitle(filename);
        QTextStream in(&file);
        int i = 0;


        while(!in.atEnd())
        {
            QString line = in.readLine();

            if(line.isEmpty() == false) { // ignore blank lines


                // here we are going to interpret the file and write appropriate data to rom

                QStringList list = line.split(" ");
                mnemonics[i] = list.at(0); // this is a QString array with all of the mneumonics for the instructions
                //


                /* TODO:
                     - make a switch case to interpret the mueumonics as the 4 most significant bits
                     -- iterate through all mneumonics in array --

                     case mneunonics[x] == "INP":
                        ROM[x] = 0b10000000
                        break;
                     ROM[x] = ROM[x] | QString::number(list.at(1)); // list.at(1) gets the second word
                */
              i++;
            }


            // test code to print out the name of the mneumonic of every instruction
            QString printstr;
            for(int x=0; x < i; x++) {
               printstr = printstr  + mnemonics[x]+ "\n";
            }
            ui->testbox->setText(printstr);


        }
        file.seek(0);
        QString text = in.readAll();
        ui->textEdit->setText((text));

}

