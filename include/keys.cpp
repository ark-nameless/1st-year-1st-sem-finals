#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "tools.h"
#include "keys.h"
#include "types.h"


Keys STR_GetKeyPress(void)
{
    bool Key[79];

    for (int i = 0; i < 79; i++) // wsadjp
        Key[i] = (0x8000 & GetAsyncKeyState((unsigned char) \
        ("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789\x01\x02\x04\x08\x09\x0D\x10\x11\x12\x14\x1B\x20\x21\x22\x23\x24\x25\x26\x27\x28\x2C\x2D\x2E\x5B\x5C\x6A\x6B\x6D\x6F\x90\x91\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7A\x7B"[i]))) != 0;

    // Shift Codes
    if (Key[0] && Key[42]) return (KEY_A);
    else if (Key[1] && Key[42]) return (KEY_B);
    else if (Key[2] && Key[42]) return (KEY_C);
    else if (Key[3] && Key[42]) return (KEY_D);
    else if (Key[4] && Key[42]) return (KEY_E);
    else if (Key[5] && Key[42]) return (KEY_F);
    else if (Key[6] && Key[42]) return (KEY_G);
    else if (Key[7] && Key[42]) return (KEY_H);
    else if (Key[8] && Key[42]) return (KEY_I);
    else if (Key[9] && Key[42]) return (KEY_J);
    else if (Key[10] && Key[42]) return (KEY_K);
    else if (Key[11] && Key[42]) return (KEY_L);
    else if (Key[12] && Key[42]) return (KEY_M);
    else if (Key[13] && Key[42]) return (KEY_N);
    else if (Key[14] && Key[42]) return (KEY_O);
    else if (Key[15] && Key[42]) return (KEY_P);
    else if (Key[16] && Key[42]) return (KEY_Q);
    else if (Key[17] && Key[42]) return (KEY_R);
    else if (Key[18] && Key[42]) return (KEY_S);
    else if (Key[19] && Key[42]) return (KEY_T);
    else if (Key[20] && Key[42]) return (KEY_U);
    else if (Key[21] && Key[42]) return (KEY_V);
    else if (Key[22] && Key[42]) return (KEY_W);
    else if (Key[23] && Key[42]) return (KEY_X);
    else if (Key[24] && Key[42]) return (KEY_Y);
    else if (Key[25] && Key[42]) return (KEY_Z);
    else if (Key[26] && Key[42]) return (KEY_U10);
    else if (Key[27] && Key[42]) return (KEY_U1);
    else if (Key[28] && Key[42]) return (KEY_U2);
    else if (Key[29] && Key[42]) return (KEY_U3);
    else if (Key[30] && Key[42]) return (KEY_U4);
    else if (Key[31] && Key[42]) return (KEY_U5);
    else if (Key[32] && Key[42]) return (KEY_U6);
    else if (Key[33] && Key[42]) return (KEY_U7);
    else if (Key[34] && Key[42]) return (KEY_U8);
    else if (Key[35] && Key[42]) return (KEY_U9);

    // Char Set Keys
    else if (Key[0]) return (KEY_a);
    else if (Key[1]) return (KEY_b);
    else if (Key[2]) return (KEY_c);
    else if (Key[3]) return (KEY_d);
    else if (Key[4]) return (KEY_e);
    else if (Key[5]) return (KEY_f);
    else if (Key[6]) return (KEY_g);
    else if (Key[7]) return (KEY_h);
    else if (Key[8]) return (KEY_i);
    else if (Key[9]) return (KEY_j);
    else if (Key[10]) return (KEY_k);
    else if (Key[11]) return (KEY_l);
    else if (Key[12]) return (KEY_m);
    else if (Key[13]) return (KEY_n);
    else if (Key[14]) return (KEY_o);
    else if (Key[15]) return (KEY_p);
    else if (Key[16]) return (KEY_q);
    else if (Key[17]) return (KEY_r);
    else if (Key[18]) return (KEY_s);
    else if (Key[19]) return (KEY_t); 
    else if (Key[20]) return (KEY_u);
    else if (Key[21]) return (KEY_v);
    else if (Key[22]) return (KEY_w);
    else if (Key[23]) return (KEY_x);
    else if (Key[24]) return (KEY_y);
    else if (Key[25]) return (KEY_z);
    else if (Key[26]) return (KEY_0);
    else if (Key[27]) return (KEY_1);
    else if (Key[28]) return (KEY_2);
    else if (Key[29]) return (KEY_3);
    else if (Key[30]) return (KEY_4);
    else if (Key[31]) return (KEY_5);
    else if (Key[32]) return (KEY_6);
    else if (Key[33]) return (KEY_7);
    else if (Key[34]) return (KEY_8);
    else if (Key[35]) return (KEY_9);
    else if (Key[36]) return (KEY_MLEFT);
    else if (Key[37]) return (KEY_MRIGHT);
    else if (Key[38]) return (KEY_MMIDDLE);
    else if (Key[39]) return (KEY_BACKSPACE);
    else if (Key[40]) return (KEY_TAB);
    else if (Key[41]) return (KEY_RETURN);
    else if (Key[42]) return (KEY_SHIFT);
    else if (Key[43]) return (KEY_CTRL);
    else if (Key[44]) return (KEY_ALT);
    else if (Key[45]) return (KEY_CAPSLOCK);
    else if (Key[46]) return (KEY_ESCAPE);
    else if (Key[47]) return (KEY_SPACE);
    else if (Key[48]) return (KEY_PAGEUP);
    else if (Key[49]) return (KEY_PAGEDOWN);
    else if (Key[50]) return (KEY_END);
    else if (Key[51]) return (KEY_HOME);
    else if (Key[52]) return (KEY_LEFT);
    else if (Key[53]) return (KEY_UP);
    else if (Key[54]) return (KEY_RIGHT);
    else if (Key[55]) return (KEY_DOWN);
    else if (Key[56]) return (KEY_PRNTSCR);
    else if (Key[57]) return (KEY_INS);
    else if (Key[58]) return (KEY_DEL);
    else if (Key[59]) return (KEY_LWIN);
    else if (Key[60]) return (KEY_RWIN);
    else if (Key[61]) return (KEY_MULTIPLY);
    else if (Key[62]) return (KEY_ADD);
    else if (Key[63]) return (KEY_SUBTRACT);
    else if (Key[64]) return (KEY_DIVIDE);
    else if (Key[65]) return (KEY_NUMLOCK);
    else if (Key[66]) return (KEY_SCRLLLOCK);
    // Function Keys
    else if (Key[67]) return (KEY_F1);
    else if (Key[68]) return (KEY_F2);
    else if (Key[69]) return (KEY_F3);
    else if (Key[70]) return (KEY_F4);
    else if (Key[71]) return (KEY_F5);
    else if (Key[72]) return (KEY_F6);
    else if (Key[73]) return (KEY_F7);
    else if (Key[74]) return (KEY_F8);
    else if (Key[75]) return (KEY_F9);
    else if (Key[76]) return (KEY_F10);
    else if (Key[77]) return (KEY_F11);
    else if (Key[78]) return (KEY_F12);

    
    else return (KEY_NONE);
}

char STR_ConvertKeytoChar(Keys key)
{
    // Shift Codes
    if (key % 2 == 0){
        if (key == KEY_A) return ('A');
        else if (key == KEY_B) return ('B');
        else if (key == KEY_C) return ('C');
        else if (key == KEY_D) return ('D');
        else if (key == KEY_E) return ('E');
        else if (key == KEY_F) return ('F');
        else if (key == KEY_G) return ('G');
        else if (key == KEY_H) return ('H');
        else if (key == KEY_I) return ('I');
        else if (key == KEY_J) return ('J');
        else if (key == KEY_K) return ('K');
        else if (key == KEY_L) return ('L');
        else if (key == KEY_M) return ('M');
        else if (key == KEY_N) return ('N');
        else if (key == KEY_O) return ('O');
        else if (key == KEY_P) return ('P');
        else if (key == KEY_Q) return ('Q');
        else if (key == KEY_R) return ('R');
        else if (key == KEY_S) return ('S');
        else if (key == KEY_T) return ('T');
        else if (key == KEY_U) return ('U');
        else if (key == KEY_V) return ('V');
        else if (key == KEY_W) return ('W');
        else if (key == KEY_X) return ('X');
        else if (key == KEY_Y) return ('Y');
        else if (key == KEY_Z) return ('Z');
    }
    else {
        if (key == KEY_a) return ('a');
        else if (key == KEY_b) return ('b');
        else if (key == KEY_c) return ('c');
        else if (key == KEY_d) return ('d');
        else if (key == KEY_e) return ('e');
        else if (key == KEY_f) return ('f');
        else if (key == KEY_g) return ('g');
        else if (key == KEY_h) return ('h');
        else if (key == KEY_i) return ('i');
        else if (key == KEY_j) return ('j');
        else if (key == KEY_k) return ('k');
        else if (key == KEY_l) return ('l');
        else if (key == KEY_m) return ('m');
        else if (key == KEY_n) return ('n');
        else if (key == KEY_o) return ('o');
        else if (key == KEY_p) return ('p');
        else if (key == KEY_q) return ('q');
        else if (key == KEY_r) return ('r');
        else if (key == KEY_s) return ('s');
        else if (key == KEY_t) return ('t');
        else if (key == KEY_u) return ('u');
        else if (key == KEY_v) return ('v');
        else if (key == KEY_w) return ('w');
        else if (key == KEY_x) return ('x');
        else if (key == KEY_y) return ('y');
        else if (key == KEY_z) return ('z');
    }
    
    if (key == KEY_0) return ('0');
    else if (key == KEY_1) return ('1');
    else if (key == KEY_2) return ('2');
    else if (key == KEY_3) return ('3');
    else if (key == KEY_4) return ('4');
    else if (key == KEY_5) return ('5');
    else if (key == KEY_6) return ('6');
    else if (key == KEY_7) return ('7');
    else if (key == KEY_8) return ('8');
    else if (key == KEY_9) return ('9');
    else if (key == KEY_U1) return ('!');
    else if (key == KEY_U2) return ('@');
    else if (key == KEY_U3) return ('#');
    else if (key == KEY_U4) return ('$');
    else if (key == KEY_U5) return ('%');
    else if (key == KEY_U6) return ('^');
    else if (key == KEY_U7) return ('&');
    else if (key == KEY_U8) return ('*');
    else if (key == KEY_U9) return ('(');
    else if (key == KEY_U10) return (')');
    else if (key == KEY_SPACE) return (' ');
    else if (key == KEY_RETURN) return ('\n');
    
    else return (KEY_NONE);
}

void STR_ONSCREEKEYBOARD(char *str, ONSCREENOPTION option, char conf, T_Color UColor, T_Color NColor, int x, int y)
{
    // int choice = -1;
    // char conv;

    // if (option & EXTRA){
    //     STR_ViewExtra(x, y + 8);
    // }
    // else if (option & NUMBERS){
    //     STR_ViewNumbers(x, y);
    // }
    // else if (option & ALPHANUM){
    //     STR_ViewCharacter(x, y);
    //     STR_ViewNumbers(x, y + 6);
    // }
    // else if (option & CHARACTERS){
    //     STR_ViewCharacter(x, y);
    // }
    // else if (option & ALPHAENUM){
    //     STR_ViewCharacter(x, y);
    //     STR_ViewNumbers(x, y + 6);
    //     STR_ViewExtra(x, y + 8);
    // }

    // int posX = x;
    // int posY = y;
    // int sel = 0;

    // do {
    //     choice = STR_GetKeyPress();
        
    //     switch(choice){
    //         case KEY_A: // LEFT
    //             if (posX == 1){
    //                 posX = 10;
    //                 sel = 10;
    //             }
    //             else {
    //                 posX -= 2;
    //             }
    //             break;
    //         case KEY_D: // RIGHT
    //             if (posX == 10){
    //                 posX = 1;
    //                 sel = 1;
    //             }
    //             else {
    //                 posX += 2;
    //                 sel += 1;
    //             }
    //             break;
    //         case KEY_S: // DOWN
    //             switch(option){
    //                 case ALPHANUM:
    //                     if (posY == 4){
    //                         posY = 1;
    //                         sel *= 1;
    //                     }
    //                     break;
    //                 case ALPHAENUM:
    //                     break;
    //             }
    //             break;
    //         case KEY_W: // UP
    //             break;
    //         default:
    //             break;
    //     }
}


void STR_ViewCharacter(int x, int y)
{
    gotoxy(x, y);
    printf("a b c d e f g h i j\n\n");
    gotoxy(x, y + 2);
    printf("k l m n p q r s t u\n\n");
    gotoxy(x, y + 4);
    printf("v w x y z \x1B \x1E \xF3\xD9\n");
}
void STR_ViewNumbers(int x, int y)
{
    gotoxy(x, y);
    printf("1 2 3 4 5 6 7 8 9 0\n");
}
void STR_ViewExtra(int x, int y)
{
    gotoxy(x, y);
    printf("! @ # $ % ^ & * _");
    gotoxy(x, y + 2);
    printf("- = + \\ < > ? / |\n");
}

void STR_HVSelection(TypeChar type, int F_Color, int R_Color, int interval, int args, ...)
{
    va_list data;
    va_start(data, args);

    int choice = va_arg(data, int);

    int x, y;

    if (type == CTYPE_NONE){
        for (int i = 3; i < args; i += 3)
        {
            x = va_arg(data, int);
            y = va_arg(data, int);
            if (choice == i / 3)
            {
                gotoxy(x, y);
                SetFBColor(F_Color, BLACK);
                putchar('_');
                gotoxy(x, y + 1);
                printf("%-2s", va_arg(data, char*));
            }
            else
            {
                gotoxy(x, y);
                SetFBColor(R_Color, BLACK);
                putchar('_');
                gotoxy(x, y + 1);
                printf("  %-2s", va_arg(data, char *));
            }
        }
    }
    else {
        for (int i = 3; i < args; i += 3)
        {
            x = va_arg(data, int);
            y = va_arg(data, int);
            if (choice == i / 3)
            {
                gotoxy(x, y);
                SetFBColor(F_Color, BLACK);
                putchar('_');
                gotoxy(x, y + 1);
                printf("%c", (type == UPPERCASE) ? toupper(va_arg(data, int)) : tolower(va_arg(data, int)));
            }
            else
            {
                gotoxy(x, y);
                SetFBColor(R_Color, BLACK);
                putchar(' ');
                gotoxy(x, y + 1);
                printf("%c", (type == UPPERCASE) ? toupper(va_arg(data, int)) : tolower(va_arg(data, int)));
            }
        }
    }
        

    va_end(data);
}

int  STR_HVSelect(int *choice, int interval, int lo, int hi)
{
    // static COORD temp = {0, 0};
    int Key = STR_GetKeyPress();

    switch(Key){
        case KEY_A: 
        case KEY_a: 
            if (*choice % interval == lo){
                *choice = interval * ((*choice / interval) + 1) ;
            }
            else {
                *choice -= 1;
            }
            break;
        case KEY_D:
        case KEY_d:
            if (*choice % interval == 0){
                *choice = (*choice / interval) * interval - (interval - 1);
            }
            else {
                *choice += 1;
            }
            break;
        case KEY_W:
        case KEY_w:
            if ((*choice + interval) / interval == 1){
                *choice = hi - (interval - *choice);
            }
            else {
                *choice -= interval;
            }
            break;
        case KEY_S:
        case KEY_s:
            if (*choice + interval > hi){
                *choice = *choice % interval;
            }
            else {
                *choice += interval;
            }
            break;
    }

    return (*choice);
}


COORD STR_GetCOORD(int linear, int interval)
{
    COORD temp = {linear % interval, linear / interval};
    return (temp);
}
