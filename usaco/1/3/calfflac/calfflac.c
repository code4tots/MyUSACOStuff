/*
ID: use.c.only
LANG: C
TASK: calfflac
*/
#include<stdio.h>
#include<ctype.h>
FILE * fin, * fout;
char text[30000], *pos, *beg, *end, *best_beg, *best_end;
int length, best_length;

char * next(char * p) {
  p++;
  while (*p != '\0' && !isalpha(*p)) p++;
  return p;
}

char * prev(char * p) {
  p--;
  while (p >= text && !isalpha(*p)) p--;
  return p;
}

void new_best() {
  if (best_length < length)
    best_beg = beg, best_end = end, best_length = length;
}

void expand() {
  while (1) {
    beg = prev(beg);
    if (beg < text) break;
    end = next(end);
    if (*end == '\0') break;
    if (toupper(*beg) != toupper(*end)) break;
    length += 2;
    new_best();
  }
}

int main() {
  fin  = fopen("calfflac.in" ,"r");
  fout = fopen("calfflac.out","w");


  pos = text;
  while (fgets(pos, 82, fin))
    while (*pos != '\0') pos++;

  pos = text;
  while (1) {
    while (*pos != '\0' && !isalpha(*pos)) pos++;
    if (*pos == '\0') break;

    /* odd length palindromes */
    beg = end = pos;
    length = 1;
    new_best();

    expand();

    /* even length palindromes */
    beg = pos;
    end = next(pos);
    if (*end != '\0' && toupper(*end) == toupper(*beg)) {
      length = 2;
      new_best();
      expand();
    }

    pos = next(pos);
  }

  fprintf(fout,"%d\n",best_length);
  *++best_end = '\0';
  fprintf(fout,"%s\n",best_beg);

  fclose(fin);
  fclose(fout);
  return 0;
}
