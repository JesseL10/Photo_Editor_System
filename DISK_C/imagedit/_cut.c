#include "head.h"
#include "function.h"
#include "SVGAmode.H"
#include "mmouse.h"

int cutJudge(BMPHeader *head,struct point fclick,struct point sclick)//裁剪判断函数
{
	int top,left,right,bottom,width,height;
	struct point lefttop;
	struct point rightbottom;
	BITMAPINFOHEADER infoHead;
	//BITMAPFILEHEADER fileHead;
	//fileHead=head->fileHead;
	infoHead=head->infoHead;
		
	width=infoHead.biWidth;
	height=infoHead.biHeight;
	
	top=384-height/2;           //计算图片位置
	bottom=384+height/2;
	right=512+width/2;
	left=512-width/2;
	lefttop.x=fclick.x;
	lefttop.y=fclick.y;
	rightbottom.x = sclick.x;
	rightbottom.y = sclick.y;
	
	if(lefttop.y==rightbottom.y||lefttop.x==rightbottom.x)
	{
		return 0;
	}	
	                 //裁剪完全不在图片上
	else if(lefttop.x<left || lefttop.y>bottom || lefttop.x>right || lefttop.y<top)
	{
		if(rightbottom.x<left || rightbottom.y>bottom || rightbottom.x>right || rightbottom.y<top)
		{
			return 0;
		}
		else
		{
			return 1;
		}
		
	}
	else if(rightbottom.x<left || rightbottom.y>bottom || rightbottom.x>right || rightbottom.y<top)
	{
		if(lefttop.x<left || lefttop.y>bottom || lefttop.x>right || lefttop.y<top)
		{	
		return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 1;
	}
}
/*
 裁剪函数
 传入：文件头，缓存像素信息，第一次点击位置，第二次点击位置 
 保留左上右下点之间部分,超出部分按
 边界处理
*/
void cut(BMPHeader *head,char *pBmpBuf,struct point fclick,struct point sclick)
{
	FILE *fp;
	int i,j,k,top,left,right,bottom,width,height,bfSize,biCount,lineByte,lineByteNew;
	int a,x1,x2,y1,y2,newHeight,newWidth;
	struct point lefttop;
	struct point rightbottom;
	unsigned char *p,*pNew;
	unsigned char *pBmpBufNew;
	RGBQUAD *pColorTable;
	BITMAPINFOHEADER infoHead;
	BITMAPFILEHEADER fileHead;
	
	fileHead=head->fileHead;
	infoHead=head->infoHead;
		
	width=infoHead.biWidth;
	height=infoHead.biHeight;
	biCount=infoHead.biBitCount; 
	lineByte=(width*biCount/8+3)/4*4; 
	 
	top=384-height/2;           //计算图片位置
	bottom=384+height/2;
	right=512+width/2;
	left=512-width/2;
	                            //判断左右
	if (fclick.x<=sclick.x)
	{
		lefttop.x = fclick.x;
		rightbottom.x = sclick.x;
	}
	else 
	{
		lefttop.x = sclick.x;
		rightbottom.x = fclick.x;
	}
	                            //判断上下
	if (fclick.y<=sclick.y)
	{
		lefttop.y = fclick.y;
		rightbottom.y = sclick.y;
	}
	else 
	{
		lefttop.y = sclick.y;
		
		rightbottom.y = fclick.y;
	}
	
	//裁剪超出图片部分按边界处理
	if(lefttop.x<left) 
	{	
		lefttop.x=left;
	}	
	if(rightbottom.x>right) 
	{	
		rightbottom.x=right;
	}
	if(lefttop.y<top)
	{
		lefttop.y=top;
	}
	if(rightbottom.y>bottom) 
	{	
		rightbottom.y=bottom;
	}
	//计算裁剪后边界值 
	x1=lefttop.x-left;
	x2=rightbottom.x-left;
	y1=bottom-rightbottom.y;
	y2=bottom-lefttop.y;
		
	
	//计算裁剪后图片的几何尺寸 
	newHeight=y2-y1;
	newWidth=x2-x1;
	lineByteNew=(newWidth*biCount/8+3)/4*4; 
	pBmpBufNew=(unsigned char*)malloc(sizeof(unsigned char)*lineByteNew);	
	pColorTable=(RGBQUAD*)malloc(sizeof(RGBQUAD)*256); 
	for(i=0;i<256;i++)
	{
		*(pColorTable+i)=head->palette[i];
	}
	
	//更新图片文件头信息 
	bfSize=newHeight*lineByteNew+fileHead.bfOffBits;
	bfSize=(bfSize+3)/4*4;
	fileHead.bfSize=bfSize;
	
	//更新图片信息头信息
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
	for(i=y1;i<=y2;i++)
	{
		                   // 内存初始化 
		for(j=x1;j<=x2;j++)
		{
			pNew=(unsigned char *)(pBmpBufNew+i);
				(*p)=255;
		}
	}	
	for(i=y1;i<=y2;i++)
	{
		for(j=x1;j<=x2;j++)
		{
			p=(unsigned char *)(pBmpBuf+i*lineByte+j);
			pNew=(unsigned char *)(pBmpBufNew+(j-x1));
			(*pNew)=(*p);
		}
		fwrite(pBmpBufNew,1,lineByteNew,fp);
	}	


	fclose(fp); 
	head->fileHead=fileHead;
	head->infoHead=infoHead;
	free(pBmpBufNew);       
	free(pColorTable);
	return ;
}