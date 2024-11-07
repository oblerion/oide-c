#include "Oide.hpp"
#include "asset/ftic80.h"

const int Oide::_nbLine()
{
    return lstr.size();
}
void Oide::_ControlSub()
{
    if(offy>0)
    {
        if(GetMouseWheelMove()>0 ||
            IsKeyDown(KEY_UP)
        )
            offy--;
    }
    const int lsize = _nbLine();
    if(offy<lsize-1)
    if(GetMouseWheelMove()<0 ||
        IsKeyDown(KEY_DOWN)
    )
    {
        offy++;
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

void Oide::_delLine(int n)
{
    const int maxline = _nbLine();
    if(n<maxline)
    {
        lstr.erase(lstr.begin()+n);
    }
}
void Oide::_addLine(int n,const char* str)
{
   // const int maxline = _nbLine();
    while(n>=_nbLine())
    {
         lstr.push_back("");
    }
    if(n<_nbLine())
    {
        std::string _lstr = str;
        lstr.insert(lstr.begin()+n,str);
    }
}
std::string Oide::_getLine(int id)
{
    const int length = _nbLine();
    if(id<0 || id>length) return "";
    return lstr[id];
    //return text_getLine(_Oide.lstr,id);
}
void Oide::_setLine(int id,const char* str)
{
    if(id<0) return;
    while(id>=_nbLine())
    {
         lstr.push_back("");
    }
    lstr[id] = str;
}

void Oide::_GUI()
{
    Color ccursor1 = ColorAlpha(config.ccursor,0.5f);
    Color ccursor2 = ColorBrightness(config.ccursor,0.5f);
    DrawRectangle(1,1,GetRenderWidth()-1,size,ccursor1);
    DrawRectangleLines(1,1,GetRenderWidth()-1,size,ccursor2);
    DrawRectangleLines(97,size,GetScreenWidth()-97,
                       GetScreenHeight()-(size*2),ccursor2);
}
void Oide::_GUI_TitleEditor()
{
    DrawTextEx(font,
        TextFormat("file : %s",filepath),
        (Vector2){1,2},size,0,config.ctext);
}
void Oide::_GUI_TitleHelp()
{
    DrawTextEx(font,
        "Console Help",
        (Vector2){1,2},size,0,config.ctext);
}
void Oide::_GUI_LineNb()
{
    for(int i=offy;i<35+offy;i++)
    {
        if(i<_nbLine())
        {
            DrawTextEx(font,
                TextFormat("%d",i+1),
                (Vector2){1,2+(float)((i-offy+1)*size)},size,0,config.ctext);
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

void Oide::_GUI_Line(Color ctext)
{
    const int nline = _nbLine();

    for(int i=offy;i<35+offy;i++)
    {
        if(i<nline)
        {
            DrawTextEx(font,
                _getLine(i).c_str(),
                (Vector2){100,2+(float)((i-offy+1)*size)},size,0,ctext);

        }
    }
    //Oide_GUI_HightLight(lstr,"int",BLUE);
}


const char* vscreen_title[8] = {
"           _     __   ",
"  ____    (_)___/ /__ ",
" / __ \\  / / __  / _ \\",
"/ /_/ / / / /_/ /  __/",
"\\____(_)_/\\__,_/\\___/",
"tape help",
"or",
"drag and drop file"};
void Oide::_GUI_title()
{
    const int nline = 8;
    for(int i=0;i<nline;i++)
    {
        DrawTextEx(font,
            vscreen_title[i],
            (Vector2){100,2+(float)(
                (i+1)*size)},size,0,config.ctext);
    }
}
const char* vscreen_help[16] = {
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
void Oide::_GUI_help()
{
    const int nline = 16;
    for(int i=0;i<nline;i++)
    {
        DrawTextEx(font,
            vscreen_help[i],
            (Vector2){100,2+(float)((i-offy+1)*size)},size,0,config.ctext);
    }
}
void Oide::_screen_clear()
{
    strcpy(filepath,"");
    lstr.clear();
    //strcpy(_Oide.lstr,"");
    cmd.Reset();
}
void Oide::Load(const char* ptext)
{
    FILE* fic = fopen(ptext,"rb");
    if(fic!=NULL)
    {
        puts(ptext);
        fseek(fic,0,SEEK_END);
        const long int size = ftell(fic);
        fseek(fic,0,SEEK_SET);

        if(size>0 && size<10000000)//OIDE_MAX_CHAR)
        {
            strcpy(filepath,ptext);
            lstr.clear();
            char sfile;
            std::string str;

            long int nline=0;
            while (fscanf(fic, "%c", &sfile) != EOF)
            {
                if(sfile=='\n' || sfile=='\0')
                {
                    nline++;
                }
            }
            lstr.reserve(nline);
            fseek(fic,0,SEEK_SET);
            while (fscanf(fic, "%c", &sfile) != EOF)
            {
                if(sfile=='\n' || sfile=='\0')
                {
                    str+='\0';
                    lstr.push_back(str.c_str());
                    str.clear();
                }
                else
                    str  += sfile;

            }
        }
        else
        {
            strcpy(filepath,ptext);
            lstr.clear();
            lstr.push_back("");
        }
        fclose(fic);
    }
}
void Oide::_write(const char* ptext)
{
    const int maxline = _nbLine();
    FILE* fic = fopen(ptext,"w");
    if(fic!=NULL)
    {
        for(int i=0;i<maxline;i++)
        {
            fprintf(fic,"%s\n",_getLine(i).c_str());
        }
        fclose(fic);
    }
}
void Oide::_drawCmd()
{
    if(cmd.Draw(size,font,config.ctext,config.ccursor)==true)
    {
        std::string ccom = cmd.GetCom();
        const int num = atoi(ccom.c_str());
        if(scene==oi_dt)
        {
            std::string cval = cmd.GetVal();
            if(num>0)
                _setLine( num-1,cval.c_str());
            else if(ccom == "edit")
            {
                cmd.Edit(_getLine(std::stoi(cval)-1).c_str());
            }
            else if(ccom == "list")
            {
                const int op = std::stoi(cval);
                if (op==0)
                {
                    offy = 0;
                }
                else
                {
                    offy = op-1;
                }
            }
            else if(ccom == "clear")
            {
                _screen_clear();
            }
            else if(ccom == "copy")
            {
                _setLine(
                    std::stoi(cmd.GetVal2())-1,
                    _getLine(std::stoi(cmd.GetVal())-1).c_str());
            }
            else if(ccom == "add")
            {
                _addLine(std::stoi(cmd.GetVal())-1,"");
            }
            else if(ccom == "del")
            {
                _delLine(std::stoi(cmd.GetVal())-1);
            }
            else if(ccom == "load")
            {
                Load(cmd.GetVal().c_str());
            }
            else if(ccom == "save")
            {
                if(cmd.GetVal().length()==0)
                {
                    _write(filepath);
                }
                else
                {
                    _write(cmd.GetVal().c_str());
                    strcpy(filepath,cmd.GetVal().c_str());
                }

            }
            else if(ccom == "config")
            {
                scene = oi_config;
                state_config.ToggleGroup007Active = cmd.GetLayout();

                state_config.ColorPicker001Value= config.cbg;
                state_config.ColorPicker002Value= config.ctext;
                state_config.ColorPicker003Value= config.ccursor;
            }
            else if(ccom == "help")
            {
                _GUI_help();
                scene = oi_help;
            }
            else if(ccom[0]=='!')
            {
                std::string lpath = GetPrevDirectoryPath(filepath);
                std::string scmd_c = cmd.GetCmd().c_str();
                std::string scmd="";
                if(lpath.length()==0)
                    scmd = scmd_c.substr(1,scmd_c.length()-1);
                else
                {
#if defined(_WIN32)
                    scmd = "cd "+lpath+" && "+scmd.substr(1,scmd_c.length()-1);
#endif
                }
                system(scmd.c_str());
            }
        }
        else if(scene==oi_config)
        {
            if(ccom == "close")
            {
                scene = oi_dt;
                ConfigSave(&config);
            }
        }
        else if(scene==oi_help)
        {
            if(ccom == "close")
            {
                scene = oi_dt;
            }
        }
    }
}

void Oide::_drawConfig()
{
    GuiLayoutConfig(&state_config);
    if(state_config.WindowBox000Active==false)
    {
        state_config.WindowBox000Active=true;
        scene=oi_dt;
        ConfigSave(&config);
    }
    else
    {
        cmd.SetLayout(state_config.ToggleGroup007Active);
        config.layout=state_config.ToggleGroup007Active;
        config.cbg = state_config.ColorPicker001Value;
        config.ctext = state_config.ColorPicker002Value;
        config.ccursor = state_config.ColorPicker003Value;
    }

}
Oide::Oide(int psize)
{
    scene=oi_dt;
    config=ConfigLoad();
    font=LoadFont_Ftic80();
    size=psize;
    offy=0;
    strcpy(filepath,"");
    state_config = InitGuiLayoutConfig();
    cmd.SetLayout(config.layout);
    lstr.reserve(1);
}

void Oide::Draw()
{
    _ControlSub();
    ClearBackground(config.cbg);
    switch(scene)
    {
        case oi_dt:
            _GUI();
            _GUI_TitleEditor();
            _GUI_LineNb();
            if(_nbLine()==0)
                _GUI_title();
            else
                _GUI_Line(config.ctext);
        break;
        case oi_config:
            _drawConfig();
        break;
        case oi_help:
            _GUI();
            _GUI_TitleHelp();
            _GUI_help();
        break;
        default:;
    }
    _drawCmd();
}
void Oide::Free()
{
    lstr.clear();
    UnloadTexture(font.texture);
}
