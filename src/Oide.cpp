#include "Oide.h"
#define SOURCE_FTIC80
#include "asset/ftic80.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#define GUI_LAYOUT_CONFIG_IMPLEMENTATION
#include "gui_layout_config.h"
GuiLayoutConfigState state_config = InitGuiLayoutConfig();
#include "cstring.h"
#define vstring std::vector<std::string>

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

struct Oide
{
    enum OideScene scene;
    struct OideConfig config;
    Font font;
    int size;
    int offy;
    vstring lstr;
    vstring lstr2;
    dstring* filepath;
};
struct Oide _Oide;
void ControlSub()
{
    if(_Oide.offy>0)
    {
        if(GetMouseWheelMove()>0 ||
            IsKeyDown(KEY_DOWN)
        )
            _Oide.offy--;
    }
    const int lsize = _Oide.lstr.size();
    if(_Oide.offy<lsize-1)
    if(GetMouseWheelMove()<0 ||
        IsKeyDown(KEY_UP)
    )
    {
        _Oide.offy++;
    }
}
struct OideConfig ConfigLoad()
{
    struct OideConfig oc = {BLACK,WHITE,DARKGRAY,0};
    FILE* fic = fopen(".oide.conf","rb");
    if(fic!=NULL)
    {
        fread(&oc,sizeof(struct OideConfig),1,fic);
        fclose(fic);
    }
    return oc;
}
void ConfigSave(struct OideConfig* oc)
{
    FILE* fic = fopen(".oide.conf","wb");
    fwrite(oc,sizeof(struct OideConfig),1,fic);
    fclose(fic);
}

void delLine(int n)
{
    if(n<(signed int)_Oide.lstr.size())
    _Oide.lstr.erase(_Oide.lstr.begin()+n);
}
void addLine(int n,const char* str)
{
    if(n<=(signed int)_Oide.lstr.size())
    _Oide.lstr.insert(_Oide.lstr.begin()+n,str);
}
const char* getLine(int id)
{
    const int length = _Oide.lstr.size();
    if(id<0 || id>length) return "";
    return _Oide.lstr[id].c_str();
}
void setLine(int id,const char* str)
{
    if(id>-1)
    {
        while(id>=(signed int)_Oide.lstr.size())
        {
            _Oide.lstr.push_back("");
        }
        _Oide.lstr[id]=str;
    }else
        printf("warning : setline %d\n",id);
}

void Oide_GUI(struct OideConfig config,int size)
{
    Color ccursor1 = ColorAlpha(config.ccursor,0.5f);
    Color ccursor2 = ColorBrightness(config.ccursor,0.5f);
    DrawRectangle(1,1,GetRenderWidth()-1,size,ccursor1);
    DrawRectangleLines(1,1,GetRenderWidth()-1,size,ccursor2);
    DrawRectangleLines(97,size,GetScreenWidth()-97,
                       GetScreenHeight()-(size*2),ccursor2);
}
void Oide_GUI_TitleEditor()
{
    const char* cfilepath = dstr_tos(_Oide.filepath);
    DrawTextEx(_Oide.font,
        TextFormat("file : %s",cfilepath),
        (Vector2){1,2},_Oide.size,0,_Oide.config.ctext);
}
void Oide_GUI_TitleHelp()
{
    DrawTextEx(_Oide.font,
        "Console Help",
        (Vector2){1,2},_Oide.size,0,_Oide.config.ctext);
}
void Oide_GUI_LineNb()
{
    for(int i=_Oide.offy;i<35+_Oide.offy;i++)
    {
        if(i<(signed int)_Oide.lstr.size())
        {
            DrawTextEx(_Oide.font,
                TextFormat("%d",i+1),
                (Vector2){1,2+(float)((i-_Oide.offy+1)*_Oide.size)},_Oide.size,0,_Oide.config.ctext);
        }
    }
}
void Oide_GUI_Line(vstring lstr,Color ctext)
{
    for(int i=_Oide.offy;i<35+_Oide.offy;i++)
    {
        if(i<(signed int)lstr.size())
        {
            DrawTextEx(_Oide.font,
                getLine(i),
                (Vector2){100,2+(float)((i-_Oide.offy+1)*_Oide.size)},_Oide.size,0,ctext);

        }
    }
}


const vstring vscreen_title = {
"           _     __   ",
"  ____    (_)___/ /__ ",
" / __ \\  / / __  / _ \\",
"/ /_/ / / / /_/ /  __/",
"\\____(_)_/\\__,_/\\___/ ",
"tape help",
"or",
"drag and drop file"
};
void Oide_screen_title()
{
    _Oide.lstr2.clear();
    for(unsigned int i=0;i<_Oide.lstr.size();i++)
    {
        _Oide.lstr2.push_back(_Oide.lstr[i]);
    }
    _Oide.lstr = vscreen_title;
}
const vstring vscreen_help = {
"",
"save [filepath]       save file",
"save                  save local file",
"load [filepath]       load file",
"",
"list [nline]          print line start at nline",
"add [nline]           add line at nline",
"del [nline]           delete line nline",
"copy [nline] [nline2] copy nline to nline2",
"edit [nline]          edit line nline",
"clear                 clear local file",
"help                  draw help",
"config                draw config gui",
"[nline]               clear line nline",
"[nline] [strline]     write strline to line nline",
"close                 close help/config"
};
void Oide_screen_help()
{
    _Oide.lstr2.clear();
    for(unsigned int i=0;i<_Oide.lstr.size();i++)
    {
        _Oide.lstr2.push_back(_Oide.lstr[i]);
    }
    _Oide.lstr = vscreen_help;
}
void Oide_screen_back()
{
    _Oide.lstr.clear();
    for(unsigned int i=0;i<_Oide.lstr2.size();i++)
    {
        _Oide.lstr.push_back(_Oide.lstr2[i]);
    }
}
void Oide_screen_clear()
{
    dstr_clear(_Oide.filepath);
    _Oide.lstr.clear();
    Cmd_reset();
}
void Oide_Load(const char* ptext)
{
    FILE* fic = fopen(ptext,"r");
    if(fic!=NULL)
    {
        dstr_cpy(_Oide.filepath,ptext);
        char sc;
        // int nb=0;
        int i=0;
        // int j=0;
        _Oide.lstr.clear();
        dstring* _lstr = DSTRING();
        while(!feof(fic))
        {
            fscanf(fic,"%c",&sc);
            if(sc=='\n')
            {
                setLine(i,dstr_tos(_lstr));
                i++;
                dstr_clear(_lstr);
                //s.clear();
            }
            else
            {
                //s+=sc;
                dstr_addc(_lstr,sc);
            }
        }
        dstr_free(_lstr);
        //nb_line=nb;
        fclose(fic);
    }
}
void Oide_write(const char* ptext)
{
    FILE* fic = fopen(ptext,"w");
    if(fic!=NULL)
    {
        for(int i=0;i<(signed int)_Oide.lstr.size();i++)
        {
            fprintf(fic,"%s\n",getLine(i));
        }
        fclose(fic);
    }
}
void Oide_drawCmd()
{
    if(Cmd_draw(_Oide.size,_Oide.font,_Oide.config.ctext,_Oide.config.ccursor)==true)
    {
        const char* ccom = Cmd_getCom();
        const int num = atoi(ccom);
        if(_Oide.scene==oi_dt)
        {
            if(num>0)
                setLine( num-1,Cmd_getVal());
            else if(sfinds(ccom,"edit")==0)
            {
                Cmd_edit(getLine(atoi(Cmd_getVal())-1));
            }
            else if(sfinds(ccom,"list")==0)
            {
                const int op = atoi(Cmd_getVal());
                if (op==0)
                {
                    _Oide.offy = 0;
                }
                else
                {
                    _Oide.offy = op-1;
                }
            }
            else if(sfinds(ccom,"clear")==0)
            {
                Oide_screen_clear();
            }
            else if(sfinds(ccom,"copy")==0)
            {
                setLine(
                    atoi(Cmd_getVal2())-1,
                    getLine(atoi(Cmd_getVal())-1));
            }
            else if(sfinds(ccom,"add")==0)
            {
                addLine(atoi(Cmd_getVal())-1,"");
            }
            else if(sfinds(ccom,"del")==0)
            {
                delLine(atoi(Cmd_getVal())-1);
            }
            else if(sfinds(ccom,"load")==0)
            {
                Oide_Load(Cmd_getVal());
            }
            else if(sfinds(ccom,"save")==0)
            {
                if(strlen(Cmd_getVal())==0)
                {
                    Oide_write(dstr_tos(_Oide.filepath));
                }
                else
                {
                    Oide_write(Cmd_getVal());
                    dstr_cpy(_Oide.filepath,Cmd_getVal());
                }

            }
            else if(sfinds(ccom,"config")==0)
            {
                _Oide.scene = oi_config;
                state_config.ToggleGroup007Active = Cmd_getLayout();

                state_config.ColorPicker001Value= _Oide.config.cbg;
                state_config.ColorPicker002Value= _Oide.config.ctext;
                state_config.ColorPicker003Value= _Oide.config.ccursor;
            }
            else if(sfinds(ccom,"help")==0)
            {
                Oide_screen_help();
                _Oide.scene = oi_help;
            }
            else if(ccom[0]=='!')
            {
                const char* lpath = GetPrevDirectoryPath(dstr_tos(_Oide.filepath));
                const char* scmd;
                if(strlen(lpath)==0)
                    scmd = TextSubtext(Cmd_getCmd(),1,strlen(Cmd_getCmd())-1);
                else
                    scmd = TextFormat("cd %s && %s",
                            lpath,
                            TextSubtext(Cmd_getCmd(),1,strlen(Cmd_getCmd())-1));
                puts(scmd);
                system(scmd);
            }
        }
        else if(_Oide.scene==oi_config)
        {
            if(sfinds(ccom,"close")==0)
            {
                _Oide.scene = oi_dt;
                ConfigSave(&_Oide.config);
            }
        }
        else if(_Oide.scene==oi_help)
        {
            if(sfinds(ccom,"close")==0)
            {
                _Oide.scene = oi_dt;
                Oide_screen_back();
            }
        }
    }
}

void Oide_drawEditor()
{// max 36
    Oide_GUI_Line(_Oide.lstr,_Oide.config.ctext);
}
void Oide_drawConfig()
{
    GuiLayoutConfig(&state_config);
    if(state_config.WindowBox000Active==false)
    {
        state_config.WindowBox000Active=true;
        _Oide.scene=oi_dt;
        ConfigSave(&_Oide.config);
    }
    else
    {
        Cmd_setLayout(state_config.ToggleGroup007Active);
        _Oide.config.layout=state_config.ToggleGroup007Active;
        _Oide.config.cbg = state_config.ColorPicker001Value;
        _Oide.config.ctext = state_config.ColorPicker002Value;
        _Oide.config.ccursor = state_config.ColorPicker003Value;
    }

}
void Oide(int psize)
{
    _Oide = {
        oi_dt,
        ConfigLoad(),
        LoadFont_Ftic80(),
        psize,
        0
    };
    Cmd();
    Cmd_setLayout(_Oide.config.layout);
    _Oide.filepath = DSTRING();
    Oide_screen_title();
}

void Oide_Draw()
{
    ControlSub();
    ClearBackground(_Oide.config.cbg);
    switch(_Oide.scene)
    {
        case oi_dt:
            Oide_GUI(_Oide.config,_Oide.size);
            Oide_GUI_TitleEditor();
            Oide_GUI_LineNb();
            Oide_drawEditor();
        break;
        case oi_config:
            Oide_drawConfig();
        break;
        case oi_help:
            Oide_GUI(_Oide.config,_Oide.size);
            Oide_GUI_TitleHelp();
            Oide_drawEditor();
        break;
        default:;
    }
    Oide_drawCmd();
}
void Oide_Free()
{
    Cmd_reset();
    Cmd_free();
    _Oide.lstr.clear();
    _Oide.lstr2.clear();
    UnloadTexture(_Oide.font.texture);
    dstr_free(_Oide.filepath);
}
