#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <alu.h>
#include <counter.h>
#include <srlatch.h>
#include <ram.h>
#include <decoder.h>
#include <qtimer.h>
#include <register.h>

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
    ALU alu1;
    QTimer *timer = new QTimer(this);
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
    void ShowDecoder(); // shows the output of the decoder on the main window
    int ALUEncoder(); // takes the values from the instruction decoder and re-encodes them to match the instructions for the alu hardware
    int clk = 0;
private slots:
    void AutoClock();
    void ClockStart();
    void ClockStop();
};
#endif // MAINWINDOW_H
