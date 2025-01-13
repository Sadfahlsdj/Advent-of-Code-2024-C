// if you get an error "malloc: Incorrect checksum for freed object..." just rerun

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

double time_now() { // used for timing
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec + now.tv_nsec * 1e-9;
}

long concat(long x, long y){ // used for p2
    char str1[256], str2[256];
    sprintf(str1, "%lu", x);
    sprintf(str2, "%lu", y);
    char* ret = strcat(str1, str2);
    return(strtol(ret, NULL, 10));
}

long* next_list(long* inp, int len, int next, long total, int problem){
    // inp - current numbers, len - len of inp, next - next number, total - total val to check for
    // problem = 0 for p1, 1 for p2
    long* out = calloc(len * 2, sizeof(int));

    int index = 0;
    for(int i = 0; i < len; i++){
        out[index++] = inp[i] * next;
        out[index++] = inp[i] + next;
        if(problem){
            out[index++] = concat(inp[i], next);
        }
    }
    return out;
}

int main(){
    char line[256] = {'\0'};
    FILE* file = fopen("input.txt", "r");
    double begin = time_now();

    long total_p1 = 0, total_p2 = 0;
    while (fgets(line, sizeof(line), file)){
        char line_cpy[256];
        memcpy(line_cpy, line, sizeof(line)); // make copy to use strtok with

        char* nums_raw = strtok(line_cpy, " ");
        int count = -1; // first number is the total, so we start_p1 at -1

        while(nums_raw != NULL){ // grabbing num count
            count++;
            nums_raw = strtok(NULL, " ");
        }

        int* nums = calloc(count, sizeof(int));
        char* nums_raw_2 = strtok(line, " ");
        int idx = 0; // will have # of inputs

        count = 0; // resetting to check for first value
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
        long *start_p2 = calloc((long) pow(3, 13), sizeof(long));

        start_p1[0] = nums[0];
        start_p2[0] = nums[0];
        int len_p1 = 1, len_p2 = 1, current_idx = 0;
        for(int i = 0; i < idx - 1; i++){
            long* next_p1 = calloc(len_p1 * 2, sizeof(long));
            long* next_p2 = calloc(len_p1 * 2, sizeof(long));

            next_p1 = next_list(start_p1, len_p1, nums[current_idx + 1], total, 0);
            next_p2 = next_list(start_p2, len_p2, nums[current_idx + 1], total, 1);

            memcpy(start_p1, next_p1, len_p1 * 2 * sizeof(long));
            memcpy(start_p2, next_p2, len_p2 * 3 * sizeof(long));

            len_p1 *= 2;
            len_p2 *= 3;
            current_idx++;
        }

        // HAVE TO USE ALL THE VALUES so have to calculate after all values are grabbed
        for(int i = 0; i < len_p1; i++){
            if(start_p1[i] == total){
                total_p1 += total;
                // printf("%lu\n", total);
                break;
            }
        }

        for(int i = 0; i < len_p2; i++){
            if(start_p2[i] == total){
                total_p2 += total;
                break;
            }
        }
    }

    double end = time_now();
    printf("p1: %lu, p2: %lu, time: %lfs", total_p1, total_p2, end - begin);
}