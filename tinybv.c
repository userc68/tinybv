#include "utilsbv.h"

int main(int argc, char *argv[]) {
  FILE *file;
  char *filename = argv[1];
  unsigned char byte;
  size_t result;
  char ascii[hex_len + 1];
  int i = 0;
  int line_count = 1;

  if (argc > 2) {
    if (strcmp(argv[2], "-0") == 0) {
      confignull = 0;
    } 
    else if (strcmp(argv[2], "-1") == 0) {
      confignull = 1;
    }
    else if (strcmp(argv[2], "-2") == 0) {
      confignull = 2;
    } 
    else {
      errormsg(argv[0], "invalid argument ");
      return EXIT_FAILURE;
    }
  }

  file = fopen(filename, "rb");
  if (file == NULL) {
    errormsg(argv[0], "file finding");
    return EXIT_FAILURE;
  }

  long int file_size = findSize(filename);
  if (file_size == -1) {
    fclose(file);
    return EXIT_FAILURE;
  }

  int total_lines = (file_size + hex_len - 1) / hex_len;

  while ((result = fread(&byte, sizeof(unsigned char), 1, file)) == 1) {
    if (i == 0) {
      char *line_str = formatlnum(line_count, total_lines);
      printf("%s | ", line_str);
      free(line_str);
    }

    ascii[i] = bytetochar(byte, confignull);
    printhex(byte);
    i++;

    if (i >= hex_len) {
      ascii[i] = '\0';
      printf(" | %s\n", ascii);
      i = 0;
      line_count++;
    }
  }

  if (i > 0) {
    ascii[i] = '\0';
    for (int j = i; j < hex_len; j++) {
      printf("   ");
    }
    printf(" | %s\n", ascii);
    line_count++;
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