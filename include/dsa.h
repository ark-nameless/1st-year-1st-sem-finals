#ifndef _DSA_H
#define _DSA_H

typedef struct CREDENTIALS {
    char        ID[10];
    char        Username[20];
    char        Password[20];
} Credentials;

typedef struct NAME {
    char        FName[20];
    char        MName[20];
    char        LName[20];
} Name_Data;

typedef struct STUDENT_INFO {
    Credentials User;
    Name_Data   Name;
    char        ContactNo[15];
    char        CourseE[20];
    char        ProfilePic[50];
    char        Gender[10];
    int         Balance_T;
    int         Subjects;
} Student_Info;

typedef struct STUDENT_PAYMENT {
    Credentials        User;
    Name_Data          Name;
    int                Balance;
    char               Course[50];
} Student_Payment;

typedef enum DATABASETYPE{
    TEACHER_T, STUDENT_T, INBOX_T, CASHIER_T, DTR_T,
    INVENTORY_T, LIBRARY_T, SYSTEM_T, TEMP_T, ADMIN_T
} DATABASETYPE;

typedef struct DataBases
{
    char         TeacherPath[50];
    char         StudentPath[50];
    char         InboxPath[50];
    char         CashierPath[50];
    char         DTRPath[50];
    char         InventoryPath[50];
    char         LibraryPath[50];
    char         SystemPath[50];
    char         TempPath[50];
    char         AdminPath[50];
    char         LogsPath[50];
    char         CoursesPath[50];
    // char         HomePath[250];
    // FILE        *Teacher;
    // FILE        *Student;
    // FILE        *Inbox;
    // FILE        *Cashier;
    // FILE        *DTR;
    // FILE        *Inventory;
    // FILE        *Library;
    // FILE        *System;
    FILE        *TempData;
    FILE        *MainData;

} DataBases;

typedef struct COURSE_DETAILS {
    char        CourseName[50];
    int        CourseTuition;
    int        CourseSubjectCount;
} Course_Details;

typedef struct MESSAGE_DETAILS {
    char        To[50];
    char        From[50];
    char        Subject[50];
    char        Content[256];
} Message_Details;


#endif