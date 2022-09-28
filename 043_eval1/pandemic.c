#include "pandemic.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define base 100000
void callError(char * info) {
  perror(info);
  exit(EXIT_FAILURE);
}

country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  ans.population = 0;
  // split the string //
  char * ptr = strchr(line, ',');
  if (ptr == NULL) {
    callError("Invalid input: no comma");
  }
  char * sentinel = line;
  while (sentinel != ptr) {
    if (!isalpha(*sentinel) && *sentinel != ' ') {
      callError("Invalid input: invalid alphabet");
    }
    sentinel++;
  }
  size_t namelen = (size_t)(ptr - line);
  if (namelen > MAX_NAME_LEN - 1) {
    callError("Invalid input : length");
  }
  // get name //
  memcpy(ans.name, line, namelen);
  ans.name[namelen] = '\0';
  ptr++;

  if (!isdigit(*ptr)) {
    callError("Invalid input : no population");
  }
  // get population //
  while (isdigit(*ptr)) {
    ans.population = ans.population * 10 + (unsigned)(*ptr - '0');
    ptr++;
  }
  if (*ptr != '\n') {
    callError("Invalid input : invalid digit");
  }

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  size_t sz = 1;
  double sum = 0;
  // initialize //
  for (int i = 0; i < 7; i++) {
    sum += data[i];
  }
  avg[0] = sum / 7;
  // iterate //
  while (sz < n_days - 6) {
    sum -= data[sz - 1];
    sum += data[sz + 6];
    avg[sz] = sum / 7;
    sz++;
  }
  return;
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  double casesNow = 0;
  for (size_t i = 0; i < n_days; i++) {
    casesNow += data[i];
    cum[i] = casesNow * base / pop;
  }
  return;
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  char * country_name;
  unsigned number_cases;
  unsigned * maxNum = malloc(n_countries * sizeof(*maxNum));
  if (maxNum == NULL) {
    callError("Error call 'malloc'. ");
  }
  // get maxNum for each countries //
  for (size_t i = 0; i < n_countries; i++) {
    unsigned temp_maxNum = 0;
    for (size_t j = 0; j < n_days; j++) {
      if (data[i][j] > temp_maxNum) {
        temp_maxNum = data[i][j];
      }
    }
    maxNum[i] = temp_maxNum;
  }
  // compare maxNum of each countries //
  unsigned temp = 0;
  for (size_t i = 0; i < n_countries; i++) {
    if (maxNum[i] > temp) {
      number_cases = maxNum[i];
      country_name = countries[i].name;
      temp = maxNum[i];
    }
  }

  // output //
  printf("%s has the most daily cases with %u\n", country_name, number_cases);
  return;
}
