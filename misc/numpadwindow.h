#ifndef NUMPADWINDOW_H
#define NUMPADWINDOW_H

#include <QDialog>

namespace Ui {
class NumPadWindow;
}

class NumPadWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NumPadWindow(QWidget *parent = nullptr);
    ~NumPadWindow();

private:
    Ui::NumPadWindow *ui;
};

#endif // NUMPADWINDOW_H
