// issue is running OOM on the stack due to clang having 8mb of stack memory by default
// caused by the atrocity of a "hashing" system that i used
// let this be a lesson

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Coord {
    int x;
    int y;
} coord;

//int hash(coord pos, coord dir, int size){
//    return ((dir.x + 1) + (dir.y + 1) * 3) * (pos.x + pos.y * size); // this shit so ass 💔
//}

void print_board(int grid[160][160], int curr_line){
    for(int i = 0; i < curr_line; i++){
        for(int j = 0; j < 10; j++){
            printf("%d", grid[i][j]);
        }
        printf("\n");
    }
}

int loop(int grid[160][160], coord start, int curr_line, int obs_x, int obs_y){ // hardcode grid size
    // obs_x & obs_y are diagnostic
    // int visited[70000] = {0};
    int visited[160][160][3][3] = {0};
    coord current = {start.x, start.y};
    coord dir = {-1, 0};

    while(current.x >= 0 && current.x < curr_line && current.y >= 0 && current.y < curr_line) {
//        printf("currently at %d, %d facing %d, %d, val = %d\n", current.x, current.y, dir.x, dir.y,
//               visited[current.x][current.y][dir.x + 1][dir.y + 1]);
        if (visited[current.x][current.y][dir.x + 1][dir.y + 1]) {
            // if visited same (x, y, dirx, diry)
            // printf("obstacle at %d, %d successfully blocked\n", obs_x, obs_y);
            return 1;
        }
        visited[current.x][current.y][dir.x + 1][dir.y + 1] = 1;

        grid[current.x][current.y] = 2; // stores visited values; identical to 0
        coord next = {current.x + dir.x, current.y + dir.y};

        if (grid[next.x][next.y] == 0 || grid[next.x][next.y] == 2) {
            current.x = next.x, current.y = next.y;
        } else { // going to do dir switching in a really shit way out of principle(?)
            if (dir.x == -1 && dir.y == 0) {
                dir.x = 0, dir.y = 1;
            } else if (dir.x == 0 && dir.y == 1) {
                dir.x = 1, dir.y = 0;
            } else if (dir.x == 1 && dir.y == 0) {
                dir.x = 0, dir.y = -1;
            } else {
                dir.x = -1, dir.y = 0;
            }
        }
    }
    return 0;
}

int main(){
    char line[160] = {'\0'}; // 12 for example, 160 for input
    int grid[160][160] = {0}; // line length - 2; 0=open, 1=obstacle, 2=open & visited
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

    coord current = {start.x, start.y}, dir = {-1, 0};
    coord current_2 = {start.x, start.y}, dir_2 = {-1, 0};

    // p1
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

    int total_p1 = 0, total_p2 = 0;
    for(int i = 0; i < curr_line; i++) {
        for (int j = 0; j < curr_line; j++) {
            if(grid[i][j] == 2){
                total_p1++;
            }
        }
    }
    printf("total p1: %d\n", total_p1);

    coord curr_keep = {current_2.x, current_2.y};
//    int i = 6, j = 3;
//    int temp = grid[i][j];
//    grid[i][j] = 1;
//    total_p2 += loop(grid, current_2, curr_line, i, j);
//    grid[i][j] = temp;

    for(int i = 0; i < curr_line; i++) {
        for (int j = 0; j < curr_line; j++) {
            current_2.x = curr_keep.x, current_2.y = curr_keep.y;
            // printf("changing %d, %d, start pos is %d, %d\n", i, j, current_2.x, current_2.y);
            if(!(i == current.x && j == current.y)){
                int temp = grid[i][j];
                grid[i][j] = 1;
                total_p2 += loop(grid, current_2, curr_line, i, j);
                grid[i][j] = temp;
            }
        }
    }

    printf("total p2: %d\n", total_p2);
}