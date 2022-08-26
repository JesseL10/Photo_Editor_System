#include "enter.h"
#include "SVGAmode.h"
#include "head.h"
#include "mmouse.h"
#include "draw.h"
#include "HANZI.H"

int enter(void)
{
	int page=0;
	int key;
	int i,x; 											  //循环变量
	char *ch[4] = {"点","击","进","入"};

	MOUSE M;
	
	Putbmp256(0,0,"picture\\01.bmp");
	Square(10, 10, 1014, 758, 2, BLACK);
	delay(1200);

	for(i=0,x=440;i<4;i++,x+=40)						  //显示“点击进入”汉字
	{
		printHZ12(x,510,ch[i],BLACK,2,2,0);
		delay(300);
	}
	
	while(page == 0)
	{
		MouseXYB(&M);
		MouseStoreBk(M.x, M.y);
		MouseDraw(M);
		delay(20);
		MousePutBk(M.x, M.y);
		
		if(M.x>434 && M.x<590 && M.y>502 && M.y<542)     //判断鼠标位置，画框，更改为手势鼠标
		{
			shape=1;
			Square(433, 501, 591, 543, 2, BLACK);
			if(Mousepress(434,495,590,530) == 1)     	//判断鼠标是否点击，进入编辑界面
			{
				shape = 0;
				page = 1; 			
			}
		}
		
		else if(kbhit())
		{
			key=bioskey(0);
			if(key == Enter)
			{
				page = 1;
			}
		}
		else  											 //恢复默认鼠标，删除方框
		{
			shape=0;
			Square(433, 501, 591, 543, 2, WHITE);
		}
	}
	return page;
}

int Mode(int * mode)
{
	
	MOUSE M;
	int page = 1;

	Putbmp256(0,0,"picture\\mode.bmp");
	printHZ16(332,105,"请选择初始模式",BLACK,3,3,5);
	printHZ16(332,106,"请选择初始模式",BLACK,3,3,5);
	printHZ16(333,105,"请选择初始模式",BLACK,3,3,5);
	printHZ16(333,106,"请选择初始模式",BLACK,3,3,5);

	
	while(page == 1)
	{
		MouseXYB(&M);
		MouseStoreBk(M.x, M.y);
		MouseDraw(M);
		delay(20);
		MousePutBk(M.x, M.y);
		
		if(M.x>183 && M.x<345 && M.y>511 && M.y<552||			//白天模式
		   M.x>110 && M.x<470 && M.y>230 && M.y<500)
		{
			shape = 1;
			printHZ12(240,520,"白天模式",BLOODRED,2,2,3);
			
			if(Mousepress(183,511,345,552) == 1||
			   Mousepress(110,230,470,500) == 1)     
			{
				shape = 0;
				*mode = LIGHT;
				page = 2; 	
			}
		}
			
		else if(M.x>635 && M.x<788 && M.y>511 && M.y<552||		//夜间模式
			    M.x>560 && M.x<915 && M.y>230 && M.y<500)
		{
			shape = 1;
			printHZ12(690,520,"夜间模式",BLOODRED,2,2,1);
			if(Mousepress(635,511,788,552) == 1 ||
			   Mousepress(560,230,915,500) == 1) 
			{
				shape = 0;
				*mode = DARK;
				page = 2;
			}
		}

		else
		{
			shape=0;
			printHZ12(240,520,"白天模式",BLACK,2,2,3);
			printHZ12(690,520,"夜间模式",BLACK,2,2,1);
		}
	}
	return page;
}