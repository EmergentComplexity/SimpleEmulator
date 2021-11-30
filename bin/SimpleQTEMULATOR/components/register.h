#ifndef REGISTER_H
#define REGISTER_H


class Register
{
private:
    int data;
    int CLK_Last = 0; // used to detect rising edge of clock
public:
    Register();
    void Update(bool CLK, int dataIn);
    int getRegVal();
};

#endif // REGISTER_H
