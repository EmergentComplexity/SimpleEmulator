
LDV 0001   ;accumulator=1
STO 0100   ;RAM[4]=1

LD 0010   ;load 'c'
STO 1001  ; copy 'c' to address9

LD 1010   ;accumulator = address10
ADD 0001   ;accumulator=accumulator + 'b'
STO 1010  ; add 'b' to address 5 Product of 'b'*'c' is here

LD 1001   ;load 'd'
SUB 0100   ;'d'-1
STO 1001   ;decrement address6

BZ 1100   ;if0skip
B 0100   ;keep looping
HLT 0000 ; done 'b' * 'c'
