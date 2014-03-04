/*
ID: use.c.only
LANG: C
TASK: palsquare
*/
#include<stdio.h>
FILE * fin, * fout;
int B;
char buffer[100];

char * convert(int n) {
  int i;

  for (i = 0; n > 0; i++, n /= B)
    if (n%B < 10) buffer[i] = '0' + n%B;
    else          buffer[i] = 'A' + n%B - 10;

  buffer[i] = '\0';
  n = i;

  for (i = 0; i < n/2; i++) {
    char tmp = buffer[i];
    buffer[i] = buffer[n-1-i];
    buffer[n-1-i] = tmp;
  }

  return buffer;
}

int is_palindrome(char * s) {
  char * a, * b;

  for (a = b = s; *b != '\0'; b++);
  b--;

  for (; a < b; a++, b--)
    if (*a != *b) return 0;

  return 1;
}

int main() {
  int i;
  fin  = fopen("palsquare.in" ,"r");
  fout = fopen("palsquare.out","w");

  fscanf(fin, "%d", &B);

  for (i = 1; i <= 300; i++)
    if (is_palindrome(convert(i*i))) {
      fprintf(fout, "%s ",convert(i));
      fprintf(fout, "%s\n", convert(i*i));
    }

  fclose(fin);
  fclose(fout);
  return 0;
}
