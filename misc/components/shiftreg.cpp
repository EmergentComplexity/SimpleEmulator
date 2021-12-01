#include "shiftreg.h"

shiftreg::shiftreg()
{
 rclk_Last = 0;
 srclk_Last = 0;
 shiftCur = 0;
 shiftOut = 0;
}


void shiftreg::update(bool srclk, bool rclk, bool data, bool clr) {

    // we are assuming a 10 bit shift register, so when data is shifted above that (11th bit), it is cleared
    shiftCur = shiftCur & 0b1111111111;
    shiftOut = shiftOut & 0b1111111111;


    if (clr == true) {
        shiftCur = 0;
        shiftOut = 0;
    }

    // the shift register can only be used when clr == 0
    else {
        // when rclk is pulsed, data goes in
        if ((rclk == 1) && (rclk_Last == 0)) {  // clock on rising edge only
           shiftCur = shiftCur << 1;
           shiftCur = shiftCur | data;
        }
        rclk_Last = rclk;


        // when srclk is pulsed, shiftout is updated
        if ((srclk == 1) && (srclk_Last == 0)) {  // clock on rising edge only
           shiftOut = shiftCur;
        }
        srclk_Last = srclk;
    }

}


int shiftreg::getShiftOut() {
    return shiftOut;
}
