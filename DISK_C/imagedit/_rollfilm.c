#include "head.h"
#include "function.h"
#include "SVGAmode.H"
#include "mmouse.h"
#pragma pack(1)   

void rollfilm(BMPHeader *head,unsigned char *pBmpBuf)	// ½º¾íÂË¾µº¯Êý
{	

	int i,j,k,width,height,biCount,lineByte,lineByteNew;
	int r,g,b;
	RGBQUAD *pColorTable;
	unsigned char *p;
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
	
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			p=(unsigned char *)(pBmpBuf+i*lineByte+j);
			r=(int)pColorTable[(*p)].r;
			g=(int)pColorTable[(*p)].g;
			b=(int)pColorTable[(*p)].b;
			
		 
			r=255-r;
			g=255-g;
			b=255-b;
			(*p)=getIndex(pColorTable,r,g,b);
		}
	}

	head->fileHead=fileHead;
	head->infoHead=infoHead;
	free(pColorTable);
	return ;
}
