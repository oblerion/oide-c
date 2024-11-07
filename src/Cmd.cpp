#include "Cmd.hpp"

Cmd::Cmd()
{
    layout_type = EN_US;
    scmd = "";
    scom = "";
    svalue = "";
    svalue2 = "";
    scmd_tmp = "";
    cursor_x=0;
    cursor_y=0;
}
void Cmd::Edit(const char* str)
{
    const int pos = std::stoi(GetVal());
    if(pos>0 && scom == "edit")
    {
        scmd = GetVal()+" "+str;
        cursor_x= scmd.length();
    }
}

void Cmd::Reset()
{
    scmd.clear();
    cursor_x=0;
}


bool Cmd::Draw(int size,Font font,Color ctxt,Color ccur)
{
    bool rb =false;
    // add letter
    int k = Kbd_GetKeyPressed(
        layout_type); //GetKeyPressed();
    const int length = scmd.length();

    if(IsKeyPressed(KEY_BACKSPACE))
    {
        if(cursor_x-1 < length && cursor_x>0)
        {
            if(length==1)
                scmd.clear();
            else
            {
                for(int i=cursor_x-1;i<length;i++)
                {
                        scmd[i]=scmd[i+1];
                }
            }
            cursor_x--;
        }
    }
    else if(IsKeyPressed(KEY_RIGHT))
    {
        if(cursor_x < 300)
            cursor_x+=1;
    }
    else if(IsKeyPressed(KEY_LEFT))
    {
        if(cursor_x > 0)
        cursor_x-=1;
    }
    else if(IsKeyPressed(KEY_ENTER))
    {
        const int fpos = scmd.find(" ");
        scmd_tmp = scmd;
        if(fpos>-1)
        {
            svalue = scmd.substr(fpos+1,scmd.length()-(fpos+1));
            scom = scmd.substr(0,fpos);

            const int fpos2 = svalue.find(" ");
            if(fpos2>-1)
            {
                const int l = svalue.length();
                svalue2 = svalue.substr(fpos2+1,l-(fpos2+1));
                svalue = svalue.substr(0,fpos2);
            }
            else
                svalue2.clear();

            rb=true;
            Reset();

        }
        else
        {
            svalue.clear();
            scom = scmd;
            rb=true;
            Reset();
        }
    }
    else if(k!=0 &&
        k != KEY_LEFT_SHIFT &&
        k != KEY_RIGHT_SHIFT)
    {
        scmd.insert(scmd.begin()+cursor_x,1,k);
        cursor_x++;
    }
    Color ccursor1 = ColorAlpha(ccur,0.5f);
    Color ccursor2 = ColorBrightness(ccur,0.5f);
    DrawRectangle(1,GetScreenHeight()-size-1,GetRenderWidth()-1,size,ccursor1);
    DrawRectangleLines(1,GetScreenHeight()-size-1,GetRenderWidth()-1,size,ccursor2);
    DrawTextEx(font,">>",(Vector2){0,(float)(GetRenderHeight()-size)},size,0,ctxt);
    DrawTextEx(font,scmd.c_str(),(Vector2){30,(float)(GetRenderHeight()-size)},size,0,ctxt);
    DrawRectangle(
        30+(cursor_x*size),
        (float)(GetRenderHeight()-size)-1,
        size/2,
        size,
        ccur
    );
    return rb;
}
std::string Cmd::GetCmd()
{
    return scmd_tmp;
}
std::string Cmd::GetCom()
{
    return scom;
}
std::string Cmd::GetVal()
{
    return svalue;
}
std::string Cmd::GetVal2()
{
    return svalue2;
}
KBD_Layout Cmd::GetLayout()
{
    return layout_type;
}
void Cmd::SetLayout(int il)
{
    switch(il)
    {
        case 0: layout_type=EN_US;break;
        case 1: layout_type=EN_UK;break;
        case 2: layout_type=FR;break;
        case 3: layout_type=FR_BEL_VAR;break;
        default: ;
    }
}

