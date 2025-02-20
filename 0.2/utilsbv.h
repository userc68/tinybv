#ifndef UTILSBV_H
#define UTILSBV_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int hex_len = 12;

void printhex(unsigned char byte) {
  printf("%02X ", byte);
}

char bytetochar(unsigned char byte) {
  if (byte == 0) return '.';
  if (byte == '\n' || byte == '\r') return ' ';
  return isprint(byte) ? byte : ' ';
}


void errormsg(char *prog, char *msg) {
  char *base = strrchr(prog, '/');
  if (base != NULL) {
    base++;
  } 
  else {
    base = prog;
  }
  printf("\033[97m%s:\033[31m error: \033[0m%s\n", base, msg);
}

long int findSize(char filename[]) {
  FILE* fp = fopen(filename, "r"); 
  if (fp == NULL) { 
    printf("File Not Found!\n"); 
    return -1; 
  } 
  fseek(fp, 0L, SEEK_END); 
  long int res = ftell(fp); 

  fclose(fp); 
  
  return res; 
} 

char *formatlnum(int line_number, int total_lines) {
  int total_digits = snprintf(NULL, 0, "%d", total_lines);
  int buffer_size = snprintf(NULL, 0, "%0*d", total_digits, line_number) + 1;
  char *output = malloc(buffer_size);
  if (output) {
      snprintf(output, buffer_size, "%0*d", total_digits, line_number);
  }
  return output;
}

#endif // UTILSBV_H
