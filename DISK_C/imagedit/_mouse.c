#include "head.h"
#include"mmouse.h"


//鼠标形状全局变量,0为默认鼠标，1为箭头鼠标
int shape;		

/*鼠标形状全局变量数组，0表示鼠标外界，1表示鼠标边界，2表示鼠标内部*/
int const mouse_shape1[18][12] =
{
	{1,1,0,0,0,0,0,0,0,0,0,0},           
    {1,2,1,0,0,0,0,0,0,0,0,0},
    {1,2,2,1,0,0,0,0,0,0,0,0},
    {1,2,2,2,1,0,0,0,0,0,0,0},
    {1,2,2,2,2,1,0,0,0,0,0,0},
    {1,2,2,2,2,2,1,0,0,0,0,0},
    {1,2,2,2,2,2,2,1,0,0,0,0},
    {1,2,2,2,2,2,2,2,1,0,0,0},
    {1,2,2,2,2,2,2,2,2,1,0,0},
    {1,2,2,2,2,2,2,2,2,2,1,0},
    {1,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,2,2,2,2,1,1,1,1,1,1},
    {1,2,2,1,1,2,2,1,0,0,0,0},
    {1,2,1,0,1,2,2,1,0,0,0,0},
    {1,1,0,0,1,2,2,2,1,0,0,0},
    {1,0,0,0,0,1,2,2,1,0,0,0},
	{0,0,0,0,0,1,2,2,1,0,0,0},
	{0,0,0,0,0,0,1,1,0,0,0,0}
};

//手势鼠标，Updated By Alligator
int const mouse_shape2[22][18] =
{
	{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,2,2,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,2,2,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,2,2,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,2,2,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,2,2,1,1,1,0,1,1,0,1,1,0},
	{0,0,0,0,0,1,2,2,1,2,2,1,2,2,1,2,2,1},
	{0,0,0,0,0,1,2,2,1,2,2,1,2,2,1,2,2,1},
	{0,0,0,0,0,1,2,2,1,2,2,1,2,2,1,2,2,1},
	{0,1,1,0,0,1,2,2,1,2,2,1,2,2,1,2,2,1},
    {1,2,2,1,0,1,2,2,1,2,2,2,2,2,2,2,2,1},
    {1,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,1},
    {0,1,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,1},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
	{0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
	{0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,1,0},
	{0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,1,0,0},
	{0,0,0,0,0,0,1,2,2,2,2,2,2,2,1,0,0,0},
	{0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0}
};

/*鼠标遮挡的背景缓存数组(1为默认鼠标，2为手势鼠标)，全局变量，*/
int mouse_bk1[18][12];
int mouse_bk2[22][18];


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
int MouseInit(void)
{
	/*****************************************************
	在dos.h中REGS的定义如下：
	struct WORDREGS
	{
		unsigned int ax, bx, cx, dx, si, di, cflag, flags;
	};
	
	struct BYTEREGS
	{
		unsigned char al, ah, bl, bh, cl, ch, dl, dh;
	};
	
	union REGS
	{
		struct WORDREGS x;
		struct BYTEREGS h;
	};
	这样al对应ax的低八位，ah对应ax的高八位，以此类推。
	调用时需要查表决定各入口参数取值,获取返回值表示的信息。
	*****************************************************/
	union REGS mouse;
	
	/*设置鼠标的功能号*/
	mouse.x.ax = 0;
	int86(0x33, &mouse, &mouse);
	return mouse.x.ax;
}

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
void MouseRange(int x1, int y1, int x2, int y2)
{
	/*REGS联合体见上*/
	union REGS mouse;
	
	/*设置横坐标范围*/
	mouse.x.ax = 7;
	mouse.x.cx = x1;
	mouse.x.dx = x2;
	int86(0x33, &mouse, &mouse);
	
	/*设置纵坐标范围*/
	mouse.x.ax = 8;
	mouse.x.cx = y1;
	mouse.x.dx = y2;
	int86(0x33, &mouse, &mouse);
}

/**********************************************************
Function：		 MouseXYB

Description：	读取当前鼠标状态，存入指定结构体

Calls：			int86

Called By：		Mousepress
				MouseBarRight
				Menu

Input：			MOUSE * mouse	存放鼠标状态结构体的地址

Output：		MOUSE * mouse	存放鼠标状态结构体被更改

Return：		mouse->but		鼠标按钮状态

Others：		None
**********************************************************/
int MouseXYB(MOUSE * mouse)
{
	/*REGS联合体见上*/
	union REGS r;
	r.x.ax = 3;
	int86(0x33, &r, &r);
	mouse->x = r.x.cx;
	mouse->y = r.x.dx;
	mouse->but = r.x.bx;
	return mouse->but;
}

/**********************************************************
Function：		 Mousepress

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
int Mousepress(int x1, int y1, int x2, int y2)
{
	/*存放鼠标状态的结构体*/
	MOUSE mouse = {0, 0, 0};
	
	/*读取鼠标状态*/
	MouseXYB(&mouse);
	
	/*判断鼠标左键是否在指定区域内按下*/
	if ((mouse.x >= x1)
		&& (mouse.x <= x2)
		&& (mouse.y >= y1)
		&& (mouse.y <= y2)
		&& ((mouse.but & 1) == 1))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/**********************************************************
Function：		 MouseStoreBk

Description：	储存被鼠标覆盖区域的显存内容
				Bk是background的缩写

Calls：			Getpixel64k

Called By：		MouseReset
				Menu

Input：			int x		鼠标光标横坐标
				int y		鼠标光标纵坐标

Output：		int mouse_bk[16][10]			全局变量储存被鼠标覆盖区域的显存内容
				int const mouse_shape[16][10]	鼠标形状全局变量数组

Return：		None
Others：		None
**********************************************************/
void MouseStoreBk(int x, int y)
{
	int i, j;
	switch(shape)
	{
		case 1:
				for (i = 0; i < 22; i++)
				{
					for (j = 0; j < 18; j++)
					{
						if (mouse_shape2[i][j] == 0)
						{
							continue;
						}
						mouse_bk2[i][j] = Getpixel256(j + x, i + y);
					}
				}
				break;
		default:
		{
				for (i = 0; i < 18; i++)
				{
					for (j = 0; j < 12; j++)
					{
						if (mouse_shape1[i][j] == 0)
						{
							continue;
						}
						mouse_bk1[i][j] = Getpixel256(j + x, i + y);
					}
				}
				break;			
		}
	}
}

/**********************************************************
Function：		 MousePutBk

Description：	恢复被鼠标覆盖区域的显存内容
				Bk是background的缩写

Calls：			Putpixel64k

Called By：		Menu

Input：			int x							鼠标光标横坐标
				int y							鼠标光标纵坐标
				int mouse_bk[17][11]			全局变量储存被鼠标覆盖区域的显存内容
				int const mouse_shape[17][11]	鼠标形状全局变量数组
				
Output：		在屏幕上恢复被鼠标覆盖区域的显存内容

Return：		None
Others：		None
**********************************************************/
void MousePutBk(int x, int y)
{
	int i, j;
	switch(shape)
	{
		case 1:
		{
			for (i = 0; i < 22; i++)
			{
				for (j = 0; j < 18; j++)
				{
					if (mouse_shape2[i][j] == 0)
					{
						continue;
					}
			
					Putpixel256(j + x, i + y, mouse_bk2[i][j]);
				}
			}
		}
		break;
		
		default:
		{
			for (i = 0; i < 18; i++)
			{
				for (j = 0; j < 12; j++)
				{
					if (mouse_shape1[i][j] == 0)
					{
						continue;
					}
			
					Putpixel256(j + x, i + y, mouse_bk1[i][j]);
				}
			}
		}
		break;
		
	}

}

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
void MouseReset(void)
{
	if (MouseInit() != 0xffff)
	{
		printf("ERROR In MouseInit\n");
		getch();
		exit(1);
	};
	MouseRange(0, 0, SCR_WIDTH - 1, SCR_HEIGHT -1);
	MouseStoreBk(0, 0);
}

/**********************************************************
Function		MouseDraw

Description：	画鼠标光标函数

Calls：			Putpixel64k

Called By：		Menu

Input：			MOUSE mouse						存放鼠标状态的结构体
				int const mouse_shape[17][11]	鼠标形状全局变量数组
				
Output：		在指定坐标处画鼠标光标

Return：		None
Others：		None
**********************************************************/
void MouseDraw(MOUSE mouse)
{
	int i, j;
	switch(shape)
	{	
		case 1:
		{
			for (i = 0; i < 22; i++)
			{
				for (j = 0; j < 18; j++)
				{
			
					if (mouse_shape2[i][j] == 0)
					{
						continue;
					}
					else if (mouse_shape2[i][j] == 1)
					{
						Putpixel256(j + mouse.x, i + mouse.y, 0);
					}
					else if (mouse_shape2[i][j] == 2)
					{
						Putpixel256(j + mouse.x, i + mouse.y, 0xffff);
					}
				}
			}		
		}
		break;
		
		default:
		{
			for (i = 0; i < 18; i++)
			{
				for (j = 0; j < 12; j++)
				{
			
					if (mouse_shape1[i][j] == 0)
					{
						continue;
					}
					else if (mouse_shape1[i][j] == 1)
					{
						Putpixel256(j + mouse.x, i + mouse.y, 0);
					}
					else if (mouse_shape1[i][j] == 2)
					{
						Putpixel256(j + mouse.x, i + mouse.y, 0xffff);
					}
				}
			}	
		}
		break;
	}
}
/*取鼠标按钮按下状态*/
int Ispress(void)
{
	_AX=3;
	geninterrupt(0x33);
	return _BX;
}