#ifndef	HEAD_H
#define	HEAD_H


#include<dos.h>			
#include<stdio.h>		
#include<time.h>		
#include<math.h>		
#include<stdlib.h>	
#include<io.h>	
#include<conio.h>		
#include<string.h>		
#include<bios.h>		
#include<malloc.h>

#define		SCR_WIDTH		1024		/*SCRREN WIDTH的缩写，屏幕宽度像素 */
#define		SCR_HEIGHT		768			/*SCREEN HEIGHT的缩写，屏幕高度像素 */

//键值
#define 	ESC 			0x011b
#define 	Backspace 		0x0e08
#define 	Enter			0x1c0d
#define 	F1  			0x3b00
#define		F2  			0x3c00

//颜色
#define 	BLACK			0			//黑色
#define 	GRAY			7			//灰色
#define     ORANGE			39			//橙色
#define     PURPLE  		196			//紫色
#define     BLUE			218			//蓝色
#define     BLOODRED        249			//红色
#define     YELLOW			251			//黄色
#define     GREEN			120			//绿色
#define 	WHITE			255			//白色
#define		MATCHA			8			//抹茶绿
#define     PINK			151			//粉色
#define		BLACKGRREN      16			//墨绿
#define		LIGHTBLUE       9			//淡蓝色
#define		BROWN           95          //棕色
#define     BEIGE           183			//米色

//主题模式
#define     DARK			0
#define		LIGHT			255

enum FUNCTION {OPEN = 1, SAVE, MOSIAC, ADJUST, FILTER, EDIT, RECOVER, CUT, BRIGHT, SHARPEN, BLUR, DIALOG, DEVINFO, HELP, GRAFFITI, EXIT};

#endif