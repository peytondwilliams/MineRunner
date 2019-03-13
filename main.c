
#include "sl.h"

#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


typedef struct board_element {
    int type;
    int bomb_val;
    bool visible;
} elem;
//type 0 is passable
//type 1 is inpassable
//type 2 is bomb
//type 3 is exit

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
    return;
}

int main() {

#define BOARD_WIDTH (9)
#define BOARD_HEIGHT (9)
#define PIXEL_WIDTH (650)
#define PIXEL_HEIGHT (800)

    elem board[BOARD_HEIGHT][BOARD_WIDTH];
    read_file(board, "maps/test_file.txt");

    player play_1 = {4, 4};

    slWindow (PIXEL_WIDTH, PIXEL_HEIGHT, "GridGame", 0);

    slSetFont(slLoadFont("ttf/coolvetica rg.ttf"), 60);
    slSetTextAlign(SL_ALIGN_CENTER);

    double cooldown = 0;
    char num[5];

    bool game_over = false;
    bool next_level = false;

    while (!slShouldClose()) {

        if (next_level) {
            next_level = false;
            //read_file(board, );
        }

        if (cooldown < 0.0) {
            cooldown = 0.0;
        }
    if(!game_over) {
        if (slGetKey('W') && cooldown == 0.0) {
            if (play_1.y < BOARD_HEIGHT - 1) {
                play_1.y += 1;
                cooldown += .2;
            }
                //play_1.x += 1;


        } else if (slGetKey('A') && cooldown == 0.0) {
             if (play_1.x > 0) {
                play_1.x -= 1;
                cooldown += .2;
            }
        } else if (slGetKey('S') && cooldown == 0.0) {
            if (play_1.y > 0) {
                play_1.y -= 1;
                cooldown += .2;
            }
        } else if (slGetKey('D') && cooldown == 0.0) {
            if (play_1.x < BOARD_WIDTH - 1) {
                play_1.x += 1;
                cooldown += .2;
            }
        }
    }
        cooldown -= slGetDeltaTime();


        slSetForeColor(1.0, 1.0, 1.0, 1.0);

        for (int row = 0; row < BOARD_HEIGHT; row++) {
            for (int col = 0; col < BOARD_WIDTH; col++) {
                if (col == play_1.x) {
                    if (row + 1 == play_1.y || row - 1 == play_1.y) {
                        if (board[row][col].type == 2) {
                            game_over = true;
                        }
                        board[row][col].visible = true;
                    }
                } else if (row == play_1.y) {
                    if (col + 1 == play_1.x || col - 1 == play_1.x) {
                         if (board[row][col].type == 2) {
                            game_over = true;
                        }
                        board[row][col].visible = true;
                    }
                }


                if (col == play_1.x && row == play_1.y) {
                    slSetForeColor(0.0, 1.0, 0.0, 1.0);
                    slRectangleFill(col * 66 + 60, row * 66 + 60, 62, 62);
                } else if (board[row][col].visible == true){
                    if (board[row][col].type == 2) {
                        slSetForeColor(1.0, 0.0, 0.0, 1.0);
                        slRectangleFill(col * 66 + 60, row * 66 + 60, 62, 62);
                    } else if (board[row][col].type == 3) {
                        slSetForeColor(0.0, 1.0, 1.0, 1.0);
                        slRectangleFill(col * 66 + 60, row * 66 + 60, 62, 62);

                    } else {
                    itoa(board[row][col].bomb_val, num, 10);
                    slSetForeColor(1.0, 1.0, 1.0, 1.0);
                    slRectangleFill(col * 66 + 60, row * 66 + 60, 62, 62);
                    slSetForeColor(0.0, 0.0, 0.0, 1.0);
                    slText(col * 66 + 60, row * 66 + 40, num);
                    }
                }
            }
        }
        if (game_over) {
            slSetForeColor(1.0, 1.0, 1.0, 1.0);
            slSetTextAlign(SL_ALIGN_LEFT);
            slText(50, 700, "Game Over, you lost!");
        }
        slSetTextAlign(SL_ALIGN_CENTER);

        slRender();

        if(slGetKey(SL_KEY_ESCAPE)) {
            slClose();
        }
    }

    slClose();
    return 0;
}
