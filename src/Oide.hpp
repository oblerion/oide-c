#pragma once
#include "raylib.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
//#include "Cmd.hpp"
#include "kbd_layout.h"
//#include "gui_layout_config.h"
#include <string>
#include <vector>

#define OIDE_VERSION "a0.2"

typedef struct {
    bool WindowBox000Active;
    Color ColorPicker001Value;
    Color ColorPicker002Value;
    Color ColorPicker003Value;
    int ToggleGroup007Active;

    Rectangle layoutRecs[10];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiLayoutConfigState;

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

