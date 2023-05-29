#ifndef _KEYS_H
#define _KEYS_H

#ifndef _WINDOWS_H
#include <windows.h>
#endif


typedef enum Keys
{
    // Character Sets
    KEY_A, KEY_a, KEY_B, KEY_b, KEY_C, KEY_c, KEY_D, KEY_d, KEY_E, KEY_e, KEY_F, KEY_f, KEY_G, KEY_g,
    KEY_H, KEY_h, KEY_I, KEY_i, KEY_J, KEY_j, KEY_K, KEY_k, KEY_L, KEY_l, KEY_M, KEY_m, KEY_N, KEY_n,
    KEY_O, KEY_o, KEY_P, KEY_p, KEY_Q, KEY_q, KEY_R, KEY_r, KEY_S, KEY_s, KEY_T, KEY_t, KEY_U, KEY_u,
    KEY_V, KEY_v, KEY_W, KEY_w, KEY_X, KEY_x, KEY_Y, KEY_y, KEY_Z, KEY_z, 
    KEY_U1, KEY_U2, KEY_U3, KEY_U4, KEY_U5, KEY_U6, KEY_U7, KEY_U8, KEY_U9, KEY_U10, 
    KEY_U11, KEY_U12, KEY_U13, KEY_U14, KEY_U15, KEY_U16, KEY_U17, KEY_U18, KEY_U19, KEY_U20,
    
    // Numerical Set
    KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, 

    // Function Keys 
    KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, 
    
    // Extra Middle Keys 
    KEY_CAPSLOCK, KEY_RIGHT, KEY_LEFT, KEY_UP, KEY_DOWN, KEY_MLEFT, KEY_MRIGHT, KEY_MMIDDLE, 
    KEY_SPACE, KEY_PAGEUP, KEY_PAGEDOWN, KEY_END, KEY_HOME, KEY_PRNTSCR,
    KEY_INS, KEY_DEL, KEY_LWIN, KEY_RWIN, KEY_NUMLOCK, KEY_SCRLLLOCK,

    // NUMPAD KEYS
    KEY_ADD, KEY_SUBTRACT, KEY_MULTIPLY, KEY_DIVIDE, KEY_EQUAL, 

    // Extra 2 Main Keys
    KEY_SHIFT, KEY_CTRL, KEY_ALT, KEY_TAB, KEY_RETURN, KEY_BACKSPACE, KEY_ESCAPE, KEY_NONE
} Keys;

typedef enum ALTER_KEY {
    CHAR_SMILE,
    CHAR_SUN,
    CHAR_ASTERISK,
    CHAR_CIRCLE,
    CHAR_SQUARE,
    CHAR_SHOWN,
    CHAR_HIDE
} ALTER_KEY;

typedef enum ON_SCREEN_OPTION {
    ALPHANUM = 1,
    CHARACTERS = 2,
    NUMBERS = 3,
    EXTRA = 4,
    ALPHAENUM = 5
} ONSCREENOPTION;


Keys STR_GetKeyPress(void);
char STR_ConvertKeytoChar(Keys key);
void STR_ONSCREEKEYBOARD(char *str, ONSCREENOPTION option, char conf, T_Color UColor, T_Color NColor, int x, int y);

void STR_ViewCharacter(int x, int y);
void STR_ViewNumbers(int x, int y);
void STR_ViewExtra(int x, int y);

int STR_HVSelect(int *choice, int interval, int lo, int hi);
void STR_HVSelection(TypeChar type, int F_Color, int R_Color, int interval, int args, ...);
COORD STR_GetCOORD(int linear, int interval);

#endif
