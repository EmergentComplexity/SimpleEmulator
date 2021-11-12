INP 0000   ;Input value 'a'
STO 0000   ;Store 'a' in address0
INP 0000   ;Input value 'b'
STO 0001   ;store 'b' in address1
INP 0000   ;Input value 'c'
STO 0010   ;store 'c' in address2
INP 0000   ;Input value 'd'
STO 0011   ;store 'd' in address3
HLT 0000   ; done inputing


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

LD 0101 ; load ad 


SUB 1010 ; ad-bc
OUT 0000 ; output the difference, the accumulator is written to the output register, 0000 because OUT doesnt need an operand
HLT 0000 ; done running

