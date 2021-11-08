INP 0000 ; Input a value 0000 because INP doesnt need an operand
STO 0001 ; Store the value inputed to address 1
INP 0000 ; Input another value
ADD 0001 ; Sum of 2 inputed values, the first value entered is in address 1 and the second is still in the accumulator
OUT 0000 ; output the sum, the accumulator is written to the output register, 0000 because OUT doesnt need an operand
B   0000 ; unconditional jump to start of program, add 2 more numbers
