#include <stdio.h>
#include <stdlib.h>

#define row 10
#define col 10

void getError(const char * msg) {
  fprintf(stderr, "Encounter some error: %s\n", msg);
  exit(EXIT_FAILURE);
}

void rotate(char matrix[row][col]) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      printf("%c", matrix[col - 1 - j][i]);
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
        getError("invalid input of matrix (too short row)");
      }
      else {
        line[numOfchar] = '\0';
        return;
      }
    }
    else if (ch == EOF) {
      if (numOfchar == col) {
        getError("invalid input of matrix (EOF)");
      }
      else {
        getError("invalid input of matrix (too short row)");
      }
    }
    else {
      if (numOfchar >= col) {
        getError("invalid input of matrix (too long row)");
      }
      else {
        line[numOfchar] = (char)ch;
        numOfchar++;
      }
    }
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
    getError("Can't open the file");
  }
  // read line by line //
  for (int i = 0; i < row; i++) {
    readLine(matrix[i], f);
  }

  // test redundant input row//
  if ((ch = fgetc(f)) != EOF) {
    getError("Error format of input matrix\n");
  }

  rotate(matrix);
  fclose(f);

  return (EXIT_SUCCESS);
}
