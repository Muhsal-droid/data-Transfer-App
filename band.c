#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "band.h"

void getbytes( unsigned char dest[], int bytes,void *src,int reverse) {
  int length = bytes;
  int last = length - 1;
  /*if starting in reverse, take account of the zero*/
  unsigned char * line = src;
  int i = 0,j = 0, k = 0,last_pos = length;
  if (reverse == 0){
    /*if reverse value is 0, then read the string till the bytes value in original order*/
    for ( k = 0; k < length; k++) {
      dest[k] = line[k];
    }
  }
  if (reverse == 1){
    /*for reverse, read the string like normal first but then decrement and start storing by the last*/
    i = last;
    while( i >= 0 ) {
      dest[j] = line[i];
      j++;
      i--;
    }
  }
  dest[last_pos] = '\0';
}/*
int main( int argc, char **argv )
{
  char *str1 = "abcdefghi";
  unsigned char dest[9] = "01234567";

  printf( "\"%s\"\n", dest );

  getbytes( dest, 8, str1, 0 );
  dest[8] = '\0';

  printf( "\"%s\"\n", dest );

  getbytes( dest, 8, str1, 1 );
  dest[8] = '\0';

  printf( "\"%s\"\n", dest );

  return 0;
}*/

void getbits( char dest[], int bytes, void *src, int start, int end){
  unsigned char * string = src;
  int m,k,n;
  k = start,m = 0,n =0;
  int remainder = 0, quotient = 0,index = 0;
  for (n = start ; n > end ; n--){
    /*to run the  loop in the range  where range = start- end as start is bigger than range*/
    remainder = n%8;
    quotient = n/8;
    index  = bytes-quotient -1;
    /*this is the formula were tols in assignment description to calculate remainder,quotient and index */
    if ((string[index]>>remainder) & 1) {
      /*take the shifted value of string at index and use the & operator to see if true*/
      dest[m] = '1';
      /*if true , the destination will store a 1*/
    }else{
      dest[m]= '0';
      /*if false , the destination will store a 0*/
    }
    start --; m++;
    /*decrement all the variables that go from a bigger value to small*/
  }
  dest[k-end]= '\0';
  /*this is to make sure the last thing being stored is a null terminator to signify where to stop*/
}

/*int main( int argc, char **argv )
{
  unsigned short num = 4096 + 1024 + 256 + 128 + 32 + 8 + 4;
  unsigned char bytes[2];
  char string[17];

  getbits( string, sizeof(unsigned short), &num, 15, -1 );
  printf( "%s\n", string );

  getbytes( bytes, sizeof(unsigned short), &num, 1);
  getbits( string, sizeof(unsigned short), bytes, 15, -1 );
  printf( "%s\n", string );

  getbits( string, sizeof(unsigned short), bytes, 15, 7 );
  printf( "%s\n", string );

  getbits( string, sizeof(unsigned short), bytes, 7, -1 );
  printf( "%s\n", string );

  getbits( string, sizeof(unsigned short), bytes, 11, 3 );
  printf( "%s\n", string );

  return 0;
}*/
unsigned long long bits2ull( char *bits ){
  unsigned long long length  = strlen(bits);
  unsigned long long store = 0;
  unsigned long long last_digit = 0;
  int power = 2 ;
  int firstone = 1;
  int counter = 0;
  int i,j;
  i = 0;
  j = 0;
  if (length ==1 && bits[i] =='0') {
    last_digit  =0;
    /*testing of the initial 1 & 0*/
  }else if (length ==1 && bits[i] =='1') {
    last_digit  =1;
    /*testing of the initial 1 & 1*/
  } else {
    while (i <length){
      if (bits[i] !='0') {
        counter = i;
        /* counter is the position we are at when subtarcting from total length*/
        store = 1;
        for(j=0;j < length-counter- firstone;j++) {
          /* subtract the one in the for loop as we want to store the first one as once */
          /* so in this loop, the first 1 does not run in this loop hence the -1  */
          store = store*power;
        }
        last_digit +=store;
      }
      i++;
    }
  }
  return last_digit;
}
/*int main( int argc, char **argv )
{
  int i;
  char *test_strings[10] = {
    "0",
    "1",
    "00",
    "01",
    "10",
    "11",
    "111",
    "0111111111111111111111111111111111111111111111111111111111111111",
    "1000000000000000000000000000000000000000000000000000000000000000",
    "1111111111111111111111111111111111111111111111111111111111111111"
    };


  for (i=0;i<10;i++)
  {
    printf( "%llu\n", bits2ull( test_strings[i] ) );
  }

  return 0;
}*/

long long bits2ll( char *bits ){
  unsigned long long length  = strlen(bits);
  unsigned long long length2  = strlen(bits) + 1;
  unsigned long long store = 0;
  unsigned long long last_digit = 0;
    char string[length] ;
    char string2[length] ;

  int gate = 0;
  int power = 2 ;
  int firstone = 1;
  int counter = 0;
  int i,j,k,m,n;
  i = 0;
  j = 0;
  k = 0;
  m = 0;
  n = 0;
  int position;
  int true = 1;
  int negative  = -1;
  int number = 0;
if (bits[0] == '1') {
  number  = true;
  i = 1;
  /*this is to see if the left most bit is 1 and if it is, take the 1 out of the index and make the boolean true. */
}
if (number == true ) {
  /*once the boolean is true, shift the left most bit to the power and it is 1, the decimal value = * -1.*/
  last_digit = (unsigned long long )1ULL << length-1;
  last_digit *= negative;
}
    while (i <length){
/* this is to calculate the rest of the values as calculated in 2ulls*/
      if (bits[i] =='1') {
        counter = i;
        store = 1 ;
        for(j=0;j < length-counter-firstone;j++) {
          store = store* (power);
        }
        last_digit +=store;
      }
      i++;
    }

  return last_digit;
}/*ss
int main( int argc, char **argv )
{
  int i;
  char *test_strings[10] = {
    "0",
    "1",
    "00",
    "01",
    "10",
    "11",
    "111",
    "0111111111111111111111111111111111111111111111111111111111111111",
    "1000000000000000000000000000000000000000000000000000000000000000",
    "1111111111111111111111111111111111111111111111111111111111111111"
    };


  for (i=0;i<10;i++)
  {
    printf( "%lld\n", bits2ll( test_strings[i] ) );
  }

  return 0;
}
*/

void spff( char *sign, char *exponent, char *significand, float*src ){
  int i= 0,j =0;
  unsigned char bytes[4];
  if (*src > 0) {
    sign[0] = '0';
  }else{
    sign[0] = '1';
  }
  sign[1] = '\0';
  getbytes( bytes, 4, src, 1);
  getbits( exponent,4, bytes, 30, 22);
  getbytes( bytes, 4, src, 1);
  getbits( significand,4, bytes, 22, -1);
  }


/*int main(int argc, char **argv[]) {
  float x;
  char sign[2],exponent[9],significand[24];
  x = -127.1;
  //x = 0.15625;
  spff(sign,exponent,significand,&x);
  printf("%f\n",x );
  printf(" %s  %s  %s  \n", sign,exponent,significand);
  printf("%sx(-1) x 2**%lld x %f\n",sign,bits2ull(exponent)-127,1.0+(float)(bits2ull(significand))/(1<<23));
  return 0;
}*/

void dpff( char *sign, char *exponent, char *significand, double *src ){
  int i= 1,j =0;
  unsigned char bytes[8];
  if (*src > 0) {
    sign[j] = '0';
  }else{
    sign[j] = '1';
  }

  sign[i] = '\0';
  getbytes( bytes, 8, src, 1);
  getbits( exponent,8, bytes, 62, 51);
  getbytes( bytes, 8, src, 1);
  getbits( significand,8, bytes, 51, -1);
}
int main( int argc, char **argv )
{
  double x;
  char sign[2], exponent[12], significand[53];

  x = -127.1;
  //x = 0.15625;

  dpff( sign, exponent, significand, &x );

  printf( "%lf\n", x );
  printf( "%s %s %s\n", sign, exponent, significand );
  printf( "%sx(-1) x 2**%lld x %lf\n", sign, bits2ull( exponent)-1023,
       1.0+(double)(bits2ull(significand))/(1ULL<<52) );
  return 0;
}
