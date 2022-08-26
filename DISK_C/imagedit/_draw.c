#include "head.h"
#include "draw.h"
#include "SVGAmode.h"


/*画一般直线函数，x1,y1为起始点坐标，x2,y2为终止点坐标*/
void Line(int x1, int y1, int x2, int y2, unsigned char color)     
{
	int i;										//循环变量
	int temp;									//坐标排序中间值
	
	/*只画屏幕显示部分*/
	if(x1>1024||x2>1024||y1>768||y2>768)
	{
		return;
	}
	
	if(x1<0 || x2<0 || y1<0 || y2<0)
	{
		return;
	}
	
	if(y1 == y2)   								//画水平线
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
	
	else if(x1 == x2)							//画竖直线
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


/*画一个像素宽的矩形框，x1,y1为左上角顶点坐标，x2,y2为右下角顶点坐标*/
void Rectangle(int left, int top, int right, int bottom, unsigned char color)
{
	Line(left,top,right,top,color);
	Line(left,top,left,bottom,color);
	Line(left,bottom,right,bottom,color);
	Line(right,bottom,right,top,color);
	
	return;
}

/*画可选边框宽度的矩形框*/
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

/*画增强菜单选择程度指数,x,y分别为参考坐标*/
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