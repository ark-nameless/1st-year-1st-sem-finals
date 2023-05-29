#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <assert.h>
#include <time.h>
#include <conio.h>
#include <string.h>

#include "tools.h"
#include "states.h"

// Globals
static COORD textpos = {0, 0};
static HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);


#if _LTOOLS
    void test_tools(void)
    {
        MessageBox(NULL, "tools.h Successfully Linked!", "Information", MB_ICONINFORMATION | MB_OK);
    }
    void SetFBColor(int FColor, int BColor)
    {
        WORD wColor = ((BColor & 0x0F) << 4) + (FColor & 0x0F);
        SetConsoleTextAttribute(outHandle, wColor);
    }
    void gotoxy(int x, int y)
    {
        textpos.X = x;
        textpos.Y = y;
        SetConsoleCursorPosition(outHandle, textpos);
    }
    void clrscr(void)
    {
        if (_DEVC){
            system("cls");
        }
        else {
            system("clear");
        }
        textpos.X = 0;
        textpos.Y = 0;
    }
    int whereX(void)
    {
        return (textpos.X);
    }
    int whereY(void)
    {
        return (textpos.Y);
    }
    void CursorOption(int option, int size)
    {
        CONSOLE_CURSOR_INFO cursor;
        cursor.dwSize = size;
        if (option == HIDDEN){
            cursor.bVisible = false;
        }
        else if (option == VISIBLE){
            cursor.bVisible = true;
        }
        SetConsoleCursorInfo(outHandle, &cursor);
    }
    void gotoX(int x)
    {
        textpos.X = x;
        SetConsoleCursorPosition(outHandle, textpos);
    }
    void gotoY(int y)
    {
        textpos.Y = y;
        SetConsoleCursorPosition(outHandle, textpos);
    }
#endif

void STR_SimulateFPS(int fps_count)
{
    unsigned int fps = 1000 / fps_count;
    unsigned int S_time, E_time;

    S_time = clock();
    E_time = clock() - S_time;

    if (fps > E_time){
        Sleep(fps - E_time);
    }
}

void STR_BlinkChar(int x, int y, char ch)
{
    static bool blink_status = true;

    gotoxy(x, y);
    if (blink_status == true)
    {
        putchar(ch);
        blink_status = false;
    }
    else
    {
        putchar(' ');
        blink_status = true;
    }
}

void STR_CycleChar(int start, int end, int option, int sleep)
{
    int x = whereX(), y = whereY();
    int i = start;
    static int color = BLUE;
    if (sleep != NO_SLEEP){
        while (i != end){
            if (option == COLOR_CYCLE){
                if (color > 13){
                    color = RED;
                }
                color++;
                SetFBColor(color, BLACK);
            }
            if (end < i){
                --i;
            }
            else{
                ++i;
            }
            gotoxy(x, y);
            putchar(i);
            Sleep(100);
        }
    }
    else {
        if (color > 13){
            color = LIGHTBLUE;
        }
        ++color;
        SetFBColor(color, BLACK);
        gotoxy(x, y);
        putchar(end);
    }
    
}

void STR_VSelection(T_Color F_Color, T_Color R_Color, int args, ...)
{
    va_list data;
    va_start(data, args);

    int choice = va_arg(data, int);
    int x, y;

    for (int i = 3; i < args; i += 3){
        x = va_arg(data, int);
        y = va_arg(data, int);
        if (choice == i / 3){
            gotoxy(x, y);
            SetFBColor(F_Color, BLACK);
            printf("> %-20s", va_arg(data, char*));
        }
        else {
            gotoxy(x, y);
            SetFBColor(R_Color, BLACK);
            printf("  %-20s", va_arg(data, char*));
        }
    }

    va_end(data);
}

int STR_VSelect(int *choice, int input, int lo, int hi)
{   
    switch(input){
        case KEY_w:
            if (*choice <= lo){
                *choice = hi;
            }
            else {
                *choice -= 1;
            }
            return (*choice);
            break;
        case KEY_s:
            if (*choice >= hi){
                *choice = lo;
            }
            else {
                *choice += 1;
            }
            return (*choice);
            break;
    }

    int temp = input;
    return (temp);
}

void STR_CleanView(int hi)
{
    for (int i = 0; i < hi; i++){
        putchar(' ');
    }
}

char STR_ConvertChoice(int choice)
{
    switch(choice){
        case 1: return ('a'); break;
        case 2: return ('b'); break;
        case 3: return ('c'); break;
        case 4: return ('d'); break;
        case 5: return ('e'); break;
        case 6: return ('f'); break;
        case 7: return ('g'); break;
        case 8: return ('h'); break;
        case 9: return ('i'); break;
        case 10: return ('j'); break;
        case 11: return ('k'); break;
        case 12: return ('l'); break;
        case 13: return ('m'); break;
        case 14: return ('n'); break;
        case 15: return ('o'); break;
        case 16: return ('p'); break;
        case 17: return ('q'); break;
        case 18: return ('r'); break;
        case 19: return ('s'); break;
        case 20: return ('t'); break;
        case 21: return ('u'); break;
        case 22: return ('v'); break;
        case 23: return ('w'); break;
        case 24: return ('x'); break;
        case 25: return ('y'); break;
        case 26: return ('z'); break;
        case 27: return (' '); break;
        case 28: return ('/'); break;
        case 29: return ('^'); break;
        case 30: return ('<'); break;
        case 31: return ('0'); break;
        case 32: return ('1'); break;
        case 33: return ('2'); break;
        case 34: return ('3'); break;
        case 35: return ('4'); break;
        case 36: return ('5'); break;
        case 37: return ('6'); break;
        case 38: return ('7'); break;
        case 39: return ('8'); break;
        case 40: return ('9'); break;
        case 41: return ('.'); break;
        case 42: return (','); break;
        case 43: return ('~'); break;
        case 44: return ('_'); break;
        case 45: return ('-'); break;
        case 46: return ('+'); break;
        case 47: return ('@'); break;
        case 48: return ('*'); break;
        case 49: return ('!'); break;
        case 50: return ('?'); break;
    }

    return (-1);
}

void LeftAppend(char *des, char *append)
{
    int i, j;
    i = j = 0;
    while (des[i++] != '\0') /* Find the end of s */ ;
    while (append[j++] != '\0') /* Find the end of s */ ;
    int total = i + j;
    char temp[total+1];

    i = j = total = 0;
    while (append[i] != '\0'){ /* Copy the contents*/
        temp[total++] = append[i++];
    }
    while (des[j] != '\0'){ /* Copy the contents*/
        temp[total++] = des[j++];
    }
    temp[total++] = '\0';
    i = 0;
    while ((des[i] = temp[i++]) != '\0') /* Copy the contents*/ ;

}

void ResetColors(void)
{
    SetFBColor(LIGHTWHITE, BLACK);
}

bool CheckFile(char *filename)
{
    FILE *Data = fopen(filename, "r");
    if (Data == NULL){
        fclose(Data);
        return (false);
    }
    else {
        fclose(Data);
        return (true);
    }
    return (false);
}

bool CheckString(char *filename, char *str)
{
    FILE *Data = fopen(filename, "r");
    char temp[100];

    if (Data == NULL){
        fclose(Data);
        return (false);
    }
    else {
        while (fgets(temp, 99, Data)!= NULL){
            if (strstr(temp, str)){
                fclose(Data);
                return (true);
            }
        }
    }

    fclose(Data);
    return (false);
}

int GetLoginType(char *ID)
{
    char temp[4];
    int i;
    for (i = 0; i < 4; i++ ){
        temp[i] = ID[i];
    }
    temp[i];
    if (strstr(temp, "ADM") || strstr(ID, "admin")){
        return (ADMIN);
    }
    else if (strstr(temp, "STU")){
        return (STUDENT);
    }
    else if (strstr(temp, "TEA")){
        return (TEACHER);
    }
    else if (strstr(temp, "LIB")){
        return (LIBRARY);
    }
    else if (strstr(temp, "CAS")){
        return (CASHIER);
    }
    else if (strstr(temp, "INV")){
        return (INVENTORY);
    }

    return (STUDENT);
}
