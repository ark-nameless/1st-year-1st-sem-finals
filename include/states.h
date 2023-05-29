#ifndef _STATES_H
#define _STATES_H

#ifndef _TYPES_H
#include "types.h"
#endif
#ifndef _KEYS_H
#include "keys.h"
#endif



void STR_GetStateString(char *var, ALTER_KEY option, T_Color fColor);
void STR_GetStateStringWithTime(char *var, ALTER_KEY option, T_Color fColor, int x, int y, int color, int C_Option);
void STR_AlterCharDisplay(ALTER_KEY option, char ch);

void STR_GetStateInt(int *var, T_Color fColor);
void STR_GetStateIntWithTime(int *var, T_Color fColor, int x, int y, int color, int C_Option);
int ChartoInt(char var);
int GetPlace(int place);

#endif