#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int contains(int array[], int size, int element){
    // intended to be used with int array
    for(int i = 0; i < size; i++){
        if(array[i] == element){
            return 1;
        }
    }
    return 0;
}

void swap(int array[], int idx1, int idx2){
    int tmp = array[idx1];
    array[idx1] = array[idx2];
    array[idx2] = tmp;
}

int main(){
    char line[256];
    FILE* file = fopen("input.txt", "r");
    int hash[100][100] = {0}, hash_indices[100] = {0}, total_p1 = 0, total_p2 = 0;
    // int hash_indices[100] = {0};

    while (fgets(line, sizeof(line), file)){
        char* sep = strchr(line, '|');
        char* comma = strchr(line, ',');

        if(sep != NULL){
            int val1 = atoi(line);
            int val2 = atoi(line + 3);

            hash[val1][hash_indices[val1]] = val2;
            hash_indices[val1]++;
        }
        else if(comma != NULL){
            char line_cpy[256];
            memcpy(line_cpy, line, sizeof(line));
            char* nums_raw = strtok(line_cpy, ",");
            int valid_p1 = 1, count = 0; // count is # of numbers in current line

            // see how many numbers in current line; doing a 2nd pass later to grab values
            while(nums_raw != NULL){
                count++;
                nums_raw = strtok(NULL, ",");
            }

            int* nums = calloc(count, sizeof(int));
            char* nums_raw_2 = strtok(line, ",");
            int idx = 0;

            // create array with values
            while(nums_raw_2 != NULL){
                nums[idx] = atoi(nums_raw_2);
                idx++;
                nums_raw_2 = strtok(NULL, ",");
            }

            // p1
            for(int i = 0; i < (idx - 1); i++){
                if(!contains(hash[nums[i]], 100, nums[i + 1])){
                    valid_p1 = 0;
                    break;
                }
            }

            if(valid_p1){
                // printf("%d\n", nums[(idx) / 2]); // halfway point
                total_p1 += nums[idx / 2];
            }

            // p2
            if(!valid_p1) {
                while (1) { // inf loop until no more changes are needed
                    int changed = 0;
                    for (int i = 0; i < (idx - 1); i++) {
                        if (!contains(hash[nums[i]], 100, nums[i + 1])) {
                            swap(nums, i, i + 1);
                            changed = 1;
                        }
                    }
                    if(!changed){
                        break; // break if no changes
                    }
                }
                total_p2 += nums[idx / 2];
            }
        }
        else{ // triggers on the blank line in input, just skips it
            continue;
        }
    }
    printf("p1: %d\n", total_p1);
    printf("p2: %d\n", total_p2);
}