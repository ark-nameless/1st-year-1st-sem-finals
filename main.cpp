#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>


#include "include/tools.h"
#include "include/camera.h"
#include "include/states.h"
#include "include/keys.h"
#include "include/types.h"
#include "include/neotools.h"
#include "include/dsa.h"
#include "include/panels.h"



char *DefAdminUsername = "admin";
char *DefAdminPassword = "admin";


int main(int argc, char** argv)
{
	PanelState MainWindow;
	DataBases MainDataBase;
	Credentials	CurrUser;
	char temp[20];

	// Globals Operations 
	ResetMainPanel(&MainWindow);
	LoadDatabase(&MainDataBase, argv[0]);
	CursorOption(HIDDEN, 0);

	while (MainWindow.RUNNING){

		// Draw
		STR_ViewDefBoarder(LIGHTAQUA, MYRIAD);
		STR_DisplayTime(95, 1, LIGHTYELLOW, MYRIAD);
		STR_VerticalSelect(3, 22, 6, MainWindow.Choice, MYRIAD, LIGHTRED, LIGHTGREEN, RED, 
												"Light Spectrum",
												"Login Account",
												"Exit Spectrum");

		// Input
		MainWindow.KeyPress = STR_GetKeyPress();
		if (KEY_NONE != MainWindow.KeyPress){
			STR_LinearSelect(&MainWindow.Choice, MainWindow.KeyPress, 1, 2);
		}

		// Events

		// RETURN KEY EVENTS
		if (KEY_RETURN == MainWindow.KeyPress){
			switch(MainWindow.Choice){
				case 1: // LOGIN
					gotoxy(95, 6);
					STR_PrintStringinRect(95, 6, MYRIAD, TITLESTRING, LIGHTGREEN, "Login Account");
					STR_PrintStringinRect(95, 8, MYRIAD, CONTENTSTRING, LIGHTGREEN, "Enter Username: ");
					STR_PrintStringinRect(95, 9, MYRIAD, CONTENTSTRING, LIGHTGREEN, ">>> ");
					gotoxy(102, 10);
					Sleep(300);
					STR_GetStateStringWithTime(CurrUser.Username, CHAR_SHOWN, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
					STR_PrintStringinRect(95, 11, MYRIAD, CONTENTSTRING, LIGHTGREEN, "Enter Password: ");
					STR_PrintStringinRect(95, 12, MYRIAD, CONTENTSTRING, LIGHTGREEN, ">>> ");
					gotoxy(102, 13);
					Sleep(300);
					STR_GetStateStringWithTime(CurrUser.Password, CHAR_ASTERISK, LIGHTGREEN, 95, 1, LIGHTYELLOW, STATIC);
					Sleep(300);
					if(LoginAccount(&CurrUser, &MainDataBase) != -1){
						STR_PrintStringinRect(95, 15, MYRIAD, TITLESTRING, LIGHTGREEN, "Login Successfull!");
						Sleep(3000);
						STR_ClearRect(95, 6, 40, 15);

						switch(GetLoginType(CurrUser.ID)){
							case ADMIN: // ADMIN 
								AdminPanel(&CurrUser, &MainWindow, &MainDataBase);
								ClearPanel();
								break;
							case STUDENT: // STUDENT !
								StudentPanel(&CurrUser, &MainWindow, &MainDataBase);
								ClearPanel();
								break;
							case TEACHER: // TEACHER !
								TeacherPanel(&CurrUser, &MainWindow, &MainDataBase);
								ClearPanel();
								break;
							case LIBRARY: // LIBRARY !
								LibrarianPanel(&CurrUser, &MainWindow, &MainDataBase);
								ClearPanel();
								break;
							case CASHIER: // CASHIER !
								CashierPanel(&CurrUser, &MainWindow, &MainDataBase);
								ClearPanel();
								break;
							case INVENTORY: // INVENTORY !
								InventoryPanel(&CurrUser, &MainWindow, &MainDataBase);
								ClearPanel();
								break;
						}
					}
					else {
						STR_PrintStringinRect(95, 15, MYRIAD, TITLESTRING, LIGHTRED, "Incorrect Credentials!");
						Sleep(2000);
						STR_ClearRect(95, 6, 40, 15);
					}

					break;
				case 2: // EXIT
					if (MessageBox(NULL, "Do you Really Want to Exit?", "Question", MB_ICONQUESTION | MB_YESNO) == 6){
						MainWindow.RUNNING = false;
					}
					break;
			}
		}
		
		// Simulate FPS
		STR_SimulateFPS(30);
	}


	// UnloadDatabase(&MainDataBase);
	ResetColors();
	return 0;
//	system("exit");
}
