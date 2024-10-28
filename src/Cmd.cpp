#include "Cmd.h"
struct Cmd _Cmd;

void Cmd()
{
    Cmd_reset();
    _Cmd.layout_type = EN_US;
    _Cmd.scmd= DSTRING();
    _Cmd.scom = DSTRING();
    _Cmd.svalue = DSTRING();
    _Cmd.svalue2 = DSTRING();
    _Cmd.scmd_tmp = DSTRING();
}
void Cmd_edit(const char* str)
{
    const int pos = atoi(Cmd_getVal());
    if(pos>0 && dstr_finds(_Cmd.scom,"edit")==0)
    {
        dstr_cpy(_Cmd.scmd,TextFormat("%s %s",Cmd_getVal(),str));
        _Cmd.cursor_x=dstr_len(_Cmd.scmd);
    }
}

void Cmd_reset()
{
    dstr_clear(_Cmd.scmd);
    _Cmd.cursor_x=0;
}


bool Cmd_draw(int size,Font font,Color ctxt,Color ccur)
{
    bool rb =false;
    // add letter
    int k = Kbd_GetKeyPressed(
        _Cmd.layout_type); //GetKeyPressed();
    const int length = dstr_len(_Cmd.scmd);

    if(IsKeyPressed(KEY_BACKSPACE))
    {
        if(_Cmd.cursor_x-1 < length && _Cmd.cursor_x>0)
        {
            if(length==1)
                dstr_clear(_Cmd.scmd);
            else
                dstr_del(_Cmd.scmd,_Cmd.cursor_x-1);
            // for(int i=_Cmd.cursor_x-1;i<length;i++)
            // {
            //         _Cmd.scmd[i]=_Cmd.scmd[i+1];
            // }
            _Cmd.cursor_x--;
        }
    }
    else if(IsKeyPressed(KEY_RIGHT))
    {
        if(_Cmd.cursor_x < 300)
            _Cmd.cursor_x+=1;
    }
    else if(IsKeyPressed(KEY_LEFT))
    {
        if(_Cmd.cursor_x > 0)
        _Cmd.cursor_x-=1;
    }
    else if(IsKeyPressed(KEY_ENTER))
    {
        const int fpos = dstr_find(_Cmd.scmd,' ');
        dstr_cpy(_Cmd.scmd_tmp,dstr_tos(_Cmd.scmd));
        if(fpos>-1)
        {
            const char* sval = TextSubtext(dstr_tos(_Cmd.scmd),fpos+1,dstr_len(_Cmd.scmd)-(fpos+1));
            dstr_cpy(_Cmd.svalue,sval);
            const char* scom= TextSubtext(dstr_tos(_Cmd.scmd),0,fpos);
            dstr_cpy(_Cmd.scom,scom);

            const int fpos2 = dstr_find(_Cmd.svalue,' ');
            if(fpos2>-1)
            {
                const int l = dstr_len(_Cmd.svalue);
                dstr_cpy(_Cmd.svalue2,TextSubtext(dstr_tos(_Cmd.svalue),fpos2+1,l-(fpos2+1)));
                dstr_cpy(_Cmd.svalue,TextSubtext(dstr_tos(_Cmd.svalue),0,fpos2));
            }
            else
                dstr_clear(_Cmd.svalue2);

            rb=true;
            Cmd_reset();

        }
        else
        {
            dstr_clear(_Cmd.svalue);
            dstr_cpy(_Cmd.scom,dstr_tos(_Cmd.scmd));
            rb=true;
            Cmd_reset();
        }
    }
    else if(k!=0 &&
        k != KEY_LEFT_SHIFT &&
        k != KEY_RIGHT_SHIFT)
    {
        //printf("c %c pos %d l %d\n",k,_Cmd.cursor_x,dstr_len(_Cmd.scmd));
        dstr_addc_p(_Cmd.scmd,(char)k,_Cmd.cursor_x);

        _Cmd.cursor_x++;
    }
    Color ccursor1 = ColorAlpha(ccur,0.5f);
    Color ccursor2 = ColorBrightness(ccur,0.5f);
    DrawRectangle(1,GetScreenHeight()-size-1,GetRenderWidth()-1,size,ccursor1);
    DrawRectangleLines(1,GetScreenHeight()-size-1,GetRenderWidth()-1,size,ccursor2);
    DrawTextEx(font,">>",(Vector2){0,(float)(GetRenderHeight()-size)},size,0,ctxt);
    DrawTextEx(font,dstr_tos(_Cmd.scmd),(Vector2){30,(float)(GetRenderHeight()-size)},size,0,ctxt);
    DrawRectangle(
        30+(_Cmd.cursor_x*size),
        (float)(GetRenderHeight()-size)-1,
        size/2,
        size,
        ccur
    );
    return rb;
}
const char* Cmd_getCmd()
{
    return dstr_tos(_Cmd.scmd_tmp);
}
const char* Cmd_getCom()
{
    return dstr_tos(_Cmd.scom);
}
const char* Cmd_getVal()
{
    return dstr_tos(_Cmd.svalue);
}
const char* Cmd_getVal2()
{
    return dstr_tos(_Cmd.svalue2);
}
KBD_Layout Cmd_getLayout()
{
    return _Cmd.layout_type;
}
void Cmd_setLayout(int il)
{
    switch(il)
    {
        case 0: _Cmd.layout_type=EN_US;break;
        case 1: _Cmd.layout_type=EN_UK;break;
        case 2: _Cmd.layout_type=FR;break;
        case 3: _Cmd.layout_type=FR_BEL_VAR;break;
        default: ;
    }
}
void Cmd_free()
{
    dstr_free(_Cmd.scom);
    dstr_free(_Cmd.svalue);
    dstr_free(_Cmd.svalue2);
    dstr_free(_Cmd.scmd);
    dstr_free(_Cmd.scmd_tmp);
}
