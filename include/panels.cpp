#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <assert.h>
#include <time.h>
#include <conio.h>

#include "tools.h"
#include "camera.h"
#include "states.h"
#include "keys.h"
#include "types.h"
#include "neotools.h"
#include "dsa.h"
#include "panels.h"

void ClearPanel(void)
{
    STR_ClearRect(3, 6, 50, 15);
    STR_ClearRect(95, 6, 50, 15);
}

int LoginAccount(Credentials *user, DataBases *MainDB)
{
    char temp[50];
    char tempid[21], tempname[21], temppass[21];
    int flag;

    // strcat(MainDB->SystemPath, "Credentials.dat");
    if (!strcmp(user->Username, "admin") && !strcmp(user->Password, "admin")){
        strcpy(user->ID, "admin");
        return (ADMIN);
    }
    else {
        sprintf(temp, "%sCredentials.dat", MainDB->SystemPath);
        MainDB->MainData = fopen(temp, "r");
        while (fscanf(MainDB->MainData, "\n%20[^|]|%20[^|]|%20[^\n]", tempid, tempname, temppass) == 3){
            if ((!strcmp(user->Username, tempname) || !strcmp(user->Username, tempid))
                && !strcmp(user->Password, temppass)){
                fclose(MainDB->MainData);
                strcpy(user->ID, tempid);
                strcpy(user->Username, tempname);
                strcpy(user->Password, temppass);
                flag = GetLoginType(user->ID);
                return (flag);
            }
        }
        fclose(MainDB->MainData);
    }

    // fclose(MainDB->MainData);
    return (-1);
} // FINISHED!

void AdminPanel(Credentials *User, PanelState *Pnl, DataBases *MainDB)
{
    Credentials newUser;
    Credentials editUser;
    bool AccCreated = false, edited = false, s_found = false;
    int choice = 1, keypress = KEY_NONE, ID_TYPE = STUDENT_T;
    char path[50];
    char temppath[50];
    Course_Details Course;
    Course_Details TempCourse;
    int ty, ay;

    clrscr();
    while (Pnl->RUNNING){
        // Draw
        STR_ViewDefBoarder(LIGHTRED, STATIC);
        STR_DisplayTime(95, 1, LIGHTGREEN, STATIC);
        STR_VerticalSelect(9, 22, 6, Pnl->Choice, STATIC, LIGHTRED, LIGHTGREEN, RED, User->Username,
                           "View All Accounts", "Register Account", "Edit Account", 
                           "Delete Account", "Manage Courses", "Manage Subjects", "Inbox", "Logout");

        // Input
        Pnl->KeyPress = STR_GetKeyPress();
		if (KEY_NONE != Pnl->KeyPress){
            STR_LinearSelect(&Pnl->Choice, Pnl->KeyPress, 1, 8);
        }

        // Events
        // RETURN KEY EVENTS
        if (KEY_RETURN == Pnl->KeyPress)
        {
            Sleep(300);
            switch(Pnl->Choice){
				case 1: // VIEW ALL ACCOUNTS    !
                    ty = 6;
                    sprintf(path, "%sCredentials.dat", MainDB->SystemPath);
                    STR_PrintStringinRect(95, ty++, STATIC, TITLESTRING, LIGHTGREEN, "All Accounts");
                    ty = 8;
                    if (CheckFile(path)){
                        MainDB->MainData = fopen(path, "r");
                        while (fscanf(MainDB->MainData, "\n%20[^|]|%20[^|]|%20[^\n]", newUser.ID, newUser.Username, newUser.Password) == 3){
                            STR_PrintStringinRect(95, ty++, STATIC, CONTENTSTRING, ty, newUser.ID);
                            STR_PrintStringinRect(95, ty++, STATIC, CONTENTSTRING, ty, newUser.Username);
                            STR_PrintStringinRect(95, ty++, STATIC, CONTENTSTRING, ty, newUser.Password);
                        }
                        fclose(MainDB->MainData);
                    }
                    else {
                        MessageBox(NULL, "Sorry Something Went Wrong with the the Database!", "Information", MB_ICONINFORMATION | MB_OK);
                    }
                    gotoxy(95, ++ty);
                    system("PAUSE");
                    STR_ClearRect(95, 6, 40, 32);
                    clrscr();
                    break;
                case 2: // REGISTER   !
                    STR_ClearRect(22, 6, 40, 20);
                    AccCreated = false;
                    while (!AccCreated){
                        // Draw
                        // STR_ClearRect(22, 6, 35, 35);
                        STR_ViewDefBoarder(LIGHTAQUA, STATIC);
                        STR_DisplayTime(95, 1, LIGHTYELLOW, STATIC);
                        STR_VerticalSelect(6, 22, 6, choice, STATIC, LIGHTRED, LIGHTGREEN, RED, "ACCOUNT TYPE",
                                           "ADMIN ACCOUNT",
                                           "TEACHER ACCOUNT",
                                           "CASHIER ACCOUNT",
                                           "LIBRARIAN ACCOUNT",
                                           "INVENTORY ACCOUNT");

                        // Input
                        keypress = STR_GetKeyPress();
                        if (KEY_NONE != keypress){
                            STR_LinearSelect(&choice, keypress, 1, 5);
                        }

                        // RETURN KEY EVENTS
                        if (KEY_RETURN == keypress){
                            Sleep(300);
                            switch(choice){
                                case 1:
                                    ID_TYPE = ADMIN;
                                    break;
                                case 2:
                                    ID_TYPE = TEACHER;
                                    break;
                                case 3:
                                    ID_TYPE = CASHIER;
                                    break;
                                case 4:
                                    ID_TYPE = LIBRARY;
                                    break;
                                case 5:
                                    ID_TYPE = INVENTORY;
                                    break;
                            }
                            s_found = false;
                            sprintf(newUser.ID, "%s", Gen_ID(ID_TYPE));
                            sprintf(path, "%sCredentials.dat", MainDB->SystemPath);
                            do {
                                gotoxy(95, 6);
                                STR_PrintStringinRect(95, 6, STATIC, TITLESTRING, LIGHTGREEN, "Create Account");
                                STR_PrintStringinRect(95, 8, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Username: ");
                                STR_PrintStringinRect(95, 9, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                                gotoxy(102, 10);
                                Sleep(300);
                                STR_GetStateStringWithTime(newUser.Username, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                                STR_PrintStringinRect(95, 11, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Password: ");
                                STR_PrintStringinRect(95, 12, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                                gotoxy(102, 13);
                                Sleep(300);
                                STR_GetStateStringWithTime(newUser.Password, CHAR_ASTERISK, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                                Sleep(300);
                                if (CheckString(path, newUser.Username) || CheckString(path, newUser.Password) || CheckString(path, newUser.ID)){
                                    MessageBox(NULL, "Sorry! That Username/Password is Unavalable!", "Warning", MB_ICONINFORMATION | MB_OK);
                                }
                                else {
                                    s_found = true;
                                }
                            } while (!s_found);
                            

                            sprintf(path, "%sCredentials.dat", MainDB->SystemPath);
                            if (CheckFile(path)){
                                MainDB->MainData = fopen(path, "a");
                            }
                            else {
                                MainDB->MainData = fopen(path, "w");
                            }
                            fprintf(MainDB->MainData, "%s|%s|%s\n", newUser.ID, newUser.Username, newUser.Password);
                            fclose(MainDB->MainData);
                            if (MessageBox(NULL, "Account Successfully Created!", "Information", MB_ICONINFORMATION | MB_OK)){
                                AccCreated = true;
                            }
                            STR_ClearRect(95, 6, 40, 15);
                        }
                        
                        // Simulate FPS
                        STR_SimulateFPS(30);
                    }
                    break;
                case 3: // EDIT ACCOUNT   !
                    AccCreated = false;
                    gotoxy(95, 6);
                    STR_PrintStringinRect(95, 6, STATIC, TITLESTRING, LIGHTGREEN, "Edit Account");
                    STR_PrintStringinRect(95, 8, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Username: ");
                    STR_PrintStringinRect(95, 9, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                    gotoxy(102, 10);
                    Sleep(300);
                    STR_GetStateStringWithTime(newUser.Username, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                    STR_PrintStringinRect(95, 11, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Password: ");
                    STR_PrintStringinRect(95, 12, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                    gotoxy(102, 13);
                    Sleep(300);
                    STR_GetStateStringWithTime(newUser.Password, CHAR_ASTERISK, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                    Sleep(300);

                    sprintf(path, "%sCredentials.dat", MainDB->SystemPath);
                    sprintf(temppath, "%TempData.dat", MainDB->SystemPath);
                    MainDB->MainData = fopen(path, "r");
                    MainDB->TempData = fopen(temppath, "w");

                    if (MainDB->MainData == NULL){
                        MessageBox(NULL, "Wrong File Operations!", "Information", MB_ICONINFORMATION | MB_OK);
                    }
                   

                    while (fscanf(MainDB->MainData, "\n%20[^|]|%20[^|]|%20[^\n]", editUser.ID, editUser.Username, editUser.Password) == 3){
                        if (((!strcmp(newUser.Username, editUser.Username)) || (!strcmp(newUser.Username, editUser.ID))) && !strcmp(newUser.Password, editUser.Password)){
                            AccCreated = true;
                            STR_ClearRect(95, 6, 40, 15);
                            STR_PrintStringinRect(95, 6, STATIC, TITLESTRING, LIGHTGREEN, "Change Info");
                            STR_PrintStringinRect(95, 8, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter New Username: ");
                            STR_PrintStringinRect(95, 9, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                            gotoxy(102, 10);
                            Sleep(300);
                            STR_GetStateStringWithTime(editUser.Username, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                            STR_PrintStringinRect(95, 11, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter New Password: ");
                            STR_PrintStringinRect(95, 12, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                            gotoxy(102, 13);
                            Sleep(300);
                            STR_GetStateStringWithTime(editUser.Password, CHAR_ASTERISK, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                            Sleep(300);

                            fprintf(MainDB->TempData, "%s|%s|%s\n", editUser.ID, editUser.Username, editUser.Password);
                        }
                        else {
                            fprintf(MainDB->TempData, "%s|%s|%s\n", editUser.ID, editUser.Username, editUser.Password);
                        }
                    }
                    fclose(MainDB->MainData);
                    fclose(MainDB->TempData);
                    remove(path);
                    rename(temppath, path);
                    if (AccCreated){
                        MessageBox(NULL, "Account Successfully Edited!", "Information", MB_ICONINFORMATION | MB_OK);
                        AccCreated = false;
                    }
                    else {
                        MessageBox(NULL, "Account Not Found!", "Information", MB_ICONWARNING | MB_OK);
                        AccCreated = false;
                    }
                    STR_ClearRect(95, 6, 40, 15);
                    break;
                case 4: // DELETE ACCOUNT    !
                    AccCreated = false;
                    gotoxy(95, 6);
                    STR_PrintStringinRect(95, 6, STATIC, TITLESTRING, LIGHTGREEN, "Delete Account");
                    STR_PrintStringinRect(95, 8, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Username: ");
                    STR_PrintStringinRect(95, 9, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                    gotoxy(102, 10);
                    Sleep(300);
                    STR_GetStateStringWithTime(newUser.Username, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                    STR_PrintStringinRect(95, 11, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Password: ");
                    STR_PrintStringinRect(95, 12, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                    gotoxy(102, 13);
                    Sleep(300);
                    STR_GetStateStringWithTime(newUser.Password, CHAR_ASTERISK, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                    Sleep(300);

                    sprintf(path, "%sCredentials.dat", MainDB->SystemPath);
                    sprintf(temppath, "%TempData.dat", MainDB->SystemPath);
                    MainDB->MainData = fopen(path, "r");
                    MainDB->TempData = fopen(temppath, "w");

                    if (MainDB->MainData == NULL){
                        MessageBox(NULL, "Wrong File Operations!", "Information", MB_ICONINFORMATION | MB_OK);
                    }
                   

                    while (fscanf(MainDB->MainData, "\n%20[^|]|%20[^|]|%20[^\n]", editUser.ID, editUser.Username, editUser.Password) == 3){
                        if (((!strcmp(newUser.Username, editUser.Username)) || (!strcmp(newUser.Username, editUser.ID))) && !strcmp(newUser.Password, editUser.Password)){
                            AccCreated = true;
                        }
                        else {
                            fprintf(MainDB->TempData, "%s|%s|%s\n", editUser.ID, editUser.Username, editUser.Password);
                        }
                    }
                    fclose(MainDB->MainData);
                    fclose(MainDB->TempData);
                    remove(path);
                    rename(temppath, path);
                    if (AccCreated){
                        MessageBox(NULL, "Account Successfully Deleted!", "Information", MB_ICONINFORMATION | MB_OK);
                        AccCreated = false;
                    }
                    else {
                        MessageBox(NULL, "Account Not Found!", "Information", MB_ICONWARNING | MB_OK);
                        AccCreated = false;
                    }
                    STR_ClearRect(95, 6, 40, 15);
                    break;
                case 5: // MANAGE COURSES
                    clrscr();
                    AccCreated = false;
                    while (!AccCreated){
                        // Draw
                        STR_ViewDefBoarder(LIGHTAQUA, STATIC);
                        STR_DisplayTime(95, 1, LIGHTYELLOW, STATIC);
                        STR_VerticalSelect(6, 22, 6, Pnl->Choice, STATIC, LIGHTRED, LIGHTGREEN, RED,
                                           "Manage Courses",
                                           "View All Courses",
                                           "Add New Course",
                                           "Edit Course",
                                           "Delete Course",
                                           "Exit");

                        // Input
                        Pnl->KeyPress = STR_GetKeyPress();
                        if (KEY_NONE != Pnl->KeyPress){
                            STR_LinearSelect(&Pnl->Choice, Pnl->KeyPress, 1, 5);
                        }

                        // Events

                        // RETURN KEY EVENTS
                        if (KEY_RETURN == Pnl->KeyPress){
                            switch(Pnl->Choice){
                                case 1: // VIEW ALL COURSES
                                    STR_PrintStringinRect(95, 6, STATIC, TITLESTRING, LIGHTGREEN, "Course List");
                                    ay = whereY();
                                    sprintf(path, "%sCourseList.dat", MainDB->CoursesPath);
                                    if (!CheckFile(path)){
                                        MessageBox(NULL, "Something Went Wrong!", "Warning", MB_ICONWARNING | MB_OK);
                                    }
                                    else {
                                        MainDB->MainData = fopen(path, "r");
                                        while (fscanf(MainDB->MainData, "\n%49[^|]|%d|%d", Course.CourseName, &Course.CourseTuition, &Course.CourseSubjectCount) == 3){
                                            STR_ColorIncrease(&keypress);
                                            STR_PrintStringinRect(95, ++ay, STATIC, CONTENTSTRING, keypress, Course.CourseName);
                                            sprintf(path, "%d", Course.CourseTuition);
                                            STR_PrintStringinRect(95, ++ay, STATIC, CONTENTSTRING, keypress, path);
                                            sprintf(path, "%d", Course.CourseSubjectCount);
                                            STR_PrintStringinRect(95, ++ay, STATIC, CONTENTSTRING, keypress, path);
                                        }
                                        fclose(MainDB->MainData);
                                    }
                                    gotoxy(95, ++ay+1);
                                    SetFBColor(keypress, BLACK);
                                    system("PAUSE");
                                    STR_ClearRect(95, 6, 50, 15);
                                    break;
                                case 2: // ADD NEW COURSE
                                    gotoxy(95, 6);
                                    STR_PrintStringinRect(95, 6, STATIC, TITLESTRING, LIGHTGREEN, "Add New Course");
                                    STR_PrintStringinRect(95, 8, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Course Name: ");
                                    STR_PrintStringinRect(95, 9, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                                    gotoxy(102, 10);
                                    Sleep(300);
                                    STR_GetStateStringWithTime(Course.CourseName, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                                    STR_PrintStringinRect(95, 11, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Tuition Fee: ");
                                    STR_PrintStringinRect(95, 12, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                                    gotoxy(102, 13);
                                    Sleep(300);
                                    STR_GetStateIntWithTime(&Course.CourseTuition, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                                    Sleep(300);
                                    
                                    sprintf(path, "%sCourseList.dat", MainDB->CoursesPath);
                                    sprintf(temppath, "%s%s.dat", MainDB->CoursesPath, Course.CourseName);
                                    if (CheckFile(temppath)){
                                        MessageBox(NULL, "Sorry That Course Already Exist!", "Warning", MB_ICONWARNING | MB_OK);
                                    }
                                    else {
                                        MainDB->MainData = fopen(temppath, "w");
                                        fprintf(MainDB->MainData, "%s|%d|%d\n", Course.CourseName, Course.CourseTuition, 0);
                                        fclose(MainDB->MainData);
                                        if (CheckFile(path)){
                                            MainDB->MainData = fopen(path, "a");
                                        }
                                        else {
                                            MainDB->MainData = fopen(path, "w");
                                        }
                                        fprintf(MainDB->MainData, "%s|%d|%d\n", Course.CourseName, Course.CourseTuition, 0);
                                        fclose(MainDB->MainData);
                                        MessageBox(NULL, "Course Successfully Added!", "Information", MB_ICONINFORMATION | MB_OK);
                                    }
	                                STR_ClearRect(95, 6, 50, 15);

                                    break;
                                case 3: // EDIT COURSE
                                    gotoxy(95, 6);
                                    STR_PrintStringinRect(95, 6, STATIC, TITLESTRING, LIGHTGREEN, "Edit Course");
                                    STR_PrintStringinRect(95, 8, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Course Name: ");
                                    STR_PrintStringinRect(95, 9, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                                    gotoxy(102, 10);
                                    Sleep(300);
                                    STR_GetStateStringWithTime(newUser.Username, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                                    sprintf(path, "%s%s.dat", MainDB->CoursesPath, newUser.Username);
                                    if (!CheckFile(path)){
                                        MessageBox(NULL, "Sorry That Course Doesn't Exist!", "Warning", MB_ICONWARNING | MB_OK);
                                    }
                                    else {
                                        STR_PrintStringinRect(95, 6, STATIC, TITLESTRING, LIGHTGREEN, "Edit Course");
                                        STR_PrintStringinRect(95, 8, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter New Course Name: ");
                                        STR_PrintStringinRect(95, 9, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                                        gotoxy(102, 10);
                                        Sleep(300);
                                        STR_GetStateStringWithTime(Course.CourseName, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                                        STR_PrintStringinRect(95, 11, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter New Tuition Fee: ");
                                        STR_PrintStringinRect(95, 12, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                                        gotoxy(102, 13);
                                        Sleep(300);
                                        STR_GetStateIntWithTime(&Course.CourseTuition, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                                        Sleep(300);
                                        
                                        sprintf(path, "%sCourseList.dat", MainDB->CoursesPath);
                                        sprintf(temppath, "%stemp.dat", MainDB->CoursesPath);
                                        MainDB->MainData = fopen(path, "r");
                                        MainDB->TempData = fopen(temppath, "w");
                                        while (fscanf(MainDB->MainData, "\n%49[^|]|%d|%d", TempCourse.CourseName, &TempCourse.CourseTuition, &TempCourse.CourseSubjectCount) == 3){
                                            if (!strcmp(newUser.Username, TempCourse.CourseName)){
                                                fprintf(MainDB->TempData, "%s|%d|%d\n", Course.CourseName, Course.CourseTuition, TempCourse.CourseSubjectCount);
                                            }
                                            else {
                                                fprintf(MainDB->TempData, "%s|%d|%d\n", TempCourse.CourseName, TempCourse.CourseTuition, TempCourse.CourseSubjectCount);
                                            }
                                        }
                                        fclose(MainDB->MainData);
                                        fclose(MainDB->TempData);
                                        remove(path);
                                        rename(temppath, path);

                                        sprintf(path, "%s%s.dat", MainDB->CoursesPath, newUser.Username);
                                        sprintf(temppath, "%stemp.dat", MainDB->CoursesPath);
                                        MainDB->MainData = fopen(path, "r");
                                        MainDB->TempData = fopen(temppath, "w");
                                        while (fscanf(MainDB->MainData, "\n%49[^|]|%d|%d", TempCourse.CourseName, &TempCourse.CourseTuition, &TempCourse.CourseSubjectCount) == 3){
                                            if (!strcmp(newUser.Username, TempCourse.CourseName)){
                                                fprintf(MainDB->TempData, "%s|%d|%d\n", Course.CourseName, Course.CourseTuition, TempCourse.CourseSubjectCount);
                                            }
                                            else {
                                                fprintf(MainDB->TempData, "%s|%d|%d\n", TempCourse.CourseName, TempCourse.CourseTuition, TempCourse.CourseSubjectCount);
                                            }
                                        }
                                        fclose(MainDB->MainData);
                                        fclose(MainDB->TempData);
                                        remove(path);
                                        sprintf(path, "%s%s.dat", MainDB->CoursesPath, Course.CourseName);
                                        rename(temppath, path);
                                        MessageBox(NULL, "Course Successfully Edited!", "Information", MB_ICONINFORMATION | MB_OK);
                                    }
	                                STR_ClearRect(95, 6, 50, 15);

                                    break;
                                case 4: // DELETE COURSE
                                    gotoxy(95, 6);
                                    STR_PrintStringinRect(95, 6, STATIC, TITLESTRING, LIGHTGREEN, "Edit Course");
                                    STR_PrintStringinRect(95, 8, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Course Name: ");
                                    STR_PrintStringinRect(95, 9, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                                    gotoxy(102, 10);
                                    Sleep(300);
                                    STR_GetStateStringWithTime(Course.CourseName, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                                    sprintf(path, "%s%s.dat", MainDB->CoursesPath, Course.CourseName);
                                    if (!CheckFile(path)){
                                        MessageBox(NULL, "Sorry That Course Doesn't Exist!", "Warning", MB_ICONWARNING | MB_OK);
                                    }
                                    else {
                                        if (MessageBox(NULL, "Are You Sure You want to Delete that Course?", "Information", MB_ICONINFORMATION | MB_YESNO) == 6){
                                            sprintf(path, "%sCourseList.dat", MainDB->CoursesPath);
                                            sprintf(temppath, "%stemp.dat", MainDB->CoursesPath);
                                            MainDB->MainData = fopen(path, "r");
                                            MainDB->TempData = fopen(temppath, "w");
                                            while (fscanf(MainDB->MainData, "\n%49[^|]|%d|%d", TempCourse.CourseName, &TempCourse.CourseTuition, &TempCourse.CourseSubjectCount) == 3){
                                                if (!strcmp(Course.CourseName, TempCourse.CourseName)){

                                                }
                                                else {
                                                    fprintf(MainDB->TempData, "%s|%d|%d\n", TempCourse.CourseName, TempCourse.CourseTuition, TempCourse.CourseSubjectCount);
                                                }
                                            }
                                            fclose(MainDB->MainData);
                                            fclose(MainDB->TempData);
                                            remove(path);
                                            rename(temppath, path);

                                            sprintf(path, "%s%s.dat", MainDB->CoursesPath, Course.CourseName);
                                            remove(path);
                                            MessageBox(NULL, "Course Successfully Deleted!", "Information", MB_ICONINFORMATION | MB_OK);
                                        }
                                        else {
                                            MessageBox(NULL, "Course Not Deleted!", "Information", MB_ICONINFORMATION | MB_OK);
                                        }
                                    }
	                                STR_ClearRect(95, 6, 50, 15);

                                    break;
                                case 5: // EXIT
                                    AccCreated = true;
                                    break;
                            }
                        }
                        
                        // Simulate FPS
                        STR_SimulateFPS(30);
                    }
                    break;
                case 6: // MANAGE SUBJECTS !
                    clrscr();
                    AccCreated = false;
                    Pnl->Choice = 1;
                    while (!AccCreated){
                        // Draw
                        STR_ViewDefBoarder(LIGHTAQUA, STATIC);
                        STR_DisplayTime(95, 1, LIGHTYELLOW, STATIC);
                        STR_VerticalSelect(6, 22, 6, Pnl->Choice, STATIC, LIGHTRED, LIGHTGREEN, RED,
                                           "Manage Courses",
                                           "View All Subjects",
                                           "Add New Subject",
                                           "Edit Subject",
                                           "Delete Subject",
                                           "Exit");

                        // Input
                        Pnl->KeyPress = STR_GetKeyPress();
                        if (KEY_NONE != Pnl->KeyPress){
                            STR_LinearSelect(&Pnl->Choice, Pnl->KeyPress, 1, 5);
                        }

                        // RETURN KEY EVENTS
                        if (KEY_RETURN == Pnl->KeyPress){
                            switch(Pnl->Choice){
                                case 1: // VIEW ALL SUBJECTS
                                    gotoxy(95, 6);
                                    STR_PrintStringinRect(95, 6, STATIC, TITLESTRING, LIGHTGREEN, "View Subject");
                                    STR_PrintStringinRect(95, 8, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Course Name: ");
                                    STR_PrintStringinRect(95, 9, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                                    gotoxy(102, 10);
                                    Sleep(300);
                                    STR_GetStateStringWithTime(Course.CourseName, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);

                                    STR_ClearRect(95, 6, 50, 15);
                                    ay = whereY()-1;
                                    sprintf(path, "%s%s.dat", MainDB->CoursesPath, Course.CourseName);
                                    if (!CheckFile(path)){
                                        MessageBox(NULL, "No Registered Subjects Yet Or That Course Doesn't Exist!\nPlease Add New Subject!", "Warning", MB_ICONWARNING | MB_OK);
                                    }
                                    else {
                                        STR_PrintStringinRect(95, 6, STATIC, TITLESTRING, LIGHTGREEN, "Subject List");
                                        ay = whereY()-1;
                                        STR_ColorIncrease(&keypress);
                                        MainDB->MainData = fopen(path, "r");
                                        fscanf(MainDB->MainData, "\n%49[^|]|%d|%d", Course.CourseName, &Course.CourseTuition, &Course.CourseSubjectCount);
                                        while (fscanf(MainDB->MainData, "\n%49[^\n]", Course.CourseName) == 1){
                                            STR_PrintStringinRect(95, ++ay, STATIC, CONTENTSTRING, keypress, Course.CourseName);
                                        }
                                        fclose(MainDB->MainData);
                                    }
                                    gotoxy(95, ay+3);
                                    SetFBColor(keypress, BLACK);
                                    system("PAUSE");
                                    STR_ClearRect(95, 6, 50, 35);
                                    break;
                                case 2: // ADD NEW SUBJECT
                                    gotoxy(95, 6);
                                    STR_PrintStringinRect(95, 6, STATIC, TITLESTRING, LIGHTGREEN, "Add New Course");
                                    STR_PrintStringinRect(95, 8, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Course Name: ");
                                    STR_PrintStringinRect(95, 9, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                                    gotoxy(102, 10);
                                    Sleep(300);
                                    STR_GetStateStringWithTime(Course.CourseName, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                                    
                                    sprintf(path, "%s%s.dat", MainDB->CoursesPath, Course.CourseName);
                                    if (!CheckFile(path)){
                                        MessageBox(NULL, "Sorry that course doesn't Exist!", "Warning", MB_ICONWARNING | MB_OK);
                                    }
                                    else {
                                        sprintf(path, "%sCourseList.dat", MainDB->CoursesPath);
                                        sprintf(temppath, "%stemp.dat", MainDB->CoursesPath);
                                        MainDB->MainData = fopen(path, "r");
                                        MainDB->TempData = fopen(temppath, "w");

                                        while (fscanf(MainDB->MainData, "\n%49[^|]|%d|%d", TempCourse.CourseName, &TempCourse.CourseTuition, &TempCourse.CourseSubjectCount) == 3){
                                            if (!strcmp(Course.CourseName, TempCourse.CourseName)){
                                                fprintf(MainDB->TempData, "%s|%d|%d\n", TempCourse.CourseName, TempCourse.CourseTuition, TempCourse.CourseSubjectCount + 1);
                                            }
                                            else {
                                                fprintf(MainDB->TempData, "%s|%d|%d\n", TempCourse.CourseName, TempCourse.CourseTuition, TempCourse.CourseSubjectCount);
                                            }
                                        }
                                        fclose(MainDB->MainData);
                                        fclose(MainDB->TempData);
                                        // MessageBox(NULL, path, "Warning", MB_OK);
                                        // MessageBox(NULL, temppath, "Warning", MB_OK);
                                        remove(path);
                                        rename(temppath, path);

                                        STR_PrintStringinRect(95, 6, STATIC, TITLESTRING, LIGHTGREEN, "Add Subject");
                                        STR_PrintStringinRect(95, 8, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Subject Name: ");
                                        STR_PrintStringinRect(95, 9, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                                        gotoxy(102, 10);
                                        Sleep(300);
                                        STR_GetStateStringWithTime(TempCourse.CourseName, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);

                                        sprintf(path, "%s%s.dat", MainDB->CoursesPath, Course.CourseName);
                                        MainDB->MainData = fopen(path, "a");
                                        fprintf(MainDB->MainData, "%s\n", TempCourse.CourseName);
                                        fclose(MainDB->MainData);
                                        MessageBox(NULL, "Subject Successfully Added!", "Information", MB_ICONINFORMATION | MB_OK);
                                    }
	                                STR_ClearRect(95, 6, 50, 15);

                                    break;
                                case 3: // EDIT SUBJECT
                                    edited = false;
                                    gotoxy(95, 6);
                                    STR_PrintStringinRect(95, 6, STATIC, TITLESTRING, LIGHTGREEN, "Edit Subject");
                                    STR_PrintStringinRect(95, 8, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Course Name: ");
                                    STR_PrintStringinRect(95, 9, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                                    gotoxy(102, 10);
                                    Sleep(300);
                                    STR_GetStateStringWithTime(newUser.Username, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                                    sprintf(path, "%s%s.dat", MainDB->CoursesPath, newUser.Username);
                                    if (!CheckFile(path)){
                                        MessageBox(NULL, "Sorry That Course Doesn't Exist!", "Warning", MB_ICONWARNING | MB_OK);
                                    }
                                    else {
                                        STR_PrintStringinRect(95, 6, STATIC, TITLESTRING, LIGHTGREEN, "Edit Course");
                                        STR_PrintStringinRect(95, 8, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Subject Name: ");
                                        STR_PrintStringinRect(95, 9, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                                        gotoxy(102, 10);
                                        Sleep(300);
                                        STR_GetStateStringWithTime(Course.CourseName, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                                        STR_PrintStringinRect(95, 11, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter New Name: ");
                                        STR_PrintStringinRect(95, 12, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                                        gotoxy(102, 13);
                                        Sleep(300);
                                        STR_GetStateStringWithTime(newUser.Username, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                                        Sleep(300);

                                        MainDB->MainData = fopen(path, "r");
                                        sprintf(temppath, "%stemp.dat", MainDB->CoursesPath);
                                        MainDB->TempData = fopen(temppath, "w");
                                        fscanf(MainDB->MainData, "\n%49[^|]|%d|%d", TempCourse.CourseName, &TempCourse.CourseTuition, &TempCourse.CourseSubjectCount);
                                        fprintf(MainDB->TempData, "%s|%d|%d\n", TempCourse.CourseName, TempCourse.CourseTuition, TempCourse.CourseSubjectCount);
                                        while (fscanf(MainDB->MainData, "\n%49[^\n]", TempCourse.CourseName) == 1){
                                            if (!strcmp(Course.CourseName, TempCourse.CourseName)){
                                                fprintf(MainDB->TempData, "%s\n", newUser.Username);
                                                edited = true;
                                            }
                                            else {
                                                fprintf(MainDB->TempData, "%s\n", TempCourse.CourseName);
                                            }
                                        }
                                        fclose(MainDB->MainData);
                                        fclose(MainDB->TempData);
                                        remove(path);
                                        rename(temppath, path);
                                        if (edited){
                                            MessageBox(NULL, "Subject Successfully Edited!", "Information", MB_ICONINFORMATION | MB_OK);
                                        }
                                        else {
                                            MessageBox(NULL, "Subject Not Found!", "Information", MB_ICONINFORMATION | MB_OK);
                                        }
                                    }
	                                STR_ClearRect(95, 6, 50, 15);

                                    break;
                                case 4: // DELETE SUBJECT
                                    edited = false;
                                    s_found = false;
                                    gotoxy(95, 6);
                                    STR_PrintStringinRect(95, 6, STATIC, TITLESTRING, LIGHTGREEN, "Delete Subject");
                                    STR_PrintStringinRect(95, 8, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Course Name: ");
                                    STR_PrintStringinRect(95, 9, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                                    gotoxy(102, 10);
                                    Sleep(300);
                                    STR_GetStateStringWithTime(newUser.Username, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                                    sprintf(path, "%s%s.dat", MainDB->CoursesPath, newUser.Username);
                                    if (!CheckFile(path)){
                                        MessageBox(NULL, "Sorry That Course Doesn't Exist!", "Warning", MB_ICONWARNING | MB_OK);
                                    }
                                    else {
                                        STR_PrintStringinRect(95, 6, STATIC, TITLESTRING, LIGHTGREEN, "Delete Course");
                                        STR_PrintStringinRect(95, 8, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Subject Name: ");
                                        STR_PrintStringinRect(95, 9, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                                        gotoxy(102, 10);
                                        Sleep(300);
                                        STR_GetStateStringWithTime(Course.CourseName, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);

                                        sprintf(temppath, "%stemp.dat", MainDB->CoursesPath);
                                        sprintf(path, "%s%s.dat", MainDB->CoursesPath, newUser.Username);
                                        MainDB->MainData = fopen(path, "r");
                                        MainDB->TempData = fopen(temppath, "w");
                                        fscanf(MainDB->MainData, "\n%49[^|]|%d|%d", TempCourse.CourseName, &TempCourse.CourseTuition, &TempCourse.CourseSubjectCount);
                                        fprintf(MainDB->TempData, "%s|%d|%d\n", TempCourse.CourseName, TempCourse.CourseTuition, TempCourse.CourseSubjectCount);
                                        while (fscanf(MainDB->MainData, "\n%49[^\n]", TempCourse.CourseName) == 1){
                                            if (!strcmp(Course.CourseName, TempCourse.CourseName)){
                                                edited = true;
                                            }
                                            else {
                                                fprintf(MainDB->TempData, "%s\n", TempCourse.CourseName);
                                            }
                                        }
                                        fclose(MainDB->MainData);
                                        fclose(MainDB->TempData);
                                        remove(path);
                                        rename(temppath, path);

                                        sprintf(path, "%sCourseList.dat", MainDB->CoursesPath);
                                        sprintf(temppath, "%stemp.dat", MainDB->CoursesPath);
                                        MainDB->MainData = fopen(path, "r");
                                        MainDB->TempData = fopen(temppath, "w");
                                        while (fscanf(MainDB->MainData, "\n%49[^|]|%d|%d", TempCourse.CourseName, &TempCourse.CourseTuition, &TempCourse.CourseSubjectCount) == 3){
                                            if (!strcmp(newUser.Username, TempCourse.CourseName)){
                                                fprintf(MainDB->TempData, "%s|%d|%d\n", TempCourse.CourseName, TempCourse.CourseTuition, TempCourse.CourseSubjectCount-1);
                                            }
                                            else {
                                                fprintf(MainDB->TempData, "%s|%d|%d\n", TempCourse.CourseName, TempCourse.CourseTuition, TempCourse.CourseSubjectCount);
                                            }
                                        }
                                        fclose(MainDB->MainData);
                                        fclose(MainDB->TempData);
                                        remove(path);
                                        rename(temppath, path);

                                        if (edited){
                                            MessageBox(NULL, "Subject Successfully Deleted!", "Information", MB_ICONINFORMATION | MB_OK);
                                        }
                                        else {
                                            MessageBox(NULL, "Subject Not Found!", "Information", MB_ICONINFORMATION | MB_OK);
                                        }
                                    }
	                                STR_ClearRect(95, 6, 50, 15);
                                    break;
                                case 5: // EXIT
                                    AccCreated = true;
                                    break;
                            }
                        }
                        
                        // Simulate FPS
                        STR_SimulateFPS(30);
                    }
                    break;
                case 7: // INBOX
                    PanelInbox(User, Pnl, MainDB);
                    break;
                case 8:
                    Pnl->RUNNING = false;
                    break;

			}
        }

        // Simulate FPS
        STR_SimulateFPS(10);
    }

    ResetMainPanel(Pnl);
}  // FINISHED!
void TeacherPanel(Credentials *User, PanelState *Pnl, DataBases *MainDB)
{
    clrscr();
    while (Pnl->RUNNING)
    {
        // Draw
        STR_ViewDefBoarder(LIGHTRED, STATIC);
        STR_DisplayTime(95, 1, LIGHTGREEN, STATIC);
        STR_VerticalSelect(6, 22, 6, Pnl->Choice, STATIC, LIGHTPURPLE, LIGHTGREEN, RED, User->Username,
                           "View Class List", "Record Attendance", "Record Activity", "View Inbox", "Logout");

        // Input
        Pnl->KeyPress = STR_GetKeyPress();
        if (KEY_NONE != Pnl->KeyPress)
        {
            STR_LinearSelect(&Pnl->Choice, Pnl->KeyPress, 1, 5);
        }

        // Events
        // RETURN KEY EVENTS
        if (KEY_RETURN == Pnl->KeyPress)
        {
            switch (Pnl->Choice)
            {
                case 1: // VIEW CLASS LIST    !
                    MessageBox(NULL, "Sorry! This Feature is Unavailable Due to Maintenance!\nSorry for the Inconveniece", "Information", MB_ICONWARNING | MB_OK);
                    break;
                case 2: // RECORD ATTENDANCE   !
                    MessageBox(NULL, "Sorry! This Feature is Unavailable Due to Maintenance!\nSorry for the Inconveniece", "Information", MB_ICONWARNING | MB_OK);
                    break;
                case 3: // RECORD ACTIVITY   !
                    MessageBox(NULL, "Sorry! This Feature is Unavailable Due to Maintenance!\nSorry for the Inconveniece", "Information", MB_ICONWARNING | MB_OK);
                    break;
                case 4: // VIEW INBOX !
                    MessageBox(NULL, "Sorry! This Feature is Unavailable Due to Maintenance!\nSorry for the Inconveniece", "Information", MB_ICONWARNING | MB_OK);
                    break;
                case 5: // LOGOUT
                    Pnl->RUNNING = false;
                    break;
            }
        }

        // Simulate FPS
        STR_SimulateFPS(10);
    }

    ResetMainPanel(Pnl);
} 
void StudentPanel(Credentials *User, PanelState *Pnl, DataBases *MainDB)
{
    Student_Info Temp;
    char path[50], temppath[50], tempname[50];
    char messagebox[500];

    clrscr();
    while (Pnl->RUNNING)
    {
        // Draw
        STR_ViewDefBoarder(LIGHTRED, STATIC);
        STR_DisplayTime(95, 1, LIGHTGREEN, STATIC);
        STR_VerticalSelect(6, 22, 6, Pnl->Choice, STATIC, LIGHTYELLOW, LIGHTGREEN, RED, User->Username,
                           "View Profile", "View Grade", "View Attendance", "View Inbox", "Logout");

        // Input
        Pnl->KeyPress = STR_GetKeyPress();
        if (KEY_NONE != Pnl->KeyPress)
        {
            STR_LinearSelect(&Pnl->Choice, Pnl->KeyPress, 1, 5);
        }

        // Events
        // RETURN KEY EVENTS
        if (KEY_RETURN == Pnl->KeyPress)
        {
            switch (Pnl->Choice)
            {
                case 1: // VIEW PROFILE    !
                    sprintf(path, "%sStudentList.dat", MainDB->StudentPath);

                    MainDB->MainData = fopen(path, "r");
                    if (MainDB->MainData != NULL){
                        while (fscanf(MainDB->MainData,"\n%9[^|]|%49[^|]|%49[^|]|%49[^|]|%d|%49[^|]|%d|%49[^\n]", 
                        Temp.User.ID, Temp.Name.FName, Temp.Name.LName, Temp.Name.MName, &Temp.Balance_T, 
                        Temp.CourseE, &Temp.Subjects, Temp.ProfilePic) == 8){
                            if (!strcmp(User->ID, Temp.User.ID)){
                                break;
                            }
                        }
                        fclose(MainDB->MainData);

                        sprintf(path, "%sTuition.dat", MainDB->CashierPath);
                        MainDB->MainData = fopen(path, "r");
                        while (fscanf(MainDB->MainData, "\n%49[^|]|%d", Temp.User.ID, &Temp.Balance_T) == 2){
                            if (!strcmp(Temp.User.ID, User->ID)){
                                break;
                            }
                        }
                        fclose(MainDB->MainData);

                        sprintf(messagebox, "ID: %s\nUsername: %s\nPassword: %s\nName: %s %c %s\nCourse: %s\nTuition Balance: %d\n",
                        User->ID, User->Username, User->Password, Temp.Name.FName, 
                        Temp.Name.MName[0], Temp.Name.LName, Temp.CourseE, Temp.Balance_T);
                        MessageBox(NULL, messagebox, "Information", MB_OK);
                    }
                    else {
                        MessageBox(NULL, "Sorry, No Data Available Yet!", "Warning", MB_ICONINFORMATION | MB_OK);
                    }
                    break;
                case 2: // VIEW GRADE   !
                    MessageBox(NULL, "Sorry! This Feature is Unavailable Due to Maintenance!\nSorry for the Inconveniece", "Information", MB_ICONWARNING | MB_OK);
                    break;
                case 3: // VIEW ATTENDANCE   !
                    MessageBox(NULL, "Sorry! This Feature is Unavailable Due to Maintenance!\nSorry for the Inconveniece", "Information", MB_ICONWARNING | MB_OK);
                    break;
                case 4: // VIEW INBOX !
                    PanelInbox(User, Pnl, MainDB);
                    break;
                case 5: // LOGOUT
                    Pnl->RUNNING = false;
                    break;
            }
        }

        // Simulate FPS
        STR_SimulateFPS(10);
    }

    ResetMainPanel(Pnl);
}
void LibrarianPanel(Credentials *User, PanelState *Pnl, DataBases *MainDB)
{
    clrscr();
    while (Pnl->RUNNING)
    {
        // Draw
        STR_ViewDefBoarder(LIGHTRED, STATIC);
        STR_DisplayTime(95, 1, LIGHTGREEN, STATIC);
        STR_VerticalSelect(7, 22, 6, Pnl->Choice, STATIC, LIGHTBLUE, LIGHTGREEN, RED, User->Username,
                           "View Account List", "View Logs", "Search Books", "Book Specification", "View Inbox", "Logout");

        // Input
        Pnl->KeyPress = STR_GetKeyPress();
        if (KEY_NONE != Pnl->KeyPress)
        {
            STR_LinearSelect(&Pnl->Choice, Pnl->KeyPress, 1, 6);
        }

        // Events
        // RETURN KEY EVENTS
        if (KEY_RETURN == Pnl->KeyPress)
        {
            switch (Pnl->Choice)
            {
                case 1: // VIEW ACCOUNTS LIST    !
                    MessageBox(NULL, "Sorry! This Feature is Unavailable Due to Maintenance!\nSorry for the Inconveniece", "Information", MB_ICONWARNING | MB_OK);
                    break;
                case 2: // VIEW LOGS   !
                    MessageBox(NULL, "Sorry! This Feature is Unavailable Due to Maintenance!\nSorry for the Inconveniece", "Information", MB_ICONWARNING | MB_OK);
                    break;
                case 3: // SEARCH BOOKS   !
                    MessageBox(NULL, "Sorry! This Feature is Unavailable Due to Maintenance!\nSorry for the Inconveniece", "Information", MB_ICONWARNING | MB_OK);
                    break;
                case 4: // BOOK SPECIFICATION !
                    MessageBox(NULL, "Sorry! This Feature is Unavailable Due to Maintenance!\nSorry for the Inconveniece", "Information", MB_ICONWARNING | MB_OK);
                    break;
                case 5: // VIEW INBOX !
                    PanelInbox(User, Pnl, MainDB);
                    break;
                case 6: // LOGOUT
                    Pnl->RUNNING = false;
                    break;
            }
        }

        // Simulate FPS
        STR_SimulateFPS(10);
    }

    ResetMainPanel(Pnl);
} 
void InventoryPanel(Credentials *User, PanelState *Pnl, DataBases *MainDB)
{
    clrscr();
    while (Pnl->RUNNING)
    {
        // Draw
        STR_ViewDefBoarder(LIGHTRED, STATIC);
        STR_DisplayTime(95, 1, LIGHTGREEN, STATIC);
        STR_VerticalSelect(5, 22, 6, Pnl->Choice, STATIC, LIGHTWHITE, LIGHTGREEN, RED, User->Username,
                           "View Inventory", "Organize Inventory", "View Inbox", "Logout");

        // Input
        Pnl->KeyPress = STR_GetKeyPress();
        if (KEY_NONE != Pnl->KeyPress)
        {
            STR_LinearSelect(&Pnl->Choice, Pnl->KeyPress, 1, 4);
        }

        // Events
        // RETURN KEY EVENTS
        if (KEY_RETURN == Pnl->KeyPress)
        {
            switch (Pnl->Choice)
            {
                case 1: // VIEW INVENTORY    !
                    MessageBox(NULL, "Sorry! This Feature is Unavailable Due to Maintenance!\nSorry for the Inconveniece", "Information", MB_ICONWARNING | MB_OK);
                    break;
                case 2: // ORGANIZE INVENTORY   !
                    MessageBox(NULL, "Sorry! This Feature is Unavailable Due to Maintenance!\nSorry for the Inconveniece", "Information", MB_ICONWARNING | MB_OK);
                    break;
                case 3: // VIEW INBOX   !
                    PanelInbox(User, Pnl, MainDB);
                    break;
                case 4: // LOGOUT
                    Pnl->RUNNING = false;
                    break;
            }
        }

        // Simulate FPS
        STR_SimulateFPS(10);
    }

    ResetMainPanel(Pnl);
} 
void CashierPanel(Credentials *User, PanelState *Pnl, DataBases *MainDB)
{
    ResetMainPanel(Pnl);
    char tempname[50];
    int payment;
    char path[50], temppath[50];
    Student_Info newStudent;
    Course_Details AvlCourses[50];
    int MaxCourse;
    bool enrolled = false, exist = false, payed = false;
    int cury;
    Student_Payment StudentList[30];
    int MaxSearch;
    int searched;
    char StudentName[50];
    int StudentBalance;
    int Change;
    Student_Payment Temp;
    int None_Tuition;

    // Load Preliminary Contents
    sprintf(path, "%sCourseList.dat", MainDB->CoursesPath);
    MaxCourse = Load_Course(path, AvlCourses);
    

    clrscr();
    while (Pnl->RUNNING)
    {
        // Draw
        STR_ViewDefBoarder(LIGHTRED, STATIC);
        STR_DisplayTime(95, 1, LIGHTGREEN, STATIC);
        STR_VerticalSelect(5, 22, 6, Pnl->Choice, STATIC, LIGHTBLUE, LIGHTGREEN, RED, User->Username,
                           "Enroll Student", "Access Payments", "View Inbox", "Logout");

        // Input
        Pnl->KeyPress = STR_GetKeyPress();
        if (KEY_NONE != Pnl->KeyPress)
        {
            STR_LinearSelect(&Pnl->Choice, Pnl->KeyPress, 1, 4);
        }

        // Events
        // RETURN KEY EVENTS
        if (KEY_RETURN == Pnl->KeyPress)
        {
            switch (Pnl->Choice)
            {
            case 1: // ENROLL STUDENT    !
                Pnl->Choice = 1;
                clrscr();
                enrolled = false;
                while (!enrolled)
                {
                    // Draw
                    STR_ViewDefBoarder(LIGHTRED, STATIC);
                    STR_DisplayTime(95, 1, LIGHTGREEN, STATIC);
                    STR_VerticalSelectCourse(MaxCourse, 22, 6, Pnl->Choice, STATIC, LIGHTBLUE, LIGHTGREEN, LIGHTRED,
                                             "Available Courses", AvlCourses);

                    // Input
                    Pnl->KeyPress = STR_GetKeyPress();
                    if (KEY_NONE != Pnl->KeyPress)
                    {
                        STR_LinearSelect(&Pnl->Choice, Pnl->KeyPress, 1, MaxCourse);
                    }

                    // Events
                    // RETURN KEY EVENTS
                    if (KEY_RETURN == Pnl->KeyPress)
                    {
                        STR_FillRect(84, 6, 48, 30, GRAY);
                        exist = false;

                        sprintf(path, "%sCredentials.dat", MainDB->SystemPath);
                        do{
                            cury = 6;
                            STR_PrintStringinRect(93, cury, STATIC, TITLESTRING, LIGHTGREEN, "Enroll Student");
                            STR_PrintStringinRect(93, (cury+=2), STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Username: ");
                            STR_PrintStringinRect(93, ++cury, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                            gotoxy(102, ++cury);
                            Sleep(300);
                            STR_GetStateStringWithTime(newStudent.User.Username, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                            STR_PrintStringinRect(93, ++cury, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Password: ");
                            STR_PrintStringinRect(93, ++cury, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                            gotoxy(102, ++cury);
                            Sleep(300);
                            STR_GetStateStringWithTime(newStudent.User.Password, CHAR_ASTERISK, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                            Sleep(300);
                            sprintf(newStudent.User.ID, "%s", Gen_ID(STUDENT));
                            if (CheckString(path, newStudent.User.Username) || CheckString(path, newStudent.User.Password) ||
                                CheckString(path, newStudent.User.ID)){
                                MessageBox(NULL, "Sorry!, it seem your Username/Password is Already in use!", "Warning", MB_ICONWARNING | MB_OK);
                            }
                            else {
                                exist = true;
                            }
                        } while (!exist);
                        

                        STR_PrintStringinRect(93, ++cury, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter First Name: ");
                        STR_PrintStringinRect(93, ++cury, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                        gotoxy(102, ++cury);
                        Sleep(300);
                        STR_GetStateStringWithTime(newStudent.Name.FName, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                        STR_PrintStringinRect(93, ++cury, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Last Name: ");
                        STR_PrintStringinRect(93, ++cury, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                        gotoxy(102, ++cury);
                        Sleep(300);
                        STR_GetStateStringWithTime(newStudent.Name.LName, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                        Sleep(300);
                        STR_PrintStringinRect(93, ++cury, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Middle Name: ");
                        STR_PrintStringinRect(93, ++cury, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                        gotoxy(102, ++cury);
                        Sleep(300);
                        STR_GetStateStringWithTime(newStudent.Name.MName, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                        Sleep(300);
                        STR_PrintStringinRect(93, ++cury, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Gender Name: ");
                        STR_PrintStringinRect(93, ++cury, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                        gotoxy(102, ++cury);
                        Sleep(300);
                        STR_GetStateStringWithTime(newStudent.Gender, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                        Sleep(300);
                        STR_PrintStringinRect(93, ++cury, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Contact Number: ");
                        STR_PrintStringinRect(93, ++cury, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                        gotoxy(102, ++cury);
                        Sleep(300);
                        STR_GetStateStringWithTime(newStudent.ContactNo, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                        Sleep(300);

                        if (!strstr(newStudent.Gender, "Fe")){
                            strcpy(newStudent.ProfilePic, "./Resources/Data/System/Female.png");
                        }
                        else {
                            strcpy(newStudent.ProfilePic, "./Resources/Data/System/Male.png");                            
                        }

                        newStudent.Balance_T = AvlCourses[Pnl->Choice].CourseTuition;
                        newStudent.Subjects = AvlCourses[Pnl->Choice].CourseSubjectCount;
                        strcpy(newStudent.CourseE, AvlCourses[Pnl->Choice].CourseName);

                        // Save Credentials
                        sprintf(path, "%sCredentials.dat", MainDB->SystemPath);
                        MainDB->MainData = fopen(path, "a");
                        fprintf(MainDB->MainData, "%s|%s|%s\n", newStudent.User.ID, newStudent.User.Username, newStudent.User.Password);
                        fclose(MainDB->MainData);
                        sprintf(path, "%sStudentRecord.dat", MainDB->CashierPath);
                        if (CheckFile(path)){
                            MainDB->MainData = fopen(path, "a");
                        }
                        else {
                            MainDB->MainData = fopen(path, "w");
                        }
                        fprintf(MainDB->MainData, "%s|%s|%s|%s|%s|%s|%d|%s\n",
                             newStudent.User.ID, newStudent.User.Username, newStudent.User.Password,
                             newStudent.Name.FName, newStudent.Name.LName, newStudent.Name.MName, 
                             newStudent.Balance_T, newStudent.CourseE);
                        fclose(MainDB->MainData);

                        sprintf(path, "%sStudentList.dat", MainDB->StudentPath);
                        if (CheckFile(path)){
                            MainDB->MainData = fopen(path, "a");
                        }
                        else {
                            MainDB->MainData = fopen(path, "w");
                        }
                        fprintf(MainDB->MainData, "%s|%s|%s|%s|%d|%s|%d|%s\n", 
                        newStudent.User.ID, newStudent.Name.FName, newStudent.Name.LName, 
                        newStudent.Name.MName, newStudent.Balance_T, newStudent.CourseE,
                        newStudent.Subjects, newStudent.ProfilePic);
                        fclose(MainDB->MainData);

                        sprintf(path, "%sTuition.dat", MainDB->CashierPath);
                        if (CheckFile(path)){
                            MainDB->MainData = fopen(path, "a");
                        }
                        else {
                            MainDB->MainData = fopen(path, "w");
                        }
                        fprintf(MainDB->MainData, "%s|%d\n", newStudent.User.ID, newStudent.Balance_T);
                        fclose(MainDB->MainData);

                        sprintf(path, "%sPaymentList.dat", MainDB->CashierPath);
                        sprintf(temppath, "%sStudentRecord.dat", MainDB->CashierPath);
                        if (!CheckString(path, "Tuition")){
                            if (CheckFile(temppath)){
                                MainDB->MainData = fopen(path, "a");
                            }
                            else {
                                MainDB->MainData = fopen(path, "w");
                            }
                            fprintf(MainDB->MainData, "%s\n", "Tuition");
                        }

                        MessageBox(NULL, "Successfully Enrolled!", "Information", MB_ICONINFORMATION | MB_OK);
                        enrolled = true;
                        STR_ClearRect(84, 6, 48, 30);
                        if (MessageBox(NULL, "Do you want to View Registration Form?", "Question", MB_ICONQUESTION | MB_YESNO) == 6){
                            Show_RegisitrationForm(&newStudent, AvlCourses[Pnl->Choice].CourseName, User, Pnl, MainDB);
                        }
                    }

                    // Simulate FPS
                    STR_SimulateFPS(10);
                    }
                break;
            case 2: // ACCESS PAYMENTS   !
                enrolled = false;
                Pnl->Choice = 1;
                while (!enrolled){
	    	        // Draw
	    	        STR_ViewDefBoarder(LIGHTAQUA, STATIC);
	    	        STR_DisplayTime(95, 1, LIGHTYELLOW, STATIC);
                    STR_VerticalSelect(7, 22, 6, Pnl->Choice, STATIC, LIGHTRED, LIGHTGREEN, RED,
                                       "Billing Window",
                                       "View Billing",
                                       "View Payment",
                                       "Add Payment",
                                       "Delete Payment",
                                       "Edit Payment",
                                       "Exit Billing");

                    // Input
	    	        Pnl->KeyPress = STR_GetKeyPress();
	    	        if (KEY_NONE != Pnl->KeyPress){
	    	        	STR_LinearSelect(&Pnl->Choice, Pnl->KeyPress, 1, 6);
	    	        }

	    	        // Events

	    	        // RETURN KEY EVENTS
	    	        if (KEY_RETURN == Pnl->KeyPress){
                        Sleep(300);
	    	        	switch(Pnl->Choice){
	    	        		case 1: // VIEW BILLING // NOTE! NEED TO UPDATE THE RENAME/REMOVE
                                exist = false;
                                STR_ClearRect(22, 6, 40, 30);
                                Pnl->Choice = 1;
                                while (!exist){
                                    // Draw
		                            STR_ViewDefBoarder(LIGHTAQUA, STATIC);
		                            STR_DisplayTime(95, 1, LIGHTYELLOW, STATIC);
		                            STR_VerticalSelect(3, 22, 6, Pnl->Choice, STATIC, LIGHTRED, LIGHTGREEN, RED, 
		                            										"Billing Option",
		                            										"View Biling",
		                            										"Exit Billing");

		                            // Input
		                            Pnl->KeyPress = STR_GetKeyPress();
		                            if (KEY_NONE != Pnl->KeyPress){
		                            	STR_LinearSelect(&Pnl->Choice, Pnl->KeyPress, 1, 2);
		                            }

		                            // Events

		                            // RETURN KEY EVENTS
		                            if (KEY_RETURN == Pnl->KeyPress){
		                            	switch(Pnl->Choice){
		                            		case 1: // VIEW BILLING
                                                STR_ClearRect(22, 6, 40, 30);
                                                Change = -1;
                                                searched = 0;
                                                gotoxy(95, 6);
                                                STR_PrintStringinRect(22, 6, STATIC, TITLESTRING, LIGHTGREEN, "Payment");
                                                STR_PrintStringinRect(22, 8, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Payment Name: ");
                                                STR_PrintStringinRect(22, 9, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                                                gotoxy(28, 10);
                                                Sleep(300);
                                                STR_GetStateStringWithTime(tempname, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                                                Sleep(300);

                                                sprintf(path, "%s%s.dat", MainDB->CashierPath, tempname);
                                                if (!strcmp(tempname, "Tuition") || !strcmp(tempname, "TUITION")){
                                                    if (!CheckFile(path)){
                                                    MessageBox(NULL, "That Bill Doesn't Exist!", "Warning", MB_ICONWARNING | MB_OK);
                                                    }
                                                    else {
                                                        do {
                                                            STR_PrintStringinRect(95, 6, STATIC, TITLESTRING, LIGHTGREEN, "Payment");
                                                            STR_PrintStringinRect(95, 8, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Student Name: ");
                                                            STR_PrintStringinRect(95, 9, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                                                            gotoxy(102, 10);
                                                            STR_GetStateStringWithTime(newStudent.User.Username, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                                                            Sleep(300);
                                                            sprintf(temppath, "%sStudentRecord.dat", MainDB->CashierPath);
                                                            MaxSearch = Load_PaymentString(temppath, newStudent.User.Username, StudentList);
                                                            if (!CheckString(temppath, newStudent.User.Username)){
                                                                if (MessageBox(NULL, "That Student Does not Exist!", "Warning!", MB_ICONINFORMATION | MB_YESNO) == 6 || MaxSearch == -1){
                                                                    searched = 0;
                                                                }
                                                                else {
                                                                    searched = -1;
                                                                }
                                                            }
                                                            else {
                                                                searched = 1;
                                                            }
                                                        } while (searched == 0);

                                                        Sleep(300);
                                                        if (searched == 1 || MaxSearch > 0){
                                                            if (MaxSearch <= 0){
                                                                MessageBox(NULL, "No User Found!", "Warning", MB_ICONINFORMATION | MB_OK);
                                                                STR_ClearRect(95, 6, 40, 30);
                                                            }
                                                            else {
                                                                payed = false;
                                                                Pnl->Choice = 1;
                                                                while (!payed){
                                                                    STR_VerticalSelectPayer(MaxSearch, 95, 6, Pnl->Choice, 
                                                                    STATIC, LIGHTAQUA, LIGHTGREEN, LIGHTRED, 
                                                                    tempname, StudentList);

                                                                    Pnl->KeyPress = STR_GetKeyPress();
		                                                            if (KEY_NONE != Pnl->KeyPress){
		                                                            	STR_LinearSelect(&Pnl->Choice, Pnl->KeyPress, 1, MaxSearch);
                                                                    }
		                                                            // RETURN KEY EVENTS
		                                                            if (KEY_RETURN == Pnl->KeyPress){
                                                                        payed = true;
                                                                    }

                                                                    STR_SimulateFPS(30);
                                                                }
                                                                STR_ClearRect(95, 6, 40, 33);
                                                                Change = -1;
                                                                Sleep(300);
                                                                STR_PrintStringinRect(95, 8, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Input Amount: ");
                                                                STR_PrintStringinRect(95, 9, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                                                                gotoxy(103, 10);
                                                                STR_GetStateIntWithTime(&payment, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                                                                Sleep(300);

                                                                sprintf(temppath, "%stemp.dat", MainDB->CashierPath);
                                                                MainDB->MainData = fopen(path, "r");
                                                                MainDB->TempData = fopen(temppath, "w");
                                                                while (fscanf(MainDB->MainData, "\n%49[^|]|%d", StudentName, &StudentBalance) == 2){
                                                                    if (!strcmp(StudentName, StudentList[Pnl->Choice].User.ID)){
                                                                        if (payment > StudentBalance){
                                                                            Change = payment - StudentBalance;
                                                                            fprintf(MainDB->TempData, "%s|%d\n", StudentName, 0);
                                                                        }
                                                                        else {
                                                                            fprintf(MainDB->TempData, "%s|%d\n", StudentName, StudentBalance - payment);
                                                                        }
                                                                    }
                                                                    else {
                                                                        fprintf(MainDB->TempData, "%s|%d\n", StudentName, StudentBalance);
                                                                    }
                                                                }
                                                                fclose(MainDB->MainData);
                                                                fclose(MainDB->TempData);
                                                                remove(path);
                                                                rename(temppath, path);

                                                                if (CheckFile(path)){
                                                                    sprintf(path, "%sStudentRecord.dat", MainDB->CashierPath);
                                                                    sprintf(temppath, "%stemp.dat", MainDB->CashierPath);
                                                                    MainDB->MainData = fopen(path, "r");
                                                                    MainDB->TempData = fopen(temppath, "w");
                                                                    while (fscanf(MainDB->MainData, "\n%9[^|]|%49[^|]|%49[^|]|%49[^|]|%49[^|]|%49[^|]|%d|%49[^\n]",
                                                                                  Temp.User.ID, Temp.User.Username, Temp.User.Password,
                                                                                  Temp.Name.FName, Temp.Name.LName, Temp.Name.MName, &Temp.Balance, Temp.Course) == 8){
                                                                                if(!strcmp(StudentList[Pnl->Choice].User.ID, Temp.User.ID)){
                                                                                    fprintf(MainDB->TempData, "%s|%s|%s|%s|%s|%s|%d|%s\n",
                                                                                            Temp.User.ID, Temp.User.Username, Temp.User.Password,
                                                                                            Temp.Name.FName, Temp.Name.LName, Temp.Name.MName,
                                                                                            (Change != -1) ? 0 : StudentList[Pnl->Choice].Balance - payment, Temp.Course);
                                                                                }
                                                                                else {
                                                                                    fprintf(MainDB->TempData, "%s|%s|%s|%s|%s|%s|%d|%s\n",
                                                                                            Temp.User.ID, Temp.User.Username, Temp.User.Password,
                                                                                            Temp.Name.FName, Temp.Name.LName, Temp.Name.MName,
                                                                                            Temp.Balance, Temp.Course);
                                                                                }

                                                                    }
                                                                    fclose(MainDB->MainData);
                                                                    fclose(MainDB->TempData);
                                                                    remove(path);
                                                                    rename(temppath, path);
                                                                    Sleep(300);
                                                                }
                                                                else {
                                                                    MessageBox(NULL, "Oh Sorry! Something Went Wrong!\nPlease Contact An ADMIN!", "Warning!", MB_ICONWARNING | MB_OK);
                                                                }

                                                                sprintf(temppath, "Name: %s, %s %c.\nPayment To: %s\nAmount Tendered: %d",
                                                                        StudentList[Pnl->Choice].Name.LName, StudentList[Pnl->Choice].Name.FName, StudentList[Pnl->Choice].Name.MName[0],
                                                                        tempname, payment);

                                                                if (Change != -1){
                                                                    sprintf(tempname, "You Have A Change of %d!", Change);
                                                                    MessageBox(NULL, tempname, "Information", MB_ICONINFORMATION | MB_OK);
                                                                }
                                                                MessageBox(NULL, "Payment Process Completed!", "Warning", MB_ICONWARNING | MB_OK); 
                                                                ClearPanel();
                                                            }
                                                        }
                                                    }
                                                }
                                                else {
                                                    if (!CheckFile(path)){
                                                    MessageBox(NULL, "That Bill Doesn't Exist!", "Warning", MB_ICONWARNING | MB_OK);
                                                    }
                                                    else {
                                                        MainDB->MainData = fopen(path, "r");
                                                        fscanf(MainDB->MainData, "%49[^|]|%d", Temp.Course, &Temp.Balance);
                                                        fclose(MainDB->MainData);
                                                        do {
                                                            STR_PrintStringinRect(95, 6, STATIC, TITLESTRING, LIGHTGREEN, "Payment");
                                                            STR_PrintStringinRect(95, 8, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Student Name: ");
                                                            STR_PrintStringinRect(95, 9, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                                                            gotoxy(102, 10);
                                                            STR_GetStateStringWithTime(newStudent.User.Username, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                                                            Sleep(300);
                                                            sprintf(temppath, "%sStudentRecord.dat", MainDB->CashierPath);
                                                            MaxSearch = Load_PaymentString(temppath, newStudent.User.Username, StudentList);
                                                            if (!CheckString(temppath, newStudent.User.Username)){
                                                                if (MessageBox(NULL, "That Student Does not Exist!", "Warning!", MB_ICONINFORMATION | MB_YESNO) == 6 || MaxSearch == -1){
                                                                    searched = 0;
                                                                }
                                                                else {
                                                                    searched = -1;
                                                                }
                                                            }
                                                            else {
                                                                searched = 1;
                                                            }
                                                        } while (searched == 0);

                                                        Sleep(300);
                                                        if (MaxSearch <= 0){
                                                            MessageBox(NULL, "No User Found!", "Warning", MB_ICONINFORMATION | MB_OK);
                                                            STR_ClearRect(95, 6, 40, 30);
                                                        }
                                                        if (searched == 1 || MaxSearch > 0){
                                                            // else {
                                                                payed = false;
                                                                Pnl->Choice = 1;
                                                                while (!payed){
                                                                    STR_VerticalSelectPayer(MaxSearch, 95, 6, Pnl->Choice, 
                                                                    STATIC, LIGHTAQUA, LIGHTGREEN, LIGHTRED, 
                                                                    tempname, StudentList);

                                                                    Pnl->KeyPress = STR_GetKeyPress();
		                                                            if (KEY_NONE != Pnl->KeyPress){
		                                                            	STR_LinearSelect(&Pnl->Choice, Pnl->KeyPress, 1, MaxSearch);
                                                                    }
		                                                            // RETURN KEY EVENTS
		                                                            if (KEY_RETURN == Pnl->KeyPress){
                                                                        payed = true;
                                                                    }

                                                                    STR_SimulateFPS(30);
                                                                }
                                                                STR_ClearRect(95, 6, 40, 33);
                                                                Change = -1;
                                                                Sleep(300);
                                                                STR_PrintStringinRect(95, 8, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Input Amount: ");
                                                                STR_PrintStringinRect(95, 9, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                                                                gotoxy(103, 10);
                                                                STR_GetStateIntWithTime(&payment, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
                                                                Sleep(300);

                                                                sprintf(temppath, "%stemp.dat", MainDB->CashierPath);
                                                                MainDB->MainData = fopen(path, "r");
                                                                MainDB->TempData = fopen(temppath, "w");
                                                                while (fscanf(MainDB->MainData, "\n%49[^|]|%d", StudentName, &StudentBalance) == 2){
                                                                    if (!strcmp(StudentName, StudentList[Pnl->Choice].User.ID)){
                                                                        if (payment > StudentBalance){
                                                                            Change = payment - StudentBalance;
                                                                            fprintf(MainDB->TempData, "%s|%d\n", StudentName, 0);
                                                                        }
                                                                        else {
                                                                            fprintf(MainDB->TempData, "%s|%d\n", StudentName, StudentBalance - payment);
                                                                        }
                                                                    }
                                                                    else {
                                                                        fprintf(MainDB->TempData, "%s|%d\n", StudentName, StudentBalance);
                                                                    }
                                                                }
                                                                fclose(MainDB->MainData);
                                                                fclose(MainDB->TempData);
                                                                remove(path);
                                                                rename(temppath, path);

                                                                sprintf(temppath, "Name: %s, %s %c.\nPayment To: %s\nAmount Tendered: %d", 
                                                                StudentList[Pnl->Choice].Name.LName, StudentList[Pnl->Choice].Name.FName, StudentList[Pnl->Choice].Name.MName[0],
                                                                tempname, payment);
                                                                
                                                                MessageBox(NULL, temppath, "Successfull Transaction!", MB_OK);
                                                                if (Change != -1){
                                                                    sprintf(temppath, "You have %s Change!", Change);
                                                                    MessageBox(NULL, temppath, "Successfull Transaction!", MB_OK);
                                                                }
                                                                STR_ClearRect(95, 6, 30, 25);
                                                        }
                                                    }
                                                }
                                                Pnl->Choice = 1;
                                                break;
                                            case 2: // EXIT
                                                exist = true;
                                                break;
                                        }
                                    }
                                }
	    	        			break;
	    	        		case 2: // VIEW PAYMENT
                                gotoxy(95, 6); 
                                cury = whereY();
                                sprintf(path, "%sPaymentList.dat", MainDB->CashierPath);
                                MainDB->MainData = fopen(path, "r");
                                STR_PrintStringinRect(95, 6, STATIC, TITLESTRING, LIGHTAQUA, "Payment Names");
                                cury += 3;
                                while(fscanf(MainDB->MainData, "\n%49[^|]|%d", tempname, &payment) == 2){
                                    STR_PrintStringinRect(95, ++cury, STATIC, CONTENTSTRING, LIGHTAQUA, tempname);
                                }
                                fclose(MainDB->MainData);
                                gotoxy(95, whereY() + 2);
                                system("PAUSE");
                                STR_ClearRect(95, 6, 37, 32);
                                break;
                            case 3: // ADD PAYMENT !
                                gotoxy(95, 6);
                                cury = whereY();
                                STR_PrintStringinRect(95, cury, STATIC, TITLESTRING, LIGHTAQUA, "Create Payment");
                                cury+=2;
                                STR_PrintStringinRect(95, cury++, STATIC, TITLESTRING, LIGHTAQUA, "Enter Payment Name:");
                                STR_PrintStringinRect(95, ++cury, STATIC, CONTENTSTRING, LIGHTAQUA, ">>> ");
                                gotoxy(103, whereY());
                                STR_GetStateStringWithTime(tempname, CHAR_SHOWN, LIGHTAQUA, 95, 1, LIGHTYELLOW, STATIC);
                                Sleep(300);
                                STR_PrintStringinRect(95, (++cury), STATIC, TITLESTRING, LIGHTAQUA, "Enter Payment Amount:");
                                STR_PrintStringinRect(95, ++cury, STATIC, CONTENTSTRING, LIGHTAQUA, ">>> ");
                                gotoxy(103, whereY());
                                STR_GetStateIntWithTime(&payment, LIGHTAQUA, 95, 1, LIGHTYELLOW, STATIC);
                                Sleep(300);

                                sprintf(path, "%sPaymentList.dat", MainDB->CashierPath);
                                sprintf(temppath, "%s%s.dat", MainDB->CashierPath, tempname);
                                if (!CheckString(path, tempname) || CheckFile(path)){
                                    if (CheckFile(path)){
                                        MainDB->MainData = fopen(path, "a");
                                    }
                                    else {
                                        MainDB->MainData = fopen(path, "w");
                                        fprintf(MainDB->MainData, "Tuition.dat|000\n");
                                    }
                                    fprintf(MainDB->MainData, "%s|%d\n", tempname, payment);
                                    fclose(MainDB->MainData);
                                    MessageBox(NULL, "Payment Added!", "Information", MB_ICONINFORMATION | MB_OK);
                                    MainDB->MainData = fopen(temppath, "w");
                                    fclose(MainDB->MainData);
                                }
                                else {
                                    MessageBox(NULL, "Sorry!, It Seem That Payment Already Existed!", "Warning", MB_ICONWARNING | MB_OK);
                                }
                                STR_ClearRect(95, 6, 40, 30);

                                break;
                            case 4: // DELETE PAYMENT !
                                gotoxy(95, 6);
                                cury = whereY();
                                STR_PrintStringinRect(95, cury, STATIC, TITLESTRING, LIGHTAQUA, "Edit Payment");
                                cury += 2;
                                STR_PrintStringinRect(95, cury++, STATIC, TITLESTRING, LIGHTAQUA, "Enter Payment Name:");
                                STR_PrintStringinRect(95, ++cury, STATIC, CONTENTSTRING, LIGHTAQUA, ">>> ");
                                gotoxy(103, whereY());
                                STR_GetStateStringWithTime(tempname, CHAR_SHOWN, LIGHTAQUA, 95, 1, LIGHTYELLOW, STATIC);
                                Sleep(300);

                                sprintf(path, "%s%s.dat", MainDB->CashierPath, tempname);
                                if (!CheckFile(path)){
                                    remove(path);
                                    sprintf(path, "%sPaymentList.dat", MainDB->CashierPath);
                                    sprintf(temppath, "%stemp.dat", MainDB->CashierPath);
                                    MainDB->MainData = fopen(path, "r");
                                    MainDB->TempData = fopen(temppath, "w");
                                    while (fscanf(MainDB->MainData, "\n%49[^|]|%d", Temp.Course, &Temp.Balance) == 2){
                                        if (!strcmp(Temp.Course, tempname)){
                                            MessageBox(NULL, "Payment Successfully Deleted!", "Information", MB_ICONINFORMATION | MB_OK);
                                        }
                                        else {
                                            fprintf(MainDB->TempData, "%s|%d\n", Temp.Course, Temp.Balance);
                                        }
                                    }
                                    fclose(MainDB->MainData);
                                    fclose(MainDB->TempData);
                                    remove(path);
                                    rename(temppath, path);
                                }
                                else {
                                    MessageBox(NULL, "Sorry!, That Payment Does Not Exist!", "Warning", MB_ICONWARNING | MB_OK);
                                }

                                STR_PrintStringinRect(95, (++cury), STATIC, TITLESTRING, LIGHTAQUA, "Enter Payment Amount:");
                                STR_PrintStringinRect(95, ++cury, STATIC, CONTENTSTRING, LIGHTAQUA, ">>> ");
                                gotoxy(103, cury++);
                                STR_GetStateIntWithTime(&payment, LIGHTAQUA, 95, 1, LIGHTYELLOW, STATIC);
                                Sleep(300);

                                sprintf(path, "%sPaymentList.dat", MainDB->CashierPath);
                                if (!CheckString(path, tempname)){
                                    if (CheckFile(path)){
                                        MainDB->MainData = fopen(path, "a");
                                    }
                                    else {
                                        MainDB->MainData = fopen(path, "w");
                                        fprintf(MainDB->MainData, "Tuition.dat|000\n");
                                    }
                                    fprintf(MainDB->MainData, "%s|%d\n", tempname, payment);
                                    fclose(MainDB->MainData);
                                    MessageBox(NULL, "Payment Added!", "Information", MB_ICONINFORMATION | MB_OK);
                                }
                                else {
                                    MessageBox(NULL, "Sorry!, It Seem That Payment Already Existed!", "Warning", MB_ICONWARNING | MB_OK);
                                }
                                STR_ClearRect(95, 6, 40, 30);
                                break;
                            case 5: // EDIT PAYMENT !
                                break;
                            case 6: // EXIT
                                enrolled = true;
	    	        			break;
	    	        	}
                        Pnl->Choice = 1;
	    	        }

	    	        // Simulate FPS
	    	        STR_SimulateFPS(30);
	            }

                ClearPanel();
                break;
            // case 3: // VIEW DTR RECORD   !
                // ClearPanel();
                // break;
            case 3: // VIEW INBOX   !
                ClearPanel();
                PanelInbox(User, Pnl, MainDB);
                break;
            case 4: // LOGOUT
                Pnl->RUNNING = false;
                ClearPanel();
                break;
            }
        }

        // Simulate FPS
        STR_SimulateFPS(10);
    }

    ResetMainPanel(Pnl);
    ClearPanel();
}

void PanelInbox(Credentials *User, PanelState *Pnl, DataBases *MainDB)
{
    bool exit = false, selected = false;
    int aY, counter, choice = 1, maxMessages;
    char path[50], temppath[50];
    Message_Details newMessage;
    Message_Details listMessage[50];
    char messagebox[512];

    clrscr();
    ResetMainPanel(Pnl);


    while (!exit)
    {

        // Draw
        STR_ViewDefBoarder(LIGHTAQUA, STATIC);
        STR_DisplayTime(95, 1, LIGHTYELLOW, STATIC);
        STR_VerticalSelect(4, 22, 6, Pnl->Choice, STATIC, LIGHTRED, LIGHTGREEN, RED,
                           "Inbox",
                           "Compose",
                           "View Inbox",
                           "Exit");

        // Input
        Pnl->KeyPress = STR_GetKeyPress();
        if (KEY_NONE != Pnl->KeyPress)
        {
            STR_LinearSelect(&Pnl->Choice, Pnl->KeyPress, 1, 3);
        }

        // Events

        // RETURN KEY EVENTS
        if (KEY_RETURN == Pnl->KeyPress)
        {
            switch (Pnl->Choice)
            {
                case 1: // WRITE
                    aY = 6;
                    STR_ClearRect(95, 6, 35, 30);
                    STR_PrintStringinRect(95, 6, STATIC, TITLESTRING, LIGHTGREEN, "Write Email");
                    aY+=2;
                    STR_PrintStringinRect(95, 9, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Name: ");
                    STR_PrintStringinRect(95, 10, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                    gotoxy(103, whereY());
                    STR_GetStateStringWithTime(newMessage.To, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, MYRIAD);
                    Sleep(300);

                    sprintf(path, "%sCredentials.dat", MainDB->SystemPath);        
                    if (CheckString(path, newMessage.To)){
                        STR_PrintStringinRect(95, 11, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Subject: ");
                        STR_PrintStringinRect(95, 12, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                        gotoxy(103, whereY());
                        STR_GetStateStringWithTime(newMessage.Subject, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, MYRIAD);
                        Sleep(300);
                        STR_PrintStringinRect(95, 13, STATIC, CONTENTSTRING, LIGHTGREEN, "Enter Message: ");
                        STR_PrintStringinRect(95, 14, STATIC, CONTENTSTRING, LIGHTGREEN, ">>> ");
                        gotoxy(103, whereY());
                        STR_GetStateStringWithTime(newMessage.Content, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, MYRIAD);
                        Sleep(300);

                        sprintf(path, "%s%s.dat", MainDB->InboxPath, newMessage.To);
                        if (CheckFile(path)){
                            MainDB->MainData = fopen(path, "a");
                        }
                        else {
                            MainDB->MainData = fopen(path, "w");
                        }

                        fprintf(MainDB->MainData, "%s|%s|%s|%s\n", User->Username, newMessage.To, newMessage.Subject, newMessage.Content);
                        fclose(MainDB->MainData);
                        MessageBox(NULL, "Message Successfully Sent!", "Information", MB_ICONINFORMATION | MB_OK);
                    }
                    else {
                        MessageBox(NULL, "Sorry That User Does not Exist!", "Warning", MB_ICONINFORMATION | MB_OK);
                    }
                    break;
                case 2: // VIEW INBOX
                    Sleep(300);
                    choice = 1;
                    sprintf(path, "%s%s.dat", MainDB->InboxPath, User->Username);
                    if (CheckFile(path)){
                        selected = false;
                        maxMessages = Load_Message(path, listMessage);
                        if (maxMessages < 0){
                            MessageBox(NULL, "Unfortunately No One Message You so Far", "Warning", MB_ICONINFORMATION | MB_OK);
                        }
                        else {
                            while (!selected){
                                // Draw
                                STR_VerticalSelectMessages(maxMessages, 85, 6, choice, STATIC, LIGHTPURPLE, LIGHTGREEN, LIGHTAQUA, "Message List", listMessage);

                                // Events
                                Pnl->KeyPress = STR_GetKeyPress();
                                if (KEY_NONE != Pnl->KeyPress){
                                    STR_LinearSelect(&choice, Pnl->KeyPress, 1, maxMessages);
                                }
                                if (Pnl->KeyPress == KEY_RETURN){
                                    Sleep(300);
                                    sprintf(messagebox, "%From: %s\n=====================\nTo: %s\n====================\nSubject: %s\n==========================\nMessage: %s\n================================================",
                                            listMessage[choice].From, listMessage[choice].To, listMessage[choice].Subject, listMessage[choice].Content);
                                        MessageBox(NULL, messagebox, "Message", MB_OK);
                                        if (MessageBox(NULL, "Do you want to see Another Message?", "Question", MB_ICONQUESTION | MB_YESNO) == 7){
                                            selected = true;
                                        }
                                }
                            }
                        }
                    }
                    else {
                        MessageBox(NULL, "Unfortunately No One Message You so Far", "Warning", MB_ICONINFORMATION | MB_OK);
                    }
                    STR_ClearRect(85, 6, 58, 33);
                    break;
                case 3: // EXIT
                    exit = true;
                    break;
            }
            STR_ClearRect(95, 6, 35, 30);
        }

        // Simulate FPS
        STR_SimulateFPS(30);
    }
    ClearPanel();
}

void Show_RegisitrationForm(Student_Info *Student, char *Course, Credentials *User, PanelState *Pnl, DataBases *MainDB)
{
    int aY = 6, none, none1;
    char path[50];
    char stringtemp[50];

    SetFBColor(LIGHTAQUA, BLACK);
    gotoxy(85, aY++); printf("Student Name: %s %c. %s", Student->Name.FName, Student->Name.MName[0], Student->Name.LName);
    gotoxy(85, aY++); printf("Student Username: %s", Student->User.Username);
    gotoxy(85, aY++); printf("Student Password: %s", Student->User.Password);
    gotoxy(85, aY++); printf("Contanct No: %s\t Gender: %s", Student->ContactNo, Student->Gender);
    gotoxy(85, aY++);printf("\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD");
    gotoxy(85, aY++); STR_PrintStringinRect(94, aY, MYRIAD, TITLESTRING, LIGHTAQUA, "Subject Enrolled");
    aY++; aY++, aY++;

    sprintf(path, "%s%s.dat", MainDB->CoursesPath, Course);
    MainDB->MainData = fopen(path, "r");
    fscanf(MainDB->MainData, "%49[^|]|%d|%d", path, &none1, &none);
    while(fscanf(MainDB->MainData, "\n%49[^\n]", stringtemp) == 1){
         gotoxy(85, aY++); printf("Subject Name: %s", stringtemp);
    }
    fclose(MainDB->MainData);
    SetFBColor(LIGHTAQUA, BLACK);
    aY++;
    gotoxy(85, aY++); printf("\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD");
    gotoxy(85, aY++); printf("Cashier Name: %s\t Total Tuition: %d", User->Username, Student->Balance_T);

    gotoxy(85, aY++); system("PAUSE");

    STR_ClearRect(85, 6, 48, 30);
} 
