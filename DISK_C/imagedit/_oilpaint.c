/***********************************************************************

***********************************************************************/
//rand ��Χ(-3,3)->level = 3�ͻ�Ч������-10,10��->level = 10�� 
#include "head.h"
#include "function.h"
#include "SVGAmode.H"
#include "mmouse.h"
#pragma pack(1) 
void oilpaint(BMPHeader *head,unsigned char *pBmpBuf) //��
{
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
	{
		*(pColorTable+i)=head->palette[i];
	}
	srand((unsigned int)time(0));//��ʼ������Ϊ���ֵ

	
	for(i=0;i<height;i++)
	{
		for(j=0;j<width-1;j++)
		{
			int dx = rand() % 8 - 4 ;//����һ��-10-10֮�����
			int dy = rand() % 8 - 4 ;//����һ��-10-10֮�����
			
			p=(unsigned char *)(pBmpBuf+i*lineByte+j);
			
			
			//��RGBֵ
			if(i+dy<0||i+dy>height-1) continue;
			if(j+dx<0||j+dx>width-1) continue;
			pNew=(unsigned char *)(pBmpBuf+(i+dy)*lineByte+j);
			r=(int)(pColorTable[*(pNew+dx)].r);
			g=(int)(pColorTable[*(pNew+dx)].g);
			b=(int)(pColorTable[*(pNew+dx)].b);
			
			//ת��
			R=r;
			G=g;
			B=b;
			
			// RGB���� 
			R=R>255?255:R;     
			G=G>255?255:G;
			B=B>255?255:B;
			
			R=R<0?0:R;
			G=G<0?0:G;
			B=B<0?0:B;
			
			(*p)=getIndex(pColorTable,R,G,B);
		}
	}
	head->fileHead=fileHead;
	head->infoHead=infoHead;
	
	free(pColorTable);
	return ;
}
