#ifndef UTILSBV_H
#define UTILSBV_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int hex_len = 10;

void printhex(unsigned char byte) {
  printf("%02X ", byte);
}

char bytetochar(unsigned char byte) {
  if (byte == '\n' || byte == '\r') return ' ';
  return isprint(byte) ? byte : '.';
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



#endif // UTILSBV_H
