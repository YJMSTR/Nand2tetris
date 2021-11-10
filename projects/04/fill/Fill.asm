// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

(LOOP)
    //无限循环读KBD 
    @KBD 
    D = M
    @BLACK      // 如果D不为0 跳转到BLACK 把屏幕全部涂黑
    D; JNE  
    @WHITE 
    D; JEQ  //如果D为0  跳转到WHITE 把屏幕全部涂白
    @LOOP
    0; JMP  //无条件跳转
@8192
D = M

(BLACK) 
    //共有从16384开始的256*512个像素要涂黑  每个寄存器有16Bit 于是每行有512/16=32个寄存器要弄成全黑
    //涂第i行第j列需要把M[16384+i*32+j/16]+j%16涂黑
    //但由于我们是要全部涂黑，可以直接让这个寄存器变黑(让它等于-1)
    //于是我们需要循环256*32 = 8192次
    //可以先写c语言代码 再对着改
    @


