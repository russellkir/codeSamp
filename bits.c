
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  //returns x&y using only ~ and |
  return ~(~x | ~y);
}

/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    //returns minimum two's complement integer
  return 0x1 << 31;

}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
  //returns 1 if all even-num bits in word set to 1
  int check = 0x55 | 0x55 << 8 | 0x55 << 16 | 0x55 << 24;
  return !((x & check) ^ check);
}



/** bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int count = 0;
  count = count + ((x>>0) & 0x1);
  count = count + ((x>>1) & 0x1);
  count = count + ((x>>2) & 0x1);
  count = count + ((x>>3) & 0x1);
  count = count + ((x>>4) & 0x1);
  count = count + ((x>>5) & 0x1);
  count = count + ((x>>6) & 0x1);
  count = count + ((x>>7) & 0x1);
  count = count + ((x>>8) & 0x1);
  count = count + ((x>>9) & 0x1);
  count = count + ((x>>10) & 0x1);
  count = count + ((x>>11) & 0x1);
  count = count + ((x>>12) & 0x1);
  count = count + ((x>>13) & 0x1);
  count = count + ((x>>14) & 0x1);
  count = count + ((x>>15) & 0x1);
  count = count + ((x>>16) & 0x1);
  count = count + ((x>>17) & 0x1);
  count = count + ((x>>18) & 0x1);
  count = count + ((x>>19) & 0x1);
  count = count + ((x>>20) & 0x1);
  count = count + ((x>>21) & 0x1);
  count = count + ((x>>22) & 0x1);
  count = count + ((x>>23) & 0x1);
  count = count + ((x>>24) & 0x1);
  count = count + ((x>>25) & 0x1);
  count = count + ((x>>26) & 0x1);
  count = count + ((x>>27) & 0x1);
  count = count + ((x>>28) & 0x1);
  count = count + ((x>>29) & 0x1);
  count = count + ((x>>30) & 0x1);
  count = count + ((x>>31) & 0x1);

  return count;
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
  //shift x over by n, create a mask that is 1's wherever you want a zero,
  //shift over by (n -1) (since mask creation starts with 1, shifting by
  //just n would create a mask 1 too large).  The mask is negated to get 
  //0's where you want them to be in the final number, and then
  //anding the 2 together gives you n 0's on the left
  int temp = x >> n;
  int mask = (0x80 << 24) >> n;
  mask = ~(mask << 1);
  return (temp & mask);
}
/* 
 * isNegative - return 1 if x < 0, return 0 otherwise 
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x) {
  int val = 0x80 << 24;
  return !((x & val) ^ val);
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  //compares case by case if x and y are positive, negative, and
  //a combination, returning x > y 
  int x_pos = !(( x >> 31) & 1);
  int y_pos = !(( y >> 31) & 1);
  int sign_diff = (x_pos ^ y_pos);
  int sign_same = !sign_diff;
  int sign_bit = ((y + (~x+1) ) >> 31) & 1;
  return (sign_diff & x_pos) | (sign_same & sign_bit);
}

/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  return (( ( (~x+1) >> 31) & 1) & !((x >> 31) & 1)) & !(x & (x + (~0x0) ) );
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
  //shifts x over 32 - n and back to see if the truncated 
  //numbers effect value, if yes then input would not fit
  //in n number bit two's complement number
  int neg_n = ~n + 1;
  int shiftVal = 32 + neg_n;
  int temp = x << shiftVal;
  temp = temp >> shiftVal;
  return !(temp ^ x);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  //take x, which is either zero or non zero, and apply ! to logically
  //negate, and then ! to give either 0 or 1
  //this is negated to give all 1's for true and 0's for false x value.
  //y is performed if x is true, and z if x is false.  Anding the value with
  //and the negated value with z will give y if temp was true, z if ~temp 
  //was true, and or-ing will be returned with if temp or ~temp were true, 
  //corresponding if x were true or false.
  int temp = !!x;
  temp = ~temp + 1;
  return (temp & y) | (~temp & z);
}
/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) {
  int temp = x; int count = 0;
  int a = 0; int b = 0; int c = 0; int d = 0; int e = 0;
  a = !!(temp & (0xff << 24 | 0xff << 16));
  temp = (temp >> (16 & (a << 4)));
  count = count + (16 & (a << 4));

  b = !!(temp & (0xff <<  8));
  temp = (temp >> (8 & (b << 3)));
  count = count + (8 & (b << 3));

  c = !!(temp & (0xf << 4));
  temp = (temp >> (4 & (c << 2)));
  count = count + (4 & (c << 2));

  d = !!(temp & (0x3 << 2));
  temp = (temp >> (2 & (d << 1)));
  count = count + (2 & (d << 1));

  e = !!(temp & (0x1 << 1));
  temp = (temp >> (1 & (e << 0)));
  count = count + (1 & (e << 0));
  temp = !!x;
  temp = ~temp + 1;
  //count = count + !!(temp);
  return ((temp &(0x1 << count)) + (!temp & 0));
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
  int temp = x; int temp2 = 0; int x_neg = (( temp >> 31) & 1);
  int expn = 127; int frac = 0; int G_v = 0; int R_v = 0; int S_v = 0;
  //iT_min case
  int min_int = 0x1 << 31;
  if(temp == min_int){
    return 0xcf000000;
  }
  //x == 0 xase
  if(temp == 0){
    return 0;
  }
  //check if x is positive
  //absolute value of x
  if(x_neg){
    temp = 0 - temp;
  }
  //extra copy of positive x
  temp2 = temp;

  //find number of significant bits
  while(temp > 1){
    temp = temp / 2;
    expn += 1;
  }

  if(expn > 150){ // expn - 127 > 23, count > 23

    //shifting right to get 23 most significant bits
    frac = (temp2 >> ((expn - 150))) & 0x7fffff; //count - 23

    //rounding values
    G_v = (frac & 0x1);
    R_v = ((temp2 >> ((expn - 151))) & 0x1); // count - 24
    S_v = (~(min_int >> (182 - (expn))) & temp2) > 0; //32 - (count - 23)
     if(R_v){
       if((G_v && !S_v) || (S_v)){
           frac = frac + 1;
           if(frac == 0x800000){
                frac = 0;
                expn += 1;
           }
       }
    }
  }
  else {
    frac = (temp2 << (150 - (expn))) & 0x7fffff;
  }
  //return R_v;
  return (x_neg << 31) | expn << 23 | frac;
}


/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
    int uf_exp = (uf >> 23) & 0xff;
    int uf_frac = uf & 0x7fffff;
    if(uf_frac && uf_exp == 0xff){
        return uf;
    }
    return( uf & ~(0x1<< 31));
}


