#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

char field[17][17];

char buffer[17];

void fill_buffer(char c) {
    char i;
    for (i=0; i < 16; i++) {
        if ((rand() % c) < 1) { /* 1 in C chance of tree */
            buffer[i] = 42; /* * */
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
    
    for (i = 0; i < 16; i++) {
        strcpy(save, field[i]); /* save current */
        strcpy(field[i], ins); /* insert next line */
        strcpy(ins, save); /* move save to ins for next pass */
    }
}

int main(void) {
    srand(time(0));
    
    memset(field, 0, sizeof(field)); /* nullify strings */
    
    for (;;) {
        int x;
        
        fill_buffer(15);
        update_field();
        
        system("cls");
        for (x = 0; x <= 16; x++) {   
            printf("%s\n", field[x]);
        }
        Sleep(100);    
    }
}