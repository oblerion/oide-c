#include "list.h"

// ----- private e_list function ---------------
struct e_lst* ELST()
{
	struct e_lst* e_list = (struct e_lst*)malloc(sizeof(struct e_lst));
	e_list->pvar = NULL;
	e_list->ptr_u = NULL;
	e_list->ptr_d = NULL;
	return e_list;
}
// ------- public list function ------------------------
lst* LST()
{
	lst* list = (lst*)malloc(sizeof(lst));
	list->size=0;
	list->ptr = NULL;
	return list;
}

int lstlen(lst* list)
{
	if(list==NULL) return -1;
	return list->size;
}
void lstadd(lst* list,void* var)
{
	if(list==NULL) return;
	if(list->ptr==NULL)
	{// list is void
		list->ptr = ELST();
		list->ptr->pvar=var;
		list->size++;
	}
	else
	{// list len => 1
		struct e_lst* eptr=list->ptr;
		while(eptr!=NULL)
		{
			if(eptr->ptr_u==NULL)
			{
				eptr->ptr_u = ELST();
				eptr->ptr_u->pvar = var;
				eptr->ptr_u->ptr_d = eptr;
				list->size++;
				break;
			}
			eptr=eptr->ptr_u;
		}
	}
}
void lstdel(lst* list,int id)
{
	int i=0;
	struct e_lst* eptr=list->ptr;
	char c_begin = 0;
	char c_end = 0;
	if(eptr->ptr_d==NULL) c_begin=1;
	if(eptr->ptr_u==NULL) c_end=1;
	while(eptr!=NULL)
	{
		if(i==id)
		{
			if( eptr->ptr_d==NULL && 
				eptr->ptr_u!=NULL)
			{
				eptr->ptr_u->ptr_d=NULL;
				list->ptr = eptr->ptr_u;
				free(eptr);
				list->size--;
			}
			else if(eptr->ptr_d!=NULL && 
					eptr->ptr_u!=NULL)
			{
				eptr->ptr_d->ptr_u= eptr->ptr_u;
				free(eptr);
				list->size--;
			}
			else if(eptr->ptr_d!=NULL && 
					eptr->ptr_u==NULL)
			{
				eptr->ptr_d->ptr_u = NULL;
				free(eptr);
				list->size--;
			}
			break;
		}
		i++;
		eptr=eptr->ptr_u;
	}
}
void* lstat(lst* list,int id)
{
	int i=0;
	struct e_lst* eptr=list->ptr;
	while(eptr!=NULL)
	{
		if(i==id) return eptr->pvar;
		i++;
		eptr=eptr->ptr_u;
	}
	return NULL;
}
int lstfind(lst* list,void* var)
{
	int i=0;
	struct e_lst* eptr=list->ptr;
	while(eptr!=NULL)
	{
		if(eptr->pvar==var) return i;
		i++;
		eptr=eptr->ptr_u;
	}
	return -1;
}
void lstclear(lst* list)
{
	if(list==NULL) return;
	struct e_lst* tmp_elst;
	while(list->ptr!=NULL)
	{
		tmp_elst = list->ptr->ptr_u;
		free(list->ptr);
		list->ptr = tmp_elst;
	}
	list->size=0;
	list->ptr=NULL;
}

void lstfree(lst* list)
{
	if(list==NULL) return;
	struct e_lst* tmp_elst;
	while(list->ptr!=NULL)
	{
		tmp_elst = list->ptr->ptr_u;
		free(list->ptr);
		list->ptr = tmp_elst;
	}
	free(list);
	list=NULL;
}
