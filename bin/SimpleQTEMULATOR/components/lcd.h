#ifndef LCD_H
#define LCD_H
#include <qstring.h>

class lcd
{
private:
    QString lcdOut;
public:
    lcd();
    void update(bool RS, bool EN, int data);
    QString getLCDVal();
};

#endif // LCD_H
