#ifndef ALU_H
#define ALU_H


class ALU
{

private:
  //  int A = 0;   // ALU input 1
  //  int B = 0;   // ALU input 2
  //  int S = 0;   // ALU instruction
  //  bool M = 0;  // M = 1 -> Logic Functions, M = 0 -> Arithmetic
  //  bool Cn = 0; // Cn = 1 -> with carry, Cn = 0 -> no carry
    int F = 0;   // the output off the ALU
public:
    ALU();
    void Update(int A, int B, int S, bool M, bool Cn); // ALU updates every clock, though it itself is a combinational logic circuit
    int getOut(); // display the output F
};

#endif // ALU_H
