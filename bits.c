/* 
 * CS:APP Data Lab 
 * 
 * <Dimitri Durmishian dimitri.durmishian>
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
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  /*Logically:
  If we have X AND Y, this means that: NOT(I have X AND I have Y)
  equals to (I do not have X OR I do not have Y), so basically
  ~(X&Y) == (~X) | (~Y) => take '~', to the right side and return
  */
  return ~((~x) | (~y));
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
    /*Logic:
    We need to create a mask, but we cannot use *, so we use right shifting 
    n is determining the position of byte we need to take out, so we do n*8
    then we place out mask under the wanted byte and apply & operator 
    then we shift it to the right to be rightmost
    and then apply mask(without shifting) again to take out unwanted symbols
    */
  int shiftNum = n << 3; // same as n*8, since left-shifting is n*2^right-op (n*2^3 == 8)
  int mask = 0xFF << shiftNum;
  return (x & mask) >> shiftNum & 0xFF;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  /*Logic:
  Right shift is arithmetical for signed integers, so we need to convert MSB into 0
  for result to become logical. We use mask: We shift 1 to the 0th position, than shift it
  right by n, since its also arithmetical shift, vacated positions will be filled with 1s
  That's why we apply ~ operator to change them, so then MSB & 0 = 0
  We also use << 1 to avoid shifting by more than 31.
  */
  int mask = ~(1 << 31 >> n << 1);
  return (x >> n) & mask;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    /*Logic:
    We create a mask to count ones in even positions in 32 bit, then we 
    shift it to the right to check all odd positions
    The masks: 0x33, 0x0F, 0xFF << 8 and 0xFF << 16 are created to do the optimization
    All of these masks count amount of 1s in sets of 4, 8, 16, 32 respectively
    In the end its all added together
    */   
    int result = 0;
    int mask = 0x55 | 0x55 << 8;

    mask = mask | (mask << 16); // mask = 010101...
    result = x & mask;
    x = x >> 1;
    result = result + (x & mask);

    mask = 0x33 | 0x33 << 8;
    mask = mask | (mask << 16); // mask = 0x33333....
    result = ((result >> 2) & mask) + (result & mask);

    mask = 0x0F | 0x0F << 8;
    mask = mask | (mask << 16); // mask = 0x0F0F0F...
    result = ((result >> 4) & mask) + (result & mask);

    mask = 0xFF | 0xFF << 16;
    result = ((result >> 8) & mask) + (result & mask);

    mask = 0xFF | 0xFF << 8;
    result = ((result >> 16) & mask) + (result & mask);
  return result;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
    /*Logic:
    If the number is non-zero, the signbit of its two's complement will be 1
    But if the number is zero its sign bit will be 0. We isolate this two bits and check with bitwise OR
    Than we perform binary addition. If the number was non-zero it will be just 1s all along, so adding 1 
    will give us all zeros
    */
    return ((x >> 31) | ((~x + 1) >> 31)) + 1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  /*Logic:
  To find the minumum representable value we need to set sign-bit to 1(negative)
  this will give us (-2*31), which is -2,147,483,648
  */
  return 1 << 31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  /*Logic:
  We shiftout all significance bits out if x is within the n bit range
  Then with the flag we check it, if temp is 0, then x is within n bits
  But if temp is -1, that means that x is out of bounds
  */
  int temp = x >> (~((~n) + 1));
  int flag = (!temp | !(temp + 1));
  return flag; 
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
    /*Logic:
    Normal right shifting rounds towards negative infinity, so
    if x is negative it will be incorrect. So we make adjustment by
    moving x to the next multiple of 2^2
    */
    int signBit = x >> 31;
    int adjust = (signBit & ((1 << n) + ~0));
    return (x+adjust)>>n;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /*Logic:
  Bitwise operator ~ gives us one's complement of a number, basically (-x-1)
  So we add 1 to make it two's complement
  */
  return ~x+1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  /*Logic:
  Here we are allowed to use logical NOT, so if the signed bit shifted to the right is 0
  the logical not will give us 1(for positive), or 0 if the the signed bit was 1(negative)
  Then we use double ! to write != 0
  */
  return !(x >> 31) & !!x;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  /*Logic:
  First we check if the signBits are different, if yes than it will be all 1,
  if they are the same then all 0. After OR with y it either leaves it unchanged or 
  makes all 1s.Then we adjust x, if x and y have different signs then it substracts 1 from x
  otherwise: leaves x unchaged.
  After the shifting it will be all 1s if x <= y, or all 0s if x > y
  */
  return ((x + ~(((x ^ y) >> 31) | y)) >> 31) & 1;;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  /*
  Logic:
  This function computes the floor of the base 2 logarithm of a positive integer x.
  It iteratively divides x into smaller halves and checks if each half contains any set bits.
  The result is constructed by shifting the position of the highest set bit found in x.
  The final result represents the position of the highest set bit, which is the floor of the log base 2 of x.
 */
  int ans=0;
  ans=(!!(x>>(16)))<<4;
  ans=ans+((!!(x>>(8+ans)))<<3);
  ans=ans+((!!(x>>(4+ans)))<<2);
  ans=ans+((!!(x>>(2+ans)))<<1);
  ans=ans+((!!(x>>(1+ans)))<<0);
  return ans;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  /*Logic:
  We shift the sign bit to get rid of it and to get all exp positions
  Then we check if number is NaN
  */
  unsigned mask1 = 0x80000000;
  unsigned mask2 = 0xFF000000;
  unsigned temp = uf << 1;

  if ((mask2 & temp) == mask2) 
  {
    if (temp != mask2)
      return uf;
  }
  return uf ^ mask1;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  unsigned ans;
  int tmpx = x;
  int f = 0;
  int delta = 0;
  int tail = 0;
  int E = 0;

  //If x is equal to 0, then return x directly
  if (x == 0)
    return x;

  //If x is the minimum value, that is -2^31, then 1 10011111 000..0 e=159,E=32,f=0,M=1
  if (x == 0x80000000)
    return 0xcf000000;

  ans = x & 0x80000000; //sign bit

  if (ans)
    tmpx = -x; //If x is a negative number, then tempx takes the opposite number of x (is positive) 
  
  //In order to construct the decimal field, we first discard 1, then add 0 to the tail, and keep adding Until 23 bits while ((tmpx >> E))
  while ((tmpx >> E))
    E++;

  E = E - 1;
   //Take 12345 as an example, the binary expression is now 11000000111001, E=13 
  tmpx = tmpx << (31 - E); //Now tmpx has a total of 31 bits.
    //tmpx = 11000000111001 000000000000000000
  tail = (tmpx >> 8) & 0x007FFFFF; 
    //10000001110010000000000
  f = tmpx & 0xff;
  //Round to even numbers
  delta = (f > 128) || ((f == 128) && (tail & 1));
  tail += delta;

  E = E + 127; 
	
  if (tail >> 23)
  {
    tail = tail & 0x007FFFFF;
    E += 1;
  }
  ans = ans | E << 23 | tail;
  
  return ans;
}
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
  /*Logic: 
  Masks are used to extract different parts of the floating-point representation: 
  mask1 for the sign bit, mask2 for the exponent bits, and mask3 for the fraction bits.
  infty is a mask representing infinity in the exponent bits.
  */
  
  int mask1 = uf&0x80000000;
  int mask2 = uf&0x7f800000;
  int mask3 = uf&0x007fffff;
  int infty = 0xff000000;
  int tempuf = uf << 1;
  int ans = uf;

  if((tempuf & infty) == infty)
    return uf;

  if(mask2 != 0)
    ans = mask1 + mask3 + mask2 + 0x00800000;

  else if(mask3 != 0)
    ans = mask1 + mask2 + (mask3 << 1);
  return ans;
}
