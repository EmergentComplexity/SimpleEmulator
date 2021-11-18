#ifndef LCDWINDOW_H
#define LCDWINDOW_H

#include <QDialog>

namespace Ui {
class LCDwindow;
}

class LCDwindow : public QDialog
{
    Q_OBJECT

public:
    explicit LCDwindow(QWidget *parent = nullptr);
    ~LCDwindow();

private:
    Ui::LCDwindow *ui;
};

#endif // LCDWINDOW_H
