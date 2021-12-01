#include "ram.h"

RAM::RAM()
{
    for(int i = 0; i < 16; i++) {
        RamArr[i] = 0;
    }

}
void RAM::Update(bool WE, bool ME, int A, int D) {
    if ( ME == false && WE == false) { // write
        RamArr[A] = D; // write operation
        S = 0b1111; // values shown during write operation
    }
    else if ( ME == false && WE == true) { // read
        S = RamArr[A];
    }
    else { // hold
        S = 0;
   }
}
int RAM::getRamVal() {
    return S;
}


int RAM::GetRamValAt(int address) {
    return RamArr[address];
}
