#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;
double calfunc(int startAge, double initial, retire_info info) {
  int year = startAge / 12;
  int month = startAge % 12;
  for (int i = 0; i < info.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", year, month, initial);
    month++;
    if (month == 12) {
      year++;
      month = 0;
    }
    initial += initial * info.rate_of_return + info.contribution;
  }
  return initial;
}
void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  initial = calfunc(startAge, initial, working);
  initial = calfunc(startAge + working.months, initial, retired);
  return;
}

void main() {
  retire_info working;
  retire_info retired;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;
  int startAge = 327;
  double initial = 21345;
  retirement(startAge, initial, working, retired);
  return;
}
