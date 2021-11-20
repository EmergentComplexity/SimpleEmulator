#ifndef RAM_H
#define RAM_H


class RAM
{

private:
    int RamArr[16];
    int S;
public:
    RAM();
    void Update(bool WE, bool ME, int A, int D);
    int getRamVal(); // S is the output of the ram, gets the value of S
    int GetRamValAt(int address); // get a ram value that is not the address that the address input currently is on: this is a software tool to see all the ram without the emulator knowing
};

#endif // RAM_H
