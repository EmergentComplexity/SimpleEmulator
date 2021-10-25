
#include <stdio.h>



int main()
{
    int ProgramCounter = 0;
    int ROM [16] = {0b10000000, 0b00110001, 0b10000000, 0b00010001,0b10010000,0b01010000,0,0,0,0,0,0,0,0,0,0};
    int opcode = 0;
    int output = 0;
    int input = 0;
    int Hault = 0;
    int Ram [16];
    int accumulator = 0;
    int data = 0;
    
    while (Hault != 1) {
        opcode = ROM[ProgramCounter] >> 4;
        data = ROM[ProgramCounter] & 0b00001111;
        //printf("  PC: %d", ProgramCounter);
        switch(opcode) {
            case 0b0000: // HLT
                Hault = 1;
                break;
            case 0b0001: // ADD
                accumulator = accumulator + Ram[data];
                ProgramCounter++;
                break;
            case 0b0010: // SUB
                accumulator = accumulator - Ram[data];
                ProgramCounter++;
                break;
            case 0b0011: // STO
                Ram[data] = accumulator;
                ProgramCounter++;
                break;
            case 0b0100: // LD
                accumulator = Ram[data];
                ProgramCounter++;
                break;
            case 0b0101: // B
                ProgramCounter = data;
                break;
            case 0b0110: // BZ
                if(accumulator == 0) {
                    ProgramCounter = data-1;
                }
                break;
            case 0b0111:
            // pos
                break;
            case 0b1000: // INP
                printf("\nEnter Input: ");
                scanf("%d", &input);
                accumulator = input;
                ProgramCounter++;
                break;
            case 0b1001: // OUT
                output = accumulator;
                printf("\noutput is: %d", output);
                ProgramCounter++;
                break;
            case 0b1010: // AND
                accumulator = accumulator & Ram[data];
                ProgramCounter++;
                break;
            case 0b1100:
            //xor
                break;
            case 0b1101: // NOT
                accumulator = !accumulator;
                ProgramCounter++;
                break;
            
        }
        
    }
    
              //   seeeeeeeemmmmmmmmmmmmmmmmmmmmmmm
    float test = 0b10000000000000000000000000000001;
    printf("Done");

    return 0;
}
