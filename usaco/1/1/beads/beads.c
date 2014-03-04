/*
ID: use.c.only
LANG: C
TASK: beads
*/
#include<stdio.h>
#include<stdlib.h>
FILE * fin, * fout;

int N;
char color[351], used[350];

int number_of_beads_from_breaking_at(int pos) {
  /* try to calculate how many beads we may take by breaking between
   * position pos and pos+1
   */
  int count = 0, cur = pos;
  char col = 'w';

  memset(used, 0, sizeof(used));

  /* first try going in the decreasing direction starting from pos */
  while (!used[cur] && 
	 (col == 'w' || color[cur] == 'w' || color[cur] == col)) {
    count++;
    used[cur] = 1;
    if (color[cur] != 'w') col = color[cur];
    if (cur == 0) cur = N-1;
    else          cur--;
  }

  /* Now try going in increasing direction */
  cur = (pos+1)%N;
  col = 'w';
  while (!used[cur] &&
	 (col == 'w' || color[cur] == 'w' || color[cur] == col)) {
    count++;
    used[cur] = 1;
    if (color[cur] != 'w') col = color[cur];
    if (cur == N-1) cur = 0;
    else            cur++;
  }

  return count;
}

int main() {
  int best = 0, i;
  fin  = fopen("beads.in" ,"r");
  fout = fopen("beads.out","w");
  
  fscanf(fin, "%d", &N);
  fscanf(fin, "%s", color);

  for (i = 0; i < N; i++) {
    int candidate = number_of_beads_from_breaking_at(i);
    if (candidate > best) best = candidate;
  }

  fprintf(fout, "%d\n", best);

  fclose(fin);
  fclose(fout);

  return 0;
}
