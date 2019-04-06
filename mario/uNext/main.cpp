#include "header.h"
#include "Core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <thread>

void threadFunc(){

char            ch;
    FILE           *fp;
    long int        nbytes_read = 0;
    char            str       [128];
    int             j = 0;
    int             first_time = 1;
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

int main(int argc, char *argv[])
{
        std::thread t1(threadFunc);
	CCore oCore;
	oCore.mainLoop();
        t1.join();

	return 0;
}
