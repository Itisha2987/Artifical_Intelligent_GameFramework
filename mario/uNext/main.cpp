#include "header.h"
#include "Core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <thread>

void threadFunc() {

  char ch;
  FILE * fp;
  long int nbytes_read = 0;
  char str[128];
  int j = 0;
  int first_time = 1;
  memset(str, '\0', 128);
  fp = fopen("../../fer/emotion.txt", "r");
  while (1) {
    if (first_time != 1) {
      fp = fopen("../../fer/emotion.txt", "r");
      fseek(fp, nbytes_read, SEEK_SET);
      sleep(10);

    }
    if (fp != NULL) {
      while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
          str[j++] = ch;
          printf("%s", str);
          CCore::expID = std::stoi(str);
          switch (CCore::expID) {
          case 0:
          case 1:
          case 3:
            CCore::x = CCore::x - 1.5;
            CCore::getMap()->changeMinions();
            break;
          case 2:
          case 4:
            CCore::x = CCore::x + 1.5;
            CCore::getMap()->changeMinions();
            break;
          case 5:
            CCore::x = CCore::x;
            CCore::getMap()->changeMinions();
            break;

          }

          memset(str, '\0', 128);
          j = 0;
        } else {
          str[j++] = ch;
        }
        nbytes_read++;

      }
      //printf("%ld\n", nbytes_read);
      first_time = 0;
    }
    fclose(fp);
  }
}

int main(int argc, char * argv[]) {
   CCore::x=0;
  std::thread t1(threadFunc);
  CCore oCore;

  oCore.mainLoop();

  return 0;
}
