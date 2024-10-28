#include "dstring.h"
// ---- private function
struct e_string* ESTRING()
{
    struct e_string* estr = (struct e_string*) malloc(sizeof(struct e_string));
    estr->car=0;
    estr->ptr_d=NULL;
    estr->ptr_u=NULL;
    return estr;
}
// ----- public function
dstring* DSTRING()
{
    dstring* dstr = (dstring*)malloc(sizeof(dstring));
    dstr->ptr= NULL;
    dstr->size=0;
    return dstr;
}
void dstr_print(dstring* dstr)
{
    if(dstr==NULL) return;
    struct e_string* estr = dstr->ptr;
    printf("\nsize %d",dstr->size);
    while(estr!=NULL)
    {
        char pu =0;
        char pd=0;
        if(estr->ptr_u==NULL) pu=0;
        else pu=1;

        if(estr->ptr_d==NULL) pd=0;
        else pd=1;
        printf("\npd %d pu %d car %c",pd,pu,estr->car);
        estr = estr->ptr_u;
    }
}

int dstr_len(dstring* dstr)
{
    if(dstr==NULL) return -1;
    return dstr->size;
}

void dstr_addc(dstring* dstr, char c)
{
    if(dstr==NULL) return;
    struct e_string* estr = dstr->ptr;
    if(estr==NULL)
    {
        dstr->ptr = ESTRING();
        dstr->ptr->car = c;
        dstr->size++;
    }
    else
    {
        while(estr!=NULL)
        {
            if(estr->ptr_u==NULL)
            {
                estr->ptr_u = ESTRING();
                estr->ptr_u->car=c;
                estr->ptr_u->ptr_d = estr;
                dstr->size++;
                break;
            }
            estr = estr->ptr_u;
        }
    }

}

void dstr_addc_p(dstring* dstr, char c,int pos)
{
    if(dstr==NULL) return;
    const int length = dstr_len(dstr);
    struct e_string* estr = dstr->ptr;
    int ipos=0;
    
    if(estr==NULL || pos==length)
    {
        dstr_addc(dstr,c);
    }
    else
    while(estr!=NULL)
    {
        if(ipos==pos)
        {
            if(estr->ptr_d==NULL &&
                estr->ptr_u!=NULL)
            {
                struct e_string* lestr = ESTRING();
                lestr->car=c;
                lestr->ptr_d=NULL;
                lestr->ptr_u=estr;
                estr->ptr_d=lestr;
                dstr->ptr=lestr;
                dstr->size++;
            }
            else if(estr->ptr_d!=NULL &&
                    estr->ptr_u!=NULL)
            {
                struct e_string* lestr = ESTRING();
                lestr->car=c;
                lestr->ptr_d=estr;
                lestr->ptr_u=estr->ptr_u;
                estr->ptr_u->ptr_d=lestr;
                estr->ptr_u=lestr;
                dstr->size++;
            }
            else if(estr->ptr_d!=NULL &&
                    estr->ptr_u==NULL)
            {
                struct e_string* lestr = ESTRING();
                lestr->car=c;
                lestr->ptr_u=NULL;
                lestr->ptr_d=estr;
                estr->ptr_u=lestr;
                dstr->size++;
            }
            break;
        }
        ipos++;
        estr = estr->ptr_u;
    }
}

void dstr_cat(dstring* dstr, const char* s)
{
    const int length = strlen(s);
    for(int i=0;i<length;i++)
    {
        dstr_addc(dstr,s[i]);
    }
}

void dstr_del(dstring* dstr, int pos)
{
    if(pos>dstr_len(dstr)) return;
    struct e_string* estr = dstr->ptr;
    int ipos=0;

    while(estr!=NULL)
    {
        if(ipos==pos)
        {
            if(estr->ptr_d==NULL &&
                estr->ptr_u!=NULL)
            {
                estr->ptr_u->ptr_d=NULL;
                dstr->ptr = estr->ptr_u;
                free(estr);
                dstr->size--;
            }
            else if(estr->ptr_d!=NULL &&
                    estr->ptr_u!=NULL)
            {
                estr->ptr_d->ptr_u = estr->ptr_u;
                free(estr);
                dstr->size--;
            }
            else if(estr->ptr_d!=NULL &&
                    estr->ptr_u==NULL)
            {
                estr->ptr_d->ptr_u = NULL;
                free(estr);
                dstr->size--;
            }
            break;
        }
        ipos++;
        estr = estr->ptr_u;
    }
}

char dstr_at(dstring* dstr, int id)
{
    struct e_string* estr = dstr->ptr;
    int ipos=0;
    while(estr!=NULL)
    {
        if(id==ipos)
        {
            return estr->car;
        }
        ipos++;
        estr = estr->ptr_u;
    }
    return 0;
}

void dstr_cpy(dstring* dstr, const char* s)
{
    dstr_clear(dstr);
    dstr_cat(dstr,s);
}

const char* dstr_sub(dstring* dstr, int pos)
{
    if(pos>dstr->size || pos<0) return NULL;
    dstring* ldstr = DSTRING();
    dstr_cpy(ldstr,dstr_tos(dstr));
    
    struct e_string* estr=NULL;
    int ipos=0;
    while(ldstr->ptr!=NULL)
    {
        if(ipos==pos) break;
        estr = ldstr->ptr->ptr_u;
        estr->ptr_d=NULL;
        free(ldstr->ptr);
        ldstr->ptr = estr;
        ldstr->size--;
        ipos++;
    }
    const char* rstr = dstr_tos(ldstr);
    dstr_free(ldstr);
    return rstr;
}

const char* dstr_subn(dstring* dstr, int pos, int n)
{
    dstring* ldstr = DSTRING();
    const char* cc = dstr_sub(dstr,pos);
    dstr_cpy(ldstr,cc);
    while(ldstr->size>n)
    {
        dstr_del(ldstr,n);
    }
    const char* cstr = dstr_tos(ldstr);
    dstr_free(ldstr);
    return cstr;
}

const char* dstr_tos(dstring* dstr)
{
    const int length = dstr_len(dstr);
    if(length>-1)
    {
        char* tstr = (char*)malloc(length);
        for(int i=0;i<length;i++)
        {
            tstr[i] = dstr_at(dstr,i);
        }
        tstr[length]='\0';
        return tstr;
    }
    return "";
}

int dstr_cmp(dstring* dstr,const char* s)
{
    int ir=0;
    const int length = strlen(s);
    if(length==dstr_len(dstr) &&
        dstr_finds(dstr,s)==0
    )
    {
        ir=1;
    }
    return ir;
}

void dstr_clear(dstring* dstr)
{
    if(dstr==NULL) return;
    struct e_string* estr=NULL;
    while(dstr->ptr!=NULL)
    {
        estr = dstr->ptr->ptr_u;
        free(dstr->ptr);
        dstr->ptr = estr;
    }
    dstr->ptr=NULL;
    dstr->size=0;
}
int dstr_find(dstring* dstr,char c)
{
	const char* tstr = dstr_tos(dstr);
	int pos=-1;
	for(int i=0;i<dstr_len(dstr);i++)
    {
        if(tstr[i]==c) { pos=i;break; }
    }
    return pos;
}
int dstr_finds(dstring* dstr, const char* s)
{
    const char* tstr = dstr_tos(dstr);
    int tofnd = strlen(s);
    int fnd = 0;
    int pos = -1;
    for(int i=0;i<dstr_len(dstr);i++)
    {
        if(tstr[i]==s[fnd])
        {
            if(fnd==0 && pos==-1)
                pos=i;
            if(fnd==tofnd-1)
                return pos;
            fnd++;

        }
        else
        {
            pos=-1;
            fnd=0;
        }
    }
    return -1;
}


void dstr_free(dstring* dstr)
{
    if(dstr==NULL) return;
    struct e_string* estr=NULL;
    while(dstr->ptr!=NULL)
    {
        estr = dstr->ptr->ptr_u;
        free(dstr->ptr);
        dstr->ptr = estr;
    }
    free(dstr);
    dstr=NULL;
}
