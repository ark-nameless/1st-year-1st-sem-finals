#ifndef _TOOLS_H
#define _TOOLS_H
#define _LTOOLS 1

#ifndef _TYPES_H
#include "types.h"
#endif

#if _LTOOLS

    void test_tools(void);
    void SetFBColor(int FColor, int BColor);
    void gotoxy(int x, int y);
    void clrscr(void);
    int whereX(void);
    int whereY(void);
    void CursorOption(int option, int size);
    void gotoX(int x);
    void gotoY(int y);

#endif

void STR_SimulateFPS(int fps_count);
void STR_BlinkChar(int x, int y, char ch);
void STR_VSelection(T_Color F_Color, T_Color R_Color, int args, ...);
int STR_VSelect(int *choice, int input, int lo, int hi);
char STR_ConvertChoice(int choice);
void STR_CleanView(int hi);
void ResetColors(void);

// Strings
void STR_CycleChar(int start, int end, int option, int sleep);
void LeftAppend(char *des, char *src);
int GetLoginType(char *ID);
bool CheckFile(char *filename);
bool CheckString(char *filename, char *str);

#endif