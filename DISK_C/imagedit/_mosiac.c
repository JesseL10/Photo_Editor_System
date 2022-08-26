#include "head.h"
#include "function.h"
#include "SVGAmode.H"
#include "mmouse.H"
#include "HANZI.H"
#include "inout.h"
#pragma pack(1)
/*
 马赛克函数
 传入：文件头，缓存像素信息，马赛克范围，点击位置
 在一个矩形范围内计算像素平均值并替换原来的像素，产生马赛克效果
 马赛克小格长宽固定为10
 马赛克范围：
 0————全图马赛克
 其它————根据输入的值确定位置与范围
*/
void mosaic(BMPHeader *head,unsigned char *pBmpBuf,int Diameter, struct point click)  
{
	int i,j,x,y,width,height,biCount,lineByte;
	int dx,dy,bottom,left;
	int Radius;
	long long R,G,B;
	int cnt;
	int w,h,a,b,L;
	RGBQUAD *pColorTable;

	unsigned char *p,*pNew;
	BITMAPFILEHEADER fileHead;
	BITMAPINFOHEADER infoHead;	
	
	fileHead=head->fileHead;
	infoHead=head->infoHead;
	
	width=infoHead.biWidth;
	height=infoHead.biHeight;
	biCount=infoHead.biBitCount; 
	lineByte=(width*biCount/8+3)/4*4; 
	
	pColorTable=(RGBQUAD*)malloc(sizeof(RGBQUAD)*256); 
	for(i=0;i<256;i++)
	{
		*(pColorTable+i)=head->palette[i];
	}
	if(Diameter==1)   //全图马赛克
	{
		Radius=5;    //马赛克小格半长宽为5
		for(i=5;i<height;i+=10)
		{
			
			for(j=5;j<width;j+=10)
			{
				R=G=B=0;
				p=(unsigned char *)(pBmpBuf+i*lineByte+j);
				
				cnt=0;
				
				for(dx=-Radius;dx<=Radius;dx++)               
				{
					for(dy=-Radius;dy<=Radius;dy++)
					{
						if(i+dy<0||i+dy>height-1) continue;    
						if(j+dx<0||j+dx>width-1) continue;

						p=pBmpBuf+(i+dy)*lineByte+(j+dx);
						R+=(long long)(pColorTable[(*p)].r);
						G+=(long long)(pColorTable[(*p)].g);
						B+=(long long)(pColorTable[(*p)].b);
						cnt++;
					}
				}
				        //马赛克效果公式
				R/=cnt;	
				G/=cnt;
				B/=cnt;
				
				for(y=i-Radius;y<i+Radius;y++)    
				{
					for(x=j-Radius;x<j+Radius;x++)
					{	
						if(y<0||y>height-1) continue;    
						if(x<0||x>width-1) continue;

						p=(unsigned char *)(pBmpBuf+y*lineByte+x);
						(*p)=getIndex(pColorTable,R,G,B);
					}
				}
			}
		}
			h=i-5;           //边缘修正（防止出现四周像素未被更改的情况）
			w=j-5;
			if(i>=height){
				for(a=h;a<height;a++){
					for(b=0;b<w;b++){
						p=(unsigned char *)(pBmpBuf+(a-1)*lineByte+b);
						pNew=(unsigned char *)(pBmpBuf+a*lineByte+b);
						(*pNew)=(*p);
					}
				}
			}
			
			if(j>=width)
			{
				for(a=0;a<height;a++){
					for(b=w;b<width;b++)
					{
						p=(unsigned char *)(pBmpBuf+a*lineByte+b-1);
						pNew=(unsigned char *)(pBmpBuf+a*lineByte+b);
						(*pNew)=(*p);
					}
				}
			}
			
	}
	if(Diameter!=1)     //根据点击位置进行马赛克
	{
		L=Diameter/2;
		Radius=5;
		bottom=384+height/2;
		left=512-width/2;
		b=bottom-click.y;
		a=click.x-left;
		for(i=b-L;i<b+L;i+=10)
		{
			
			for(j=a-L;j<a+L;j+=2*Radius)
			{
				R=G=B=0;
				p=(unsigned char *)(pBmpBuf+i*lineByte+j);
				cnt=0;
				
				for(dy=-Radius;dy<=Radius;dy++)               
				{
					for(dx=-Radius;dx<=Radius;dx++)
					{
						if(i+dy<0||i+dy>height-1) continue; 
						if(j+dx<0||j+dx>width-1) continue;
						p=pBmpBuf+(i+dy)*lineByte+(j+dx);
						R+=(long long)(pColorTable[(*p)].r);
						G+=(long long)(pColorTable[(*p)].g);
						B+=(long long)(pColorTable[(*p)].b);
						cnt++;
					}
				}
				R/=cnt;	          //马赛克效果公式
				G/=cnt;
				B/=cnt;
				for(y=i-Radius;y<i+Radius;y++)
				{
					for(x=j-Radius;x<j+Radius;x++)
					{
						if(y<0||y>height-1) continue; 
						if(x<0||x>width-1) continue;
						p=(unsigned char *)(pBmpBuf+y*lineByte+x);
						(*p)=getIndex(pColorTable,R,G,B);
					}
				}
			}
		}
	}

	head->fileHead=fileHead;
	head->infoHead=infoHead;
	
	free(pColorTable);
	return;
}



void pmosiac(BMPHeader *head,unsigned char *pBmpBuf,int mode)
{
	int diameter=0;				//画笔直径
	int key;					//键值
	int width,height;			//图片的宽度和高度
	BITMAPINFOHEADER t;
	MOUSE M;					//定义鼠标结构体
	POINT a;					//鼠标点击像素的结构体
	t=head->infoHead;
	width=t.biWidth;
	height=t.biHeight;
	shape=0;
	
	while(1)
	{
		MouseXYB(&M);
		MouseStoreBk(M.x, M.y);
		MouseDraw(M);
		delay(20);
		MousePutBk(M.x, M.y);
		
		if(kbhit())
		{
			key=bioskey(0);
			if(key==Enter)
			{
				Close(310,630,575,660,mode);
				return;
			}
		}
		if(M.x>363 && M.x<373 && M.y>646 && M.y<656)				//选择马赛克范围（小）
		{
			shape=1;
			if(Mousepress(363,646,373,656)==1)
				diameter=8;
		}
	
		else if(M.x>398 && M.x<412 && M.y>643 && M.y<657)			//选择马赛克范围（中）
		{
			shape=1;
			if(Mousepress(398,643,412,657)==1)
				diameter=13;
		}
		else if(M.x>438 && M.x<455 && M.y>640 && M.y<660)			//选择马赛克范围（大）
		{
			shape=1;
			if(Mousepress(438,640,455,660)==1)
				diameter=23;
		}
		else if(M.x>480 && M.x<504 && M.y>636 && M.y<659)			//整张图片打码
		{
			shape=1;
			if(Mousepress(480,636,504,659)==1)
			{
				diameter=1;
				mosaic(head,pBmpBuf,diameter,a);
				Close(512-(width/2),384-(height/2),512+(width/2),384+(height/2),mode);
				display(head,pBmpBuf);
				diameter = 0;
			}
		}
		else if(M.x>525 && M.x<575 && M.y>633 && M.y<659)			//完成按钮
		{
			shape=1;
			Close(525,633,575,659,BLUE);
			printHZ16(534,638,"完成",WHITE,1,1,0);
			printHZ16(535,638,"完成",WHITE,1,1,0);
			if(Mousepress(525,633,575,659) == 1)					//点击完成结束马赛克返回编辑函数
			{
				Close(310,630,575,660,mode);
				return;
			}
		}
		else
		{
			shape=0;
			Close(525,633,575,659,GRAY);
			printHZ16(534,638,"完成",BLACK,1,1,0);
			printHZ16(535,638,"完成",BLACK,1,1,0);
		}

		if(M.x>517-(width/2)&& M.x<507+(width/2) && M.y>389-(height/2) && M.y<379+(height/2) && diameter!=0)//手动打码部分
		{
			if(M.but==1)
			{
				a.x = M.x;
				a.y = M.y;
				mosaic(head,pBmpBuf,diameter,a);
				Close(512-(width/2),384-(height/2),512+(width/2),384+(height/2),mode);
				display(head,pBmpBuf);
			}
		}
		else
			continue;
	}
}

