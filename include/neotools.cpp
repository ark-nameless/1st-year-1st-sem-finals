#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <assert.h>
#include <time.h>
#include <conio.h>
#include <stdarg.h>
#include <MMsystem.h>

#include "tools.h"
#include "states.h"
#include "neotools.h"
#include "dsa.h"
#include "types.h"

#define     RectOption(option)              (option == 3) ? 1 : 0


int CurColor = GREEN;


int STR_VerticalSelect(int args, int x, int y, int choice, int C_Option, int T_Color, int SColor, int DColor, ...)
{
    va_list data;
    va_start(data, args);
    char name[30];

    // Setting Contents
    strcpy(name, va_arg(data, char*));

    STR_PrintStringinRect(x, y, C_Option, TITLESTRING, T_Color, name);

    // HEADER
    if (args > 1)
    {
        if (C_Option == STATIC)
        {
            gotoxy(x, whereY() + 1);
            SetFBColor(CurColor, BLACK);
            printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB");
        }
        else if (C_Option == MYRIAD)
        {
            gotoxy(x, whereY() + 1);
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            putchar('\xC8');
            for (int i = 0; i < 24; i++)
            {
                STR_ColorIncrease(&CurColor);
                SetFBColor(CurColor, BLACK);
                putchar('\xCD');
            }
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            putchar('\xBC');
        }
        else if (C_Option == GRADATION)
        {
            gotoxy(x, whereY() + 1);
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            printf("\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC");
        }
    }
    if (args > 1){
        y += 3;
        for (int i = 1; i < args; ++i){
            strcpy(name, va_arg(data, char *));
            if (i == choice){
                STR_PrintStringinRect(x, y, C_Option, CONTENTSTRING, SColor, name);
                gotoX(x+1);
                SetFBColor(SColor, BLACK);
                putchar('\x1A');
                ResetColors();
            }
            else{
                STR_PrintStringinRect(x, y, C_Option, CONTENTSTRING, DColor, name);
            }
            y++;
        }
    }
    
    // FOOTER
    if (args > 1){
        if (C_Option == STATIC){
            gotoxy(x, whereY()+1);
            SetFBColor(CurColor, BLACK);
            printf("\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC");
        }
        else if (C_Option == MYRIAD){
            gotoxy(x, whereY()+1);
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            putchar('\xC8');
            for (int i = 0; i < 24; i++)
            {
                STR_ColorIncrease(&CurColor);
                SetFBColor(CurColor, BLACK);
                putchar('\xCD');
            }
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            putchar('\xBC');
        }
        else if (C_Option == GRADATION){
            gotoxy(x, whereY() + 1);
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            printf("\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC");
        }
    }

    va_end(data);
    return (0);
}

void STR_PrintStringinRect(int x, int y, int C_Option, int S_Option, int S_Color, char *Str)
{
    gotoxy(x, y);
    if (C_Option == STATIC){
        if (S_Option == TITLESTRING){
            SetFBColor(CurColor, BLACK);
            printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB");
            gotoxy(x, (y+=1));
            putchar('\xBA');
            SetFBColor(S_Color, BLACK);
            printf("  %-21s ", Str);
            SetFBColor(CurColor, BLACK);
            putchar('\xBA');
            gotoxy(x, (y += 1));
            printf("\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC");
        }
        else {
            gotoxy(x, (y+=1));
            SetFBColor(CurColor, BLACK);
            putchar('\xBA');
            SetFBColor(S_Color, BLACK);
            printf("  %-21s ", Str);
            SetFBColor(CurColor, BLACK);
            putchar('\xBA');
        }
    }
    else if (C_Option == MYRIAD){
        STR_ColorIncrease(&CurColor);
        if (S_Option == TITLESTRING){
            SetFBColor(CurColor, BLACK);
            putchar('\xC9');
            for (int i = 0; i < 24; i++){
                STR_ColorIncrease(&CurColor);
                SetFBColor(CurColor, BLACK);
                putchar('\xCD');
            }
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            putchar('\xBB');

            gotoxy(x, (y+=1));
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            putchar('\xBA'); SetFBColor(S_Color, BLACK);
            printf("  %-21s ", Str);
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            putchar('\xBA');
            gotoxy(x, (y += 1));

            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            putchar('\xC8');
            for (int i = 0; i < 24; i++){
                STR_ColorIncrease(&CurColor);
                SetFBColor(CurColor, BLACK);
                putchar('\xCD');
            }
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            putchar('\xBC');
        }
        else {
            gotoxy(x, (y+=1));
            SetFBColor(CurColor, BLACK);
            SetFBColor(CurColor, BLACK);
            putchar('\xBA');
            SetFBColor(S_Color, BLACK);
            printf("  %-21s ", Str);
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            putchar('\xBA');
        }
    }
    if (C_Option == GRADATION)
    {
        STR_ColorIncrease(&CurColor);
        if (S_Option == TITLESTRING)
        {
            SetFBColor(CurColor, BLACK);
            printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB");
            gotoxy(x, (y += 1));
            putchar('\xBA');
            SetFBColor(S_Color, BLACK);
            printf("  %-21s ", Str);
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            putchar('\xBA');
            gotoxy(x, (y += 1));
            printf("\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC");
        }
        else
        {
            gotoxy(x, (y += 1));
            SetFBColor(CurColor, BLACK);
            putchar('\xBA');
            SetFBColor(S_Color, BLACK);
            printf("  %-21s ", Str);
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            putchar('\xBA');
        }
    }
    else {
        assert(C_Option >= STATIC || C_Option <= GRADATION);
        assert(S_Option != TITLESTRING || S_Option != CONTENTSTRING);
    }

    SetFBColor(LIGHTWHITE, BLACK);
}

void STR_ColorIncrease(int *color){
    if (*color >= 15){
        *color = GREEN;
    }
    else if (*color <= 1){
        *color = LIGHTWHITE;
    }
    else {
        *color += 1;
    }
    while(*color == BLACK || *color == WHITE || *color == GRAY || *color == BLUE){
        ++(*color);
    }
    
}

void STR_LinearSelect(int *choice, int dir, int lo, int hi)
{
    switch(dir){
        case KEY_s: case KEY_d: case KEY_RIGHT: case KEY_DOWN:
            if (*choice == hi){
                *choice = lo;
            }
            else {
                *choice += 1;
            }
            break;
        case KEY_w: case KEY_a: case KEY_LEFT: case KEY_UP:
            if (*choice == lo){
                *choice = hi;
            }
            else {
                *choice -= 1;
            }
            break;
    }
}

void STR_QUIT(void)
{
    // for(int i = 0);
}

void STR_DisplayTime(int x, int y, int color, int C_Option)
{
    time_t now;
    time(&now);
    struct tm *time = localtime(&now);

    char Clock[20];

    if (time->tm_min < 10){
        sprintf(Clock, "%d:0%d:%d", time->tm_hour, time->tm_min, time->tm_sec);
    }
    else {
        sprintf(Clock, "%d:%d:%d", time->tm_hour, time->tm_min, time->tm_sec);
    }
    STR_PrintStringinRect(x, y, C_Option, TITLESTRING, color, Clock);
}

char *Gen_ID(int type)
{
    // assert(type < STUDENT || type > ADMIN);
    char id[15];
    switch(type){
        case STUDENT:
            sprintf(id, "STU-%d", t_rand());
            break;
        case TEACHER:
            sprintf(id, "TEA-%d", t_rand());
            break;
        case LIBRARY:
            sprintf(id, "LIB-%d", t_rand());
            break;
        case CASHIER:
            sprintf(id, "CAS-%d", t_rand());
            break;
        case INVENTORY:
            sprintf(id, "INV-%d", t_rand());
            break;
        case ADMIN:
            sprintf(id, "ADM-%d", t_rand());
            break;
    }

    return (strdup(id));
}

int t_rand(void)
{
    srand((unsigned)time(NULL));
    return (rand());
}

void LoadDatabase(DataBases *DataBase, char *home)
{
    strcpy(DataBase->TeacherPath, "./Resources/Data/Teacher/");
    strcpy(DataBase->StudentPath, "./Resources/Data/Students/");
    strcpy(DataBase->InboxPath, "./Resources/Data/Inbox/");
    strcpy(DataBase->CashierPath, "./Resources/Data/Cashier/");
    strcpy(DataBase->DTRPath, "./Resources/Data/DTR/");
    strcpy(DataBase->InventoryPath, "./Resources/Data/Inventory/");
    strcpy(DataBase->LibraryPath ,"./Resources/Data/Library/");
    strcpy(DataBase->SystemPath, "./Resources/Data/System/");
    strcpy(DataBase->AdminPath, "./Resources/Data/Admin/");
    strcpy(DataBase->CoursesPath, "./Resources/Data/Courses/");
    strcpy(DataBase->TempPath, "./Resources/Data/tmp.dat");
    strcpy(DataBase->LogsPath, "./Resources/Logs/logs.dat");
    // strcpy(DataBase->HomePath, home);
    // DataBase->Teacher = NULL;
    // DataBase->Student = NULL;
    // DataBase->Inbox = NULL;
    // DataBase->Cashier = NULL;
    // DataBase->DTR = NULL;
    // DataBase->Inventory = NULL;
    // DataBase->Library = NULL;
    // DataBase->System = NULL;
    DataBase->TempData = NULL;
    DataBase->MainData = NULL;

}

void UnloadDatabase(DataBases *Database)
{
    free(Database);
}

void SaveData(int type, DataBases *DataBase, char *databasename)
{
    switch(type){
        case TEACHER_T:
            break; 
        case STUDENT_T:
            break;
        case INBOX_T:
            break;
        case CASHIER_T:
            break;
        case DTR_T:
            break;
        case INVENTORY_T: 
            break; 
        case LIBRARY_T: 
            break; 
        case SYSTEM_T: 
            break; 
        case TEMP_T: 
            break; 
        case ADMIN_T: 
            break;
    }
}

void STR_ClearRect(int x, int y, int w, int h)
{
    ResetColors();
    gotoxy(x, y++);
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            putchar(' ');
        }
        gotoxy(x, y++);
    }
}

void ResetMainPanel(PanelState *Pnl)
{
    Pnl->Choice = 1;
    Pnl->KeyPress = KEY_NONE;
    Pnl->RUNNING = true;
}

void STR_FillRect(int x, int y, int w, int h, int color)
{
    SetFBColor(color, color);
    gotoxy(x, y++);
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            putchar('\xDB');
        }
        gotoxy(x, y++);
    }
}



int STR_VerticalSelectCourse(int max, int x, int y, int choice, int C_Option, int T_Color, int SColor, int DColor, char *Header, Course_Details Course[50])
{
    char name[30];
    int i = 0;

    // Setting Contents

    STR_PrintStringinRect(x, y, C_Option, TITLESTRING, T_Color, Header);

    // HEADER
    if (C_Option == STATIC)
    {
            gotoxy(x, whereY() + 1);
            SetFBColor(CurColor, BLACK);
            printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB");
    }
    else if (C_Option == MYRIAD)
    {
            gotoxy(x, whereY() + 1);
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            putchar('\xC8');
            for (int i = 0; i < 24; i++)
            {
                STR_ColorIncrease(&CurColor);
                SetFBColor(CurColor, BLACK);
                putchar('\xCD');
            }
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            putchar('\xBC');
    }
    else if (C_Option == GRADATION)
    {
            gotoxy(x, whereY() + 1);
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            printf("\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC");
    }
    y += 3;
    for (int i = 1; i <= max; ++i){
        if (i == choice){
            STR_PrintStringinRect(x, y, C_Option, CONTENTSTRING, SColor, Course[i].CourseName);
            gotoX(x+1);
            SetFBColor(SColor, BLACK);
            putchar('\x1A');
            ResetColors();
        }
        else{
            STR_PrintStringinRect(x, y, C_Option, CONTENTSTRING, DColor, Course[i].CourseName);
        }
        y++;
    }
    
        
    // FOOTER
    
    if (C_Option == STATIC){
        gotoxy(x, whereY()+1);
        SetFBColor(CurColor, BLACK);
        printf("\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC");
    }
    else if (C_Option == MYRIAD){
        gotoxy(x, whereY()+1);
        STR_ColorIncrease(&CurColor);
        SetFBColor(CurColor, BLACK);
        putchar('\xC8');
        for (int i = 0; i < 24; i++)
        {
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            putchar('\xCD');
        }
        STR_ColorIncrease(&CurColor);
        SetFBColor(CurColor, BLACK);
        putchar('\xBC');
    }
    else if (C_Option == GRADATION){
        gotoxy(x, whereY() + 1);
        STR_ColorIncrease(&CurColor);
        SetFBColor(CurColor, BLACK);
        printf("\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC");
    }

    return (0);
}


int Load_Course(char *filename, Course_Details Course[50])
{
    if (CheckFile(filename)){
        FILE *temp = fopen(filename, "r");
        Course_Details Temp;
        int i = 0;
        int max = 0;

        while (fscanf(temp, "\n%49[^|]|%d|%d", Temp.CourseName, &Temp.CourseTuition, &Temp.CourseSubjectCount) == 3){
            ++max;
            strcpy(Course[max].CourseName, Temp.CourseName);
            Course[max].CourseTuition = Temp.CourseTuition;
            Course[max].CourseSubjectCount;
        }

        return (max);
    }

    return (-1);
}

int Load_Payment(char *filename, Student_Payment Student[30])
{
    if (CheckFile(filename)){
        FILE *temp = fopen(filename, "r");
        Student_Info Temp;
        int i = 0;
        int max = 0;

        while (fscanf(temp, "\n%9[^|]|%49[^|]|%49[^|]|%49[^|]|%49[^|]|%49[^|]|%d|%49[^\n]", 
        Temp.User.ID, Temp.User.Username, Temp.User.Password, 
        Temp.Name.FName, Temp.Name.LName, Temp.Name.MName, &Temp.Balance_T, Temp.CourseE) == 8){
            ++max;
            Student[max].User = Temp.User;
            Student[max].Name = Temp.Name;
            Student[max].Balance = Temp.Balance_T;
            strcpy(Student[max].Course, Temp.CourseE);
        }

        return (max);
    }

    return (-1);
}

int Load_PaymentString(char *filename, char *key, Student_Payment Student[30])
{
    if (CheckFile(filename)){
        FILE *temp = fopen(filename, "r");
        Student_Info Temp;
        int i = 0;
        int max = 0;

        while (fscanf(temp, "\n%9[^|]|%49[^|]|%49[^|]|%49[^|]|%49[^|]|%49[^|]|%d|%49[^\n]",
                      Temp.User.ID, Temp.User.Username, Temp.User.Password,
                      Temp.Name.FName, Temp.Name.LName, Temp.Name.MName, &Temp.Balance_T, Temp.CourseE) == 8)
        {
            if (strstr(Temp.Name.LName, key) || strstr(Temp.Name.FName, key)){
                ++max;
                strcpy(Student[max].User.ID, Temp.User.ID);
                strcpy(Student[max].User.Username, Temp.User.Username);
                strcpy(Student[max].User.Password, Temp.User.Password);
                strcpy(Student[max].Name.FName, Temp.Name.FName);
                strcpy(Student[max].Name.LName, Temp.Name.LName);
                strcpy(Student[max].Name.MName, Temp.Name.MName);
                Student[max].Balance = Temp.Balance_T;
                strcpy(Student[max].Course, Temp.CourseE);
            }
        }

        return (max);
    }

    return (-1);
}

int STR_VerticalSelectPayer(int max, int x, int y, int choice, int C_Option, int T_Color, int SColor, int DColor, char *Header, Student_Payment Student[30])
{
    char tempname[100];
    int i = 0;

    // Setting Contents

    STR_PrintStringinRect(x, y, C_Option, TITLESTRING, T_Color, Header);

    // HEADER
    if (C_Option == STATIC)
    {
            gotoxy(x, whereY() + 1);
            SetFBColor(CurColor, BLACK);
            printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB");
    }
    else if (C_Option == MYRIAD)
    {
            gotoxy(x, whereY() + 1);
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            putchar('\xC8');
            for (int i = 0; i < 24; i++)
            {
                STR_ColorIncrease(&CurColor);
                SetFBColor(CurColor, BLACK);
                putchar('\xCD');
            }
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            putchar('\xBC');
    }
    else if (C_Option == GRADATION)
    {
            gotoxy(x, whereY() + 1);
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            printf("\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC");
    }
    y += 3;
    for (int i = 1; i <= max; ++i){
        sprintf(tempname, "%s, %s %c.", Student[i].Name.LName, Student[i].Name.FName, Student[i].Name.MName[0]);
        if (i == choice){
            STR_PrintStringinRect(x, y, C_Option, CONTENTSTRING, SColor, tempname);
            gotoX(x+1);
            SetFBColor(SColor, BLACK);
            putchar('\x1A');
            ResetColors();
        }
        else{
            STR_PrintStringinRect(x, y, C_Option, CONTENTSTRING, DColor, tempname);
        }
        y++;
    }
    
        
    // FOOTER
    
    if (C_Option == STATIC){
        gotoxy(x, whereY()+1);
        SetFBColor(CurColor, BLACK);
        printf("\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC");
    }
    else if (C_Option == MYRIAD){
        gotoxy(x, whereY()+1);
        STR_ColorIncrease(&CurColor);
        SetFBColor(CurColor, BLACK);
        putchar('\xC8');
        for (int i = 0; i < 24; i++)
        {
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            putchar('\xCD');
        }
        STR_ColorIncrease(&CurColor);
        SetFBColor(CurColor, BLACK);
        putchar('\xBC');
    }
    else if (C_Option == GRADATION){
        gotoxy(x, whereY() + 1);
        STR_ColorIncrease(&CurColor);
        SetFBColor(CurColor, BLACK);
        printf("\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC");
    }

    return (0);
}


int Load_Message(char *filename, Message_Details MessageList[30])
{
    if (CheckFile(filename)){
        FILE *temp = fopen(filename, "r");
        Message_Details Temp;
        int i = 0;
        int max = 0;

        while (fscanf(temp, "\n%49[^|]|%49[^|]|%49[^|]|%255[^\n]", Temp.From, Temp.To,
                Temp.Subject, Temp.Content) == 4){
            ++max;
            strcpy(MessageList[max].From , Temp.From);
            strcpy(MessageList[max].To , Temp.To);
            strcpy(MessageList[max].Subject , Temp.Subject);
            strcpy(MessageList[max].Content , Temp.Content);
        }

        return (max);
    }

    return (-1);
}

int STR_VerticalSelectMessages(int max, int x, int y, int choice, int C_Option, int T_Color, int SColor, int DColor, char *Header, Message_Details MessageList[50])
{
    char tempname[100];
    int i = 0;

    // Setting Contents

    STR_PrintStringinRect(x, y, C_Option, TITLESTRING, T_Color, Header);

    // HEADER
    if (C_Option == STATIC)
    {
            gotoxy(x, whereY() + 1);
            SetFBColor(CurColor, BLACK);
            printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB");
    }
    else if (C_Option == MYRIAD)
    {
            gotoxy(x, whereY() + 1);
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            putchar('\xC8');
            for (int i = 0; i < 24; i++)
            {
                STR_ColorIncrease(&CurColor);
                SetFBColor(CurColor, BLACK);
                putchar('\xCD');
            }
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            putchar('\xBC');
    }
    else if (C_Option == GRADATION)
    {
            gotoxy(x, whereY() + 1);
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            printf("\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC");
    }
    y += 3;
    for (int i = 1; i <= max; ++i){
        sprintf(tempname, "From: %s To: %s Subject: %s", MessageList[i].From, MessageList[i].To, MessageList[i].Subject);
        if (i == choice){
            STR_PrintStringinRect(x, y, C_Option, CONTENTSTRING, SColor, tempname);
            gotoX(x+1);
            SetFBColor(SColor, BLACK);
            putchar('\x1A');
            ResetColors();
        }
        else{
            STR_PrintStringinRect(x, y, C_Option, CONTENTSTRING, DColor, tempname);
        }
        y++;
    }
    
        
    // FOOTER
    
    if (C_Option == STATIC){
        gotoxy(x, whereY()+1);
        SetFBColor(CurColor, BLACK);
        printf("\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC");
    }
    else if (C_Option == MYRIAD){
        gotoxy(x, whereY()+1);
        STR_ColorIncrease(&CurColor);
        SetFBColor(CurColor, BLACK);
        putchar('\xC8');
        for (int i = 0; i < 24; i++)
        {
            STR_ColorIncrease(&CurColor);
            SetFBColor(CurColor, BLACK);
            putchar('\xCD');
        }
        STR_ColorIncrease(&CurColor);
        SetFBColor(CurColor, BLACK);
        putchar('\xBC');
    }
    else if (C_Option == GRADATION){
        gotoxy(x, whereY() + 1);
        STR_ColorIncrease(&CurColor);
        SetFBColor(CurColor, BLACK);
        printf("\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC");
    }

    return (0);
}
