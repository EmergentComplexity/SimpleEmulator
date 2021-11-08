
INP 0000   ;Input a value, 0000 because INP doesneeeet need an operand
STO 0000   ;Store term1 in address0
INP 0000   ;Input another value
STO 0001   ;store term2 in address1
LDV 0001   ;accumulator=1
STO 0010   ;RAM[2]=1
LD 0111   ;accumulator
ADD 0000   ;accumulator=accumulator + term1
STO 0111

LD 0001   ;load term2
SUB 0010   ;term2-1
STO 0001   ;term2=term2-1
BZ 1110   ;if0skip
B 0110   ;keep looping
LD 0111   ;product is stored here

OUT 0000   ;output the product
