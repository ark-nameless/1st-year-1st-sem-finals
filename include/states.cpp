#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <assert.h>

#include "tools.h"
#include "states.h"
#include "types.h"
#include "keys.h"
#include "neotools.h"

void STR_GetStateString(char *var, ALTER_KEY option, T_Color fColor)
{
    Keys key;
    char ch;
    int i = 0;
    SetFBColor(fColor, BLACK);
    do {
        key = STR_GetKeyPress();
        ch = STR_ConvertKeytoChar(key);
        if (key <= 82 || key == KEY_SPACE){
            var[i++] = ch;
            STR_AlterCharDisplay(option, ch);
        }
        else if (key == KEY_BACKSPACE && i > 0){
            var[--i] = '\0';
            printf("\b \b");
        }
        Sleep(100);
    } while (key != KEY_RETURN);
    var[i++] = '\0';
}

void STR_GetStateStringWithTime(char *var, ALTER_KEY option, T_Color fColor, int x, int y, int color, int C_Option)
{
    Keys key;
    char ch;
    int i = 0;
    int ax = whereX();
    int ay = whereY();
    do
    {
        // Draw Time
        STR_DisplayTime(x, y, color, C_Option);

        SetFBColor(fColor, BLACK);
        gotoxy(ax, ay);
        key = STR_GetKeyPress();
        ch = STR_ConvertKeytoChar(key);
        if (key <= 82 || key == KEY_SPACE)
        {
            ax++;
            var[i++] = ch;
            STR_AlterCharDisplay(option, ch);
        }
        else if (key == KEY_BACKSPACE && i > 0)
        {
            --ax;
            var[--i] = '\0';
            printf("\b \b");
        }
        Sleep(80);
    } while (key != KEY_RETURN);
    var[i++] = '\0';
    // gotoY(++ay);
}

void STR_AlterCharDisplay(ALTER_KEY option, char ch)
{
    switch(option){
        case CHAR_SMILE:
            putchar('\x01');
            break;
        case CHAR_SUN:
            putchar('\x0F');
            break;
        case CHAR_ASTERISK:
            putchar('\x2A');
            break;
        case CHAR_CIRCLE:
            putchar('\xF8');
            break;
        case CHAR_SQUARE:
            putchar('\xFE');
            break;
        case CHAR_SHOWN:
            putchar(ch);
            break;
        case CHAR_HIDE:
            break;
        default:
            MessageBox(NULL, "Invalid Option!", "Information", MB_ICONWARNING | MB_OK);
            break;
    }
}

void STR_GetStateInt(int *var, T_Color fColor)
{
    Keys key;
    char ch;
    int i = 0;
    char str[20];
    SetFBColor(fColor, BLACK);
    do {
        key = STR_GetKeyPress();
        ch = STR_ConvertKeytoChar(key);
        if (key <= 82 || key == KEY_SPACE){
            str[i++] = ch;
            putchar(ch);
        }
        else if (key == KEY_BACKSPACE && i > 0){
            str[--i] = '\0';
            printf("\b \b");
        }
        Sleep(100);
    } while (key != KEY_RETURN);
    str[i++] = '\0';


    int len = strlen(str);
    i = 0;
    int j = len;
    int total = 0;
    int place;

    while (i < len){
        place = ChartoInt(str[i++]);
        total += place * GetPlace(j--);
    }

    *var = total;
}

void STR_GetStateIntWithTime(int *var, T_Color fColor, int x, int y, int color, int C_Option)
{
    Keys key;
    char ch;
    int i = 0;
    char str[20];
    int ax = whereX();
    int ay = whereY();
    SetFBColor(fColor, BLACK);
    do {
        // Draw Time
        STR_DisplayTime(x, y, color, C_Option);

        SetFBColor(fColor, BLACK);
        gotoxy(ax, ay);
        key = STR_GetKeyPress();
        ch = STR_ConvertKeytoChar(key);
        if (key <= 82 || key == KEY_SPACE){
            ax++;
            str[i++] = ch;
            putchar(ch);
        }
        else if (key == KEY_BACKSPACE && i > 0){
            --ax;
            str[--i] = '\0';
            printf("\b \b");
        }
        Sleep(100);
    } while (key != KEY_RETURN);
    str[i++] = '\0';


    int len = strlen(str);
    i = 0;
    int j = len;
    int total = 0;
    int place;

    while (i < len){
        place = ChartoInt(str[i++]);
        total += place * GetPlace(j--);
    }

    *var = total;
}

int ChartoInt(char var)
{
    switch(var){
        case '1':
            return (1);
            break;
        case '2':
            return (2);
            break;
        case '3':
            return (3);
            break;
        case '4':
            return (4);
            break;
        case '5':
            return (5);
            break;
        case '6':
            return (6);
            break;
        case '7':
            return (7);
            break;
        case '8':
            return (8);
            break;
        case '9':
            return (9);
            break;
        case '0':
            return (0);
            break;
    }

    return (0);
}

int GetPlace(int place)
{
    switch(place){
        case 1: return (1); case 2: return (10); case 3: return (100); case 4: return (1000); case 5: return (10000);
        case 6: return (100000); case 7: return (1000000); case 8: return (10000000);
        case 9: return (100000000); case 10: return (1000000000); case 11: return (10000000000);
    }
}


