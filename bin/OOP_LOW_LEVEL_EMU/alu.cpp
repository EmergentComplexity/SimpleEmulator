#include "alu.h"

ALU::ALU()
{

}


void ALU::Update(int A, int B, int S, bool M, bool Cn) {
    switch (S) {
        case 0b0000: {
            if (M == true) {
                F = !A;
            }
            else if (Cn == false) {
                F = A - 1;
            }
            else if (Cn == true) {
                F = A;
            }
            break;
        }

        case 0b0001: {
            if (M == true) {
                F = !(A & B);
            }
            else if (Cn == false) {
                F = ((A & B) - 1);
            }
            else if (Cn == true) {
                F = (A & B);
            }
            break;
        }

        case 0b0010: {
            if (M == true) {
                F = ((!A) | B);
            }
            else if (Cn == false) {
                F = ((A & (!B)) - 1);
            }
            else if (Cn == true) {
                F = (A & (!B));
            }
            break;
        }

        case 0b0011: {
            if (M == true) {
                F = 1;
            }
            else if (Cn == false) {
                F = -1; // 2s comp
            }
            else if (Cn == true) {
                F = 0;
            }
            break;
        }

        case 0b0100: {
            if (M == true) {
                F = !(A | B);
            }
            else if (Cn == false) {
                F = (A + (A | (!B)));
            }
            else if (Cn == true) {
                F = (A + (A | (!B)) + 1);
            }
            break;
        }

        case 0b0101: {
            if (M == true) {
                F = !B;
            }
            else if (Cn == false) {
                F = ((A & B) + (A | (!B)));
            }
            else if (Cn == true) {
                F = ((A & B) + (A | (!B)) +1);
            }
            break;
        }

        case 0b0110: {
            if (M == true) {
                // F = !(A xor B);
            }
            else if (Cn == false) {
                F = (A - B - 1);
            }
            else if (Cn == true) {
                F = (A - B);
            }
            break;
        }
        case 0b0111: {
            if (M == true) {
                F = (A | (!B));
            }
            else if (Cn == false) {
                F = (A | (!B));
            }
            else if (Cn == true) {
                F = ((A | (!B)) + 1);
            }
            break;
        }

        case 0b1000: {
            if (M == true) {
                F = ((!A) & B);
            }
            else if (Cn == false) {
                F = (A + (A | B));
            }
            else if (Cn == true) {
                F = (A + (A | B) + 1);
            }
            break;
        }

        case 0b1001: {
             if (M == true) {
                // F = A xor B;
            }
            else if (Cn == false) {
                F = (A + B);
            }
            else if (Cn == true) {
                F = (A + B + 1);
            }
             break;
        }

        case 0b1010: {
            if (M == true) {
                F = B;
            }
            else if (Cn == false) {
                F = ((A & !(B)) + (A | B));
            }
            else if (Cn == true) {
                F = ((A & !(B)) + (A | B) + 1);
            }
            break;
        }

        case 0b1011: {
            if (M == true) {
                F = (A | B);
            }
            else if (Cn == false) {
                F = (A | B);
            }
            else if (Cn == true) {
                F = ((A | B) + 1);
            }
            break;
        }

        case 0b1100: {
            if (M == true) {
                F = 0;
            }
            else if (Cn == false) {
                F = (A + (A << 1));
            }
            else if (Cn == true) {
                F = (A + A + 1);
            }
            break;
        }

        case 0b1101: {
            if (M == true) {
                F = (A & !B);
            }
            else if (Cn == false) {
                F = ((A & B) + A);
            }
            else if (Cn == true) {
                F = ((A & B) + A + 1);
            }
            break;
        }

        case 0b1110: {
            if (M == true) {
                 F = (A & B);
            }
            else if (Cn == false) {
                F = ((A & B) + A);
            }
            else if (Cn == true) {
                F = ((A & B) + A + 1);
            }
            break;
        }
        case 0b1111: {
            if (M == true) {
                F = A;
            }
            else if (Cn == false) {
                F = A;
            }
            else if (Cn == true) {
                F = A + 1;
            }
            break;
        }


    }
}

int ALU::getOut() {
    return F;
}
