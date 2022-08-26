#include "head.h"
#include "function.h"
#include "SVGAmode.H"
#include "mmouse.H"
#include "HANZI.H"
#include "inout.h"
#pragma pack(1)
/************************************************************
 �����˺���
 ���룺�ļ�ͷ������������Ϣ�������˷�Χ�����λ��
 ��һ�����η�Χ�ڼ�������ƽ��ֵ���滻ԭ�������أ�����������Ч��
 ������С�񳤿�̶�Ϊ10
 �����˷�Χ��
 0��������ȫͼ������
 ���������������������ֵȷ��λ���뷶Χ
*************************************************************/
void pen(BMPHeader *head,unsigned char *pBmpBuf,int color, struct point click)  
{	
	int r=8;
	int i,j,x,y,width,height,biCount,lineByte;
	int dx,dy,bottom,top,left,right;
	int Radius;
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
	bottom=384+height/2;
	left=512-width/2;
	y=bottom-click.y;
	x=click.x-left;
		for(i=y-r;i<y+r;i++)
		{
			L=sqrt(abs(2*r*(i-y+r)-(i-y+r)*(i-y+r)));
			for(j=x-L;j<x+L;j++)
			{
				//R=G=B=0;
				p=(unsigned char *)(pBmpBuf+i*lineByte+j);
			}
			for(j=x-L;j<x+L;j++)
			{
				if(i<0||i>height-1) continue; 
				if(j<0||j>width-1) continue;

				p=(unsigned char *)(pBmpBuf+i*lineByte+j);
				(*p)=color;
			}
				
			
		}

	head->fileHead=fileHead;
	head->infoHead=infoHead;
	
	free(pColorTable);
	return;
}


/***************
Ϳѻ�ʺ���
****************/

void pgraffiti(BMPHeader *head,unsigned char *pBmpBuf,int mode)
{
	int color=0;
	int key;					//��ֵ
	int width,height;			//ͼƬ�Ŀ�Ⱥ͸߶�
	BITMAPINFOHEADER t;
	MOUSE M;					//�������ṹ��
	POINT a;					//��������صĽṹ��
	t=head->infoHead;
	width=t.biWidth;
	height=t.biHeight;
	shape=0;
	/*Circlefill(439,612,13,PINK);
	Close(370,630,420,660,mode);
	printHZ16(399,612,"��",color,1,1,0);
	printHZ16(400,612,"��",color,1,1,0);
	printHZ16(399,630,"ɫ",color,1,1,0);
	printHZ16(400,630,"ɫ",color,1,1,0);*/
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
				Close(370,630,720,660,mode);//Close(370,600,720,660,mode);
				return;
			}
		}
		
		if(M.x>426 && M.x<452 && M.y>632 && M.y<658)			//������ɫ����ɫ��
		{
			shape=1;
			if(Mousepress(426,632,452,658)==1)
				color=BLOODRED;
		}
	
		else if(M.x>465 && M.x<490 && M.y>632 && M.y<658)		//������ɫ����ɫ��
		{
			shape=1;
			if(Mousepress(465,632,490,658)==1)
				color=ORANGE;
		}
		else if(M.x>504 && M.x<530 && M.y>632 && M.y<658)		//������ɫ����ɫ��
		{
			shape=1;
			if(Mousepress(504,632,530,658)==1)
				color=YELLOW;
		}
		else if(M.x>543 && M.x<569 && M.y>632 && M.y<658)		//������ɫ����ɫ��
		{
			shape=1;
			if(Mousepress(543,632,569,658)==1)
				color=GREEN;
		}
		
		else if(M.x>582 && M.x<608 && M.y>632 && M.y<658)		//������ɫ����ɫ��
		{
			shape=1;
			if(Mousepress(582,632,608,658)==1)
				color=BLUE;
		}

		else if(M.x>621 && M.x<647 && M.y>632 && M.y<658)		//������ɫ����ɫ��
		{
			shape=1;
			if(Mousepress(621,632,647,658)==1)
				color=PURPLE;
		}
		
		else if(M.x>660 && M.x<710 && M.y>632 && M.y<658)		//��ɰ�ť
		{
			shape=1;
			Close(660,632,710,658,BLUE);
			printHZ16(669,637,"���",WHITE,1,1,0);
			printHZ16(670,637,"���",WHITE,1,1,0);
			if(Mousepress(660,632,710,658) == 1)				//����������༭����
			{
				Close(370,630,720,660,mode);
				return;
			}
		}
		
		/*else if(M.x>426 && M.x<452 && M.y>600 && M.y<626)
		{
			shape = 1;
			if(Mousepress(246,600,452,626) == 1)
			{
				color = PINK;
			}
		}*/
		else
		{
			shape=0;
			Close(660,632,710,658,GRAY);
			printHZ16(669,637,"���",BLACK,1,1,0);
			printHZ16(670,637,"���",BLACK,1,1,0);
			
		}
		//�����ͼƬ������
		if(M.x>512-(width/2) && M.x<512+(width/2) && M.y>384-(height/2) && M.y<384+(height/2) && color!=0 )
		{
			if(M.but==1)
			{
				a.x = M.x;
				a.y = M.y;
				pen(head,pBmpBuf,color,a);
				Close(512-(width/2),384-(height/2),512+(width/2),384+(height/2),mode);
				display(head,pBmpBuf);
				delay(50);
			}
		}
		else
		{
			continue;
		}
	}
}

