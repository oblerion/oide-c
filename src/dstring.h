#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// #include <vector>
struct e_string
{
    char car;
    struct e_string* ptr_d;
    struct e_string* ptr_u;
};

typedef struct
{
    int size;
    struct e_string* ptr;
}dstring;

dstring DSTRING(); //constructor
dstring DSTRING_CPY(const char* str);
void dstr_print(dstring dstr);              //debug print string
int dstr_len(dstring dstr);                 //get lenght
void dstr_addc(dstring* dstr,char c);        //add char to end
void dstr_addc_p(dstring* dstr, char c,int pos);
void dstr_cat(dstring* dstr,const char* s);       //add string to end
void dstr_del(dstring* dstr,int pos);        //remove char at pos
char dstr_at(dstring dstr,int id);          //get char at id
void dstr_cpy(dstring* dstr,const char* s);        //clear and copy string
const char* dstr_sub(dstring* dstr,int pos);        //dstr = all after pos
const char* dstr_subn(dstring* dstr,int pos,int n); //dstr = n char after pos
const char* dstr_tos(dstring dstr);               //create char* with dstr
int dstr_find(dstring dstr,char c);
int dstr_finds(dstring dstr,const char* s);        //get pos of string s
// std::vector<int> dstr_finds_a(dstring dstr,const char* s);
int dstr_cmp(dstring dstr,const char* s);	//1 == ,0 not
void dstr_clear(dstring* dstr);              //clear string
void dstr_free(dstring* dstr);               //free memory

