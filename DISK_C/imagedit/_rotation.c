#include"head.h"
#include "function.h"
#include "SVGAmode.h"
#include "mmouse.h"
#pragma pack(1)

/*******************************
 旋转函数
 传入图片头，像素缓存区，旋转方向
  1--顺时针旋转90 
 -1--逆时针旋转90 
*******************************/
void rotation(BMPHeader *head,char *pBmpBuf,int direction)
{
	FILE *fp;
	int i,j,k,width,height,biCount,lineByte,lineByteNew;
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

	// 计算新的行长度 
	lineByteNew=(height*biCount/8+3)/4*4;
	pBmpBufNew=(unsigned char*)malloc(sizeof(unsigned char)*lineByteNew); 
	
	// 更新信息头信息 
	infoHead.biBitCount=biCount;
	infoHead.biClrImportant=0;
	infoHead.biClrUsed=0;
	infoHead.biCompression=0;
	infoHead.biHeight=width;
	infoHead.biPlanes=1;
	infoHead.biSize=40;
	infoHead.biSizeImage=lineByteNew*width;
	infoHead.biWidth=height;
	infoHead.biXPelsPerMeter=0;
	infoHead.biYPelsPerMeter=0;
	
	fp=fopen(".//picture//buffer//after.bmp","wb");
	
	fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);
	fwrite(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);
	fwrite(pColorTable,sizeof(RGBQUAD),256,fp);
	
	//向右旋转90度
	if(direction==1)
	{
		for(j=0;j<width;j++)
		{
			for(i=0;i<height;i++)
			{
				p=(unsigned char *)(pBmpBufNew+i);
				(*p)=255;
			}
			for(i=0;i<height;i++)
			{
				p=(unsigned char *)(pBmpBuf+i*lineByte+(width-j-1));
				pNew=(unsigned char *)(pBmpBufNew+i);
				(*pNew)=(*p);
			}
			fwrite(pBmpBufNew,1,lineByteNew,fp);
		}
	}
	// 向左旋转90度
	else
	{
		for(j=0;j<width;j++)
		{
			for(i=0;i<height;i++)
			{
				p=(unsigned char *)(pBmpBufNew+i);
				(*p)=255;
			}
			for(i=0;i<height;i++)
			{
				p=(unsigned char *)(pBmpBuf+i*lineByte+j);
				pNew=(unsigned char *)(pBmpBufNew+(height-i-1));
				(*pNew)=(*p);
			}	
			fwrite(pBmpBufNew,1,lineByteNew,fp);
		}
	}
	
	
	fclose(fp);
	
	head->fileHead=fileHead;
	head->infoHead=infoHead;
	
	free(pColorTable);
	free(pBmpBufNew);
	return ;
}