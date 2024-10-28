#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>

// element list
struct e_lst
{
	void* pvar;
	struct e_lst* ptr_u;
	struct e_lst* ptr_d;	
};
// list
typedef struct
{
	int size;
	struct e_lst* ptr;
} lst;

lst* LST();                         // constructor
int lstlen(lst* list);              // lenght of list
void lstadd(lst* list,void* var);   // add var to list
void lstdel(lst* list,int id);      // delete at id
void* lstat(lst* list,int id);      // get at id
int lstfind(lst* list,void* var);   // find var
void lstclear(lst* list);           // clear list
void lstfree(lst* list);            // free memory space
#endif
