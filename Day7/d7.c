#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long concat(long x, long y){
    return x * (long) pow(10, (long) (log10(y)) + 1) + y;
}

long* next_list(long* inp, int len, int next, long total, int problem){
    // inp - current numbers, len - len of inp, next - next number, total - total val to check for
    // problem = 0 for p1, 1 for p2
    // if [-1] is returned, it's a success
    long* out = calloc(len * 2, sizeof(int));

    int index = 0;
    for(int i = 0; i < len; i++){
        out[index] = inp[i] * next;
        out[index + 1] = inp[i] + next;
        if(problem){
            out[index + 2] = concat(inp[i], next);
        }
        index += (2 + problem);
    }

//    printf("next is %d, total is %lu, input values are: ", next, total);
//    for(int i = 0; i < len; i++){
//        printf("%lu ", inp[i]);
//    }
//    printf("; output values are: ");
//    for(int i = 0; i < len * 2; i++){
//        printf("%lu ", out[i]);
//    }
//    printf("\n");

    return out;
}
int main(){
    char line[256] = {'\0'};
    FILE* file = fopen("input.txt", "r");

    int curr_line = 0;
    long total_p1 = 0, total_p2 = 0;
    while (fgets(line, sizeof(line), file)){
        char line_cpy[256];
        memcpy(line_cpy, line, sizeof(line)); // make copy to use strtok with

        char* nums_raw = strtok(line_cpy, " ");
        int count = -1; // first number is the total, so we start_p1 at -1

        while(nums_raw != NULL){
            count++;
            nums_raw = strtok(NULL, " ");
        }
        int* nums = calloc(count, sizeof(int));
        char* nums_raw_2 = strtok(line, " ");
        int idx = 0; // will have # of inputs

        count = 0; // resetting to see first value
        long total = 0; // will store first value in each line
        // create array with values
        while(nums_raw_2 != NULL){
            if(count == 0){
                total = (long) strtol(nums_raw_2, NULL, 10);
                // need strtol to grab a long, not atoi which only does ints
            }
            else{
                nums[idx] = atoi(nums_raw_2);
                idx++;
            }

            count++;
            nums_raw_2 = strtok(NULL, " ");
        }

        // printf("total: %lu\n", total);
        long *start_p1 = calloc((long) pow(2, 13), sizeof(long));
        long *start_p2 = calloc((long) pow(2, 13), sizeof(long));

        start_p1[0] = nums[0];
        start_p2[0] = nums[0];
        int len = 1, current_idx = 0;
        for(int i = 0; i < idx - 1; i++){
            long* next_p1 = calloc(len * 2, sizeof(long));
            long* next_p2 = calloc(len * 2, sizeof(long));

            next_p1 = next_list(start_p1, len, nums[current_idx + 1], total, 0);
            next_p2 = next_list(start_p2, len, nums[current_idx + 1], total, 1);

            memcpy(start_p1, next_p1, len * 2 * sizeof(long));
            memcpy(start_p2, next_p2, len * 2 * sizeof(long));

            len *= 2;
            current_idx++;
        }

        // HAVE TO USE ALL THE VALUES, cannot break midway
        for(int i = 0; i < len; i++){
            if(start_p1[i] == total){
                total_p1 += total;
                break;
            }
        }

        for(int i = 0; i < len; i++){
            if(start_p2[i] == total){
                total_p2 += total;
                break;
            }
        }
    }
    printf("p1: %lu\n", total_p1);
    printf("p2: %lu", total_p2);
}