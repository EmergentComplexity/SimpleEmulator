LD 0101 ; load ad 


SUB 1010 ; ad-bc
OUT 0000 ; output the difference, the accumulator is written to the output register, 0000 because OUT doesnt need an operand
HLT 0000 ; done running
