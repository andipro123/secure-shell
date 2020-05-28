#include <stdio.h>

void red () {
  printf("\033[1;31m");
}

void yellow() {
  printf("\033[1;33m");
}

void cyan() {
  printf("\033[1;36m");
}

void blue() {
  printf("\033[1;34m");
}

void green() {
  printf("\033[1;32m");
}

void magenta() {
  printf("\033[1;35m");
}

void reset () {
  printf("\033[0m");
}
