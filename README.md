**由于这个作业是在两台电脑上完成的，一开始没有传上git，故文件夹里的代码可能不全，请参考本文件中的代码**

coursera上有part1的课程，但都是英文

配套的中文书籍可以在z-lib上找到，名为《计算机系统要素》
00部分是简介，直接跳过了

配套的文件可以在Nand2tetris官网找到

vscode甚至有专门为这门课的HDL做的代码高亮拓展



## 第一周 Module 1: Boolean Functions and Gate Logic Roadmap

#### HDL入门

在配套中文书籍的附录A.1到A.6部分

### project1

任务：用HDL实现15个芯片

一开始只构建好了Nand门（与非门），其他的门电路和芯片都能够通过它构建。

#### Not

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/01/Not.hdl

/**
 * Not gate:
 * out = not in
 */

CHIP Not {
    IN in;
    OUT out;

    PARTS:
    // Put your code here:
    Nand(a = in, b = true, out = out);
}
```

#### Or

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/01/Or.hdl

 /**
 * Or gate:
 * out = 1 if (a == 1 or b == 1)
 *       0 otherwise
 */

CHIP Or {
    IN a, b;
    OUT out;

    PARTS:
    // Put your code here:
    Not(in = a, out = nota);
    Not(in = b, out = notb);
    Nand(a = nota, b = notb, out = out);
}
```

#### And

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/01/And.hdl

/**
 * And gate: 
 * out = 1 if (a == 1 and b == 1)
 *       0 otherwise
 */

CHIP And {
    IN a, b;
    OUT out;

    PARTS:
    Not(in = a, out = nota);
    Not(in = b, out = notb);
    Or(a = nota, b = notb, out = notaOrnotb);
    Not(in = notaOrnotb, out = out);
}
```

#### Xor

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/01/Xor.hdl

/**
 * Exclusive-or gate:
 * out = not (a == b)
 */

CHIP Xor {
    IN a, b;
    OUT out;

    PARTS:
    Not(in = a, out = nota);
    Not(in = b, out = notb);
    And(a = nota, b = b, out = nab);
    And(a = a, b = notb, out = anb);
    Or(a = nab, b = anb, out = out);
}
```

#### And16

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/01/And16.hdl

/**
 * 16-bit bitwise And:
 * for i = 0..15: out[i] = (a[i] and b[i])
 */

CHIP And16 {
    IN a[16], b[16];
    OUT out[16];

    PARTS:
    And(a = a[0], b = b[0], out = out[0]);
    And(a = a[1], b = b[1], out = out[1]);
    And(a = a[2], b = b[2], out = out[2]);
    And(a = a[3], b = b[3], out = out[3]);
    And(a = a[4], b = b[4], out = out[4]);
    And(a = a[5], b = b[5], out = out[5]);
    And(a = a[6], b = b[6], out = out[6]);
    And(a = a[7], b = b[7], out = out[7]);
    And(a = a[8], b = b[8], out = out[8]);
    And(a = a[9], b = b[9], out = out[9]);
    And(a = a[10], b = b[10], out = out[10]);
    And(a = a[11], b = b[11], out = out[11]);
    And(a = a[12], b = b[12], out = out[12]);
    And(a = a[13], b = b[13], out = out[13]);
    And(a = a[14], b = b[14], out = out[14]);
    And(a = a[15], b = b[15], out = out[15]);
}
```

#### DMux

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/01/DMux.hdl

/**
 * Demultiplexor:
 * {a, b} = {in, 0} if sel == 0
 *          {0, in} if sel == 1
 */

CHIP DMux {
    IN in, sel;
    OUT a, b;

    PARTS:
    // Put your code here:
    Not(in = sel, out = notsel);
    And(a = in, b = notsel, out = a);
    And(a = in, b = sel, out = b);
}
```

#### Mux

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/01/Mux.hdl

/** 
 * Multiplexor:
 * out = a if sel == 0
 *       b otherwise
 */

CHIP Mux {
    IN a, b, sel;
    OUT out;

    PARTS:
    // Put your code here:
    Not(in = sel, out = notsel);
    And(a = a, b = notsel, out = oa);
    And(a = b, b = sel, out = ob);
    Or(a = oa, b = ob, out = out);
}
```

#### DMux4Way

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/01/DMux4Way.hdl

/**
 * 4-way demultiplexor:
 * {a, b, c, d} = {in, 0, 0, 0} if sel == 00
 *                {0, in, 0, 0} if sel == 01
 *                {0, 0, in, 0} if sel == 10
 *                {0, 0, 0, in} if sel == 11
 */

CHIP DMux4Way {
    IN in, sel[2];
    OUT a, b, c, d;

    PARTS:
    // Put your code here:
    Not(in = sel[0], out = nsel0);
    Not(in = sel[1], out = nsel1);
    And(a = nsel1, b = nsel0, out = s00);
    And(a = in, b = s00, out = a);
    And(a = nsel1, b = sel[0], out = s01);
    And(a = in, b = s01, out = b);
    And(a = sel[1], b = nsel0, out = s10);
    And(a = in, b = s10, out = c);
    And(a = sel[1], b = sel[0], out = s11);
    And(a = in, b = s11, out = d);
}
```

#### DMux8Way

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/01/DMux8Way.hdl
/** 
* 8-way demultiplexor: 
* {a, b, c, d, e, f, g, h} = {in, 0, 0, 0, 0, 0, 0, 0} if sel == 000 
*                            {0, in, 0, 0, 0, 0, 0, 0} if sel == 001 
*                            etc. *                            {0, 0, 0, 0, 0, 0, 0, in} if sel == 111 */
CHIP DMux8Way {    
	IN in, sel[3];
    OUT a, b, c, d, e, f, g, h;
    PARTS:    
    // Put your code here:
    Not(in = sel[0], out = n0);
    Not(in = sel[1], out = n1);
    Not(in = sel[2], out = n2);
    And(a = n1, b = n0, out = n00);
    And(a = n1, b = sel[0], out = n01);
    And(a = sel[1], b = n0, out = n10);
    And(a = sel[1], b = sel[0], out = n11);
    And(a = n2, b = n00, out = n000);
    And(a = n2, b = n01, out = n001);
    And(a = n2, b = n10, out = n010);
    And(a = n2, b = n11, out = n011);
    And(a = sel[2], b = n00, out = n100);
    And(a = sel[2], b = n01, out = n101);
    And(a = sel[2], b = n10, out = n110);
    And(a = sel[2], b = n11, out = n111);
    And(a = in, b = n000, out = a);
    And(a = in, b = n001, out = b);
    And(a = in, b = n010, out = c);
    And(a = in, b = n011, out = d);
    And(a = in, b = n100, out = e);
    And(a = in, b = n101, out = f);
    And(a = in, b = n110, out = g);
    And(a = in, b = n111, out = h);
}
```

#### Mux16

```HDL
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/01/Mux16.hdl
/** 
* 16-bit multiplexor:  
* for i = 0..15 out[i] = a[i] if sel == 0  
*                        b[i] if sel == 1 
*/
CHIP Mux16 {    
	IN a[16], b[16], sel;
    OUT out[16];
    PARTS:    
    // Put your code here:
    Mux(a=a[0], b=b[0], sel=sel, out=out[0]);
    Mux(a=a[1], b=b[1], sel=sel, out=out[1]);
    Mux(a=a[2], b=b[2], sel=sel, out=out[2]);
    Mux(a=a[3], b=b[3], sel=sel, out=out[3]);
    Mux(a=a[4], b=b[4], sel=sel, out=out[4]);
    Mux(a=a[5], b=b[5], sel=sel, out=out[5]);
    Mux(a=a[6], b=b[6], sel=sel, out=out[6]);    
    Mux(a=a[7], b=b[7], sel=sel, out=out[7]);    
    Mux(a=a[8], b=b[8], sel=sel, out=out[8]);   
    Mux(a=a[9], b=b[9], sel=sel, out=out[9]);
    Mux(a=a[10], b=b[10], sel=sel, out=out[10]);   
    Mux(a=a[11], b=b[11], sel=sel, out=out[11]);  
    Mux(a=a[12], b=b[12], sel=sel, out=out[12]);  
    Mux(a=a[13], b=b[13], sel=sel, out=out[13]); 
    Mux(a=a[14], b=b[14], sel=sel, out=out[14]);    
    Mux(a=a[15], b=b[15], sel=sel, out=out[15]);
}
```

#### Mux4Way16

```HDL
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/01/Mux4Way16.hdl
/** 
* 4-way 16-bit multiplexor: 
* out = a if sel == 00 
*       b if sel == 01 
*       c if sel == 10 
*       d if sel == 11 
*/
CHIP Mux4Way16 {
	IN a[16], b[16], c[16], d[16], sel[2];    
	OUT out[16];    
	PARTS:    
	// Put your code here:
    Mux16(a = a, b = b, sel = sel[0], out = ab);
    Mux16(a = c, b = d, sel = sel[0], out = cd); 
    Mux16(a = ab, b = cd, sel = sel[1], out = out);
}
```

#### Mux8Way16

```HDL
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/01/Mux8Way16.hdl
/** 
* 8-way 16-bit multiplexor: 
* out = a if sel == 000 
* b if sel == 001 
*       etc. 
*       h if sel == 111 
*/
CHIP Mux8Way16 {    
	IN a[16], b[16], c[16], d[16],  	
	e[16], f[16], g[16], h[16],  
    sel[3];   
    OUT out[16]; 
    PARTS:    
    // Put your code here:
    Mux4Way16(a = a, b = b, c = c, d = d, sel = sel[0..1], out = c1); 
    Mux4Way16(a = e, b = f, c = g, d = h, sel = sel[0..1], out = c2);
    Mux16(a = c1, b = c2, sel = sel[2], out = out);
}
```

#### Not16

```HDL
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/01/Not16.hdl
/** 
* 16-bit Not: 
* for i=0..15: out[i] = not in[i] 
*/
CHIP Not16 { 
	IN in[16];
    OUT out[16];
    PARTS:   
    // Put your code here:
    Nand(a=in[0], b=in[0], out=out[0]);    
    Nand(a=in[1], b=in[1], out=out[1]);  
    Nand(a=in[2], b=in[2], out=out[2]);   
    Nand(a=in[3], b=in[3], out=out[3]);  
    Nand(a=in[4], b=in[4], out=out[4]);   
    Nand(a=in[5], b=in[5], out=out[5]);   
    Nand(a=in[6], b=in[6], out=out[6]);  
    Nand(a=in[7], b=in[7], out=out[7]);    
    Nand(a=in[8], b=in[8], out=out[8]);    
    Nand(a=in[9], b=in[9], out=out[9]);    
    Nand(a=in[10], b=in[10], out=out[10]);    
    Nand(a=in[11], b=in[11], out=out[11]);    
    Nand(a=in[12], b=in[12], out=out[12]);    
    Nand(a=in[13], b=in[13], out=out[13]);    
    Nand(a=in[14], b=in[14], out=out[14]);    
    Nand(a=in[15], b=in[15], out=out[15]);
}
```

#### Or8Way

```HDL
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/01/Or8Way.hdl
/** 
* 8-way Or:  
* out = (in[0] or in[1] or ... or in[7]) 
*/
CHIP Or8Way {
	IN in[8];  
    OUT out;    
    PARTS:    
    // Put your code here:   
    Or(a = in[0], b = in[1], out = c1);    
    Or(a = c1, b = in[2], out = c2);   
    Or(a = c2, b = in[3], out = c3);    
    Or(a = c3, b = in[4], out = c4);   
    Or(a = c4, b = in[5], out = c5);   
    Or(a = c5, b = in[6], out = c6);   
    Or(a = c6, b = in[7], out = out);
}
```

#### Or16

```HDL
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/01/Or16.hdl
/** 
* 16-bit bitwise Or: 
* for i = 0..15 out[i] = (a[i] or b[i]) 
*/
CHIP Or16 {  
	IN a[16], b[16];
    OUT out[16];    
    PARTS:    
    // Put your code here:
    Or(a=a[0], b=b[0], out=out[0]);
    Or(a=a[1], b=b[1], out=out[1]);  
    Or(a=a[2], b=b[2], out=out[2]);
    Or(a=a[3], b=b[3], out=out[3]);
    Or(a=a[4], b=b[4], out=out[4]); 
    Or(a=a[5], b=b[5], out=out[5]);
    Or(a=a[6], b=b[6], out=out[6]);
    Or(a=a[7], b=b[7], out=out[7]);   
    Or(a=a[8], b=b[8], out=out[8]);  
    Or(a=a[9], b=b[9], out=out[9]);
    Or(a=a[10], b=b[10], out=out[10]);    
    Or(a=a[11], b=b[11], out=out[11]);    
    Or(a=a[12], b=b[12], out=out[12]);    
    Or(a=a[13], b=b[13], out=out[13]);   
    Or(a=a[14], b=b[14], out=out[14]);    
    Or(a=a[15], b=b[15], out=out[15]);
 }
```

## 第二周：Boolean Arithmetic and the ALU

***Counting is the religion of this generation, its hope and salvation.***

### 任务：实现半加器，全加器，Add16，Inc16以及ALU

#### HalfAdder

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/02/HalfAdder.hdl

/**
 * Computes the sum of two bits.
 */

CHIP HalfAdder {
    IN a, b;    // 1-bit inputs
    OUT sum,    // Right bit of a + b 
        carry;  // Left bit of a + b

    PARTS:
    // Put you code here:
    Xor(a = a, b = b, out = sum);
    And(a = a, b = b, out = carry);
}
```

#### FullAdder

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/02/FullAdder.hdl

/**
 * Computes the sum of three bits.
 */

CHIP FullAdder {
    IN a, b, c;  // 1-bit inputs
    OUT sum,     // Right bit of a + b + c
        carry;   // Left bit of a + b + c

    PARTS:
    // Put you code here:
    HalfAdder(a=a, b=b, sum=s1, carry=c1);
    HalfAdder(a=s1, b=c, sum=s2, carry=c2);
    HalfAdder(a=c1, b=c2, sum=carry, carry=c3);
    And(a=true, b=s2, out=sum);
}
```

#### Add16

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/02/Adder16.hdl

/**
 * Adds two 16-bit values.
 * The most significant carry bit is ignored.
 */

CHIP Add16 {
    IN a[16], b[16];
    OUT out[16];

    PARTS:
    // Put you code here:
    HalfAdder(a = a[0], b = b[0], sum = out[0], carry = carry1);
    FullAdder(a = a[1], b = b[1], c = carry1, sum = out[1], carry = carry2);
    FullAdder(a = a[2], b = b[2], c = carry2, sum = out[2], carry = carry3);
    FullAdder(a = a[3], b = b[3], c = carry3, sum = out[3], carry = carry4);
    FullAdder(a = a[4], b = b[4], c = carry4, sum = out[4], carry = carry5);
    FullAdder(a = a[5], b = b[5], c = carry5, sum = out[5], carry = carry6);
    FullAdder(a = a[6], b = b[6], c = carry6, sum = out[6], carry = carry7);
    FullAdder(a = a[7], b = b[7], c = carry7, sum = out[7], carry = carry8);
    FullAdder(a = a[8], b = b[8], c = carry8, sum = out[8], carry = carry9);
    FullAdder(a = a[9], b = b[9], c = carry9, sum = out[9], carry = carry10);
    FullAdder(a = a[10], b = b[10], c = carry10, sum = out[10], carry = carry11);
    FullAdder(a = a[11], b = b[11], c = carry11, sum = out[11], carry = carry12);
    FullAdder(a = a[12], b = b[12], c = carry12, sum = out[12], carry = carry13);
    FullAdder(a = a[13], b = b[13], c = carry13, sum = out[13], carry = carry14);
    FullAdder(a = a[14], b = b[14], c = carry14, sum = out[14], carry = carry15);
    FullAdder(a = a[15], b = b[15], c = carry15, sum = out[15], carry = carry16);
}
```

#### Inc16

这东西的意思是给输入对应的十进制数+1

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/02/Inc16.hdl

/**
 * 16-bit incrementer:
 * out = in + 1 (arithmetic addition)
 */

CHIP Inc16 {
    IN in[16];
    OUT out[16];

    PARTS:
    // Put you code here:
    Add16(a = in, b[0] = true, out = out);
}
```

#### ALU

算术逻辑单元

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/02/ALU.hdl

/**
 * The ALU (Arithmetic Logic Unit).
 * Computes one of the following functions:
 * x+y, x-y, y-x, 0, 1, -1, x, y, -x, -y, !x, !y,
 * x+1, y+1, x-1, y-1, x&y, x|y on two 16-bit inputs, 
 * according to 6 input bits denoted zx,nx,zy,ny,f,no.
 * In addition, the ALU computes two 1-bit outputs:
 * if the ALU output == 0, zr is set to 1; otherwise zr is set to 0;
 * if the ALU output < 0, ng is set to 1; otherwise ng is set to 0.
 */

// Implementation: the ALU logic manipulates the x and y inputs
// and operates on the resulting values, as follows:
// if (zx == 1) set x = 0        // 16-bit constant
// if (nx == 1) set x = !x       // bitwise not
// if (zy == 1) set y = 0        // 16-bit constant
// if (ny == 1) set y = !y       // bitwise not
// if (f == 1)  set out = x + y  // integer 2's complement addition
// if (f == 0)  set out = x & y  // bitwise and
// if (no == 1) set out = !out   // bitwise not
// if (out == 0) set zr = 1
// if (out < 0) set ng = 1

CHIP ALU {
    IN  
        x[16], y[16],  // 16-bit inputs        
        zx, // zero the x input?
        nx, // negate the x input?
        zy, // zero the y input?
        ny, // negate the y input?
        f,  // compute out = x + y (if 1) or x & y (if 0)
        no; // negate the out output?

    OUT 
        out[16], // 16-bit output
        zr, // 1 if (out == 0), 0 otherwise
        ng; // 1 if (out < 0),  0 otherwise

    PARTS:
    // Put you code here:
    //zx nx 可以用Mux4Way16确定得到的x的值
    //zy ny同理
    Not16(in = x, out = notx);  
    Not16(in = y, out = noty);
    And16(a = x, b = notx, out = c0); //全0
    Not16(in = c0, out = notc0);      //全1
    Mux4Way16(a = x, b = c0, c = notx, d = notc0, sel[0] = zx, sel[1] = nx, out = ox);
    Mux4Way16(a = y, b = c0, c = noty, d = notc0, sel[0] = zy, sel[1] = ny, out = oy);
    And16(a = ox, b = oy, out = oxandoy);
    Add16(a = ox, b = oy, out = oxaddoy);
    Mux16(a = oxandoy, b = oxaddoy, sel = f, out = o);
    Not16(in = o, out = noto);
    Mux16(a = o, b = noto, sel = no, out = ofinal);
    And16(a = ofinal, b[0..15] = true, out[0..7] = o1, out[8..15] = o2);
    And16(a = ofinal, b[0..15] = true, out[0..14] = oo, out[15] = o15);
    Or8Way(in = o1, out = oo1);
    Or8Way(in = o2, out = oo2);
    Not(in = oo1, out = no1);
    Not(in = oo2, out = no2);
    And(a = no1, b = no2, out = zr);
    And(a = o15, b = true, out = ng);
    And16(a = ofinal, b[0..15] = true, out = out);
}
```

## 第三周：Memory  时序逻辑

***It's a poor sort of memory that only works backward.***

计算机存储数据需要依靠memory elements（记忆单元）来保存数据，memory elements由sequential chips（时序芯片）组成。

记忆单元中的大部分能够被封装到flip-flop（触发器）中，它是一种底层**时序门**(sequential gate)，也是具有记忆功能的最小记忆单元。其能够储存一个基本的比特位，我们称之为“寄存器（register）”（和后面CPU内部的寄存器不是一个东西）。

### 背景知识

#### 时钟（Clock）

主时钟（master clock）提供连续的交变信号序列，硬件实现基于振荡器在低电平-高电平之间的交替变化。

#### 触发器（Flip-Flops)

计算机里最基本的时序单元。

本课程中使用称为数据触发器（Data Flip-Flop，DFF或D触发器）的变体。其包含1比特位的输入和1比特位的输出，以及时钟输入。其能够实现out(t)=in(t-1)

#### 寄存器（Registers）

能够储存某一时刻的值。

芯片设计的规则规定内部管脚的扇入（fan-in）必须为1，即它们必须只有一个单独的输入源。

#### 计数器（Counter）

out(t)=out(t-1)+c

#### 时间问题

时序结构中DFF保证了它们的输出变化仅仅在一个时钟周期到下一个时钟周期的交界点上，而不在时钟周期内。

比如ALU计算x+y时，x和y的电信号可能不会同时到达ALU，此时可能产生垃圾值。解决方法是将计算机时钟周期设计为比一个bit在计算机任意两个芯片之间传输所需最长时间更长即可。

#### D触发器（DFF门）

设计所有记忆单元的基本组件。

### 任务：构建本章的所有芯片

#### Bit

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/03/a/Bit.hdl

/**
 * 1-bit register:
 * If load[t] == 1 then out[t+1] = in[t]
 *                 else out does not change (out[t+1] = out[t])
 */

CHIP Bit {
    IN in, load;
    OUT out;

    PARTS:
    // Put your code here:
    Mux(a = t, b = in, sel = load, out = o);
    DFF(in = o, out = t, out = out);
}
```

#### Register

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/03/a/Register.hdl

/**
 * 16-bit register:
 * If load[t] == 1 then out[t+1] = in[t]
 * else out does not change
 */

CHIP Register {
    IN in[16], load;
    OUT out[16];

    PARTS:
    // Put your code here:
    Bit(in = in[0], out = out[0], load = load);
    Bit(in = in[1], out = out[1], load = load);
    Bit(in = in[2], out = out[2], load = load);
    Bit(in = in[3], out = out[3], load = load);
    Bit(in = in[4], out = out[4], load = load);
    Bit(in = in[5], out = out[5], load = load);
    Bit(in = in[6], out = out[6], load = load);
    Bit(in = in[7], out = out[7], load = load);
    Bit(in = in[8], out = out[8], load = load);
    Bit(in = in[9], out = out[9], load = load);
    Bit(in = in[10], out = out[10], load = load);
    Bit(in = in[11], out = out[11], load = load);
    Bit(in = in[12], out = out[12], load = load);
    Bit(in = in[13], out = out[13], load = load);
    Bit(in = in[14], out = out[14], load = load);
    Bit(in = in[15], out = out[15], load = load);
}
```

#### RAM8

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/03/a/RAM8.hdl

/**
 * Memory of 8 registers, each 16 bit-wide. Out holds the value
 * stored at the memory location specified by address. If load==1, then 
 * the in value is loaded into the memory location specified by address 
 * (the loaded value will be emitted to out from the next time step onward).
 */

CHIP RAM8 {
    IN in[16], load, address[3];
    OUT out[16];

    PARTS:
    DMux8Way(in = load, sel = address, a = in0, b = in1, c = in2, d = in3, e = in4, f = in5, g = in6, h = in7);
    Register(in = in, load = in0, out = o0);
    Register(in = in, load = in1, out = o1);
    Register(in = in, load = in2, out = o2);
    Register(in = in, load = in3, out = o3);
    Register(in = in, load = in4, out = o4);
    Register(in = in, load = in5, out = o5);
    Register(in = in, load = in6, out = o6);
    Register(in = in, load = in7, out = o7);
    Mux8Way16(a = o0, b = o1, c = o2, d = o3, e = o4, f = o5, g = o6, h = o7, sel = address, out = out);
}
```

#### RAM64

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/03/a/RAM64.hdl

/**
 * Memory of 64 registers, each 16 bit-wide. Out holds the value
 * stored at the memory location specified by address. If load==1, then 
 * the in value is loaded into the memory location specified by address 
 * (the loaded value will be emitted to out from the next time step onward).
 */

CHIP RAM64 {
    IN in[16], load, address[6];
    OUT out[16];

    PARTS:
    // Put your code here:
    //先选丢进哪个RAM8里，再考虑它在该RAM8里的address，用DMux实现选位置
    DMux8Way(in = load, sel = address[3..5], a = in0, b = in1, c = in2, d = in3, e = in4, f = in5, g = in6, h = in7);
    RAM8(in = in, load = in0, address = address[0..2], out = o0);
    RAM8(in = in, load = in1, address = address[0..2], out = o1);
    RAM8(in = in, load = in2, address = address[0..2], out = o2);
    RAM8(in = in, load = in3, address = address[0..2], out = o3);
    RAM8(in = in, load = in4, address = address[0..2], out = o4);
    RAM8(in = in, load = in5, address = address[0..2], out = o5);
    RAM8(in = in, load = in6, address = address[0..2], out = o6);
    RAM8(in = in, load = in7, address = address[0..2], out = o7);
    Mux8Way16(a = o0, b = o1, c = o2, d = o3, e = o4, f = o5, g = o6, h = o7, sel = address[3..5], out = out);
}
```

#### PC

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/03/a/PC.hdl

/**
 * A 16-bit counter with load and reset control bits.
 * if      (reset[t] == 1) out[t+1] = 0
 * else if (load[t] == 1)  out[t+1] = in[t]
 * else if (inc[t] == 1)   out[t+1] = out[t] + 1  (integer addition)
 * else                    out[t+1] = out[t]
 */

CHIP PC {
    IN in[16],load,inc,reset;
    OUT out[16];

    PARTS:
    //可能存在load inc和reset中超过1个是1的情况
    Inc16(in = t, out = inco);  //t是out[t]，当前正在计算out[t+1]
    Mux16(a = t, b = inco, sel = inc, out = out1);
    Mux16(a = out1, b = in, sel = load, out = out2);  //如果load  不管inc
    Mux16(a = out2, b = false, sel = reset, out = out3);    //如果reset， 不管inc和load
    Register(in = out3, load = true, out = t, out = out);
}
```

#### RAM512

```
// This file is part of the materials accompanying the book 
// "The Elements of Computing Systems" by Nisan and Schocken, 
// MIT Press. Book site: www.idc.ac.il/tecs
// File name: projects/03/b/RAM512.hdl

/**
 * Memory of 512 registers, each 16 bit-wide. Out holds the value
 * stored at the memory location specified by address. If load==1, then 
 * the in value is loaded into the memory location specified by address 
 * (the loaded value will be emitted to out from the next time step onward).
 */

CHIP RAM512 {
    IN in[16], load, address[9];
    OUT out[16];

    PARTS:
    // Put your code here:
    DMux8Way(in = load, sel = address[6..8], a = i0, b = i1, c = i2, d = i3, e = i4, f = i5, g = i6, h = i7);
    RAM64(in = in, load = i0, address = address[0..5], out = o0);
    RAM64(in = in, load = i1, address = address[0..5], out = o1);
    RAM64(in = in, load = i2, address = address[0..5], out = o2);
    RAM64(in = in, load = i3, address = address[0..5], out = o3);
    RAM64(in = in, load = i4, address = address[0..5], out = o4);
    RAM64(in = in, load = i5, address = address[0..5], out = o5);
    RAM64(in = in, load = i6, address = address[0..5], out = o6);
    RAM64(in = in, load = i7, address = address[0..5], out = o7);
    Mux8Way16(a = o0, b = o1, c = o2, d = o3, e = o4, f = o5, g = o6, h = o7, sel = address[6..8], out = out);
}
```

#### RAM4k

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/03/b/RAM4K.hdl

/**
 * Memory of 4K registers, each 16 bit-wide. Out holds the value
 * stored at the memory location specified by address. If load==1, then 
 * the in value is loaded into the memory location specified by address 
 * (the loaded value will be emitted to out from the next time step onward).
 */

CHIP RAM4K {
    IN in[16], load, address[12];
    OUT out[16];

    PARTS:
    // Put your code here:
    DMux8Way(in = load, sel = address[9..11], a = i0, b = i1, c = i2, d = i3, e = i4, f = i5, g = i6, h = i7);
    RAM512(in = in, load = i0, address = address[0..8], out = o0);
    RAM512(in = in, load = i1, address = address[0..8], out = o1);
    RAM512(in = in, load = i2, address = address[0..8], out = o2);
    RAM512(in = in, load = i3, address = address[0..8], out = o3);
    RAM512(in = in, load = i4, address = address[0..8], out = o4);
    RAM512(in = in, load = i5, address = address[0..8], out = o5);
    RAM512(in = in, load = i6, address = address[0..8], out = o6);
    RAM512(in = in, load = i7, address = address[0..8], out = o7);
    Mux8Way16(a = o0, b = o1, c = o2, d = o3, e = o4, f = o5, g = o6, h = o7, sel = address[9..11], out = out);
}
```

#### RAM16K

```
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/03/b/RAM16K.hdl

/**
 * Memory of 16K registers, each 16 bit-wide. Out holds the value
 * stored at the memory location specified by address. If load==1, then 
 * the in value is loaded into the memory location specified by address 
 * (the loaded value will be emitted to out from the next time step onward).
 */

CHIP RAM16K {
    IN in[16], load, address[14];
    OUT out[16];

    PARTS:
    // Put your code here:
    DMux4Way(in = load, sel = address[12..13], a = i0, b = i1, c = i2, d = i3);
    RAM4K(in = in, load = i0, address = address[0..11], out = o0);
    RAM4K(in = in, load = i1, address = address[0..11], out = o1);
    RAM4K(in = in, load = i2, address = address[0..11], out = o2);
    RAM4K(in = in, load = i3, address = address[0..11], out = o3);
    Mux4Way16(a = o0, b = o1, c = o2, d = o3, sel =  address[12..13], out = out);
}
```

## 第四周：Machine Language  机器语言

这周将从用户的角度来观察我们将要搭建的hack计算机

### Hack机器语言规范

Hack是基于冯诺依曼架构的16位计算机，由一个CPU、俩内存（指令内存（ROM）和数据内存（RAM））和两个内存映射IO设备（显示器和键盘）组成。

Hack的两个内存区都是16位宽，15位地址空间。其中指令内存为只读设备。

Hack有两个16为寄存器分别称为D和A，其支持被算术和逻辑指令显示操作，如A=D-1，D=!A

D仅用于存数据，A可以存地址或数据。

Hack规定内存的存取总是对地址"M"进行操作，如"D=M+1". 而储存M的内存单元的地址为A中的数值。因此，在对某个内存进行存取操作时，如D=Memory[516]-1，需要先将A中值设为516，然后令D=M-1.

#### A指令

形如

```
@value  //
```

用来为A寄存器存储15位的值。同时M被设置为RAM中A索引到的某个寄存器

#### C指令

形如

```
dest = comp; jump
```

comp表示要做的运算，dest表示comp算完要存到哪里，jump表示下一步要去哪。其中dest和jump都是可选的。

jump通过jump域的三个位中的值来确定是否jump。如果记这三位为j1,j2,j3，那么它们分别表示当ALU的输出<0,=0,>0时进行跳转。

为了防止A寄存器冲突（表示dest的地址还是表示jump指定的地址），在可能引发jump的C指令中不能引用M，在引用M的C指令中也不能引发jump。

#### 符号

##### 预定义符号

用R0到R15表示0到15号RAM地址

SP、LCL、ARG、THIS和THAT表示0到4号RAM地址

SCREEN和KBD被定义为表示RAM地址16384(0x4000)和24576(0x6000)，这两个地址分别为屏幕和键盘内存映像（memory-map）的基地址。

##### 标签符号

由伪指令“(Xxx)”声明一个自定义符号，Xxx表示程序中下一条命令的指令内存地址。该符号可以在定义之前使用。

##### 变量符号

用户定义的符号Xxx若不是预定义符号也不是标签符号，那么它是变量符号。其有独立的内存地址（从0x0010，即RAM地址16）开始。

#### 输入输出

Hack平台连接的交互设备：屏幕和键盘与计算机平台的交互是通过内存映像（memory map）实现的。

屏幕为$$256\times 512$$的黑白屏幕，左上角为第0行第0列。屏幕内容由RAM基地址为16384（0x4000）开始的内存映射表示。

第$r$行第$c$列为$RAM[16384+r\times 32 + \lfloor\frac{c}{16}\rfloor]$的字的c%16位   对这部分内存进行读写即可修改屏幕内容（1=黑，0=白）

键盘通过RAM基地址24576（0x6000）的单字内存进行交互。

在键盘上按下某个键时，其对应的16位ASCII码值出现在$RAM[24576]$。没有击键时该内存单元的值为0.Hack的键盘还能识别一些ASCII中没有的字符，比如方向键，pageup啥的

#### 语法和文件格式

##### 二进制文件

由若干行长为16的01串组成，每行对应一条机器语言指令。

文件被加载到内存中时，第n行所表示的二进制码会被储存至指令内存地址为n的单元中。（行号和地址都是从0开始记的）。机器语言程序文件的后缀为.hack

##### 汇编语言文件

后缀为.asm

由文本行组成，每行代表一条指令或一个符号定义

形如(Symbol)的代码会让编译器把Symbol标签分配给下一条命令被存储的内存单元地址。其被称为伪命令（不产生任何机器码）

以下规约只适合汇编程序：

1.常数和符号：常数非负且由十进制表示。用户自定义的符号不能以数字开头，可以由任何字母、数字、下划线、点、$、:等构成。

2.注释：// 单行注释，和C语言一样

3.空格 ： 空格字符和空行被程序忽略

4.大小写：所有汇编助记符必须大写。其他东西一般标签大写，变量名小写。

### 任务

#### 乘法（Mult.asm)

它好像不想让我把R1当成循环变量，不知道为啥

```hack
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

```



#### I/O程序 (Fill.asm)
```
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
//先想框架怎么写
//16384是屏幕的基地址，16384+8192=24576是键盘的基地址
//先整一个无限循环不断从键盘中读入 
//如果键盘有输入 (M!=0) 就跳转到把屏幕涂黑的循环
// 否则跳转到把屏幕涂白的循环
(LOOP)
    @KBD
    D = M
    @BLACK 
    D; JNE
    @WHITE 
    D; JEQ 
    @LOOP 
    0; JMP 
(BLACK)
//从16384开始  屏幕规格是256*512， 每行有512/16 = 32个16位寄存器 一共有32*256=8192个  
    @SCREEN 
    D = A
    @i 
    M = D   //i的值 = 16384 
    (BLACKLOOP)
        @i 
        D = M 
        @KBD 
        D = D - A 
        @LOOP   //如果屏幕已经满了（基地址指向键盘了）  直接回去继续读键盘
        D; JEQ
        D = -1 
        @i 
        A = M     
        M = D //填满这个寄存器  但此时i中存的还是这个寄存器的地址
        D = 1 
        @i 
        D = D + M 
        M = D   
        @BLACKLOOP 
        0; JMP 
(WHITE) 
    @SCREEN 
    D = A 
    @i 
    M = D 
    (WHITELOOP)
        @i 
        D = M 
        @KBD 
        D = D - A 
        @LOOP 
        D; JEQ 
        D = 0 
        @i 
        A = M 
        M = D 
        D = 1  
        @i 
        D = D + M 
        M = D 
        @WHITELOOP
        0; JMP  
​```hack
```

## 第五周： Computer Architecture   计算机体系结构

这门课最难的部分

这周作业由于复习期中考逾期了。



计算机基于固定的硬件平台，能够执行固定的指令集

指令能够组成任意的程序

1930年以前的计算机将程序的逻辑嵌入到硬件中，而1930年之后程序被储存到计算机的内存中，成为了软件。

通过载入不同的程序，同样的计算机可以实现完全不同的功能

### 冯诺依曼结构

可以执行任意类别程序的计算机被称作通用图灵机，而实现这一理念的计算机架构为冯诺依曼结构。

### Hack计算机的结构

有一块内存用来存放各种数据，以及构成程序的一行行指令。除此之外还会有个CPU用来执行指令

CPU由两个主要部分组成，一个是第二周作业中的ALU，另外一部分是一堆寄存器，此外还有控制单元对指令进行解码，指示硬件如何执行指令。控制单元还负责决定下一步需要取出和执行哪一条指令。

内存也由两部分组成，一部分储存数据，一部分储存程序对应的指令

### 任务：构造Hack计算机

需要用HDL实现Memory，Computer，CPU三个芯片

#### Memory

由RAM16K，Screen和Keyboard组成 ，总共24K+1个16位寄存器

因此需要先根据address判断要操作哪块内存中的寄存器

address[14]为0即表示该地址指向的寄存器位于RAM16K中

address[14]为1的情况下address[13]为0表示该地址值为16384~24575范围内，为Screen

address[14]为1且address[13]为1时，当且仅当剩下的位全为0表示Keyboard，否则为不合法输入

并不知道不合法输入要怎么用HDL处理，程序是按不是RAM或者Screen时必定是Keyboard来写的

```HDL
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/05/Memory.hdl

/**
 * The complete address space of the Hack computer's memory,
 * including RAM and memory-mapped I/O. 
 * The chip facilitates read and write operations, as follows:
 *     Read:  out(t) = Memory[address(t)](t)
 *     Write: if load(t-1) then Memory[address(t-1)](t) = in(t-1)
 * In words: the chip always outputs the value stored at the memory 
 * location specified by address. If load==1, the in value is loaded 
 * into the memory location specified by address. This value becomes 
 * available through the out output from the next time step onward.
 * Address space rules:
 * Only the upper 16K+8K+1 words of the Memory chip are used. 
 * Access to address>0x6000 is invalid. Access to any address in 
 * the range 0x4000-0x5FFF results in accessing the screen memory 
 * map. Access to address 0x6000 results in accessing the keyboard 
 * memory map. The behavior in these addresses is described in the 
 * Screen and Keyboard chip specifications given in the book.
 */

CHIP Memory {
    IN in[16], load, address[15];
    OUT out[16];

    PARTS:
    // Put your code here:
    Not(in = address[14], out = isRAM);
    And(a = isRAM, b = load, out = RAMload);
    RAM16K(in = in, load = RAMload, address = address[0..13], out = RAMout);
    Not(in = address[13], out = isS1);
    Not(in = isRAM, out = isnRAM);
    And(a = isnRAM, b = isS1, out = isScreen);
    And(a = isScreen, b = load, out = Screenload);
    Screen(in = in, load = Screenload, address = address[0..12], out = Screenout);
    Keyboard(out = Keyboardout);
    Mux16(a = Screenout, b = RAMout, sel = isRAM, out = out1);
    Or(a = isRAM, b = isScreen, out = ispart12);
    Mux16(a = Keyboardout, b = out1, sel = ispart12, out = out);
}
```



#### CPU

CPU中的控制单元需要判断输入的指令是A指令还是C指令，并执行对应的操作。

A指令不需要ALU参与运算，并且没有用上inM里的数据，只需要把instruction的后15位存进A即可。这时outM应当输出A索引到的值

每条指令形如`i xx a cccccc ddd jjj`，$i$表示是A指令还是C指令，如果是C指令，那么$a$位域决定是让A寄存器中的值参与ALU运算，还是让M中的值参与ALU运算。$c$位域决定ALU执行什么函数，$d$位域决定计算结果保持至哪里，$j$位域决定在什么条件下才$jump$。注意为了防止A寄存器冲突（表示dest的地址还是表示jump指定的地址），在可能引发jump的C指令中不能引用M，在引用M的C指令中也不能引发jump。

利用之前写好的ALU来执行计算。

书上的图5.9给出了电路图，建议对着书写

A寄存器和D寄存器有对应的内建芯片ARegister和DRegister，直接调用即可

而C指令的jump逻辑需要依靠PC和ALU输出的ng和zr来确定。$j1\&ng,j2\&zr, j3\&(!(ng\&zr))$​或起来为1即跳转。jump操作即为让PC从A寄存器中接受数据​（跳到A指向的位置去）

dest对应d位域的值可以参考书P68的

举例：

```HDL
@value
D = A
```

第一行首先是个A指令，把A寄存器值设为value

此时writeM为0，表示没有对M的写入操作，Memory找出value在内存中对应的值并把它传回来做为下一条指令的输入中的inM

第二条指令为C指令，没有jump操作，机器语言为1 11 0 110000 010 000  表示将A中值输入ALU 并把outD置0后取反（通过ALU计算出A的值）  即为comp的值，再存到010对应的寄存器（D）中 

```HDL
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/05/CPU.hdl

/**
 * The Hack CPU (Central Processing unit), consisting of an ALU,
 * two registers named A and D, and a program counter named PC.
 * The CPU is designed to fetch and execute instructions written in 
 * the Hack machine language. In particular, functions as follows:
 * Executes the inputted instruction according to the Hack machine 
 * language specification. The D and A in the language specification
 * refer to CPU-resident registers, while M refers to the external
 * memory location addressed by A, i.e. to Memory[A]. The inM input 
 * holds the value of this location. If the current instruction needs 
 * to write a value to M, the value is placed in outM, the address 
 * of the target location is placed in the addressM output, and the 
 * writeM control bit is asserted. (When writeM==0, any value may 
 * appear in outM). The outM and writeM outputs are combinational: 
 * they are affected instantaneously by the execution of the current 
 * instruction. The addressM and pc outputs are clocked: although they 
 * are affected by the execution of the current instruction, they commit 
 * to their new values only in the next time step. If reset==1 then the 
 * CPU jumps to address 0 (i.e. pc is set to 0 in next time step) rather 
 * than to the address resulting from executing the current instruction. 
 */
//inM表示当前RAM[A]的值 
//如果当前指令要修改M的值(M=D或M=A)  那么writeM为1  M的新值为outM 这个要修改的寄存器的地址为addressM
//这些输出发送给了Memory，由Memory执行这个修改。CPU只需要发送命令就行

CHIP CPU {

    IN  inM[16],         // M value input  (M = contents of RAM[A]) 表示当前A中存的地址指向的位置上的值
        instruction[16], // Instruction for execution                           
        reset;           // Signals whether to re-start the current
                         // program (reset==1) or continue executing
                         // the current program (reset==0).

    OUT outM[16],        // M value output
        writeM,          // Write to M? 
        addressM[15],    // Address in data memory (of M)
        pc[15];          // address of next instruction

    PARTS:
    // Put your code here:
    //i xx a cccccc ddd jjj
    //指令最高位为0表示A指令  1表示C指令
    Mux16(a = instruction, b = ALUout, sel = instruction[15], out = inA); 
    //在d1=1 或是为A指令时存进A寄存器
    Not(in = instruction[15], out = isA);
    And(a = instruction[15], b = instruction[5], out = CloadA);
    Or(a = isA, b = CloadA, out = loadA);
    ARegister(in = inA, load = loadA, out = outA, out[0..14] = addressM, out = pcin);
    //在d2=1 且为C指令时存进D
    And(a = instruction[15], b = instruction[4], out = loadD);
    DRegister(in = ALUout, load = loadD, out = outD);
    //在d3=1 且为C指令时存进M(打上writeM标记即可)，通知Memory把M修改为outM的值
    And(a = instruction[15], b = instruction[3], out = writeM);
    //在为C指令时判断将A输入ALU还是将M输入ALU，否则A指令直接输出outA至ALU outM = RAM[A] 
    And(a = instruction[12], b = instruction[15], out = sel1);
    Mux16(a = outA, b = inM, sel = sel1, out = ALUin);  //将A或M输入ALU
    And(a = instruction[15], b = instruction[11], out = zx);
    And(a = instruction[15], b = instruction[10], out = nx);
    And(a = instruction[15], b = instruction[9], out = zy);
    And(a = instruction[15], b = instruction[8], out = ny);
    And(a = instruction[15], b = instruction[7], out = f);
    And(a = instruction[15], b = instruction[6], out = no);
    ALU(x = outD, y = ALUin, zx = zx, nx = nx, zy = zy, ny = ny, f = f, no = no, out = ALUout, out = outM, zr = zr, ng = ng);
    //ALU的结果即为C指令中的COMP， A指令时输出的是outA&ALUin
    And(a = ng, b = instruction[2], out = t1);  // < 0
    And(a = zr, b = instruction[1], out = t2);  // = 0
    Or(a = ng, b = zr, out = ngz);  
    Not(in = ngz, out = pos);   
    And(a = pos, b = instruction[0], out = t3);  // > 0
    Or(a = t1, b = t2, out = tt1);             
    Or(a = tt1, b = t3, out = tt);
    And(a = instruction[15], b = tt, out = PCload); //注意C指令才能触发jump  
    PC(in = pcin, load = PCload, inc = true, reset = reset, out[0..14] = pc);   
}
```



#### Computer

由ROM32K， CPU和Memory三个芯片组成

根据书上的图写

当reset为0的时候  执行ROM32K中的程序

当reset为1 重启程序

ROM32K的address参数不知道是啥意思，但看图pc和它连着，就输入pc罢

```HDL
// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/05/Computer.hdl

/**
 * The HACK computer, including CPU, ROM and RAM.
 * When reset is 0, the program stored in the computer's ROM executes.
 * When reset is 1, the execution of the program restarts. 
 * Thus, to start a program's execution, reset must be pushed "up" (1)
 * and "down" (0). From this point onward the user is at the mercy of 
 * the software. In particular, depending on the program's code, the 
 * screen may show some output and the user may be able to interact 
 * with the computer via the keyboard.
 */

CHIP Computer {

    IN reset;

    PARTS:
    // Put your code here:
    ROM32K(address = pc, out = instruction);
    Memory(in = outM, load = writeM, address = addressM, out = inM);
    CPU(inM = inM, instruction = instruction, reset = reset, outM = outM, writeM = writeM, addressM = addressM, pc = pc);
}

```

## 第六周  Assembler 汇编编译器

Hack计算机的机器语言需要被翻译成对应的二进制码，才能让Hack计算机执行。

写一个程序 ，把Hack汇编语言翻译成Hack机器语言中的二进制码，该程序被称为汇编编译器。

Hack机器语言的语法见第四周部分的内容

编译器需要对于每条语句，判断其是哪一种指令，识别其中的符号，进行对应的文本处理。

保证给定的汇编程序代码没有bug。

程序需要分析语句是A指令还是C指令，并执行对应操作

还要处理空行，空格和注释。 

A指令形如`@value`，处理起来比较简单  

对应的16位机器码中，首位为0，剩下的15位是`value`对应的二进制值

C指令形如 dest = comp; jump; 其中dest或jump域都可以为空。如果dest为空，''`=`''会被省略；而如果jump为空，最后的“；”会被省略。

书上给了张c指令对应的二进制表示的表，照抄就行

### 没有符号的情况

按照书上给出的思路实现Praser和Code模块即可。

要是没给的话还真不会写

### 有符号的情况

先预处理符号 存入符号表

如果A指令中有符号 但符号表里没有 说明那是个变量 分配一个从16开始的地址

用C++实现写了大概400行，wings表示用py会好写得多

代码见github