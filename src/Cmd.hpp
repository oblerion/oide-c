#pragma once
#include "raylib.h"
#include "kbd_layout.h"
#include <cstring>
#include <string>

#define CONSOLE_WIDTH 300
class Cmd
{
private:
    std::string scmd;
    std::string scmd_tmp;
    std::string scom;
    std::string svalue;
    std::string svalue2;
    int cursor_x;
    int cursor_y;
    KBD_Layout layout_type;
public:
    Cmd();
    void Edit(const char* str);
    void Reset();
    bool Draw(int size,Font font,Color ctxt,Color ccur);
    std::string GetCmd();
    std::string GetCom();
    std::string GetVal();
    std::string GetVal2();
    KBD_Layout GetLayout();
    void SetLayout(int il);
};

