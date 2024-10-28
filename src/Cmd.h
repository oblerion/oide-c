#pragma once
#include "raylib.h"
#include "kbd_layout.h"
//#include <string>
#include <string.h>
#include "dstring.h"

#define CONSOLE_WIDTH 300
struct Cmd
{
    //char scmd[CONSOLE_WIDTH];
    dstring* scmd;
    dstring* scmd_tmp;
    dstring* scom;
    dstring* svalue;
    dstring* svalue2;
    int cursor_x;
    int cursor_y;
    KBD_Layout layout_type;
};
void Cmd();
void Cmd_edit(const char* str);
void Cmd_reset();
bool Cmd_draw(int size,Font font,Color ctxt,Color ccur);
const char* Cmd_getCmd();
const char* Cmd_getCom();
const char* Cmd_getVal();
const char* Cmd_getVal2();
KBD_Layout Cmd_getLayout();
void Cmd_setLayout(int il);
void Cmd_free();
