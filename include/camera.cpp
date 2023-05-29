#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <assert.h>
#include <time.h>
#include <conio.h>

#include "camera.h"
#include "tools.h"
#include "neotools.h"
#include "types.h"


static int CurrColor = GREEN;



void test_camera(void)
{
    MessageBox(NULL, "CAMERA.h Successfully Linked!", "Information", MB_ICONINFORMATION | MB_OK);
}


void STR_ViewDefBoarder(int color, int C_Option)
{
    int x, y;
    x = y = 0;
    // MAINBORDER 
    gotoxy(x++, y++);
    SetFBColor(color, BLACK);
    // TOP
    printf("\xC9");for (int i = 0; i < 70; i++){ putchar('\xCD');} putchar('\xBB');
    gotoxy(72, 0);
    printf("\xC9");for (int i = 0; i < 70; i++){ putchar('\xCD');} putchar('\xBB');

    // BOTTOM
    gotoxy(0, 39);
    printf("\xC8");for (int i = 0; i < 70; i++){ putchar('\xCD');} putchar('\xBC');
    gotoxy(72, 39);
    printf("\xC8");for (int i = 0; i < 70; i++){ putchar('\xCD');} putchar('\xBC');

    // LEFT
    gotoY((y=1)++);
    for (int i = 0; i < 38; i++){
        gotoX(0);
        putchar('\xBA');
        gotoX(71);
        putchar('\xBA');
        gotoY(y++);
    }
    // RIGHT
    gotoY((y=1)++);
    for (int i = 0; i < 38; i++){
        gotoX(72);
        putchar('\xBA');
        gotoX(143);
        putchar('\xBA');
        gotoY(y++);
    }

    // LEFT WINDOW
    STR_PlaceLightBox(1, 1, color, C_Option);
    STR_PlaceLightBox(1, 36, color, C_Option);
    STR_PlaceLightBox(66, 1, color, C_Option);
    STR_PlaceLightBox(66, 36, color, C_Option);
    // BOTTOM LEFT
    STR_PlaceLightBox(73, 1, color, C_Option);
    STR_PlaceLightBox(73, 36, color, C_Option);
    STR_PlaceLightBox(137, 36, color, C_Option);
    STR_PlaceLightBox(137, 1, color, C_Option);

    // MOTION
    // TO BE ADDED
}

void STR_PlaceLightBox(int x, int y, int color, int C_Option)
{
    gotoxy(x, y++);
    printf("\xC9\xCD\xCD\xCD\xBB");
        gotoxy(x, y++);
        printf("\xBA ");
        if (C_Option != STATIC){
            STR_ColorIncrease(&CurrColor);
            SetFBColor(CurrColor, BLACK);
            putchar('\x0F');
            SetFBColor(color, BLACK);
        }
        else {
            putchar('\x0F');
        }
        printf(" \xBA");
        gotoxy(x, y++);
        printf("\xC8\xCD\xCD\xCD\xBC");
}

