

LDV 0001   ;accumulator=1
STO 0100   ;RAM[4]=1

LD 0011   ;load 'd'
STO 0110  ; copy 'd' to address6

LD 0101   ;accumulator = address5
ADD 0000   ;accumulator=accumulator + 'a'
STO 0101  ; add 'a' to address 5 Product of 'a'*'d' is here

LD 0110   ;load 'd'
SUB 0100   ;'d'-1
STO 0110   ;decrement address6

BZ 1100   ;if0skip
B 0100   ;keep looping
HLT 0000 ; done 'a' * 'd'
