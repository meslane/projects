#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define A 97
#define D 100

char field[16][17];
char buffer[17];

char ppos = 8; /* player X position (0-15) */

int score = 0;

void fill_buffer(char c) {
    char i;
    for (i=0; i < 16; i++) {
        if ((rand() % c) < 1) { /* 1 in C chance of tree */
            buffer[i] = 94; /* ^ */
        }
        else {
            buffer[i] = 32; /* space */
        }
    }
    buffer[16] = 0;
}

void update_field() {
    char i;
    char save[17];
    char ins[17];
    
    strcpy(ins, buffer); /* load buffer for first line */
    
    for (i = 0; i <= 16; i++) {
        strcpy(save, field[i]); /* save current */
        strcpy(field[i], ins); /* insert next line */
        strcpy(ins, save); /* move save to ins for next pass */
    }
}

void test_motion() {
    if (kbhit()) {
        char scancode;
        scancode = _getch();
        
        if (scancode == A && ppos != 0) {
            ppos--;
        }
        else if (scancode == D && ppos != 15) {
            ppos++;
        }
    }
}

int test_collision() {
    if (field[8][ppos] == 94) {
        field[8][ppos] = 88;
        return 1;
    }
    else {
        field[8][ppos] = 186;
        return 0;       
    }
}

int main(int argc, char *argv[]) {
    srand(time(0));
    
    memset(field, 32, sizeof(field)); /* spaceify strings */
    
    int i;
    for (i = 0; i < 16; i++) {
        field[i][16] = 0; /* null terminate */
    }
    
    char d; /* difficulty */
    switch(atoi(argv[1])) {
        default:
            d = 15;
            break;
        case 1:
            d = 20;
            break;
        case 2:
            d = 15;
            break;
        case 3:
            d = 10;
            break;
        case 4:
            d = 5;
            break;
    }
    
    int s = 0;
    while (s == 0) {
        int y;
        
        fill_buffer(d);
        update_field();
        test_motion();
        s = test_collision();
        
        score++;
        
        system("cls");
        for (y = 16; y >= 0; y--) {   
            printf("%s\n", field[y]);
        }
        Sleep(100);    
    }
    printf("%i", score);
}