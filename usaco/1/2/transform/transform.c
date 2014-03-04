/*
  ID: use.c.only
  LANG: C
  TASK: transform
*/
#include<stdio.h>
#define MAX_N 10
FILE * fin, * fout;
int N;
char before[MAX_N][MAX_N+1],
  after[MAX_N][MAX_N+1];

void copy_pattern(char src[MAX_N][MAX_N+1], char dst[MAX_N][MAX_N+1]) {
  int i, j;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      dst[i][j] = src[i][j];
}

void rotate(char x[MAX_N][MAX_N+1]) {
  int i, j;
  char tmp[MAX_N][MAX_N+1];

  copy_pattern(x,tmp);

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      x[j][N-1-i] = tmp[i][j];
}

void reflect(char x[MAX_N][MAX_N+1]) {
  int i, j;
  char tmp;

  for (i = 0; i < N; i++)
    for (j = 0; j < N/2; j++) {
      tmp = x[i][j];
      x[i][j] = x[i][N-1-j];
      x[i][N-1-j] = tmp;
    }
}

int patterns_match(char x[MAX_N][MAX_N+1], char y[MAX_N][MAX_N+1]) {
  int i, j;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      if (x[i][j] != y[i][j])
	return 0;
  return 1;
}

void print_pattern(char x[MAX_N][MAX_N+1]) {
  int i;
  for (i = 0; i < N; i++)
    fprintf(fout,"%s\n", x[i]);
  fprintf(fout,"\n");
}

int solve() {
  int i;

  for (i = 1; i <= 3; i++) {
    rotate(before);
    if (patterns_match(before,after))
      return i;
  }
  rotate(before);

  reflect(before);
  if (patterns_match(before,after))
      return 4;

  for (i = 0; i < 3; i++) {
    rotate(before);
    if (patterns_match(before,after))
      return 5;
  }
  rotate(before);

  if (patterns_match(before,after))
    return 6;

  return 7;
}

int main() {
  int i;
  fin  = fopen("transform.in" ,"r");
  fout = fopen("transform.out","w");

  fscanf(fin, "%d", &N);

  for (i = 0; i < N; i++)
    fscanf(fin, "%s", before[i]);
  for (i = 0; i < N; i++)
    fscanf(fin, "%s", after[i]);

  fprintf(fout,"%d\n", solve());

  fclose(fin);
  fclose(fout);
  return 0;
}
