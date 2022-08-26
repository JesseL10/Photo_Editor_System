#include "head.h"
#include "mmouse.h"
#include "SVGAmode.h"
#include "draw.h"
#include "enter.h"
#include "edit.h"
#include "inout.h"
#include "HANZI.H"
#include "function.h"
#include "menu.h"

void main()
{
	
	MOUSE M;									//定义鼠标结构体 M
	int page = 0;								//欢迎界面
	int mode;									//初始模式
	SetSVGA256();    	 						//0x105模式，256色
	MouseInit();								//鼠标初始化
	MouseRange(0,0,1024,768);

	while(1)
	{	
		switch(page)
		{
			case 0:								//欢迎界面
			{
				page = enter();						
			}
			break;
			
			case 1:								//模式选择界面
			{
				page = Mode(&mode);				
			}
			break;
			
			case 2:								//编辑界面
			{
				page = edit(mode);				
			}
			break;
			
			default:							//退出程序
			{
				delay(50);						//防止鼠标问题
				exit(0);
			}
			break;
		}
	}
}