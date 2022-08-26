#include "head.h"
#include "function.h"
#include "SVGAmode.H"
#include "mmouse.h"
#pragma pack(1) 
/**************************************************
 ������
 ÿ�����ص�RGBֵ������Ϊ��λ�õĳ�ʼֵimg��I,j��
 ��ȥ�����·��ڶ�������img(i+5,j+5)�Ĳ���ͳһ
 ����128���ڿ��ƻҶȣ���ʾ�����Ƹ���Ļ�ɫ��

��ͼ���ϵ�ÿ���������ĶԽ��ߵ����ص��γɲ�ֵ��
�����������Ƶ���ɫ��ͻ����ͬ����ɫ����Ե����
��ʹͼ���������У����������ڸ����Ч����

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
			// ��ǰλ��RGBֵ 
			p=(unsigned char *)(pBmpBuf+i*lineByte+j);
			r=(long long)(pColorTable[(*p)].r);
			g=(long long)(pColorTable[(*p)].g);
			b=(long long)(pColorTable[(*p)].b);
			
			// ��ǰ��Խ���RGBֵ 
			pNew=(unsigned char *)(pBmpBuf+(i+level)*lineByte+j);
			rr=(int)(pColorTable[*(pNew+level)].r);
			rg=(int)(pColorTable[*(pNew+level)].g);
			rb=(int)(pColorTable[*(pNew+level)].b);
			
			// ����Ч����ʽ 
			R=r-rr+127;
			G=g-rg+127;
			B=b-rb+127;
			
			// RGB���� 
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




