#ifndef SHIFTREG_H
#define SHIFTREG_H


// this class emulates a shift register

class shiftreg
{

private:
    int shiftOut;  // the current output of the shift register, updates with srclk when it is made equal to shiftCur
    int shiftCur;  // the current values of the data inside the shift register, updates with rclk when it shifts left and the data input is added onto the first bit
    bool rclk_Last;
    bool srclk_Last;
public:
    shiftreg();
    // srclk updates shiftOut
    // rclk updates shiftCur
    // data is the input data
    // clr clears the register
    void update(bool srclk, bool rclk, bool data, bool clr);
    int getShiftOut();
};

#endif // SHIFTREG_H
