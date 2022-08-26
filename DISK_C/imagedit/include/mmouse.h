/*
Function List：
	1.unsigned int Getpixel64k(int x, int y);
		取点颜色函数，仅适用于0x117模式！
		
	2.int MouseInit(void);
		鼠标复位
	
	3.void MouseRange(int x1, int y1, int x2, int y2);
		设置鼠标移动范围
		
	4.int MouseXYB(MOUSE * mouse);
		读取当前鼠标状态，存入指定结构体
		
	5.int MouseBarLeft(int x1, int y1, int x2, int y2);
		判断鼠标左键是否在指定区域内按下
		
	6.void MouseStoreBk(int x, int y);
		储存被鼠标覆盖区域的显存内容
		
	7.void MousePutBk(int x, int y);
		恢复被鼠标覆盖区域的显存内容
		
	8.void MouseReset(void);
		重置鼠标状态，范围为全屏
		
	9.void MouseDraw(MOUSE mouse);
		画鼠标光标函数		

History：		对本文件的修改请及时按如下格式记录在下面（每个修改单独列出）！
	Example：	Date：
				Author：
				Version：
				Modification：
**********************************************************/
#ifndef	MMOUSE_H
#define	MMOUSE_H

#include"SVGAmode.h"

extern int shape;//鼠标形状

/*鼠标结构体，包含鼠标状态*/
typedef struct mouse_
{
	int x;			/*光标横坐标*/
	int y;			/*光标纵坐标*/
	int but;		/*按钮的状态，0,1位分别表示左右键，该位为1表示按下，0表示松开*/
}	MOUSE;

/**********************************************************
Function：		 MouseInit

Description：	鼠标复位

Calls：			int86
				
Called By：		MouseReset

Input：			None

Output：		鼠标复位

Return：		unsigned int	函数执行结果，
								0x0000	不支持
								0xffff	支持
				
Others：		None
**********************************************************/
extern int MouseInit(void);

/**********************************************************
Function：		 MouseRange

Description：	设置鼠标移动范围

Calls：			int86
				
Called By：		MouseReset

Input：			int x1		移动范围左上角横坐标
				int y1		移动范围左上角纵坐标
				int x2		移动范围右下角横坐标
				int y2		移动范围右下角纵坐标

Output：		None
Return：		None
				
Others：		None
**********************************************************/
extern void MouseRange(int x1, int y1, int x2, int y2);

/**********************************************************
Function：		 MouseXYB

Description：	读取当前鼠标状态，存入指定结构体

Calls：			int86

Called By：		MouseBarLeft
				MouseBarRight
				Menu

Input：			MOUSE * mouse	存放鼠标状态结构体的地址

Output：		MOUSE * mouse	存放鼠标状态结构体被更改

Return：		mouse->but		鼠标按钮状态

Others：		None
**********************************************************/
extern int MouseXYB(MOUSE * mouse);

/**********************************************************
Function：		 MouseBarLeft

Description：	判断鼠标左键是否在指定区域内按下

Calls：			MouseXYB

Called By：		Menu

Input：			int x1		移动范围左上角横坐标
				int y1		移动范围左上角纵坐标
				int x2		移动范围右下角横坐标
				int y2		移动范围右下角纵坐标

Output：		None

Return：		1		鼠标左键在指定区域内按下
				0		鼠标左键没在指定区域内按下

Others：		None
**********************************************************/
extern int Mousepress(int x1, int y1, int x2, int y2);

/**********************************************************
Function：		 MouseStoreBk

Description：	储存被鼠标覆盖区域的显存内容
				Bk是background的缩写

Calls：			Getpixel64k

Called By：		MouseReset
				Menu

Input：			int x		鼠标光标横坐标
				int y		鼠标光标纵坐标

Output：		int mouse_bk[10][10]			全局变量储存被鼠标覆盖区域的显存内容
				int const mouse_shape[10][10]	鼠标形状全局变量数组

Return：		None
Others：		None
**********************************************************/
extern void MouseStoreBk(int x, int y);

/**********************************************************
Function：		 MousePutBk

Description：	恢复被鼠标覆盖区域的显存内容
				Bk是background的缩写

Calls：			Putpixel64k

Called By：		Menu

Input：			int x							鼠标光标横坐标
				int y							鼠标光标纵坐标
				int mouse_bk[10][10]			全局变量储存被鼠标覆盖区域的显存内容
				int const mouse_shape[10][10]	鼠标形状全局变量数组
				
Output：		在屏幕上恢复被鼠标覆盖区域的显存内容

Return：		None
Others：		None
**********************************************************/
extern void MousePutBk(int x, int y);

/**********************************************************
Function：		 MouseReset

Description：	重置鼠标状态，范围为全屏

Calls：			MouseInit
				MouseRange
				MouseStoreBk
				
				printf
				getch
				exit

Called By：		Menu

Input：			None
				
Output：		重置鼠标状态

Return：		None
Others：		None
**********************************************************/
extern void MouseReset(void);

/**********************************************************
Function		MouseDraw

Description：	画鼠标光标函数

Calls：			Putpixel64k

Called By：		Menu

Input：			MOUSE mouse						存放鼠标状态的结构体
				int const mouse_shape[10][10]	鼠标形状全局变量数组
				
Output：		在指定坐标处画鼠标光标

Return：		None
Others：		None
**********************************************************/
extern void MouseDraw(MOUSE mouse);// shape:0为箭头鼠标,1为手势鼠标
int Ispress(void);
typedef struct point
{
	int x;
	int y;
} POINT;


#endif