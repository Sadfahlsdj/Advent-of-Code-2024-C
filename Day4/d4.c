#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
// c stdlib doesn't have min/max functions so i use macros to define them

int find_p1(char* grid, int size, int index){
    // function to check xmas for a single char; size should be the length of 1 dimension
    // assume the char being checked is x
    int has_up = 0, has_down = 0, has_left = 0, has_right = 0;
    int x = index / size, y = index % size;
    int total = 0;

    // check which sides the char being checked is far enough away from
    if(x >= 3){
        has_up = 1;
    }
    if(size - x - 1 >= 3){
        has_down = 1;
    }
    if(y >= 3){
        has_left = 1;
    }
    if(size - y - 1 >= 3){
        has_right = 1;
    }

    // cardinals
    if(has_up){
        // printf("char at %d, %d has up\n", x, y);
        if(grid[size * x + y - size] == 'M' && grid[size * x + y -  2 * size] ==
        'A' && grid[size * x + y - 3 * size] == 'S'){
            total++;
        }
    }
    if(has_down){
        // printf("char at %d, %d has down\n", x, y);
        if(grid[size * x + y + size] == 'M' && grid[size * x + y + 2 * size] ==
                                             'A' && grid[size * x + y + 3 * size] == 'S'){
            total++;
        }
    }
    if(has_left){
        // printf("char at %d, %d has left\n", x, y);
        /*printf("current = %d, %d, left values are %d, %d, %d\n", x, y, size * x + y - 1,
               size * x + y - 2, size * x + y - 3);
        printf("%c %c %c %c\n", grid[size * x + y], grid[size * x + y - 1], grid[size * x + y - 2],
               grid[size * x + y - 3]);*/
        if(grid[size * x + y - 1] == 'M' && grid[size * x + y - 2] ==
                                             'A' && grid[size * x + y - 3] == 'S'){
            total++;
        }
    }
    if(has_right){
        // printf("char at %d, %d has right\n", x, y);
        if(grid[size * x + y + 1] == 'M' && grid[size * x + y + 2] ==
                                          'A' && grid[size * x + y + 3] == 'S'){
            total++;
        }
    }

    //intercardinals
    if(has_up && has_left){
        if(grid[size * x + y - (size + 1)] == 'M' && grid[size * x + y - 2 * (size + 1)] ==
            'A' && grid[size * x + y - 3 * (size + 1)] == 'S'){
            total++;
        }
    }
    if(has_up && has_right){
        if(grid[size * x + y - (size - 1)] == 'M' && grid[size * x + y - 2 * (size - 1)] ==
            'A' && grid[size * x + y - 3 * (size - 1)] == 'S'){
            total++;
        }
    }
    if(has_right && has_down){
        if(grid[size * x + y + (size + 1)] == 'M' && grid[size * x + y + 2 * (size + 1)] ==
            'A' && grid[size * x + y + 3 * (size + 1)] == 'S'){
            total++;
        }
    }
    if(has_down && has_left){
        if(grid[size * x + y - (1 - size)] == 'M' && grid[size * x + y - 2 * (1 - size)] ==
            'A' && grid[size * x + y - 3 * (1 - size)] == 'S'){
            total++;
        }
    }

    return total;
}

int find_p2(char* grid, int size, int index){
    // assume that index being checked is A
    int x = index / size, y = index % size;
    if(x <= 0 || y <= 0 || x >= size || y >= size){ // on an edge of the grid - always false
        return 0;
    }

    int tl_dr = 0, tr_dl = 0; // topleft/downright, topright/downleft diags

    // topleft/downright diag has correct chars
    if((grid[size * x + y - (size + 1)] == 'M' && grid[size * x + y + (size + 1)] == 'S') ||
            (grid[size * x + y - (size + 1)] == 'S' && grid[size * x + y + (size + 1)] == 'M')){
        tl_dr = 1;
    }

    // topright/downleft diag has correct chars
    if((grid[size * x + y - (size - 1)] == 'M' && grid[size * x + y + (size - 1)] == 'S') ||
       (grid[size * x + y - (size - 1)] == 'S' && grid[size * x + y + (size - 1)] == 'M')){
        tr_dl = 1;
    }

    return MIN(tl_dr, tr_dl); // 1 if both are 1, 0 otherwise
}
int main(){
    int input_size = 140; // 6 for example_small, 10 for example, 140 for input
    char* grid = calloc(input_size * input_size, sizeof(char));
    // 1d array that we will jury rig into a 2d array
    FILE* file = fopen("input.txt", "r");

    char line[input_size];
    int total_p1 = 0, total_p2 = 0;

    while (fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = 0; // remove trailing newline
        strcat(grid, line); // add current line to grid
    }

    for(int i = 0; i < input_size * input_size; i++){
        if(grid[i] == 'X'){
            total_p1 += find_p1(grid, input_size, i);
        }
        if(grid[i] == 'A'){
            total_p2 += find_p2(grid, input_size, i);
        }
    }
    printf("%d\n", total_p1);
    printf("%d", total_p2);
}