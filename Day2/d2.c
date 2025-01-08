#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int safe(int l[], int size){
    int inc = -1;
    if(l[0] > l[1]){
        inc = 0;
    }
    else{
        inc = 1;
    }

    for(int i = 0; i < size - 1; i++){
        int diff = l[i + 1] - l[i];
        if(abs(diff) > 3 || abs(diff) < 1){
            return 0;
        }

        if((diff > 0 && inc == 0) || (diff < 0 && inc == 1)){
            return 0;
        }
    }
    return 1;
}

int main(){
    FILE* file = fopen("input.txt", "r");
    char line[256];

    int total_p1 = 0;
    int total_p2 = 0;

    while (fgets(line, sizeof(line), file)){
        char line2[256];
        memcpy(line2, line, 256 * sizeof(char)); // need a copy since strtok modifies input

        // first pass to count how many numbers there are in the line
        char* token = strtok(line2, " ");
        int num_count = 0;
        while(token != NULL){
            num_count++;
            token = strtok(NULL, " ");
        }

        // second pass to actually do logic
        char* token_2 = strtok(line, " ");
        int *nums = calloc(num_count, sizeof(int));
        int curr_index = 0;
        while(token_2 != NULL){
            nums[curr_index] = atoi(token_2);
            curr_index++;
            token_2 = strtok(NULL, " ");
        }

        // p1
        total_p1 += safe(nums, curr_index);

        // p2
        int added = 0;
        for(int i = 0; i < curr_index; i++){
            int *new_nums = calloc(num_count - 1, sizeof(int));
            int curr_index_new = 0;
            int curr_index_old = 0;
            // construct new list that is old list without ignored value
            // c does not allow removing from list...
            for(int j = 0; j < num_count; j++){
                if(j != i){
                    new_nums[curr_index_new] = nums[curr_index_old];
                    curr_index_new++;
                }
                curr_index_old++;
            }

            //try new list, if it works then break loop
            int s = safe(new_nums, num_count - 1);
            total_p2 += s;
            added += s;
            if(s){
                break;
            }
        }

    }
    printf("%d\n", total_p1);
    printf("%d", total_p2);
}