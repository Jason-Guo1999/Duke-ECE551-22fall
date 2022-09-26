#include <stdio.h>
#include <stdlib.h>

#define row 10
#define col 10

void rotate(char matrix[row][col]) {
  for (int i = 0; i < row; i++) {
    for (int j = col - 1; j >= 0; j--) {
      printf("%c", matrix[j][i]);
    }
    printf("\n");
  }
  return;
}

void readLine(char line[], FILE * f) {
  int numOfchar = 0;
  int ch;
  while (1) {
    ch = fgetc(f);
    if (ch == '\n') {
      if (numOfchar != col) {
        fprintf(stderr, "Invalid input");
        exit(EXIT_FAILURE);
      }
      else {
        line[numOfchar] = '\0';
        return;
      }
    }
    else if (ch == EOF) {
      fprintf(stderr, "Invalid input");
      exit(EXIT_FAILURE);
    }
    else if (ch < 0 || ch > 255) {
      fprintf(stderr, "Invalid input");
      exit(EXIT_FAILURE);
    }
    else {
      if (numOfchar >= col) {
        fprintf(stderr, "INvalid input");
        exit(EXIT_FAILURE);
      }
      else {
        line[numOfchar] = ch;
        numOfchar++;
      }
    }
  }
  return;
}
void readfile(char target[row][col], FILE * f) {
  for (int i = 0; i < row; i++) {
    readLine(target[i], f);
  }
  return;
}
int main(int argc, char * argv[]) {
  char matrix[row][col];
  FILE * f;
  int ch;
  if (argc != 2) {
    fprintf(stderr, "Error command!\n");
    exit(EXIT_FAILURE);
  }
  if ((f = fopen(argv[1], "r")) == 0) {
    fprintf(stderr, "can't open file");
    exit(EXIT_FAILURE);
  }
  // read //
  readfile(matrix, f);

  // test redundant input row//
  if ((ch = fgetc(f)) != EOF) {
    fprintf(stderr, "Invalid input");
    exit(EXIT_FAILURE);
  }
  int j;
  j = fclose(f);
  if (j != 0) {
    perror("can't close");
    exit(EXIT_FAILURE);
  }
  rotate(matrix);

  return EXIT_SUCCESS;
}
