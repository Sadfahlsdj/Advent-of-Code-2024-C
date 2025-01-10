#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Coord {
    int x;
    int y;
} coord;

int main(){
    char line[132] = {'\0'}; // 12 for example, 132 for input
    int grid[130][130] = {0}; // line length - 2; 0=open, 1=obstacle, 2=open & visited
    coord start = {0, 0};
    FILE* file = fopen("input.txt", "r");

    int curr_line = 0;
    while (fgets(line, sizeof(line), file)){
        int temp_index = 0;

        for (char* c = line; *c != '\n' && *c != '\0'; c++ ){
            char ch = *c;
            // printf("c: %s ch: %c\n", c, ch);
            if(ch == '.'){
                grid[curr_line][temp_index] = 0;
            }
            else if(ch == '#'){
                grid[curr_line][temp_index] = 1;
            }
            else if(ch == '^'){
                start.x = curr_line;
                start.y = temp_index;
                grid[curr_line][temp_index] = 0;
            }
            temp_index++;
        }
        curr_line++;
    }

    coord current = {start.x, start.y};
    coord dir = {-1, 0};
    while(current.x >= 0 && current.x < curr_line && current.y >= 0 && current.y < curr_line){
        grid[current.x][current.y] = 2; // stores visited values; identical to 0
        coord next = {current.x + dir.x, current.y + dir.y};

        if(grid[next.x][next.y] == 0 || grid[next.x][next.y] == 2){
            current.x = next.x, current.y = next.y;
        }
        else{ // going to do dir switching in a really shit way out of principle(?)
            if(dir.x == -1 && dir.y == 0){
                dir.x = 0, dir.y = 1;
            }
            else if(dir.x == 0 && dir.y == 1){
                dir.x = 1, dir.y = 0;
            }
            else if(dir.x == 1 && dir.y == 0){
                dir.x = 0, dir.y = -1;
            }
            else{
                dir.x = -1, dir.y = 0;
            }
        }
    }

    int total_p1 = 0;
    for(int i = 0; i < curr_line; i++) {
        for (int j = 0; j < curr_line; j++) {
            if(grid[i][j] == 2){
                total_p1++;
            }
        }
    }
    printf("total p1: %d", total_p1);

//    for(int i = 0; i < curr_line; i++){
//        for(int j = 0; j < 10; j++){
//            printf("%d", grid[i][j]);
//        }
//        printf("\n");
//    }


}