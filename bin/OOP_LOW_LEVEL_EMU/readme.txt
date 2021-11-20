THis is a low level object oriented version of the emulator. this is designed to simulate what would be done in real hardware rather than to simply execute the instructions


Please read the comments in mainwindow.cpp
 Schematics are uploaded under SimpleEmulator/doc

This code is meant to simulate  a computer cunstructed with the following hardware:

Ram/Rom
  - 74189 Tri-State 64 Bit RAM
  - Datasheet: https://www.jameco.com/Jameco/Products/ProdDS/49883.pdf
  - video demonstration: https://www.youtube.com/watch?v=6w8gCISbwy4&t=250s
  
Program Counter/ Sub-instruction counter
  -  74LS161 ICS and Semiconductors, 4-Bit Synchronous Binary Counter
  -  Datasheet: https://www.ti.com/lit/ds/symlink/sn54ls161a-sp.pdf?ts=1637395556954&ref_url=https%253A%252F%252Fwww.google.com%252F

Registers: (Accumulator, ALU Register, Output Register)
  - DM74HC74N DIP-14 Dual D-Type Trigger Flip-Flop IC Chip SN74HC74
  - Datasheet: https://www.mouser.com/datasheet/2/308/74HC74-108792.pdf
  
ALU
  - IC 74LS181 4-Bit Arithmetic Logic Unit
  - Datasheet: https://www.jameco.com/Jameco/Products/ProdDS/46973.pdf
  
  
 The other stuff being simulated is more general Such as the SR latch and the Instruction decoder being based of the theoretical model rather than any particular IC implimentation 
