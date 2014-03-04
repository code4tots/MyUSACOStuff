/*
  ID: use.c.only
  LANG: C
  TASK: crypt1
*/
#include<stdio.h>
FILE * fin, * fout;
int permitted_digits[10],
  number_of_permitted_digits,
  multiplicand, /* 3 digits */
  multiplier, /* 2 digits */
  largest_permitted_digit,
  smallest_permitted_digit,
  answer;

int is_permitted_digit(int digit) {
  int i;
  for (i = 0; i < number_of_permitted_digits; i++)
    if (digit == permitted_digits[i])
      return 1;
  return 0;
}

int is_permitted_number(int n, int number_of_digits) {
  while (number_of_digits) {
    if (!is_permitted_digit(n%10))
      return 0;
    n /= 10;
    number_of_digits--;
  }
  return n == 0;
}

int next_digit(int digit) {
  int i, next = 10;
  for (i = 0; i < number_of_permitted_digits; i++)
    if (digit < permitted_digits[i] && permitted_digits[i] < next)
      next = permitted_digits[i];
  return next;
}

int next(int n) {
  if (n == 0)
    return smallest_permitted_digit;
  if (n%10 == largest_permitted_digit)
    return next(n/10)*10 + smallest_permitted_digit;
  return (n/10)*10 + next_digit(n%10);
}

int smallest_permitted_number(int c) {
  /* generates smallest permitted number with exactly c digits */
  return (c==0)?0:smallest_permitted_number(c-1)*10 + smallest_permitted_digit;
}

int main() {
  int i, j;
  fin  = fopen("crypt1.in" ,"r");
  fout = fopen("crypt1.out","w");

  fscanf(fin,"%d",&number_of_permitted_digits);
  for (i = 0; i < number_of_permitted_digits; i++)
    fscanf(fin,"%d",&permitted_digits[i]);

  smallest_permitted_digit = permitted_digits[0];
  for (i = 0; i < number_of_permitted_digits; i++)
    if (permitted_digits[i] < smallest_permitted_digit)
      smallest_permitted_digit = permitted_digits[i];

  largest_permitted_digit = permitted_digits[0];
  for (i = 0; i < number_of_permitted_digits; i++)
    if (permitted_digits[i] > largest_permitted_digit)
      largest_permitted_digit = permitted_digits[i];

  for (i = smallest_permitted_number(3); i < 1000; i=next(i)) {
    for (j = smallest_permitted_number(2); j < 100; j=next(j)) {
      if (is_permitted_number(i*(j/10), 3) &&
	  is_permitted_number(i*(j%10), 3) &&
	  is_permitted_number(i * j, 4))
	answer++;
    }
  }
  
  fprintf(fout,"%d\n",answer);
  
  fclose(fin);
  fclose(fout);
  return 0;
}
