#include "Oide.h"
#include "text.h"
#include "asset/ftic80.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#define GUI_LAYOUT_CONFIG_IMPLEMENTATION
#include "gui_layout_config.h"
#include "cstring.h"

struct Oide
{
    enum OideScene scene;
    struct OideConfig config;
    Font font;
    int size;
    int offy;
    char lstr[100000];
    //char lstr2[1000000];
    char filepath[150];
    GuiLayoutConfigState state_config;
};
struct Oide _Oide;

const int nbLine()
{
   // const char* cstr = dstr_tos(_Oide.lstr);
    return text_nbLine(_Oide.lstr);
}
void ControlSub()
{
    if(_Oide.offy>0)
    {
        if(GetMouseWheelMove()>0 ||
            IsKeyDown(KEY_UP)
        )
            _Oide.offy--;
    }
    const int lsize = nbLine();
    if(_Oide.offy<lsize-1)
    if(GetMouseWheelMove()<0 ||
        IsKeyDown(KEY_DOWN)
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
    const int maxline = nbLine();
    if(n<maxline)
    {
        //_Oide.lstr.erase(_Oide.lstr.begin()+n);
        const char* rstr = text_delLine(_Oide.lstr,n);
        strcpy(_Oide.lstr,rstr);
    }
}
void addLine(int n,const char* str)
{
    const int maxline = nbLine();
    if(n<maxline)
    {
        const char* rstr = text_addLine(_Oide.lstr,n,str);
        strcpy(_Oide.lstr,rstr);
    }
    //_Oide.lstr.insert(_Oide.lstr.begin()+n,DSTRING_CPY(str));
}
const char* getLine(int id)
{
    const int length = nbLine();
    if(id<0 || id>length) return "";
    return text_getLine(_Oide.lstr,id);
}
void setLine(int id,const char* str)
{
    const char* rstr = text_setLine(_Oide.lstr,id,str);
    strcpy(_Oide.lstr,rstr);
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
    DrawTextEx(_Oide.font,
        TextFormat("file : %s",_Oide.filepath),
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
        if(i<nbLine())
        {
            DrawTextEx(_Oide.font,
                TextFormat("%d",i+1),
                (Vector2){1,2+(float)((i-_Oide.offy+1)*_Oide.size)},_Oide.size,0,_Oide.config.ctext);
        }
    }
}
// void Oide_GUI_HightLight(
//     vstring lstr,
//     const char* s,
//     Color color)
// {
//     for(int i=_Oide.offy;i<35+_Oide.offy;i++)
//     {
//         if(i<(signed int)lstr.size())
//         {
//             std::vector<int> vi =
//             dstr_finds_a(lstr[i],s);
//             for(int fi=0;fi<(signed int)vi.size();fi++)
//             {
//                // printf("f %d\n",vi[fi]);
//                 DrawTextEx(_Oide.font,
//                     s,
//                     (Vector2){(float)100+vi[fi],2+(float)((i-_Oide.offy+1)*_Oide.size)},_Oide.size,0,color);
//
//             }
//             // vi.clear();
//         }
//     }
// }

void Oide_GUI_Line(Color ctext)
{
    const int nline = nbLine();
    const char* tmp_line[35];
    for(int i=0;i<35;i++)
    {
        tmp_line[i] = getLine(i+_Oide.offy);
        printf("i %d l = %lu\n",i,strlen(tmp_line[i]));
    }

    for(int i=_Oide.offy;i<35+_Oide.offy;i++)
    {
        if(i<nline)
        {
            DrawTextEx(_Oide.font,
                tmp_line[i-_Oide.offy],
                (Vector2){100,2+(float)((i-_Oide.offy+1)*_Oide.size)},_Oide.size,0,ctext);

        }
    }
    //Oide_GUI_HightLight(lstr,"int",BLUE);
}


const char* vscreen_title =
"           _     __   \n"
"  ____    (_)___/ /__ \n"
" / __ \\  / / __  / _ \\\n"
"/ /_/ / / / /_/ /  __/\n"
"\\____(_)_/\\__,_/\\___/\n"
"tape help\n"
"or\n"
"drag and drop file\n";
void Oide_GUI_title()
{
    const int nline = text_nbLine(vscreen_title);
    for(int i=0;i<nline;i++)
    {
        DrawTextEx(_Oide.font,
            text_getLine(vscreen_title,i),
            (Vector2){100,2+(float)(
                (i+1)*_Oide.size)},_Oide.size,0,_Oide.config.ctext);


    }
}
const char* vscreen_help =
"\n"
"save [filepath]       save file\n"
"save                  save local file\n"
"load [filepath]       load file\n"
"\n"
"list [nline]          print line start at nline\n"
"add [nline]           add line at nline\n"
"del [nline]           delete line nline\n"
"copy [nline] [nline2] copy nline to nline2\n"
"edit [nline]          edit line nline\n"
"clear                 clear local file\n"
"help                  draw help\n"
"config                draw config gui\n"
"[nline]               clear line nline\n"
"[nline] [strline]     write strline to line nline\n"
"close                 close help/config";
void Oide_GUI_help()
{
    const int nline = text_nbLine(vscreen_help);
    for(int i=0;i<nline;i++)
    {
        DrawTextEx(_Oide.font,
            text_getLine(vscreen_help,i),
            (Vector2){100,2+(float)((i-_Oide.offy+1)*_Oide.size)},_Oide.size,0,_Oide.config.ctext);
    }
}
void Oide_screen_clear()
{
    strcpy(_Oide.filepath,"");
    //_Oide.lstr.clear();
    strcpy(_Oide.lstr,"");
    Cmd_reset();
}
void Oide_Load(const char* ptext)
{
    FILE* fic = fopen(ptext,"r");
    if(fic!=NULL)
    {
        fseek(fic,0,SEEK_END);
        const long int size = ftell(fic);
        fseek(fic,0,SEEK_SET);
        char lc[1];
        if(size<1000000)
        {
            strcpy(_Oide.filepath,ptext);
            for(int i=0;i<size;i++)
            {
                fscanf(fic,"%c",lc);
                printf("i %d c %s\n",i,lc);
                if(strlen(lc)+strlen(_Oide.lstr)<1000000)
                strcat(_Oide.lstr,lc);
                // i++;
                // sptr=fgets(lc,256,fic);
            }
        }
        fclose(fic);
    }
}
void Oide_write(const char* ptext)
{
    const int maxline = nbLine();
    FILE* fic = fopen(ptext,"w");
    if(fic!=NULL)
    {
        for(int i=0;i<maxline;i++)
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
                    Oide_write(_Oide.filepath);
                }
                else
                {
                    Oide_write(Cmd_getVal());
                    strcpy(_Oide.filepath,Cmd_getVal());
                }

            }
            else if(sfinds(ccom,"config")==0)
            {
                _Oide.scene = oi_config;
                _Oide.state_config.ToggleGroup007Active = Cmd_getLayout();

                _Oide.state_config.ColorPicker001Value= _Oide.config.cbg;
                _Oide.state_config.ColorPicker002Value= _Oide.config.ctext;
                _Oide.state_config.ColorPicker003Value= _Oide.config.ccursor;
            }
            else if(sfinds(ccom,"help")==0)
            {
                Oide_GUI_help();
                _Oide.scene = oi_help;
            }
            else if(ccom[0]=='!')
            {
                const char* lpath = GetPrevDirectoryPath(_Oide.filepath);
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
            }
        }
    }
}

void Oide_drawConfig()
{
    GuiLayoutConfig(&_Oide.state_config);
    if(_Oide.state_config.WindowBox000Active==false)
    {
        _Oide.state_config.WindowBox000Active=true;
        _Oide.scene=oi_dt;
        ConfigSave(&_Oide.config);
    }
    else
    {
        Cmd_setLayout(_Oide.state_config.ToggleGroup007Active);
        _Oide.config.layout=_Oide.state_config.ToggleGroup007Active;
        _Oide.config.cbg = _Oide.state_config.ColorPicker001Value;
        _Oide.config.ctext = _Oide.state_config.ColorPicker002Value;
        _Oide.config.ccursor = _Oide.state_config.ColorPicker003Value;
    }

}
void Oide(int psize)
{
    _Oide = (struct Oide){
        oi_dt,
        ConfigLoad(),
        LoadFont_Ftic80(),
        psize,
        0,
        "",
        //"",
        "",
        InitGuiLayoutConfig()
    };
    Cmd();
    Cmd_setLayout(_Oide.config.layout);
    //strcpy(_Oide.filepath,"");
    //Oide_GUI_title();
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
            if(strlen(_Oide.lstr)==0)
                Oide_GUI_title();
            else
                Oide_GUI_Line(_Oide.config.ctext);
        break;
        case oi_config:
            Oide_drawConfig();
        break;
        case oi_help:
            Oide_GUI(_Oide.config,_Oide.size);
            Oide_GUI_TitleHelp();
            Oide_GUI_help();
        break;
        default:;
    }
    Oide_drawCmd();
}
void Oide_Free()
{
    Cmd_free();
    UnloadTexture(_Oide.font.texture);
}
