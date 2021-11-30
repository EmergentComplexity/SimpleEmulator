#include "lcd.h"

lcd::lcd()
{
    lcdOut.clear();
}


void lcd::update(bool RS, bool EN, int data) {
    if(EN == 1) {
        if (RS == 0) { // Send commands to the lcd
            if (data == 0) {
                lcdOut.clear();
            }
        }
        else if (RS == 1) { // Send characters to the lcd
           lcdOut = lcdOut + char(data);
        }
    }
}
QString lcd::getLCDVal() {
    return lcdOut;
}
