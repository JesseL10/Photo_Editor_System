#include "head.h"
#include "function.h"
#include "SVGAmode.H"
#include "mmouse.h"
#pragma pack(1)   //强制处理，节省内存
/********************************
 亮度调节函数
 传入图片头，像素块，调节级数，当前亮度级数 
 先根据当前级数恢复图片 
 再将图片亮度转换为所选级数 
*******************************/
void brightness(BMPHeader *head,unsigned char *pBmpBuf,int level)
{	
	FILE *fp;
	int i,j,k,width,height,biCount,lineByte,lineByteNew;
	int R,G,B;
	RGBQUAD *pColorTable;
	unsigned char *p,*pNew;
	unsigned char *pBmpBufNew;
	double rate;
	BITMAPFILEHEADER fileHead;
	BITMAPINFOHEADER infoHead;	
	
	fileHead=head->fileHead;
	infoHead=head->infoHead;
	
	width=infoHead.biWidth;
	height=infoHead.biHeight;
	biCount=infoHead.biBitCount; 
	lineByte=(width*biCount/8+3)/4*4; 
	
	
	rate=1.0;
	

	// 根据所选级数计算新的调节倍率 
	switch(level)
	{
		case 5:
			rate=1.3;
			break;
		case 4:
			rate=1.2;
			break;
		case 3:
			break;
		case 2:
			rate=0.9;
			break;
		case 1:
			rate=0.75;
			break;
	}
	

	pColorTable=(RGBQUAD*)malloc(sizeof(RGBQUAD)*256); 

	
	for(i=0;i<256;i++)
	{
		*(pColorTable+i)=head->palette[i];
	}
	fp=fopen(".//picture//buffer//after.bmp","wb");
	fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);
	fwrite(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);
	fwrite(pColorTable,sizeof(RGBQUAD),256,fp);
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			
			if(rate!=1)
			{

				p=(unsigned char *)(pBmpBuf+i*lineByte+j);
				//计算新的RGB分量 
				R=(int)(pColorTable[(*p)].r*rate);
				G=(int)(pColorTable[(*p)].g*rate);
				B=(int)(pColorTable[(*p)].b*rate);
				
				// RGB修正 
				if(R>255) R=2*255-R;
				if(G>255) G=2*255-G;
				if(B>255) B=2*255-B;
				
				//查找新的索引值 
				(*p)=getIndex(pColorTable,R,G,B);
			}
			else 
			{
				continue;
			}
		}

	}
	fwrite(pBmpBuf,1,lineByte*height,fp);
	
	fclose(fp);
	head->fileHead=fileHead;
	head->infoHead=infoHead;
	free(pColorTable);
	return ;
}






/*******************************
 索引值查找函数
 传入调色板，RGB信息 
 在传入调色板中查找最相近的颜色
 返回最相近颜色的索引值 
*******************************/
int getIndex(RGBQUAD *pColorTable,unsigned char r,unsigned char g,unsigned char b)
{
	int i,deltal=100;
	int tot,index;
	for(i=0;i<256;i++)
	{
		tot=0;
		
		// 累加RGB偏移量 
		tot+=abs(pColorTable[i].r-r);
		tot+=abs(pColorTable[i].g-g);
		tot+=abs(pColorTable[i].b-b);
		
		// 寻找最接近颜色 
		if(tot<deltal) 
		{
			deltal=tot;
			index=i;
		}
	}
	return index;
}
void Pretreatment(BMPHeader *head,unsigned char *pBmpBuf)  //预处理函数
{
	FILE *fp;
	int width,height,biCount,lineByte; 
	int i,j;
	BITMAPFILEHEADER fileHead;
	BITMAPINFOHEADER infoHead;
	RGBQUAD *pColorTable;
	
	fileHead=head->fileHead;
	infoHead=head->infoHead;
	width=infoHead.biWidth;
	height=infoHead.biHeight;
	biCount=infoHead.biBitCount; 
	lineByte=(width*biCount/8+3)/4*4; 
	pColorTable=head->palette;
	
	fp=fopen(".//picture//buffer//brightness.bmp","wb");
	
	fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);
	fwrite(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);
	fwrite(pColorTable,sizeof(RGBQUAD),256,fp);
	fwrite(pBmpBuf,lineByte*height,1,fp);
		
	fclose(fp);

	return;
}
