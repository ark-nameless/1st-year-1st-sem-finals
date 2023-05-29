#ifndef _NEOTOOLS_H
#define _NEOTOOLS_H

#ifndef _DAS_H
#include "dsa.h"
#endif

int STR_VerticalSelect(int args, int x, int y, int choice, int C_Option, int T_Color, int SColor, int DColor, ...);
void STR_PrintStringinRect(int x, int y, int C_Option, int S_Option, int S_Color, char *Str);
void STR_ColorIncrease(int *color);
void STR_LinearSelect(int *choice, int dir, int lo, int hi);

void STR_QUIT(void);
char *Gen_ID(int type);
int t_rand(void);
void STR_DisplayTime(int x, int y, int color, int C_Option);
void STR_ClearRect(int x, int y, int w, int h);
void STR_FillRect(int x, int y, int w, int h, int color);
    
void UnloadDatabase(DataBases *Database);
void LoadDatabase(DataBases *DataBase, char *home);
void SaveData(int type, DataBases *DataBase, char *databasename);
void ResetMainPanel(PanelState *Pnl);

int Load_Course(char *filename, Course_Details Course[50]);
int STR_VerticalSelectCourse(int max, int x, int y, int choice, int C_Option, int T_Color, int SColor, int DColor, char *Header, Course_Details Course[50]);
int Load_Payment(char *filename, Student_Payment Student[30]);
int Load_PaymentString(char *filename, char *key, Student_Payment Student[30]);
int STR_VerticalSelectPayer(int max, int x, int y, int choice, int C_Option, int T_Color, int SColor, int DColor, char *Header, Student_Payment Student[30]);
int Load_Message(char *filename, Message_Details MessageList[30]);
int STR_VerticalSelectMessages(int max, int x, int y, int choice, int C_Option, int T_Color, int SColor, int DColor, char *Header, Message_Details MessageList[50]);

#endif