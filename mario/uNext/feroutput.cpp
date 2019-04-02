#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int
main()
{

    char            ch;
    FILE           *fp;
    long int        nbytes_read = 0;
    char            str       [128];
    int             j = 0;
    int             first_time = 1;
    memset(str, '\0', 128);
    fp = fopen("/home/itisha/Desktop/BTP 4th Sem/real-time_emotion_analyzer-master/emotion.txt", "r");
    while (1) {
            if (first_time != 1) {
                    fp = fopen("/home/itisha/Desktop/BTP 4th Sem/real-time_emotion_analyzer-master/emotion.txt", "r");
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
    return 0;
}

