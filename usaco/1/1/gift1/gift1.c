/*
ID: use.c.only
LANG: C
TASK: gift1
*/
#include<stdio.h>
#include<string.h>
FILE * fin, * fout;
int NP, balance[10];
char name[10][15];

int lookup(char * n) {
  int i;
  for (i = 0; i < NP; i++)
    if (strcmp(name[i],n) == 0) break;
  return i;
}

int main() {
  int i;

  fin  = fopen("gift1.in" ,"r");
  fout = fopen("gift1.out","w");

  fscanf(fin, "%d", &NP);

  for (i = 0; i < NP; i++)
    fscanf(fin, "%s", name[i]);

  for (i = 0; i < NP; i++) {
    int j, k, initial, people;
    char n[15];

    fscanf(fin, "%s%d%d", n, &initial, &people);
    j = lookup(n);

    if (people > 0) {
      balance[j] -= (initial/people) * people;

      for (k = 0; k < people; k++) {
	fscanf(fin, "%s", n);
	balance[lookup(n)] += (initial/people);
      }
    }
  }

  for (i = 0; i < NP; i++)
    fprintf(fout,"%s %d\n", name[i], balance[i]);

  return 0;
}
