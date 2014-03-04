/*
ID: use.c.only
LANG: C
TASK: dualpal
*/
#include<stdio.h>
FILE * fin, * fout;
int N, S;

int ispal(int n, int b) {
  int x = 1, y = 1;
  while (n/y > 0) y *= b;
  y /= b;
  for (; x < y; x *= b, y /= b)
    if ((n/x)%b != (n/y)%b) return 0;
  return 1;
}

int isdpal(int n) {
  int palc = 0, b;
  for (b = 2; b <= 10; b++)
    if (ispal(n,b)) palc++;
  return palc >= 2;
}

int main() {
  int n;
  fin  = fopen("dualpal.in" ,"r");
  fout = fopen("dualpal.out","w");

  fscanf(fin,"%d%d",&N,&S);

  for (n = S+1; N; n++)
    if (isdpal(n)) N--, fprintf(fout,"%d\n",n);

  fclose(fin);
  fclose(fout);
  return 0;
}
