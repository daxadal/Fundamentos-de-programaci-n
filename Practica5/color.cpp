/*
Eric García de Ceca Elejoste
Práctica 5
*/

#include "color.h"

//Color
void setColor(unsigned short color)                 
{                                                   
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle,color);
}