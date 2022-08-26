#include "head.h"
#include "function.h"
#include "SVGAmode.H"
#include "mmouse.h"
#pragma pack(1)   //强制处理，节省内存

void black(BMPHeader *head,unsigned char *pBmpBuf)
{

	int i,j,k,width,height,biCount,lineByte,lineByteNew;
	int R,G,B;
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
		*(pColorTable+i)=head->palette[i];	
	
	
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			p=(unsigned char *)(pBmpBuf+i*lineByte+j);	
			k=(float)(pColorTable[(*p)].r*0.299 + pColorTable[(*p)].g*0.587 + pColorTable[(*p)].b*0.114);
			if (k <155)
			{
				k = 0;
			}
			else
			{
				k=255;
			}
			(*p)=k;
		}
	}

	head->fileHead=fileHead;
	head->infoHead=infoHead;
	free(pColorTable);
	return ;
}