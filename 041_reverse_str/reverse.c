#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  //WRITE ME!
  //  if (!str) {
  //return;
  //}
  size_t ptr1 = 0;
  size_t ptr2 = strlen(str);
  ptr2 = ptr2 - 1;
  while (ptr1 < ptr2 && ptr2 >= 0 && ptr1 < strlen(str)) {
    char temp = str[ptr1];
    str[ptr1] = str[ptr2];
    str[ptr2] = temp;
    ptr1++;
    ptr2--;
  }
  return;
}

int main(void) {
  char str0[] = "";
  char str1[] = "1";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be "
                "no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
