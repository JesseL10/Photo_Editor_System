#include "head.h"
#include "draw.h"
#include "SVGAmode.h"


/*��һ��ֱ�ߺ�����x1,y1Ϊ��ʼ�����꣬x2,y2Ϊ��ֹ������*/
void Line(int x1, int y1, int x2, int y2, unsigned char color)     
{
	int i;										//ѭ������
	int temp;									//���������м�ֵ
	
	/*ֻ����Ļ��ʾ����*/
	if(x1>1024||x2>1024||y1>768||y2>768)
	{
		return;
	}
	
	if(x1<0 || x2<0 || y1<0 || y2<0)
	{
		return;
	}
	
	if(y1 == y2)   								//��ˮƽ��
	{
		if(x1>x2)
		{
			temp=x1;
			x1=x2;
			x2=temp;
		}	  

		for(i=x1;i<=x2;i++)
		{
			Putpixel256(i,y1,color);
		}
		return;
	}
	
	else if(x1 == x2)							//����ֱ��
	{
		if(y1>y2)
		{
			temp=y1;
			y1=y2;
			y2=temp;
		}	  

		for(i=y1;i<=y2;i++)
		{
			Putpixel256(x1,i,color);
		}
		return;
	}

}


/*��һ�����ؿ�ľ��ο�x1,y1Ϊ���ϽǶ������꣬x2,y2Ϊ���½Ƕ�������*/
void Rectangle(int left, int top, int right, int bottom, unsigned char color)
{
	Line(left,top,right,top,color);
	Line(left,top,left,bottom,color);
	Line(left,bottom,right,bottom,color);
	Line(right,bottom,right,top,color);
	
	return;
}

/*����ѡ�߿��ȵľ��ο�*/
void Square(int left, int top, int right, int bottom, int width, unsigned char color)
{	
	int i;
	if(width<0)
	{
		printf("the value of parameter 'width' should greater than 0");
		return;
	}
	
	Rectangle(left, top, right, bottom, color);
	for(i=1;i<width;i++)
	{
		Rectangle(left + i, top + i, right - i, bottom - i, color);	
	}

}

/*����ǿ�˵�ѡ��̶�ָ��,x,y�ֱ�Ϊ�ο�����*/
void draw_degree(int x, int y, int mode)
{
	int COLOR;
	
	(mode == LIGHT)?(COLOR = BLACK):(COLOR = WHITE);
	
	Close(70,95,145,565,mode);
	
	Line(x,y,x+34,y,COLOR);
	Line(x,y+1,x+34,y+1,COLOR);
	
	Line(x+14,y-90,x+14,y+90,COLOR);
	Line(x+15,y-90,x+15,y+90,COLOR);
	
	Line(x+15,y-90,x+33,y-90,COLOR);
	Line(x+15,y-89,x+33,y-89,COLOR);
	
	Line(x+15,y-45,x+33,y-45,COLOR);
	Line(x+15,y-44,x+33,y-44,COLOR);
	
	Line(x+15,y+44,x+33,y+44,COLOR);
	Line(x+15,y+45,x+33,y+45,COLOR);
	
	Line(x+15,y+89,x+33,y+89,COLOR);
	Line(x+15,y+90,x+33,y+90,COLOR);
}	