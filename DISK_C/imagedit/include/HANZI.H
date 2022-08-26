#ifndef _HANZI_H_
#define _HANZI_H_

#include<dos.h>
#include<stdio.h>
#include<process.h>
#include<graphics.h>

void printHZ12(int x,int y,char *s,int color, int dx, int dy, int space);      		  /*12*12点阵汉字的显示*/

void printHZ16(int x,int y,unsigned char *s,int color,int dx,int dy,int space);       /*16*16点阵汉字的显示*/

void printHZ24F(int x,int y,char *s,int color,int dx,int dy,int space);   			  /*24*24点阵仿宋汉字的显示*/

void printHZ24H(int x,int y,char *s,int color,int dx,int dy,int space);  			  /*24*24点阵黑体汉字的显示*/

void printHZ24K(int x,int y,char *s,int color ,int dx,int dy,int space);    		  /*24*24点阵楷体汉字的显示*/

void printHZ24S(int x,int y,char *s,int color, int dx, int dy, int space);   		  /*24*24点阵宋体汉字的显示*/

void Put_Asc16(int cx, int cy, char key, char fcolor);

void Put_Asc16_Size(int cx, int cy, int xsize, int ysize, char key, char fcolor);

void put_asc(int cx, int cy,const char *s, char color,int xsize, int ysize);
#endif