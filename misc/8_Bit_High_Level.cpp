include "mainwindow.h"
#include "ui_mainwindow.h"

// for the 8 bit high level emu
// this version should be able to take in a longer program up to 256 instructions rather than 16



void MainWindow::ClockStart8B() {
    int freq = (1.00/ui->ClockEdit->text().toFloat() ) * (float)1000;
    ui->currentInstructionBox8->setText( QString::number(currentCount));
    timer3->start(freq);

}
void MainWindow::ClockStop8B() {
    timer3->stop();
}




void MainWindow::AutoClock8B() {
    if(ROMLoaded == true) { // you can only run the code after the ROM is Loaded

        currentCount++;
        if (currentCount > 255) {
            currentCount = -1;
            if (current8->next != NULL) {
                current8 = current8->next;
            }
            else {
                 ROMLoaded = false;
            }
        }
        else if( currentCount > -1) { // -1 is used to initialize, but there is no -1 index of the ROM array
            InstructionDecoder8B();
        }

    }

}



void MainWindow::CLOCKButtonPressed8B() {
    if(ROMLoaded == true) { // you can only run the code after the ROM is Loaded

        currentCount++;
        if (currentCount > 255) {
            currentCount = -1;
            if (current8->next != NULL) {
                current8 = current8->next;
            }
            else {
                 ROMLoaded = false;
            }
        }
        else if( currentCount > -1) { // -1 is used to initialize, but there is no -1 index of the ROM array
            ui->currentInstructionBox8->setText( QString::number(currentCount));
            InstructionDecoder8B();
        }

    }
}

void MainWindow::InstructionDecoder8B() {

    if (current != NULL) {
    opcode = current8->Values[currentCount] >> 4;
    data = current8->Values[currentCount] & 0b00001111;

   if ( (current8->Values[currentCount - 1] >> 4) == 0b0000) {
        printstr = " Hello";  // clear string after HLT
   }
    switch(opcode) {
        case 0b0000: { // HLT: This effectively stops the clock
            ui->currentInstructionName8->setText( "HLT");

            if (current8->next != NULL) {
                currentCount = -1;
                current8 = current8->next;
            }
            else {
                 ROMLoaded = false;
            }

            break;
        }

        case 0b0001: { // ADD: This adds whatever is in the specified RAM address to whatever is in the accumulator
            ui->currentInstructionName8->setText( "ADD");
            accumulator = accumulator + Ram[data];
            break;
        }

        case 0b0010: { // SUB: This subtracts whatever is in the specified RAM address from whatever is in the accumulator
            ui->currentInstructionName8->setText( "SUB");
            accumulator = accumulator - Ram[data];
            break;
        }

        case 0b0011: { // STO: this is the command used to write to RAM
            Ram[data] = accumulator;
            ui->currentInstructionName8->setText( "STO");
            break;
        }

        case 0b0100: {// LD: this is the command used to read from RAM
            accumulator = Ram[data];
            ui->currentInstructionName8->setText( "LD");
            break;
        }

        case 0b0101: { // B: this is an unconditional branch
            ui->currentInstructionName8->setText( "B");
            currentCount = data -1; // unconditional jump -1 t0 get rid of the counter increment
            break;
        }

        case 0b0110: { // BZ: this is a conditional branch
            ui->currentInstructionName8->setText( "BZ");
            if (accumulator == 0) {
                currentCount = data-1;
                }
            break;
        }

        case 0b0111: { // LDV: this is the command used to load a constant
            accumulator = data;
            ui->currentInstructionName8->setText( "LDV");
            break;
        }

        case 0b1000: { // INP: Read input register into the accumulator, This is simulated with a QLineEdit to read data from. In hardware, the input register would be connected to input periphrials which would have to be emulated here as well
            ui->currentInstructionName8->setText( "INP");
            QString displayVal = ui->INPUTREG8->text();
            accumulator = displayVal.toInt();
            break;
        }

        case 0b1001: { // OUT: write the accumulator to the output register, This is simulated with a QLineEdit to write data to. In hardware, the output register would be connected to output periphrials which would have to be emulated here as well
            ui->currentInstructionName8->setText( "OUT");
            ui->OUTPUTREG8->setText(QString::number(accumulator));
            break;
        }

        case 0b1010: { // AND: Bitwise AND with whatever is in the accumulator and whatever is in the specified address
            ui->currentInstructionName8->setText( "AND");
            accumulator = accumulator & Ram[data];
            break;
        }

        case 0b1011: { // OR: Bitwise OR with whatever is in the accumulator and whatever is in the specified address
            ui->currentInstructionName8->setText( "OR");
            accumulator = accumulator | Ram[data];
            break;

        }

        case 0b1100: { // NOT: Bitwise NOT with whatever is in the accumulator
            ui->currentInstructionName8->setText( "NOT");
            accumulator = !accumulator;
            break;
        }

        case 0b1101: { // This instruction is free
            ui->currentInstructionName8->setText( "FREE");

            break;
        }

        case 0b1110: {
            ui->currentInstructionName8->setText( "FREE");

            break;
        }
        case 0b1111: {
            ui->currentInstructionName8->setText( "FREE");

            break;
        }
    }
    }
    ui->AccumulatorBox8->setText(QString::number(accumulator));
    printstr = printstr  + ui->currentInstructionName->text() + " " + QString("%1").arg(data, 8, 2, QChar('0')) +  "\n";
    ui->testbox8->setText(printstr);
}







void MainWindow::InstructionEncoder8(QString mnemonic, QString data, int* ROM) {
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


void MainWindow::AppendROM8B( ROMS8Bit ** NodeHead, int ROM[256]) {
    ROMS8Bit* new_rom = new ROMS8Bit();
    ROMS8Bit* last = *NodeHead;
    for(int i = 0; i < 256; i++) {
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
