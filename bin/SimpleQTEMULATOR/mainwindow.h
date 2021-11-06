#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>        //lets us open files
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

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
    int input = 0;  // Input Register
    int opcode;
    int accumulator = 0;
    int ROM [16] = {0b10000000, 0b00110001, 0b10000000, 0b00010001,0b10010000,0b01010000,0,0,0,0,0,0,0,0,0,0};
    int Ram [16];
    int data = 0;
    void InstructionDecoder();
    QString mnemonics [16]; //assumes max program length of 16 instructions, contains the mneumonic

    QString currentFile = "";   //lets us open files
private slots: // executed when signal is submitted
    void CLOCKButtonPressed();

    void on_actionOpen_triggered();
};
#endif // MAINWINDOW_H
