/*
  ID: use.c.only
  LANG: C
  TASK: milk2
*/

#include <stdio.h>
#define MAX_N 5000
#define MAX(a,b) ((a)>(b)?(a):(b))
FILE * fin, * fout;
struct Interval {
  int begin, end;
};
int N, heap_size;
struct Interval interval[MAX_N];

void swap_intervals(int a, int b) {
  int tmp;

  tmp = interval[a].begin;
  interval[a].begin = interval[b].begin;
  interval[b].begin = tmp;

  tmp = interval[a].end;
  interval[a].end = interval[b].end;
  interval[b].end = tmp;
}

void sift_down(int x) {
  int left, right, largest;
  while (2 * x + 1 < heap_size) {
    left = 2 * x + 1;
    right = 2 * x + 2;
    largest = x;
    
    if (interval[left].begin > interval[x].begin)
      largest = left;

    if (right < heap_size && interval[right].begin > interval[largest].begin)
      largest = right;

    if (largest == x) break;

    swap_intervals(largest,x);
    x = largest;
  }
}

void sort_intervals_by_starting_time() {
  int i;

  heap_size = N;

  for (i = (N-2)/2; i >= 0; i--)
    sift_down(i);
  
  while (heap_size > 1) {
    swap_intervals(0,--heap_size);
    sift_down(0);
  }

}

int main() {
  int i, longest_milked, longest_idle;
  struct Interval current_milking_interval;
  fin  = fopen("milk2.in" ,"r"),
    fout = fopen("milk2.out","w");
  
  fscanf(fin, "%d",&N);
  for (i = 0; i < N; i++)
    fscanf(fin, "%d%d",&interval[i].begin,&interval[i].end);

  sort_intervals_by_starting_time();

  longest_milked = 0;
  longest_idle = 0;
  current_milking_interval.begin =
    current_milking_interval.end = 0;
  for (i = 0; i < N; i++) {
    if (interval[i].begin <= current_milking_interval.end)
      current_milking_interval.end = MAX(interval[i].end,
					 current_milking_interval.end);
    else {
      if (i > 0)
	longest_idle = MAX(longest_idle,
			   interval[i].begin - current_milking_interval.end);
      current_milking_interval.begin = interval[i].begin;
      current_milking_interval.end   = interval[i].end;
    }

    longest_milked = MAX(longest_milked,
			 current_milking_interval.end-
			 current_milking_interval.begin);
  }

  fprintf(fout,"%d %d\n",longest_milked, longest_idle);

  fclose(fin);
  fclose(fout);
}
