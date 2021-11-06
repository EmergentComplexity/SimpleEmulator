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
    int ROM [16];
    int Ram [16];
    int data = 0;
    bool ROMLoaded = false; // becomes true after a file is opened and the data is entered into the ROM array
    void InstructionDecoder();
    void InstructionEncoder( QString mnemonic, QString data, int *ROM);
    QString mnemonics [16]; //assumes max program length of 16 instructions, contains the mneumonic


    QString currentFile = "";   //lets us open files
private slots: // executed when signal is submitted
    void CLOCKButtonPressed();

    void on_actionOpen_triggered();
};
#endif // MAINWINDOW_H
