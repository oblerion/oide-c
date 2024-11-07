#pragma once
#include "raylib.h"
#include <cstdio>
#include <cstdlib>
#include "Cmd.hpp"
#include "kbd_layout.h"
#include "gui_layout_config.h"
#include <string>
#include <vector>

#define OIDE_VERSION "a0.2"

enum OideScene
{
   oi_dt=0,
   oi_config,
   oi_help
};

struct OideConfig
{
    Color cbg;
    Color ctext;
    Color ccursor;
    int layout;
};


class Oide
{
private:
    enum OideScene scene;
    struct OideConfig config;
    Font font;
    int size;
    int offy;
    std::vector<std::string> lstr;
    char filepath[150];
    GuiLayoutConfigState state_config;
    Cmd cmd;

    const int _nbLine();
    void _ControlSub();
    void _delLine(int n);
    void _addLine(int n,const char* str);
    std::string _getLine(int id);
    void _setLine(int id,const char* str);
    void _GUI();
    void _GUI_TitleEditor();
    void _GUI_TitleHelp();
    void _GUI_LineNb();
    void _GUI_Line(Color ctext);
    void _GUI_title();
    void _GUI_help();
    void _screen_clear();
    void _write(const char* ptext);
    void _drawCmd();
    void _drawConfig();
public:
    Oide(int psize);
    void Load(const char* ptext);
    void Draw();
    void Free();
};

