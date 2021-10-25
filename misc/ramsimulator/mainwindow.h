#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    int S;
    int A;
    int D;
    bool ME;
    bool WE;
    int data[16];
    void RamOperations();


private slots: // executed when signal is submitted
    void SetAButtonPressed();
    void SetDButtonPressed();
    void MECheckboxClicked();
    void WECheckboxClicked();
};
#endif // MAINWINDOW_H
