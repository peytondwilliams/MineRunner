#include "sl.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>


typedef struct board_element {
    int type;
    int bomb_val;
    bool visible;
} elem;
//type 0 is passable
//type 1 is inpassable
//type 2 is bomb

typedef struct player_element {
    int x;
    int y;
} player;

void read_file(elem board[9][9], char *file) {
    FILE *fp = NULL;
    fp = fopen(file, "r");


    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int type = 0;
            int bomb_val = 0;
            int visible = 0;
            fscanf(fp, "%d, %d, %d", &type, &bomb_val, &visible);
            elem temp = {type, bomb_val, visible};
            board[i][j] = temp;
        }
        fscanf(fp, "\n");
    }

    fclose(fp);
    fp = NULL;
    return 0;
}

int main() {

#define BOARD_WIDTH (9)
#define BOARD_HEIGHT (9)
#define PIXEL_WIDTH (650)
#define PIXEL_HEIGHT (650)

    elem board[BOARD_HEIGHT][BOARD_WIDTH];
    read_file(board, "maps/test_file.txt");

    player play_1 = {0, 0};

    slWindow (PIXEL_WIDTH, PIXEL_HEIGHT, "GridGame", 0);

    double cooldown = 0;

    while (!slShouldClose()) {

        if (cooldown < 0.0) {
            cooldown = 0.0;
        }

        if (slGetKey('W') && cooldown == 0.0) {
            if (play_1.y < BOARD_HEIGHT - 1) {
                play_1.y += 1;
                cooldown += .11;
            }
        } else if (slGetKey('A') && cooldown == 0.0) {
             if (play_1.x > 0) {
                play_1.x -= 1;
                cooldown += .11;
            }
        } else if (slGetKey('S') && cooldown == 0.0) {
            if (play_1.y > 0) {
                play_1.y -= 1;
                cooldown += .11;
            }
        } else if (slGetKey('D') && cooldown == 0.0) {
            if (play_1.x < BOARD_WIDTH - 1) {
                play_1.x += 1;
                cooldown += .11;
            }
        }

        cooldown -= slGetDeltaTime();


        slSetForeColor(1.0, 1.0, 1.0, 1.0);

        for (int row = 0; row < BOARD_HEIGHT; row++) {
            for (int col = 0; col < BOARD_WIDTH; col++) {
                if (row == play_1.x && col == play_1.y) {
                    slSetForeColor(1.0, 0.0, 0.0, 1.0);
                } else {
                    slSetForeColor(1.0, 1.0, 1.0, 1.0);
                }
                slRectangleFill(row * 66 + 60, col * 66 + 60, 62, 62);
            }
        }


        slRender();
    }

    slClose();
    return 0;
}
