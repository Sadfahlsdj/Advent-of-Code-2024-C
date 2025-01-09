#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <math.h>

#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

int main(){
    regex_t reg;
    int value = -1;
    regoff_t off, len;
    char *pattern = "mul\\([0-9]+,[0-9]+\\)|do\\(\\)|don't\\(\\)";

    regcomp(&reg, pattern, REG_EXTENDED); // compile regex string

    char line[5000]; // lines are huge on this one
    FILE* file = fopen("input.txt", "r");

    long total_p1 = 0, total_p2 = 0;
    int do_mul = 1; // starts on, turns on/off with do/don't
    while (fgets(line, sizeof(line), file)){
        char *s = line;
        regmatch_t pmatch[100] = {0}; // stores matches

        while(1) {
            if((regexec(&reg, s, ARRAY_SIZE(pmatch), pmatch, 0))){
                // non zero value means theres no more matches
                break;
            }
            off = pmatch[0].rm_so + (s - line); // offset of match (from start of str)
            len = pmatch[0].rm_eo - pmatch[0].rm_so; // length of match

            char substr[30] = {'\0'};
            strncpy(substr, line + off, len); // contains regex match

            if(len == 4){ // do() is 4 chars
                do_mul = 1;
            }
            else if(len == 7){ // don't() is 7 chars
                do_mul = 0;
            }
            else{
                int left = 0, right = 0;
                left = atoi(substr + 4);
                right = atoi(substr + (int) log10(left) + 6);

                total_p1 += left * right;
                if(do_mul) {
                    total_p2 += left * right;
                }
            }
            s += pmatch[0].rm_eo; // moves string along to next match
        }
    }
    regfree(&reg);
    printf("p1 answer: %lu\n", total_p1);
    printf("p2 answer: %lu\n", total_p2);
}