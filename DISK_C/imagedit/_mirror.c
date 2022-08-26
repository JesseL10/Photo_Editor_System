#include"head.h"
#include "SVGAmode.h"
#pragma pack(1)

/*******************************
交换像素函数
传入两点指针 
交换两点的值 
*******************************/
void swapdot(unsigned char *a,unsigned char *b)
{
	unsigned char temp;
	temp=*a;
	*a=*b;
	*b=temp;
	return ;
}

/*******************************
镜像函数
传入图片头，像素缓存区，镜像方向 
1--水平镜像
2--垂直镜像 
*******************************/
void mirror(BMPHeader *head,char *pBmpBuf,int direction)
{
	int i,j,width,height,biCount,lineByte;
	RGBQUAD *pColorTable;
	unsigned char *p1,*p2;
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
	
	//水平 
	if(direction==1)
	{
		for(i=0;i<height;i++)
		{
			for(j=0;j<(width+1)>>1;j++)
			{
				p1=(unsigned char *)(pBmpBuf+i*lineByte+j);
				p2=(unsigned char *)(pBmpBuf+i*lineByte+width-j-1);
				swapdot(p1,p2);
			}
		}
	}
	//垂直 
	else
	{
		for(i=0;i<(height+1)>>1;i++)
		{
			for(j=0;j<width;j++)
			{
				p1=(unsigned char *)(pBmpBuf+i*lineByte+j);
				p2=(unsigned char *)(pBmpBuf+(height-i-1)*lineByte+j);
				swapdot(p1,p2);
			}
		}
	}
	 
	infoHead.biBitCount=biCount;
	infoHead.biClrImportant=0;
	infoHead.biClrUsed=0;
	infoHead.biCompression=0;
	infoHead.biHeight=height;
	infoHead.biPlanes=1;
	infoHead.biSize=40;
	infoHead.biSizeImage=lineByte*height;
	infoHead.biWidth=width;
	infoHead.biXPelsPerMeter=0;
	infoHead.biYPelsPerMeter=0;

	head->fileHead=fileHead;
	head->infoHead=infoHead;
	
	free(pColorTable);
	return ;
}