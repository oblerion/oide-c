#pragma once
#include <stdlib.h>
#include <string.h>

const int text_nbLine(const char* stext);
const char* text_getLine(const char* stext,int posline);
const char* text_sub(const char* stext,int pos,int n);
const char* text_setLine(const char* stext,int posline,const char* sed);
const char* text_addLine(const char* stext,int posline,const char* sed);
const char* text_delLine(const char* stext,int posline);

const int text_nbLine(const char* stext)
{
	int nb=0;
	const int l = strlen(stext);
	if(l>0)
	{
		for(int i=0;i<=l;i++)
			if(stext[i]=='\n')
				nb+=1;
		nb++;
	}
	return nb;
}
const char* text_getLine(const char* stext,int posline)
{
	const int lgt = strlen(stext);
	const int maxline = text_nbLine(stext);
	int nline=0;
	int last_pos=0;
	int next_pos=0;
	char* ls = NULL;
	if(posline>maxline-1 || posline<0) return "";
	for(int i=0;i<lgt;i++)
	{
		if(stext[i]=='\n'|| stext[i]=='\0')
		{
			nline++;
			if(next_pos>0) last_pos=next_pos+1;
			next_pos=i;
		}
		if(nline-1==posline)
		{
			const int l = next_pos-last_pos;
			if(l>0)
			{
				ls = (char*)malloc(sizeof(char)*l);
				if(ls==NULL) return "";
				else
				{
					int p=0;
					for(int j=last_pos;j<next_pos;j++)
					{
						ls[p]=stext[j];
						p++;
					}
					ls[l]='\0';
					return ls;
				}
			}
			else return "";
		}
	}
	return "";
}
const char* text_sub(const char* stext,int pos,int n)
{
	const int lgt = strlen(stext);
	if(pos+n>lgt) return "";
	char* ls = (char*)malloc(sizeof(char)*n);
	for(int i=pos;i<pos+n;i++)
	{	
		ls[i-pos] = stext[i];
	}
	ls[n]='\0';
	return ls;
}
const char* text_setLine(const char* stext,int posline,const char* sed)
{
	const int lgt = strlen(stext);
	const int maxline = text_nbLine(stext);
	if(posline>maxline-1 || posline<0) return "";
	int nline=0;
	int last_pos=0;
	int next_pos=0;
	char* ls=NULL;
	for(int i=0;i<=lgt;i++)
	{
		if(stext[i]=='\n' || stext[i]=='\0')
		{
			nline++;
			if(next_pos>0) last_pos=next_pos+1;
			next_pos=i;
		}
		if(nline-1==posline)
		{
			const char* sf;
			if(posline==0)
				sf = "";
			else
				sf = text_sub(stext,0,last_pos);
			const char* se = text_sub(stext,next_pos,strlen(stext)-next_pos);
			ls = (char*)malloc(sizeof(char)*(strlen(sf)+strlen(sed)+strlen(se)));
			strcpy(ls,sf);
			strcat(ls,sed);
			strcat(ls,se);
			return ls;
		}
	}
	return "";
}
const char* text_addLine(const char* stext,int posline,const char* sed)
{
	const int lgt = strlen(stext);
	const int maxline = text_nbLine(stext);
	if(posline>maxline-1 || posline<0) return "";
	int nline=0;
	int last_pos=0;
	int next_pos=0;
	char* ls=NULL;
	for(int i=0;i<=lgt;i++)
	{
		if(stext[i]=='\n' || stext[i]=='\0')
		{
			nline++;
			if(next_pos>0) last_pos=next_pos+1;
			next_pos=i;
		}
		if(nline-1==posline)
		{
			const char* sf;
			if(posline==0)
				sf = "";
			else
				sf = text_sub(stext,0,last_pos);
			const char* sm = text_sub(stext,last_pos,next_pos-last_pos);
			const char* se = text_sub(stext,next_pos,strlen(stext)-next_pos);
			ls = (char*)malloc(sizeof(char)*(strlen(sf)+strlen(sm)+strlen(sed)+strlen(se)));
			strcpy(ls,sf);
			strcat(ls,sed);
			strcat(ls,"\n");
			strcat(ls,sm);
			strcat(ls,se);
			return ls;
		}
	}
	return "";
}

const char* text_delLine(const char* stext,int posline)
{
	const int lgt = strlen(stext);
	const int maxline = text_nbLine(stext);
	if(posline>maxline-1 || posline<0) return "";
	int nline=0;
	int last_pos=0;
	int next_pos=0;
	char* ls=NULL;
	for(int i=0;i<=lgt;i++)
	{
		if(stext[i]=='\n' || stext[i]=='\0')
		{
			nline++;
			if(next_pos>0) last_pos=next_pos+1;
			next_pos=i;
			if(posline==maxline-1) next_pos--;
		}
		if(nline-1==posline)
		{
			const char* sf;
			if(posline>0)
			{
				sf = text_sub(stext,0,last_pos);
			}
			const char* se = text_sub(stext,next_pos+1,strlen(stext)-(next_pos+1));
			ls = (char*)malloc(sizeof(char)*(strlen(sf)+strlen(se)));
			strcpy(ls,"");
			if(posline>0)
			{
				strcpy(ls,sf);
			}
			//printf("|%s|",se);
			strcat(ls,se);
			return ls;
		}
	}
	return "";
}
