
#include <stdio.h>



int main()
{
    int ProgramCounter = 0; // This is used to address the ROM.
    int ROM [16] = {0b10000000, 0b00110001, 0b10000000, 0b00010001,0b10010000,0b01010000,0,0,0,0,0,0,0,0,0,0}; // this is the program being run
    
    /*
        This program will add 2 numbers and output the sum in an infinite loop
    PC ROM Value  ASM 
    
    0  0b10000000 INP 0000   ; Input a value, 0000 because INP doesnt need an operand
    1  0b00110001 STO 0001   ; Store the value inputed to address 1
    2  0b10000000 INP 0000   ; Input another value
    3  0b00010001 ADD 0001   ; sum of 2 inputed values, the first value entered is in address 1 and the second is still in the accumulator
    4  0b10010000 OUT 0000   ; output the sum, the accumulator is written to the output register, 0000 because OUT doesnt need an operand
    5  0b01010000 B   0000   ; unconditional branch to set program counter to ROM address 0 to create infinite loop
    */
    int opcode = 0; // The opcode is the upper 4 bits of the 8-bit Rom value
    int output = 0; // Output Register
    int input = 0;  // Input Register
    int Hault = 0;  // Hault Flag
    int Ram [16];        // We are simulating the RAM as a 4-bit addressed array. This is an integer array and thus can take any integer value, but the actual hardware can only have 4 bits
    int accumulator = 0; // Accumulator Register, it is used for data that is being worked with
    int data = 0;        // The data is the lower 4 bits of the 8-bit Rom value. most of the time it is treated as a Ram address, however it can also be a constant value depending on the instruction
    
    while (Hault != 1) {
        opcode = ROM[ProgramCounter] >> 4;           
        data = ROM[ProgramCounter] & 0b00001111;
        //printf("  PC: %d", ProgramCounter);
        switch(opcode) {
            case 0b0000: // HLT: THis effectively stops the clock
                Hault = 1;
                break;
            case 0b0001: // ADD
                accumulator = accumulator + Ram[data]; // Arithmetic operations with 2 operands work with the accumuator and a RAM location as there is only 1 accumulator
                ProgramCounter++;  // go to the next instruction: this symbolizes a clock pulse
                break;
            case 0b0010: // SUB
                accumulator = accumulator - Ram[data];
                ProgramCounter++;
                break;
            case 0b0011: // STO: this is the command used to write to RAM
                Ram[data] = accumulator;
                ProgramCounter++;
                break;
            case 0b0100: // LD: this is the command used to read from RAM
                accumulator = Ram[data];
                ProgramCounter++;
                break;
            case 0b0101: // B: this is an unconditional branch
                ProgramCounter = data;
                break;
            case 0b0110: // BZ: this is a conditional branch
                if(accumulator == 0) {
                    ProgramCounter = data-1;
                }
                break;
            case 0b0111:
            // pos
                break;
            case 0b1000: // INP: Read input register into the accumulator, this  is simulated with scanf, whereas in actual hardware, you can change what is in the input register at any time, INP only controls when it is read
                printf("\nEnter Input: ");
                scanf("%d", &input);
                accumulator = input;
                ProgramCounter++;
                break;
            case 0b1001: // OUT: write the accumulator to the output register, this is simulated with printf, wheras in actual hardware, the output register always outputs its value, OUT only controls when the output value is changed
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
    
  
    printf("Done"); // you get here after HLT

    return 0;
}
