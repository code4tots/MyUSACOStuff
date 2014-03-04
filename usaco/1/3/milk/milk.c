/*
ID: use.c.only
LANG: C
TASK: milk
*/
#include<stdio.h>
#define MAX_NUMBER_OF_FARMERS 5000
FILE * fin, * fout;
int M, N; /* M is number of farmers */
typedef struct Farmer Farmer;
struct Farmer {
  int P, A;
};
Farmer farmers[MAX_NUMBER_OF_FARMERS];

void sort_farmers_by_price() {
  /* heapsort */
  int heap_size = M, i;

  for (i = (M-2)/2; i >= 0; i--) {
    /* sift-down */
    int j = i;
    while (2 * j + 1 < heap_size) {
      int left = 2 * j + 1, right = 2 * j + 2, largest = j;

      if (farmers[left].P > farmers[largest].P)
	largest = left;

      if (right < heap_size && farmers[right].P > farmers[largest].P)
	largest = right;

      if (largest == j)
	break;

      {
	Farmer tmp = farmers[largest];
	farmers[largest] = farmers[j];
	farmers[j] = tmp;
      }

      j = largest;
    }
  }
  
  while (heap_size > 1) {
    /* position largest item to correct position */
    {
      Farmer tmp = farmers[0];
      farmers[0] = farmers[heap_size-1];
      farmers[heap_size-1] = tmp;
    }

    heap_size--;

    /* sift-down */
    i = 0;
    while (2 * i + 1 < heap_size) {
      int left = 2 * i + 1, right = 2 * i + 2, largest = i;

      if (farmers[left].P > farmers[largest].P)
	largest = left;

      if (right < heap_size && farmers[right].P > farmers[largest].P)
	largest = right;

      if (largest == i)
	break;

      {
	Farmer tmp = farmers[largest];
	farmers[largest] = farmers[i];
	farmers[i] = tmp;
      }

      i = largest;
    }
  }
}

int main() {
  int i, total_cost = 0;
  fin  = fopen("milk.in" ,"r");
  fout = fopen("milk.out","w");

  fscanf(fin, "%d%d", &N, &M);

  for (i = 0; i < M; i++)
    fscanf(fin, "%d%d", &farmers[i].P, &farmers[i].A);

  sort_farmers_by_price();

  for (i = 0; N > 0; i++) {
    int buy_amount = (N < farmers[i].A) ? N : farmers[i].A;
    total_cost += buy_amount * farmers[i].P;
    N -= buy_amount;
  }

  fprintf(fout,"%d\n",total_cost);

  fclose(fin);
  fclose(fout);
  return 0;
}
