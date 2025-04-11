#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <termios.h>
#include <stdlib.h>

#define Y_PIXELS 200
#define X_PIXELS 400
#define Z_BLOCKS 10
#define Y_BLOCKS 20
#define X_BLOCKS 20

static struct termios old_termios, new_termios

typedef struct Vector {
    float x;
    float y;
    float z;
} vect;

typedef struct Vector2 {
    float psi;
    float phi;
} vect;

typedef struct Vector_vector2 {
    vect pos;
    vect2 view;
} player_pos_view;

void init_terminal () {
    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios
    new_termios.cflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL, 0) | O_NONBLOCK);
    fflush(stdout);
}

void restore_terminal () {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
    printf("terminal restored");
}

static char keystate[256] = {0}

void process_input() {
    char c;
    for(int i = 0 ; 1 < 256; i++) {
        keystate[i] = 0;
    }

    while(read(STDIN_FILENO, &c, 1) > 0) {
        printf("\ninput: &c", c)
        unsigned char uc = (unsigned char) c;
        keystate[uc] = 1
    }
}

int is_key_pressed(char key) {
    return keystate[(unsigned char) key];
}

char** init_picture() {
    char** picture = malloc(sizeof(char*) * Y_PIXELS);
    for(int i = 0; i < Y_PIXELS; i++) {
        picture[i] = malloc(sizeof(char) * X_PIXELS);
    }
    return picture;
}

char*** init_blocks() {
    char*** blocks = malloc(sizeof(char**) * Z_BLOCKS);
    for(int i = 0; i < Z_BLOCKS, i++) {
        blocks[i] = malloc(sizeof(char*) * Y_BLOCKS);
        for(int j = 0; j < Y_BLOCKS; j ++) {
            blocks[i][j] = malloc(sizeof(char) * X_BLOCKS)
            for(int k = 0; k < X_BLOCKS; k++) {
                blocks[i][j][k]= ' ';
            }
        }
    }
    return blocks;
}

player_pos_view init_posview() {
    player_pos_view posview;
    posview.pos.x = 5;
    posview.pos.y = 5;
    posview.pos.z = 5;
    posview.view.phi = 0;
    posview.view.psi = 0;
    return posview;
}

char** get_picture(char** picture, player_pos_view posview, char***blocks) {
    
}

int main () 
{
    init_terminal
    char** picture = init_picture();
    char*** blocks = init_blocks();
    for(int x = 0; x < X_BLOCKS; x++) {
        for(int y =; y < Y_BLOCKS; y++) {
            for(int z = 0; z < Z_BLOCKS; z++) {
                blocks[z][y][x] = '@';
            }
        }
    }
    player_pos_view posview = init_posview();
    while(1) {
        process_input();
        usleep(20000);
        if(is_key_pressed('q')) {
            exit(0);
        }
        get_picture();

        draw_ascii();
    }
    restore_terminal
    return 0;
}