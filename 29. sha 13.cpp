#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LANE_SIZE 64        
#define MATRIX_ROWS 5         
#define MATRIX_COLS 5         
#define TOTAL_LANES (MATRIX_ROWS * MATRIX_COLS)

typedef unsigned long long lane_t;

void initialize_state(lane_t state[MATRIX_ROWS][MATRIX_COLS]) {
    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLS; j++) {
            state[i][j] = 0; 
        }
    }
}

void absorb_message_block(lane_t state[MATRIX_ROWS][MATRIX_COLS], int block_number) {
  
    int row = rand() % MATRIX_ROWS;
    int col = rand() % MATRIX_COLS;
    state[row][col] = (unsigned long long)(block_number + 1); 
}

int all_lanes_nonzero(lane_t state[MATRIX_ROWS][MATRIX_COLS]) {
    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLS; j++) {
            if (state[i][j] == 0) {
                return 0; 
            }
        }
    }
    return 1; 
}

int main() {
    lane_t state[MATRIX_ROWS][MATRIX_COLS];
    initialize_state(state);

    srand(time(NULL)); 

    int count = 0;
    while (!all_lanes_nonzero(state)) {
        absorb_message_block(state, count);
        count++;
    }

    printf("Total message blocks absorbed before all lanes are nonzero: %d\n", count);
    return 0;
}
