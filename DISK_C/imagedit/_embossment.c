#include "head.h"
#include "function.h"
#include "SVGAmode.H"
#include "mmouse.h"
#pragma pack(1) 
/**************************************************
 浮雕函数
 每个像素的RGB值都设置为该位置的初始值img（I,j）
 减去其右下方第二的像素img(i+5,j+5)的差，最后统一
 加上128用于控制灰度，显示出类似浮雕的灰色。

将图像上的每个点与它的对角线的像素点形成差值，
这样淡化相似的颜色，突出不同的颜色、边缘，从
而使图像产生纵深感，产生类似于浮雕的效果。

**************************************************/

void embossment(BMPHeader *head,unsigned char *pBmpBuf)
{
	
	int level=2;
	int i,j,width,height,biCount,lineByte;
	long long r,g,b,rr,rg,rb;
	long long R,G,B;
	RGBQUAD *pColorTable;
	unsigned char *pBmpBufNew;
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
		*(pColorTable+i)=head->palette[i];
	
	for(i=0;i<height;i++)
	{
		for(j=0;j<width-1;j++)
		{
			if(i+level<0||i+level>height-1) continue;
			if(j+level<0||j+level>width-1) continue;
			// 当前位置RGB值 
			p=(unsigned char *)(pBmpBuf+i*lineByte+j);
			r=(long long)(pColorTable[(*p)].r);
			g=(long long)(pColorTable[(*p)].g);
			b=(long long)(pColorTable[(*p)].b);
			
			// 当前点对角线RGB值 
			pNew=(unsigned char *)(pBmpBuf+(i+level)*lineByte+j);
			rr=(int)(pColorTable[*(pNew+level)].r);
			rg=(int)(pColorTable[*(pNew+level)].g);
			rb=(int)(pColorTable[*(pNew+level)].b);
			
			// 浮雕效果公式 
			R=r-rr+127;
			G=g-rg+127;
			B=b-rb+127;
			
			// RGB修正 
			if(R>255) R=2*255-R;
			if(G>255) G=2*255-G;
			if(B>255) B=2*255-B;
			(*p)=getIndex(pColorTable,R,G,B);
		}
	}
	head->fileHead=fileHead;
	head->infoHead=infoHead;
	
	free(pColorTable);
	return ;
}




