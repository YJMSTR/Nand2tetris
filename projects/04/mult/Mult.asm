// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.

@R2
M = 0
@i
M = 0
(LOOP)
    @i
    D = M               //D = i
    @R1          
    D = M - D           //D = i-D
    @END
    D; JEQ              //如果i == R1 跳去END
    @R0
    D = M               //D = R0
    @R2
    M = D + M           //M = R2 + R0 
    @i
    M = M + 1
    @LOOP
    0; JMP              //GOTO LOOP
(END)
    @END
    0; JMP              //无限循环，这是结束Hack程序执行的标准方式           
