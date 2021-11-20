#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::AutoClock));
    connect(ui->ClockStart, SIGNAL(clicked()), this, SLOT(ClockStart()));
    connect(ui->ClockStop, SIGNAL(clicked()), this, SLOT(ClockStop()));

    int ROM [16] = {0b10000000, 0b00110001, 0b10000000, 0b00010001,0b10010000,0b01010000,0,0,0,0,0,0,0,0,0,0}; // this is the program being run

    // fill simulated rom chips
    for( int i = 0; i < 16; i++) {
        InstructionRom.Update(0,0, i, ((ROM[i] & 0b11110000) >> 4));
        DataRom.Update(0,0, i,(ROM[i] & 0b00001111));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ClockStart() {
    int freq = (1.00/ui->ClockEdit->text().toFloat() ) * (float)1000;
    timer->start(freq /2);

}
void MainWindow::ClockStop() {
    timer->stop();
}

// Everything that the emulated computer does is here
void MainWindow::AutoClock() {
    clk++;
    if (clk > 1) {
        clk = 0;
    }
    ui->CLKEdit->setText( QString::number(clk));

    // updates here

   // The subcounter increments every clock cycle, once it reaches 4 it flips the SR latch which clocks the program counter and clears itself
   // the subcounter is needed because instructions can take more than one clock cycle to execute, so the subcounter can step through the instruction while the PC holds on that instruction
   SubCounter.Update(clk, latch.getQ(), 1,0b0000);
   ui->SubCountEdit->setText( QString::number(SubCounter.getCount()));
   latch.Update( clk, ((SubCounter.getCount() & 0b0100) >> 2));




   // The program Counter PC increments when the subcounter counts up to 4 and flips the latch for a clock cycle
   // The  PC is responsiable for addressing the program rom
   // If the decoded instruction is 'B' , the PC will load the data value from the rom, thus implementing a branch instruction
   // If the decoded instruction is 'BZ' and the value in the accumulator is 0 , the PC will load the data value from the rom, thus implementing a conditional branch instruction
   PC.Update(!latch.getQ(), 1, !(instructionDecoder.getB() || (instructionDecoder.getBZ() && (Accumulator.getRegVal() == 0))),DataRom.getRamVal());    // in hardware accumulator == 0 could be implemented by connecting all accumulator bits to a NOR gate
   ui->CountEdit->setText( QString::number(PC.getCount()));




   // 2 ram chips are used for the program memory, their address lines are tied together so they can store 8 bits in each location as they form a 16 byte rom
   // one of the ram chips stores the instruction and the other stores a data value whoose meaning is defined by the instruction ( it could be an address to branch to, point to a ram address, a constant value, or not used at all)
   InstructionRom.Update(1,0, PC.getCount(),0b0000);
   ui->InstructionRomEdit->setText( QString::number(InstructionRom.getRamVal()));
   DataRom.Update(1,0, PC.getCount(),0b0000);
   ui->DataRomEdit->setText( QString::number(DataRom.getRamVal()));

   // the instruction decoder decodes the instruction from the instruction Rom
   instructionDecoder.Update(InstructionRom.getRamVal());
   ShowDecoder();








   // ALU has 2 operands: A and B. A is always the accumulator. B could be the input, The Rom data, or the Ram data depending on the instruction
   // the other inputs to the ALU S, M and Cn determine the instruction that the ALU is doing; S is a 4 bit integer.  M and Cn are bools

   // The B input to the ALU could be the input, the Ram, or the data rom; these inputs are multiplexed to B based on the instruction
   // The multiplexer going to B is determined by the instruction decoder and stays that way throughout the instruction
   // The F output of the ALU is a bus going to the ALU register, the output register, and the ram; the output is written to the register or ram by clocking the register or writing the ram depending on the instruction
   // The inputs S, M and Cn are determined by the instruction decoder and stays that way throughout the instruction

   // writing to registers and to ram depends on the subcounter.
   // writing to ram , the alu register and the output register can be done earlier in the subcounter count
   // writing the accumulator must happen after though as it depends on the alu register being already updated
   // the alu register is necessary because for some operations, the accumulator is on both sides of the equation for the instruction so what the accumulator is going to be depends on the result of a past value through the ALU which must be stored
   // though the alu register is not needed for all of the instructions that uses it, doing so simplifies the schematic of data flow.

   // All instructions other than B and BZ involve the ALU
   // ADD takes the Ram output, adds it with the accumulator in the ALU, stores it in the ALU register and then the accumulator stores what is in the ALU register
   // SUB takes the Ram output, subs it from the accumulator in the ALU, stores it in the ALU register and then the accumulator stores what is in the ALU register
   // STO passes the accumulator value through the ALU, and writes the ram at the specified address
   // LD  takes the Ram output, passes it through the ALU, stores it in the ALU register and then the accumulator stores what is in the ALU register
   // LDV takes the Rom data, passes it through the ALU, stores it in the ALU register and then the accumulator stores what is in the ALU register
   // INP takes the input, passes it through the ALU, stores it in the ALU register and then the accumulator
   // OUT passes the accumulator value through the ALU  and stores it to the output register
   // AND takes the Ram output, ANDS it with the accumulator in the ALU, stores it in the ALU register and then the accumulator stores what is in the ALU register
   // OR  takes the Ram output, ORs it from the accumulator in the ALU, stores it in the ALU register and then the accumulator stores what is in the ALU register
   // NOT nots the accululator in the ALU, stores it in the ALU register and then the Accumulator

   // These instructions are decoded from the rom and then encoded again to ALU instructions by ALUEncoder()
   // ALU instructions:      S   M  Cn
   // ADD: (F = A+B)        1001 0  0
   // SUB: (F = A-B),       0110 0  1
   // STO, OUT: (F = A)     0000 0  1
   // LD, LDV, INP: (F = B) 1010 1  0
   // AND: ( F = A & B)     1110 1  0
   // OR: (F = A | B)       1011 1  0
   // NOT: (F = !A)         0000 1  0


   // The  input for ALU operand B
   // ADD, SUB, LD, AND, OR: -> RAM
   // LDV: -> dataRom
   // STO, NOT, OUT -> X
   // INP: input
   int B = 0;
   if((instructionDecoder.getADD() == true) || (instructionDecoder.getSUB() == true) || (instructionDecoder.getLD() == true) || (instructionDecoder.getAND() == true) || (instructionDecoder.getOR() == true)) {
       B = SystemRam.getRamVal();
   }
   else if(instructionDecoder.getLDV() == true) {
       B = DataRom.getRamVal();
   }
   else if(instructionDecoder.getINP() == true) {
       B = ui->INPEdit_2->text().toInt();
   }

   int EncoderVal = ALUEncoder();


   alu1.Update(Accumulator.getRegVal(), B, ((EncoderVal & 0b111100) >> 2), ((EncoderVal & 0b000010) >> 1), (EncoderVal & 0b000001));
   //


   // Now the Outputs
   // Outputs can write to a Register or to Ram
   // Ram, OUTRegister, ALURegister write on subclock == 1
   // Accumulator writes on subclock == 3;
   // these times are arbitrary as long as Accumulator writes after ALURegister
   // ADD, SUB, LD, LDV, AND, OR, NOT, INP write to the accumulator (and by extension to ALURegister)
   // STO writes to Ram
   // OUT writes to OUTRegister

   bool writeAccumALUreg = ( (instructionDecoder.getINP() == true) ||(instructionDecoder.getADD() == true) || (instructionDecoder.getSUB() == true) || (instructionDecoder.getLD() == true) || (instructionDecoder.getLDV() == true) || (instructionDecoder.getAND() == true) || (instructionDecoder.getOR() == true) || (instructionDecoder.getNOT() == true));
   bool writeAccum = ((SubCounter.getCount() == 3) && writeAccumALUreg);

   Accumulator.Update((clk && writeAccum), ALU_Register.getRegVal());
   ui->AccumulatorEdit->setText(QString::number(Accumulator.getRegVal()));

   bool writeALUreg = ((SubCounter.getCount() == 1) && writeAccumALUreg);
   ALU_Register.Update((clk && writeALUreg), alu1.getOut());
   ui->ALURegEdit->setText(QString::number(ALU_Register.getRegVal()));

   bool writeOUTreg = ((SubCounter.getCount() == 1) && instructionDecoder.getOUT());
   OUT_Register.Update((clk && writeOUTreg), alu1.getOut());
   ui->OUTRegEdit->setText(QString::number(OUT_Register.getRegVal()));

   bool writeRam = ((SubCounter.getCount() == 1) && instructionDecoder.getSTO());
   SystemRam.Update(!(clk && writeRam), 0,DataRom.getRamVal(),alu1.getOut());
   ui->RAMA0Edit->setText(QString::number(SystemRam.GetRamValAt(0)));
   ui->RAMA1Edit->setText(QString::number(SystemRam.GetRamValAt(1)));
   ui->RAMA2Edit->setText(QString::number(SystemRam.GetRamValAt(2)));
   ui->RAMA3Edit->setText(QString::number(SystemRam.GetRamValAt(3)));
   ui->RAMA4Edit->setText(QString::number(SystemRam.GetRamValAt(4)));
   ui->RAMA5Edit->setText(QString::number(SystemRam.GetRamValAt(5)));
   ui->RAMA6Edit->setText(QString::number(SystemRam.GetRamValAt(6)));
   ui->RAMA7Edit->setText(QString::number(SystemRam.GetRamValAt(7)));
   ui->RAMA8Edit->setText(QString::number(SystemRam.GetRamValAt(8)));
   ui->RAMA9Edit->setText(QString::number(SystemRam.GetRamValAt(9)));
   ui->RAMA10Edit->setText(QString::number(SystemRam.GetRamValAt(10)));
   ui->RAMA11Edit->setText(QString::number(SystemRam.GetRamValAt(11)));
   ui->RAMA12Edit->setText(QString::number(SystemRam.GetRamValAt(12)));
   ui->RAMA13Edit->setText(QString::number(SystemRam.GetRamValAt(13)));
   ui->RAMA14Edit->setText(QString::number(SystemRam.GetRamValAt(14)));
   ui->RAMA15Edit->setText(QString::number(SystemRam.GetRamValAt(15)));

}




// show what the decoder outputs on the window, this code is not meant to be effecient, rather to accurately simulate hardware function whithin the decoder object
void MainWindow::ShowDecoder() {

    ui->HLTEdit->setText(" ");
    ui->ADDEdit->setText(" ");
    ui->SUBEdit->setText(" ");
    ui->STOEdit->setText(" ");
    ui->LDEdit->setText(" ");
    ui->BEdit->setText(" ");
    ui->BZEdit->setText(" ");
    ui->LDVEdit->setText(" ");
    ui->INPEdit->setText(" ");
    ui->OUTEdit->setText(" ");
    ui->ANDEdit->setText(" ");
    ui->OREdit->setText(" ");
    ui->NOTEdit->setText(" ");

    if(instructionDecoder.getHLT() == true) {
        ui->HLTEdit->setText("1");
    }
    else if(instructionDecoder.getADD() == true) {
        ui->ADDEdit->setText("1");
    }
    else if(instructionDecoder.getSUB() == true) {
        ui->SUBEdit->setText("1");
    }
    else if(instructionDecoder.getSTO() == true) {
        ui->STOEdit->setText("1");
    }
    else if(instructionDecoder.getLD() == true) {
        ui->LDEdit->setText("1");
    }
    else if(instructionDecoder.getB() == true) {
        ui->BEdit->setText("1");
    }
    else if(instructionDecoder.getBZ() == true) {
        ui->BZEdit->setText("1");
    }
    else if(instructionDecoder.getLDV() == true) {
        ui->LDVEdit->setText("1");
    }
    else if(instructionDecoder.getINP() == true) {
        ui->INPEdit->setText("1");
    }
    else if(instructionDecoder.getOUT() == true) {
        ui->OUTEdit->setText("1");
    }
    else if(instructionDecoder.getAND() == true) {
        ui->ANDEdit->setText("1");
    }
    else if(instructionDecoder.getOR() == true) {
        ui->OREdit->setText("1");
    }
    else if(instructionDecoder.getNOT() == true) {
        ui->NOTEdit->setText("1");
    }
}

// ALU instructions:      S   M  Cn
// ADD: (F = A+B)        1001 0  0
// SUB: (F = A-B),       0110 0  1
// STO, OUT: (F = A)     0000 0  1
// LD, LDV, INP: (F = B) 1010 1  0
// AND: ( F = A & B)     1110 1  0
// OR: (F = A | B)       1011 1  0
// NOT: (F = !A)         0000 1  0

int MainWindow::ALUEncoder() { // returns int representing the 6 bits for ALU instruction: S = ((output & 0b111100) >> 2), M = ((output & 0b000010) >>1), Cn  = ((output & 0b000001)
    int output = 0;
    if(instructionDecoder.getADD() == true) {
        output = 0b100100;
    }
    else if(instructionDecoder.getSUB() == true) {
        output = 0b011001;
    }
    else if((instructionDecoder.getSTO() == true)||(instructionDecoder.getOUT() == true)) {
        output = 0b000001;
    }
    else if((instructionDecoder.getLD() == true) || (instructionDecoder.getLDV() == true) || (instructionDecoder.getINP() == true)) {
        output = 0b101010;
    }
    else if(instructionDecoder.getAND() == true) {
        output = 0b111010;
    }
    else if(instructionDecoder.getOR() == true) {
        output = 0b101110;
    }
    else if(instructionDecoder.getNOT() == true) {
        output = 0b000010;
    }
    return output;
}
