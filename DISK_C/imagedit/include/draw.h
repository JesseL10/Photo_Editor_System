#ifndef	DRAW_H
#define	DRAW_H

#include "SVGAmode.h"

void Rectangle(int left,int top,int right,int bottom,unsigned char color);/*画矩形框*/

void Line(int x1,int y1,int x2, int y2,unsigned char color);/*画水平直线*/

void draw_degree(int x, int y, int mode);/*画增强菜单选择程度指数,x,y分别为中点参考坐标*/

void Square(int left, int top, int right, int bottom, int width, unsigned char color);

//void interface(int mode);

#endif