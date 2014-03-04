/*
ID: use.c.only
LANG: C
TASK: friday
*/
#include<stdio.h>
FILE * fin, * fout;

enum DayOfWeek {
  SATURDAY,
  SUNDAY,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,

  NUMBER_OF_DAYS_OF_WEEK
};

int count[NUMBER_OF_DAYS_OF_WEEK];

enum Month {
  JANUARY,
  FEBRUARY,
  MARCH,
  APRIL,
  MAY,
  JUNE,
  JULY,
  AUGUST,
  SEPTEMBER,
  OCTOBER,
  NOVEMBER,
  DECEMBER
};

int is_leap_year(int year) {
  if (year%100 != 0)
    return year%4 == 0;
  return year%400 == 0;
}

/* number of days in given month */
int number_of_days_in_month(int year, enum Month month) {
  switch(month) {
  case SEPTEMBER:
  case APRIL:
  case JUNE:
  case NOVEMBER:
    return 30;
  case FEBRUARY:
    return is_leap_year(year) ? 29 : 28;
  default:
    return 31;
  }
}

int main() {
  int N;
  enum Month month = JANUARY;
  int year = 1900;
  enum DayOfWeek dow = SATURDAY; /* January 13, 1900 was a Saturday */
  fin  = fopen("friday.in" ,"r");
  fout = fopen("friday.out","w");

  fscanf(fin, "%d", &N);

  while (year < 1900 + N) {
    count[dow]++;
    dow = (dow + number_of_days_in_month(year,month))%NUMBER_OF_DAYS_OF_WEEK;

    if (month == DECEMBER)
      year++, month = JANUARY;
    else
      month++;
  }

  for (dow = SATURDAY; dow < FRIDAY; dow++)
    fprintf(fout,"%d ", count[dow]);
  fprintf(fout,"%d\n",count[FRIDAY]);
  printf("hey!\n");
  fclose(fin);
  fclose(fout);
  return 0;
}
