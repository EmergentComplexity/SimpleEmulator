#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>        //lets us open files
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QLabel>
#include <QFont>
#include <QTimer>

// Components for the Low Level Emulator
#include <components/alu.h>
#include <components/counter.h>
#include <components/srlatch.h>
#include <components/ram.h>
#include <components/decoder.h>
#include <components/register.h>
#include <components/lcd.h>

#include <components/shiftreg.h> // used for LCD

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int currentCount = 0;
    int output = 0; // Output Register
    double input = 0.0;  // Input Register
    int opcode;
    int accumulator = 0;
    int ROM [16];
    QTimer *timer = new QTimer(this);   // 4 bit high level timer
    QTimer *timer2 = new QTimer(this);  // 4 bit low level timer
    QTimer *timer3 = new QTimer(this);  // 8 bit high level timer

    bool isLL4 = false;  // Low level 4 bit
    bool isHL4 = false;  // High level 4 bit
    bool isHL8 = false;  // High level 8 bit
    class ROMS {
    public:
        int Values [16];
        ROMS *next;
    };


    ROMS *head = NULL;
    ROMS *current = NULL;
    int Ram [16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int data = 0;
    bool ROMLoaded = false; // becomes true after a file is opened and the data is entered into the ROM array



    QString mnemonics [16]; //assumes max program length of 16 instructions, contains the mneumonic





    class ROMS8Bit {
    public:
        int Values[256];
        ROMS8Bit *next;
    };
    ROMS8Bit *head8 = NULL;
    ROMS8Bit *current8 = NULL;
    int Ram8Bit[256] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,0,0};

    // 4 bit low level stuff
    ALU alu1;
    counter PC;
    counter SubCounter;
    SRLatch latch;
    RAM InstructionRom;
    RAM DataRom;
    Decoder instructionDecoder;
    RAM SystemRam;
    Register Accumulator;
    Register ALU_Register;
    Register OUT_Register;
    shiftreg lcdShiftReg;
    lcd mainDisplay;
    void ShowDecoder(); // shows the output of the decoder on the main window
    int ALUEncoder(); // takes the values from the instruction decoder and re-encodes them to match the instructions for the alu hardware
    int clk = 0;
   QString printstr;// to print rom data

    QString currentFile = "";   //lets us open files
private slots: // executed when signal is submitted

    void NumPressed(); //keypad
    void on_actionOpen_triggered();
    void on_button_4bit_clicked();
    void on_button_4bit_LowLevel_clicked();
    void on_button_8bit_clicked();
    void on_change_sim_clicked();
    void on_change_sim_2_clicked();
    // for 4 bit high level emulation
    void AutoClock();
    void ClockStart();
    void ClockStop();
    void CLOCKButtonPressed();
    void InstructionDecoder();
    void AppendROM( ROMS ** NodeHead, int ROM[16]);
    void InstructionEncoder( QString mnemonic, QString data, int *ROM);

    // for 4 bit low level emulation
    void AutoClock2();
    void ClockStart2();
    void ClockStop2();

    // for 8 bit high level emulation
    void AutoClock8B();
    void ClockStart8B();
    void ClockStop8B();
    void CLOCKButtonPressed8B();
    void InstructionDecoder8B();
    void AppendROM8B( ROMS8Bit ** NodeHead, int ROM[256]);
    void InstructionEncoder8( QString mnemonic, QString data, int *ROM);




    /*
    void on_actionRAM_triggered();
    void on_actionLCD_triggered();
    void on_actionNUM_PAD_triggered();
    */
    void on_change_sim_5_clicked();
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
