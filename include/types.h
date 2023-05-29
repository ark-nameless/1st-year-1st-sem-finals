#ifndef _TYPES_H
#define _TYPES_H

#define Uint32 unsigned long int
#define Sint32 signed long int
#define Uint16 unsigned short int
#define Sint16 signed short int
#define Uint8 unsigned char
#define Sint8 signed char

#define _DEVC 1

typedef enum T_Color
{
    BLACK,
    BLUE,
    GREEN,
    AQUA,
    RED,
    PURPLE,
    YELLOW,
    WHITE,
    GRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTAQUA,
    LIGHTRED,
    LIGHTPURPLE,
    LIGHTYELLOW,
    LIGHTWHITE
} T_Color;

typedef enum TypeChar
{
    UPPERCASE,
    LOWERCASE,
    CTYPE_NONE
} TypeChar;

typedef enum CYCLECHAR {
    COLOR_NONE, 
    COLOR_CYCLE,
    NO_SLEEP,
    YES_SLEEP
} ColorCycle;

typedef enum LOADING_SCREEN{
    SKIP_LOADING,
    LOAD
} Load_Screen;

typedef enum CURSOR_OPTION {
    HIDDEN,
    VISIBLE
} CURSOR_OPTION;

typedef enum SELECTION_OPTION {
    STATIC, MYRIAD, GRADATION,
    TITLESTRING, CONTENTSTRING
} SELECTION_OPTION;


typedef enum ID_TYPE{
    STUDENT, TEACHER, LIBRARY, CASHIER, INVENTORY, ADMIN
}ID_TYPE;

typedef struct PANELSTATE {
    bool        RUNNING;
    int         Choice;
    int         KeyPress;
} PanelState;



#endif