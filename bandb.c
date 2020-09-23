#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bandb.h"

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
}
void getbits( char dest[], int bytes, void *src, int start, int end){
  unsigned char * string = src;
  int m,k,n,space;
  char string1 = '1', string2 = '0';
  k = start,m = 0,n =0,space = k-end;
  int remainder = 0, quotient = 0,index = 0;
  for (n = start ; n > end ; n--){
    /*to run the  loop in the range  where range = start- end as start is bigger than range*/
    remainder = (n%8); quotient = (n/8); index  = (bytes-quotient-1);
    int var = ((string[index]>>remainder) & 1);
    switch(var){
      case 1:
      dest[m] = string1;
  break;
      default:
    dest[m]= string2;
    }
    start --; m++;
    /*decrement all the variables that go from a bigger value to small*/
  }
  dest[space]= '\0';
  /*this is to make sure the last thing being stored is a null terminator to signify where to stop*/
}
unsigned long long bits2ull( char *bits ){
  /*initialization for all the variables being used*/
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
long long bits2ll( char *bits ){
  unsigned long long length  = strlen(bits);
  unsigned long long store = 0;
  unsigned long long last_digit = 0;
  int power = 2 ;
  int firstone = 1;
  int counter = 0;
  int i,j;
  i = 0;
  j = 0;
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
  last_digit = (unsigned long long )1ULL << (length-1);
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
}
void spff( char *sign, char *exponent, char *significand, float*src ){
  int i= 0,j =1;
  unsigned char bytes[4];
  if (*src > 0) {
    sign[i] = '0';
    /*if the first is positive, sign is equal to zero*/
  }else{
    sign[i] = '1';
    /*if the first is negative, sign is equal to one*/
  }
  sign[j] = '\0';
  /* the last value needs to be stored as a null terminator*/
  getbytes( bytes, 4, src, 1);
  getbits( exponent,4, bytes, 30, 22);
  getbytes( bytes, 4, src, 1);
  getbits( significand,4, bytes, 22, -1);
  }

void dpff( char *sign, char *exponent, char *significand, double *src ){
  int i= 1,j =0;
  unsigned char bytes[8];
  if (*src > 0) {
    sign[j] = '0';
    /*if the first is positive, sign is equal to zero*/
  }else{
    sign[j] = '1';
     /*if the first is negative, sign is equal to one*/
  }
  sign[i] = '\0';
  /* the last value needs to be stored as a null terminator*/
  getbytes( bytes, 8, src, 1);
  getbits( exponent,8, bytes, 62, 51);
  getbytes( bytes, 8, src, 1);
  getbits( significand,8, bytes, 51, -1);
}
