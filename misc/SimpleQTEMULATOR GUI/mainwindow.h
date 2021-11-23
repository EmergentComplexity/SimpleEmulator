#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>        //lets us open files
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QLabel>
#include <QFont>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int currentCount = 0;
    int output = 0; // Output Register
    double input = 0.0;  // Input Register
    int opcode;
    int accumulator = 0;
    int ROM [16];
    int Ram [16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int data = 0;
    bool ROMLoaded = false; // becomes true after a file is opened and the data is entered into the ROM array
    void InstructionDecoder();
    void InstructionEncoder( QString mnemonic, QString data, int *ROM);
    QString mnemonics [16]; //assumes max program length of 16 instructions, contains the mneumonic

    QString currentFile = "";   //lets us open files
private slots: // executed when signal is submitted
    void NumPressed(); //keypad
    void CLOCKButtonPressed();
    void on_actionOpen_triggered();
    void on_button_4bit_clicked();
    void on_button_8bit_clicked();
    void on_change_sim_clicked();
    void on_change_sim_2_clicked();
};
#endif // MAINWINDOW_H
