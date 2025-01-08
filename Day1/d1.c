#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int compare(const void* a, const void* b) {
   return (*(int*)a - *(int*)b);
}

int main(){
	FILE* file = fopen("input.txt", "r");
	char line[256];
	int left[1000] = {0};
	int right[1000] = {0};
	int curr_line = 0;
	int birb[100000] = {0}; //THIS IS THE HASH TABLE FOR COUNTS LOL

	while (fgets(line, sizeof(line), file)){
        left[curr_line] = atoi(line);
        right[curr_line] = atoi(line + (int) log10(atoi(line)) + 4);
        birb[right[curr_line]]++;
        curr_line++;
    }
	qsort(left, curr_line, sizeof(int), compare);
	qsort(right, curr_line, sizeof(int), compare);
	
	int total_p1 = 0;

	for(int i = 0; i < curr_line; i++){
        total_p1 += abs(left[i] - right[i]);
    }
	// printf("%d", total_p1);
	// p2
	
	int total_p2 = 0;
	for(int i = 0; i < curr_line; i++){
	   total_p2 += left[i] * birb[left[i]];
	}

	printf("%d", total_p2);

} 
