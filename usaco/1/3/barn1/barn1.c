/*
ID: use.c.only
LANG: C
TASK: barn1
*/
#include<stdio.h>
#define MAX_M 50
#define MAX_S 200
#define MAX_C MAX_S
FILE * fin, * fout;
int M, S, C, stall[MAX_S], spaces[MAX_S], SC, buffer[MAX_S], ans;
/* spaces[] contains an array of the length of contiguous unoccupied spaces */
/* SC is the number of contiguous unoccupied spaces */

int main() {
  int i, j, start, end, *sp;
  fin  = fopen("barn1.in" ,"r");
  fout = fopen("barn1.out","w");

  fscanf(fin,"%d%d%d",&M,&S,&C);

  for (i = 0; i < S; i++)
    stall[i] = 0;

  for (i = 0; i < C; i++) {
    int x;
    fscanf(fin,"%d",&x);
    stall[x] = 1;
  }

  for (start = 0; start < S   && !stall[start]; start++);
  for (end   = S; end > start && !stall[end  ]; end  --);
  if (stall[end]) end++;

  ans = end - start;

  while (stall[start]) start++;
  while (start < end) {
    int a = start;
    while (!stall[start]) start++;
    spaces[SC++] = start - a;
    while (stall[start]) start++;
  }

  /* mergesort the spaces in between */
  for (i = 1; i < SC; i *= 2) {
    /* i is segment length */
    for (j = i; j < SC; j += 2*i) {
      /* j is middle of merge thingy */

      /* Now perform merge --
       * merge [j-i,j) with [j,j+i) */
      int k = j-i, a = j-i, b = j, upper = (j+i < SC) ? j+i : SC;

      while (a < j && b < upper)
	buffer[k++] = (spaces[a] > spaces[b]) ? spaces[a++] : spaces[b++];

      while (a < j)
	buffer[k++] = spaces[a++];

      while (b < upper)
	buffer[k++] = spaces[b++];

      for (k = j-i; k < upper; k++)
	spaces[k] = buffer[k];
    }
  }



  for (i = 0; i < SC && M > 1; i++, M--)
    ans -= spaces[i];

  fprintf(fout,"%d\n",ans);

  fclose(fin);
  fclose(fout);
  return 0;
}
