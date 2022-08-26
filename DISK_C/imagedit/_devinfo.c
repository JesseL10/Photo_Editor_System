#include "head.h"
#include "HANZI.H"
#include "draw.h"
#include "mmouse.h"
#include "menu.h"

void devinfo(int color)
{
	int key;		//键值
	MOUSE M;		//鼠标结构体
	shape = 0;
	
	Square(10,38,1014,650, 3, color);
	Close(13,41,1011,647,MATCHA);

	printHZ16(416,60,"开发人员信息",BLACK,2,2,0);
	printHZ16(417,60,"开发人员信息",BLACK,2,2,0);
	printHZ12(120,130,"开发人员：华中科技大学人工智能与自动化学院",BLACK,2,2,0);
	printHZ12(240,165,"自动化类",BLACK,2,2,0);
	put_asc(336,160,"1910",BLACK, 2, 2);
	printHZ12(405,165,"班",BLACK,2,2,0);
	printHZ12(442,165,"李想",BLACK,2,2,0);
	printHZ12(502,165,"郭家栋",BLACK,2,2,0);

	printHZ12(120,230,"指导老师：周纯杰、何顶新、彭刚、高常鑫、陈忠、周凯波、",BLACK,2,2,0);
	printHZ12(240,265,"桑农、左峥嵘、汪国有",BLACK,2,2,0);

	printHZ12(120,320,"关于软件：",BLACK,2,2,0);
	printHZ12(168,365,"此软件为",BLACK,2,2,0);
	put_asc(265,362,"C",BLACK, 2, 2);
	printHZ12(285,365,"课设专用，禁止用于任何商业用途！",BLACK,2,2,0);

	printHZ12(168,410,"该软件的用户界面参考借鉴了美图秀秀及",BLACK,2,2,0);
	put_asc(600,406,"VSCO",BLACK, 2, 2);
	printHZ12(666,410,"等图像编辑软件",BLACK,2,2,0);

	printHZ12(168,455,"在此，向",BLACK,2,2,0);
	put_asc(264,452,"C",BLACK, 2, 2);
	printHZ12(279,455,"语言课程设计的所有老师、助教，以及在程序编写过程中给予",BLACK,2,2,0);
	printHZ12(120,490,"我们帮助和灵感的学长学姐和同学致谢。软件仍有很多不足和需改进的地方，",BLACK,2,2,0);
	printHZ12(120,525,"但在课设中学到的一切，必将对日后我们在编程设计和软件开发的道路上产生",BLACK,2,2,0);
	printHZ12(120,560,"深远的影响！",BLACK,2,2,0);

	put_asc(300,630,"School", BLUE, 1, 1);
	put_asc(356,630,"of", BLUE, 1, 1);
	put_asc(380,630,"Artificial", BLUE, 1, 1);
	put_asc(468,630,"Intelligence", BLUE, 1, 1);
	put_asc(572,630,"and", BLUE, 1, 1);
	put_asc(604,630,"Automation,", BLUE, 1, 1);
	put_asc(700,630,"HUST", BLUE, 1, 1);

	while(1)
	{
		MouseXYB(&M);
		MouseStoreBk(M.x, M.y);
		MouseDraw(M);
		delay(20);
		MousePutBk(M.x, M.y);
		
		if(M.x>487 && M.x<537 && M.y>590 && M.y<620)
		{
			shape = 1;
			Close(487,590,537,620,BLUE);
			printHZ16(496,598,"返回",WHITE,1,1,0);
			printHZ16(497,598,"返回",WHITE,1,1,0);
			if(Mousepress(487,590,537,620) == 1)
			{
				return;
			}
		}
		
		else if( kbhit() )		//ESC退出返回编辑界面
		{
			key=bioskey(0);
			if(key == ESC)
			{
				return;
			}
		}	

		else
		{
			shape = 0;
			Close(487,590,537,620,GRAY);
			printHZ16(496,598,"返回",BLACK,1,1,0);
			printHZ16(497,598,"返回",BLACK,1,1,0);
		}
	}
}

void help(int mode)
{
	int key;
	MOUSE M;
	int color;
	int flag;
	shape = 0;
	(mode == LIGHT) ? (color = BLACK) : (color = WHITE);
	printHZ16(272,50,"点击下方菜单查看各功能使用方法",color,2,2,1);
	printHZ16(272,51,"点击下方菜单查看各功能使用方法",color,2,2,1);
	printHZ16(273,50,"点击下方菜单查看各功能使用方法",color,2,2,1);
	printHZ16(273,51,"点击下方菜单查看各功能使用方法",color,2,2,1);
	put_asc(425, 90,"(Esc", color ,1, 1);
	printHZ16(460,90,"键返回主界面)",color,1,1,1);

	while(1)
	{
		MouseXYB(&M);
		MouseStoreBk(M.x, M.y);
		MouseDraw(M);
		delay(20);
		MousePutBk(M.x, M.y);
		
		if( kbhit() )				//ESC退出返回编辑界面
		{
			key=bioskey(0);
			if(key == ESC)
			{
				return ;
			}
		}
		
		else if(M.x>20 && M.x<175 && M.y>690 && M.y<735)//打开图片
		{
			shape=1;
			if(Mousepress(20,690,175,735) == 1)
			{
				Close(250,210,850,490,mode);
				Clear(flag,mode);
				flag=OPEN;
				ui(mode, DIALOG, OPEN);
				printHZ16(300,250,"在对话框中输入将编辑图片的名称,如",color,1,1,1);
				put_asc(595, 250,"\"flo.bmp\"", color ,1, 1);
				
				printHZ16(300,300,"点击“确认”按钮或按下“回车”键即可打开图片！",color,1,1,1);
				
				printHZ16(300,350,"点击关闭按钮或按下",color,1,1,1);
				put_asc(455, 350,"\"Esc\"", color ,1, 1);
				printHZ16(500,350,"键可关闭对话框",color,1,1,1);
				
				printHZ16(299,400,"注",color,1,1,1);
				printHZ16(300,400,"注：打开图片前可先查看使用帮助和切换你喜欢的模式",color,1,1,1);
				printHZ16(335,425,"对图片加工处理的功能都需在成功打开图片后才能进行操作哦~",color,1,1,1);
			}
		}
		
		else if(M.x>255 && M.x<305 && M.y>690 && M.y<750) 			//编辑
		{
			shape=1;
			if(Mousepress(225,690,305,750) == 1)
			{
				Close(250,210,850,490,mode);
				if(flag != 0)
				{
					Clear(flag,mode);
				}

				ui(mode, EDIT, 0);
				flag = EDIT;
				printHZ16(269,220,"旋转",color,1,1,1);
				printHZ16(270,220,"旋转：点击“向左九十度”或“向右九十度”，图片即向对应方向旋转",color,1,1,1);
				printHZ16(269,270,"镜像",color,1,1,1);
				printHZ16(270,270,"镜像：点击“水平”或“垂直”，图片即可向对应方向镜像反转",color,1,1,1);
				printHZ16(269,320,"裁剪",color,1,1,1);
				printHZ16(270,320,"裁剪：点击“裁剪”，通过鼠标点击图片区域中的位置，即可裁剪成功！",color,1,1,1);
				printHZ16(269,370,"缩放",color,1,1,1);
				printHZ16(270,370,"缩放：点击“缩放”，选择缩放比例，图片即可完成缩放！",color,1,1,1);
				printHZ16(253,420,"涂鸦笔",color,1,1,1);
				printHZ16(254,420,"涂鸦笔：点击“涂鸦笔”后，出现画笔颜色盘，选择喜欢的颜色后，即可通过",color,1,1,1);
				printHZ16(320,445,"鼠标在图片区域内开始你的创作。创作完成后，点击“完成”或按下",color,1,1,1);
				printHZ16(320,470,"“回车”键结束，即可进行其他编辑功能",color,1,1,1);
			}
		}	
		
		else if(M.x>375&& M.x<440 && M.y>690 && M.y<750)    		//马赛克
		{
			shape=1;
			if(Mousepress(375,690,440,750) == 1)
			{
				Close(250,210,850,490,mode);
				if(flag != 0)
				{
					Clear(flag,mode);
				}
				
				ui(mode, MOSIAC, 0);
				Close(525,633,575,659,GRAY);
				printHZ16(534,638,"完成",BLACK,1,1,0);
				printHZ16(535,638,"完成",BLACK,1,1,0);
				
				flag = MOSIAC;
				
				printHZ16(300,250,"选择马赛克的范围大小，即可通过鼠标点击图片区域开始操作！",color,1,1,1);
				printHZ16(300,275,"打码完成后，点击“完成”或按“回车”键结束，即可进行其他编辑功能",color,1,1,1);
				printHZ16(299,325,"小贴士",color,1,1,1);
				printHZ16(300,325,"小贴士：图片区域若需完全打码，点击范围选择菜单中的马赛克图标即可！",color,1,1,1);
				printHZ16(300,350,"方便又快捷！",color,1,1,1);
			}
		}
		
		else if(M.x>520 && M.x<570 && M.y>690 && M.y<750)			//增强	
		{
			shape=1;
			if(Mousepress(520,690,570,750) == 1)
			{
				Close(250,210,850,490,mode);
				delay(100);
				if(flag != 0)
				{
					Clear(flag,mode);
				}

				ui(mode, ADJUST, 0);
				flag = ADJUST;
				printHZ16(279,250,"亮度",color,1,1,1);
				printHZ16(280,250,"亮度：点击“亮度”，选择你想要的曝光程度，即可更改图片亮度！",color,1,1,1);
				printHZ16(279,300,"锐化",color,1,1,1);
				printHZ16(280,300,"锐化：点击“锐化”，选择你想要的锐化程度，即可对照片进行锐化！",color,1,1,1);
				printHZ16(279,350,"模糊",color,1,1,1);
				printHZ16(280,350,"模糊：点击“模糊”，选择你想要的模糊程度，照片即可呈现出朦胧的感觉！",color,1,1,1);
			}
		}
		
		else if(M.x>650 && M.x<700 && M.y>690 && M.y<750)			//滤镜	
		{
			shape=1;
			if(Mousepress(650,690,700,750) == 1)
			{
				Close(250,210,850,490,mode);
				delay(100);
				if(flag != 0)
				{
					Clear(flag,mode);
				}

				ui(mode, FILTER, 0);
				flag = FILTER;
				printHZ16(300,250,"打开滤镜菜单，丰富又好看的滤镜功能供你选择！",color,1,1,1);
				printHZ16(325,300,"“漫画”、“油画”、“反色”、“浮雕”、“倒影”",color,1,1,1);
				printHZ16(374,350,"注",color,1,1,1);
				printHZ16(375,350,"注：尺寸太大的照片无法使用倒影功能哦~",color,1,1,1);
			}
		}	
		
		else if(M.x>780 && M.x<830 && M.y>690 && M.y<750)			//保存
		{
			shape=1;
			if(Mousepress(780,360,830,750) == 1)
			{
				Close(250,210,850,490,mode);
				Clear(flag,mode);
				flag=SAVE;
				ui(mode, DIALOG, SAVE);
				printHZ16(300,250,"编辑完成后，在对话框中给图片设置一个自己喜欢的名字吧！",color,1,1,1);
				
				printHZ16(300,300,"点击“确认”按钮或按下“回车”键即可保存！",color,1,1,1);
				
				printHZ16(300,350,"点击关闭按钮或按下",color,1,1,1);
				put_asc(455, 350,"\"Esc\"", color ,1, 1);
				printHZ16(500,350,"键可关闭对话框",color,1,1,1);
				printHZ16(299,400,"注",color,1,1,1);
				printHZ16(300,400,"注：图片的名称不能有“空格”或“点”字符哦~",color,1,1,1);
			}
		}
		
		else if(M.x>900&& M.x<970 && M.y>690 &&M.y<750)				//关闭图片
		{
			shape=1;
			if(Mousepress(900,690,970,750) == 1)
			{
				Close(250,210,850,490,mode);
				Clear(flag,mode);
				printHZ16(325,250,"创作完成，保存作品后还想继续创作？",color,1,1,1);
				printHZ16(350,300,"点击关闭图片,关闭当前图片后，即可打开新的图片",color,1,1,1);
				printHZ16(375,350,"还在等什么？赶快开始你的创作之旅吧！",color,1,1,1);
			}
		}
		else
		{
			shape=0;
		}
	}
}
