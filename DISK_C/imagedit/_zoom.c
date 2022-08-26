#include "head.h"
#include "function.h"
#include "SVGAmode.H"
#include "mmouse.h"
#include "HANZI.H"
#pragma pack(1)

void zoom(BMPHeader *head,unsigned char *pBmpBuf, double lx, double ly)
{

	FILE *fp;
	int width,height,biCount,lineByte,bfSize;
	int newHeight,newWidth,lineByteNew; 
	int i,j,k,x,y;
	BITMAPFILEHEADER fileHead;
	BITMAPINFOHEADER infoHead;
	RGBQUAD *pColorTable;
	unsigned char *pBmpBufNew;
	unsigned char *p,*pNew;
	
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
	
	newHeight=(int)(ly*height+0.5);  
	newWidth=(int)(lx*width+0.5);
	lineByteNew=(newWidth*biCount/8+3)/4*4;
	 
	bfSize=(long long)newHeight*lineByteNew+fileHead.bfOffBits; // 计算缩放后大小 
	bfSize=(bfSize+3)/4*4;
	
	pBmpBufNew=(unsigned char*)malloc(sizeof(unsigned char)*lineByteNew);
	
	fileHead.bfSize=bfSize;
	
	infoHead.biBitCount=biCount;
	infoHead.biClrImportant=0;
	infoHead.biClrUsed=0;
	infoHead.biCompression=0;
	infoHead.biHeight=newHeight;
	infoHead.biPlanes=1;
	infoHead.biSize=40;
	infoHead.biSizeImage=lineByteNew*newWidth;
	infoHead.biWidth=newWidth;
	infoHead.biXPelsPerMeter=0;
	infoHead.biYPelsPerMeter=0;
	
	fp=fopen(".//picture//buffer//after.bmp","wb");
	
	fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);
	fwrite(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);
	fwrite(pColorTable,sizeof(RGBQUAD),256,fp);
	
	
	for(y=0;y<newHeight;y++)
	{
		for(x=0;x<newWidth;x++)
		{
			p=(unsigned char *)(pBmpBufNew+x);
			(*p)=255;
		}
		
		for(x=0;x<newWidth;x++)
		{
			// 四舍五入寻找最近点 
			i=(int)(y/ly+0.5);
			j=(int)(x/lx+0.5);
			
			// 坐标越界修正 
			if(j==width)
			{	
				x--;
			}	
			if(i==height)
			{	
				y--;
			}	
			p=(unsigned char *)(pBmpBuf+i*lineByte+j);
			pNew=(unsigned char *)(pBmpBufNew+x);
			(*pNew)=(*p);
		}
		fwrite(pBmpBufNew,1,lineByteNew,fp);
	}
		
	fclose(fp);
	
 	head->fileHead=fileHead;
	head->infoHead=infoHead;
	
	
	
	free(pColorTable);
	free(pBmpBufNew); 
	return;
}

void pzoom(double *lx, double *ly, int color)
{
	MOUSE M;
	int key;
	int i,x,y=630;
	char *ch[6]={"2:1","1:2","3:2","2:3","4:3","3:4"};
	shape=0;
	printHZ12(250,635,"缩放比例",color,2,2,0);
	printHZ12(251,635,"缩放比例",color,2,2,0);
	put_asc(345,y,"(x:y):",color,1, 2);
	put_asc(346,y,"(x:y):",color,1, 2);
	for(i=0,x=410;i<6;i++,x+=60)
	{
		put_asc(x,y,ch[i],color,1, 2);
	}

	while(*lx==0 && *ly==0)
	{
		MouseXYB(&M);
		MouseStoreBk(M.x, M.y);
		MouseDraw(M);
		delay(20);
		MousePutBk(M.x, M.y);
		
		if( kbhit() )
		{
			key=bioskey(0);
			if(key == ESC)
			{
				return;
			}
		}
		//缩放比例选择
		else if(M.x>410 && M.x<430 && M.y>630 && M.y<655)	//2:1
		{
			shape=1;
			if(Mousepress(410,630,430,655) == 1)
			{
				*lx=1;
				*ly=0.5;
				return;
			}
		}
		else if(M.x>470 && M.x<490 && M.y>630 && M.y<655)	//1:2
		{
			shape=1;
			if(Mousepress(470,630,490,655) == 1)
			{
				*lx=0.5;
				*ly=1;
				return;
			}
		}
		else if(M.x>530 && M.x<550 && M.y>630 && M.y<655)	//3:2
		{
			shape=1;
			if(Mousepress(530,630,550,655) == 1)
			{
				*lx=1;
				*ly=0.65;
				return;
			}
		}
		else if(M.x>590 && M.x<610 && M.y>630 && M.y<655)	//2:3
		{
			shape=1;
			if(Mousepress(590,630,610,655) == 1)
			{
				*lx=0.65;
				*ly=1;
				return;
			}
		}
		else if(M.x>650 && M.x<670 && M.y>630 && M.y<655)	//5:4
		{
			shape=1;
			if(Mousepress(650,630,670,655) == 1)
			{
				*lx=1;
				*ly=0.8;
				return;
			}
		}
		else if(M.x>710 && M.x<730 && M.y>630 && M.y<655)	//4:5
		{
			shape=1;
			if(Mousepress(710,630,730,655) == 1)
			{
				*lx=0.8;
				*ly=1;
				return;
			}
		}
		else
			shape=0;
	}
	//return;
}
