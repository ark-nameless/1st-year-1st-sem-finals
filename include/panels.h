#ifndef _PANELS_H
#define _PANELS_H

void ClearPanel(void);

void AdminPanel(Credentials *User, PanelState *Pnl, DataBases *MainDB);
int LoginAccount(Credentials *user, DataBases *MainDB);
void TeacherPanel(Credentials *User, PanelState *Pnl, DataBases *MainDB);
void StudentPanel(Credentials *User, PanelState *Pnl, DataBases *MainDB);
void LibrarianPanel(Credentials *User, PanelState *Pnl, DataBases *MainDB);
void InventoryPanel(Credentials *User, PanelState *Pnl, DataBases *MainDB);
void CashierPanel(Credentials *User, PanelState *Pnl, DataBases *MainDB);
void PanelInbox(Credentials *User, PanelState *Pnl, DataBases *MainDB);
void Show_RegisitrationForm(Student_Info *Student, char *Course, Credentials *User, PanelState *Pnl, DataBases *MainDB);

#endif