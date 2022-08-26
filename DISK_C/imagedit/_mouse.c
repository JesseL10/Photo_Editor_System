#include "head.h"
#include"mmouse.h"


//�����״ȫ�ֱ���,0ΪĬ����꣬1Ϊ��ͷ���
int shape;		

/*�����״ȫ�ֱ������飬0��ʾ�����磬1��ʾ���߽磬2��ʾ����ڲ�*/
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

//������꣬Updated By Alligator
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

/*����ڵ��ı�����������(1ΪĬ����꣬2Ϊ�������)��ȫ�ֱ�����*/
int mouse_bk1[18][12];
int mouse_bk2[22][18];


/**********************************************************
Function��		 MouseInit

Description��	��긴λ

Calls��			int86
				
Called By��		MouseReset

Input��			None

Output��		��긴λ

Return��		unsigned int	����ִ�н����
								0x0000	��֧��
								0xffff	֧��
				
Others��		None
**********************************************************/
int MouseInit(void)
{
	/*****************************************************
	��dos.h��REGS�Ķ������£�
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
	����al��Ӧax�ĵͰ�λ��ah��Ӧax�ĸ߰�λ���Դ����ơ�
	����ʱ��Ҫ����������ڲ���ȡֵ,��ȡ����ֵ��ʾ����Ϣ��
	*****************************************************/
	union REGS mouse;
	
	/*�������Ĺ��ܺ�*/
	mouse.x.ax = 0;
	int86(0x33, &mouse, &mouse);
	return mouse.x.ax;
}

/**********************************************************
Function��		 MouseRange

Description��	��������ƶ���Χ

Calls��			int86
				
Called By��		MouseReset

Input��			int x1		�ƶ���Χ���ϽǺ�����
				int y1		�ƶ���Χ���Ͻ�������
				int x2		�ƶ���Χ���½Ǻ�����
				int y2		�ƶ���Χ���½�������

Output��		None
Return��		None
				
Others��		None
**********************************************************/
void MouseRange(int x1, int y1, int x2, int y2)
{
	/*REGS���������*/
	union REGS mouse;
	
	/*���ú����귶Χ*/
	mouse.x.ax = 7;
	mouse.x.cx = x1;
	mouse.x.dx = x2;
	int86(0x33, &mouse, &mouse);
	
	/*���������귶Χ*/
	mouse.x.ax = 8;
	mouse.x.cx = y1;
	mouse.x.dx = y2;
	int86(0x33, &mouse, &mouse);
}

/**********************************************************
Function��		 MouseXYB

Description��	��ȡ��ǰ���״̬������ָ���ṹ��

Calls��			int86

Called By��		Mousepress
				MouseBarRight
				Menu

Input��			MOUSE * mouse	������״̬�ṹ��ĵ�ַ

Output��		MOUSE * mouse	������״̬�ṹ�屻����

Return��		mouse->but		��갴ť״̬

Others��		None
**********************************************************/
int MouseXYB(MOUSE * mouse)
{
	/*REGS���������*/
	union REGS r;
	r.x.ax = 3;
	int86(0x33, &r, &r);
	mouse->x = r.x.cx;
	mouse->y = r.x.dx;
	mouse->but = r.x.bx;
	return mouse->but;
}

/**********************************************************
Function��		 Mousepress

Description��	�ж��������Ƿ���ָ�������ڰ���

Calls��			MouseXYB

Called By��		Menu

Input��			int x1		�ƶ���Χ���ϽǺ�����
				int y1		�ƶ���Χ���Ͻ�������
				int x2		�ƶ���Χ���½Ǻ�����
				int y2		�ƶ���Χ���½�������

Output��		None

Return��		1		��������ָ�������ڰ���
				0		������û��ָ�������ڰ���

Others��		None
**********************************************************/
int Mousepress(int x1, int y1, int x2, int y2)
{
	/*������״̬�Ľṹ��*/
	MOUSE mouse = {0, 0, 0};
	
	/*��ȡ���״̬*/
	MouseXYB(&mouse);
	
	/*�ж��������Ƿ���ָ�������ڰ���*/
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
Function��		 MouseStoreBk

Description��	���汻��긲��������Դ�����
				Bk��background����д

Calls��			Getpixel64k

Called By��		MouseReset
				Menu

Input��			int x		����������
				int y		�����������

Output��		int mouse_bk[16][10]			ȫ�ֱ������汻��긲��������Դ�����
				int const mouse_shape[16][10]	�����״ȫ�ֱ�������

Return��		None
Others��		None
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
Function��		 MousePutBk

Description��	�ָ�����긲��������Դ�����
				Bk��background����д

Calls��			Putpixel64k

Called By��		Menu

Input��			int x							����������
				int y							�����������
				int mouse_bk[17][11]			ȫ�ֱ������汻��긲��������Դ�����
				int const mouse_shape[17][11]	�����״ȫ�ֱ�������
				
Output��		����Ļ�ϻָ�����긲��������Դ�����

Return��		None
Others��		None
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
Function��		 MouseReset

Description��	�������״̬����ΧΪȫ��

Calls��			MouseInit
				MouseRange
				MouseStoreBk
				
				printf
				getch
				exit

Called By��		Menu

Input��			None
				
Output��		�������״̬

Return��		None
Others��		None
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

Description��	������꺯��

Calls��			Putpixel64k

Called By��		Menu

Input��			MOUSE mouse						������״̬�Ľṹ��
				int const mouse_shape[17][11]	�����״ȫ�ֱ�������
				
Output��		��ָ�����괦�������

Return��		None
Others��		None
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
/*ȡ��갴ť����״̬*/
int Ispress(void)
{
	_AX=3;
	geninterrupt(0x33);
	return _BX;
}