/*
ID: use.c.only
LANG: C
TASK: ride
*/

#include <stdio.h>

int main() {
  FILE * fin  = fopen("ride.in" ,"r");
  FILE * fout = fopen("ride.out","w");
  char comet[7], group[7], *p;
  int c = 1, g = 1;
  fscanf(fin,"%s", comet);
  fscanf(fin,"%s", group);
  for (p = comet; *p != '\0'; p++) {
    c *= (*p - 'A' + 1);
    c %= 47;
  }
  for (p = group; *p != '\0'; p++) {
    g *= (*p - 'A' + 1);
    g %= 47;
  }
  fprintf(fout,(c == g) ? "GO\n" : "STAY\n");
  return 0;
}
