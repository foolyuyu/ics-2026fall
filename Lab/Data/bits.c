/* 
 * CS:APP Data Lab 
 * 
 * <王小愚 2500013175>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
  只能用这些！！！
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
        额我不会用dlc编译啊？？？？（待补充
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
        这个也（待补充
 */


#endif
/* Copyright (C) 1991-2024 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
// 2026 puzzle selection (16 puzzles, 48 correctness points).
// Previous years' selections are in git history.
// Grading: integer puzzles -> BDD checker; float puzzles -> btest (see driver.pl).
// Bit manipulations (rating sum 15)
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  // x,y 以及 ~x,~y分别做按位与&，可以判断出是否相同（相同时得到结果必然是0和1），不同时，所得结果都是0和0
  // 此时需要对结果全部取反（这样按位与才能得到不同结果）相同0，不相同1，即为异或运算
  int var1 = x & y;
  int var2 = ~x & ~y;
  int result = ~var1 & ~var2;
  return result;
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {
  // 按位取反再加1，此时，在末尾1的左侧，所有值都与x异，在末尾1的右侧，得到了100...0，与x同，所以再使用&可以把相同的1变成1，其余变成0，即为00..0100..0
  int var1 = ~x + 1;
  return var1 & x;
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  // 把x右移n * 8个字节，然后与0b11111111进行按位与，截取到这一字节
  int var1 = 0xFF;
  int var2 = x >> (n << 3);
  return var1 & var2;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int logicalShift(int x, int n) {
  // 确定符号位，做算数右移>>，把符号位改为0
  int var1 = 0x01 << 31; //100...0
  int var2 = (var1 >> n) << 1; //11...100...0
  return ~var2 & (x >> n);  
}
/*
 * grayToBinary - convert a 31-bit Gray code to binary (0 <= x <= TMax)
 *   The binary value b of Gray code g satisfies
 *     b[i] = g[i] ^ g[i+1] ^ ... ^ g[MSB]
 *   i.e. b is the prefix-XOR of g from the most significant bit down.
 *   Examples: grayToBinary(0)=0, grayToBinary(1)=1, grayToBinary(3)=2,
 *             grayToBinary(2)=3, grayToBinary(6)=4
 *   Hint: a prefix-XOR over 32 bits can be done in log-many steps by
 *         "doubling" the shift distance (1, 2, 4, 8, 16).
 *   Legal ops: ^ >>
 *   Max ops: 20
 *   Rating: 3
 */
int grayToBinary(int x) {
  // 第一次做异或，可以把相邻两位异或运算；得到的值可以利用进行相邻四位的异或运算，以此类推；
  // 每次参与异或的数量翻倍，并且由于x为正，高位项在后续按位异或操作时不会受到影响
  x = x ^ (x >> 1); 
  x = x ^ (x >> 2); 
  x = x ^ (x >> 4); 
  x = x ^ (x >> 8);
  x = x ^ (x >> 16);
  return x;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  // 第一轮错位把奇数位和偶数位相加，得到的数进行第二轮相加（这次11001100-2bit为一个数，错位相加
  // 依次类推，直到加完只剩下一个数
  int var1 = (0x55 << 8) + 0x55; // 01010101先取奇数位
  int mask = (var1 << 16) + var1;
  int var2 = (mask & x) + (mask & (x >> 1));
  var1 = (0x33 << 8) + 0x33; //0x0011001100110011
  mask = (var1 << 16) + var1;
  var2 = (mask & var2) + (mask & (var2 >> 2));
  var1 = (0x0F << 8) + 0x0F; //0x0000111100001111
  mask = (var1 << 16) + var1;
  var2 = (mask & var2) + (mask & (var2 >> 4));
  mask = (0xFF << 16) + 0xFF; //0x00000000111111110000000011111111
  var2 = (mask & var2) + (mask & (var2 >> 8));
  mask = (0xFF << 8) + 0xFF; //0x1111111111111111
  int result = (mask & var2) + (mask & (var2 >> 16));
  return result;
}
// Two's complement arithmetic (rating sum 17)
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
  //利用按位异或，如果所有位都相同的话，得到0，其他情况都不是0，再利用!保证相同1，不同0
  int check = x ^ y; 
  return !check;
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  // x >> n（在x为正时，如果x为负且有余数，需要加1）
  /*int reminder = x & ~(~0 << n);
  return (x >> n) + (!!reminder & (x >> 31));*/

  // 另一种做法：如果是负数，令x-1再去做向负无穷的整数除法，这样对于原本能整除的，算出来的结果也是小了1，这样只需要把负数整体加1就可以了
  int s = x >> 31
  return ((x + s) >> n) + (s & 1);
  
}
/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
  // 如果是非负数x >> 31是0，是负数，x >> 31是-1
  // 需继续对非负数分类讨论，若是正数 0 + 1,是0的话0 + 0，同时负数不能被影响
  int s = x >> 31;
  return s + !!(~s & x);
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  // 加法溢出中，只存在两种情况，负+负=正 和 正+正=负，即判断xy符号是否一致以及其与结果是否不一致
  int total = x + y;
  int x_s = x >> 31, y_s = y >> 31, total_s = total >> 31;
  int overflow = !(x_s ^ y_s) & (x_s ^ total_s); // 两s进行^运算，一致0，不一致0xFF
  return !overflow;
}
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  // 如果不考虑正负，取相反数的方法是按位取反再+1，但是这里面在求绝对值，所以提出符号位很重要
  // 得到1111or0000，可以借此来进行有符号指导的按位取反
  int s = x >> 31;
  return (s ^ x) + (s & 1);
}
/*
 * satSub - compute x - y, saturating to Tmax on positive overflow and
 *   Tmin on negative overflow.
 *   Examples: satSub(5,3)=2, satSub(0x80000000,1)=0x80000000,
 *             satSub(0x7FFFFFFF,0x80000000)=0x7FFFFFFF
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satSub(int x, int y) {
  // 算结果，判断是否溢出，如果溢出了确定类型并生成Max
  int b = ~y + 1;
  int result = x + b; //此时就像addOK()一样判断错误类型
  int x_s = x >> 31, b_s = b >> 31, result_s = result >> 31;
  int overflow = !(x_s ^ b_s) & (x_s ^ result_s);
  int max = (1 << 31) + result_s; // 如果result是负数，说明发生了正溢出，result=11...1，返回0x7FF...F
  return (~overflow & result) + (overflow & max); 
}
// Floating point (rating sum 16)
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  // 乘2相当于e+1，但是special value和denormalized value的行为不太一样
  // 返回值有可能是，±inf，NaN，正常结果
  unsigned s = uf & 0x80000000u;
  unsigned e = uf & 0x7F800000u;
  unsigned f = uf & 0x007FFFFFu;
  // 如果uf是NaN，即e位全1，且f位不全为0，就返回原值
  if (!(e ^ 0x7F800000u) && f) {
    return uf;
  }
  // 如果是inf，直接返回
  if (!(e ^ 0x7F800000u) && !f) {
    return uf;
  }
  // 如果是denormalized的话，denormalized进位为normalized很自然的和正常的不进位可以相同方式表达
  if ((!e)){
    return s + (f << 1); // e位全是0，不用加了
  } 
  // 如果是normalized的话，直接指数+1就可以了
  e = e + 0x00800000u;
  // 判断是否溢出
  if (!(e ^ 0x7F800000u)) {
    return 0x7F800000u + s;
  }
  return s + e + f;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating poin「t value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  // e=127+23=140时，恰好不需要移位
  unsigned s = us & 0x80000000u;
  unsigned e = (uf >> 23) & 0x000000FFu;
  unsigned f = (uf & 0x007FFFFFu) + 0x00800000u;
  // inf和NaN
  if (!(e ^ 0x000000FFu)) {
    return 0x80000000u;
  }
  unsigned move = e + 0xFFFFFF81u + 0xFFFFFFE9; // e - 127 - 23
  if (move & 0x80000000u) {
    return f >> (~move + 1);
  }
  return f << move;

}
/* 
 * float_negpwr2 - Return bit-level equivalent of the expression 2.0^-x
 *   (2.0 raised to the power -x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^-x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 20 
 *   Rating: 4
 */
unsigned float_negpwr2(int x) {
    // float正数能表达的范围为1*2^(-126-23)=2^-149 ~ 1.11...1*2^128<2^129
    // 150 = 0b010010110 = 0x00000096u
    // 如果-149<=x<=-127，denormalized，f位补一个1，其余都为0，e = 0
    // 如果-126<=x<=128，normalized，f位全0，e = x + 127,

}
/* 
 * float_greater - Return bit-level equivalent of expression x > y for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 45
 *   Rating: 4
 */
unsigned float_greater(unsigned x, unsigned y) {
  return 2;
}
