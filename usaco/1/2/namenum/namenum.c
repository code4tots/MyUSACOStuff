/*
ID: use.c.only
LANG: C
TASK: namenum
*/
#include<stdio.h>
FILE * fin, * fout, * din;
char names[5000][80], number[80];
size_t number_of_names, length_of_number, answer_count;

int match_char(char digit, char letter) {
  switch(letter) {
  case 'A':case 'B':case 'C':
    return digit == '2';
  case 'D':case 'E':case 'F':
    return digit == '3';
  case 'G':case 'H':case 'I':
    return digit == '4';
  case 'J':case 'K':case 'L':
    return digit == '5';
  case 'M':case 'N':case 'O':
    return digit == '6';
  case 'P':case 'R':case 'S':
    return digit == '7';
  case 'T':case 'U':case 'V':
    return digit == '8';
  case 'W':case 'X':case 'Y':
    return digit == '9';
  default:
    return 0;
  }
}

int match_string(char * number, char * name) {
  for (;*number != '\0'; number++,name++)
    if (!match_char(*number,*name)) return 0;
  return 1;
}

int main() {
  int i, j;
  fin  = fopen("namenum.in" ,"r");
  din  = fopen("dict.txt"   ,"r");
  fout = fopen("namenum.out","w");

  /* load names from dictionary
   * We are guaranteed, list of names is already sorted */
  while (!feof(din))
    fscanf(din,"%s",names[number_of_names++]);
  number_of_names--;

  /* load number from input */
  fscanf(fin, "%s", number);
  length_of_number = strlen(number);

  /* iterate over each name in dictionary and see if it matches
   * number */
  for (i = 0; i < number_of_names; i++) {
    if (length_of_number != strlen(names[i]))
      continue;
    if (match_string(number,names[i])) {
      answer_count++;
      fprintf(fout,"%s\n",names[i]);
    }
  }

  if (answer_count == 0)
    fprintf(fout,"NONE\n");

  fclose(fin);
  fclose(din);
  fclose(fout);
  return 0;
}
