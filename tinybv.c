#include "utilsbv.h"

int main(int argc, char *argv[]) {
  FILE *file;
  const char *filename = argv[1];
  unsigned char byte;
  size_t result;
  char ascii[hex_len + 1];
  int i = 0;

  file = fopen(filename, "rb");
  if (file == NULL) {
    errormsg(argv[0], "file finding");
    return EXIT_FAILURE;
  }

  while ((result = fread(&byte, sizeof(unsigned char), 1, file)) == 1) {
    ascii[i] = bytetochar(byte);
    printhex(byte);
    i++;

    if (i >= hex_len) {
      ascii[i] = '\0';
      printf(" | %s\n", ascii);
      i = 0;
    }
  }

  if (i > 0) {
    ascii[i] = '\0';
    for (int j = i; j < hex_len; j++) {
      printf("   "); 
    }
    printf(" | %s\n", ascii);
  }

  if (ferror(file)) {
    errormsg(argv[0], "error reading file");
    fclose(file);
    return EXIT_FAILURE;
  }

  fclose(file);
  printf("\n");

  return EXIT_SUCCESS;
}