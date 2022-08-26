#include "head.h"
#include "function.h"
#include "SVGAmode.H"
#include "inout.h"
#include "mmouse.h"
#pragma pack(1)

void inverted(BMPHeader *head,unsigned char *pBmpBuf) //粒子
{
	FILE *fp;
	int dx,dy;
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
	srand((unsigned int)time(0));//初始化种子为随机值

	
	for(i=0;i<height;i++)
	{
	
		for(j=0;j<width-1;j++)
		{	
			dy =0;
			if(i<(int)(height/4))
			{
				dx = rand() %10-5 ;//产生一个-10-10之间的数	
			}
			else if(i<(int)(height/2))
			{
				dx = rand() % 8-4;	
			}
			else if(i<(int)(height*3/4))
			{
				dx = rand() % 6-3;	
			}
			else
			{
				dx = rand() % 2-1;
			}
			p=(unsigned char *)(pBmpBuf+i*lineByte+j);
			
			
			//震荡RGB值
			if(i+dy<0||i+dy>height-1) continue;
			if(j+dx<0||j+dx>width-1) continue;
			pNew=(unsigned char *)(pBmpBuf+(i+dy)*lineByte+j);
			r=(int)(pColorTable[*(pNew+dx)].r);
			g=(int)(pColorTable[*(pNew+dx)].g);
			b=(int)(pColorTable[*(pNew+dx)].b);
			
			//转换
			R=r;
			G=g;
			B=b;
			
			// RGB修正 
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

void Splicing(BMPHeader *head,BMPHeader *oldhead,unsigned char *tempf,unsigned char *temp)  //拼接函数
{
	FILE *fp;
	int width,height,biCount,lineByte,bfSize;
	int oldwidth,oldheight,oldbiCount,oldlineByte;
	int newHeight,newWidth,lineByteNew; 
	int i,j;
	BITMAPFILEHEADER fileHead;
	BITMAPINFOHEADER infoHead;
	//BITMAPFILEHEADER oldfileHead;
	BITMAPINFOHEADER oldinfoHead;
	
	RGBQUAD *pColorTable;
	unsigned char *pBmpBufNew;
	unsigned char *p,*pNew;
	
	fileHead=head->fileHead;
	infoHead=head->infoHead;
	width=infoHead.biWidth;
	height=infoHead.biHeight;
	biCount=infoHead.biBitCount; 
	lineByte=(width*biCount/8+3)/4*4;

	//oldfileHead=oldhead->fileHead;
	oldinfoHead=oldhead->infoHead;
	oldwidth=oldinfoHead.biWidth;
	oldheight=oldinfoHead.biHeight;
	oldbiCount=oldinfoHead.biBitCount; 
	oldlineByte=(oldwidth*oldbiCount/8+3)/4*4; 
	
	pColorTable=(RGBQUAD*)malloc(sizeof(RGBQUAD)*256); 
	for(i=0;i<256;i++)
	{
		*(pColorTable+i)=head->palette[i];
	}
	//之后加选择
	newHeight=(int)(oldheight+height);  
	newWidth=width;
	lineByteNew=(newWidth*biCount/8+3)/4*4;
	bfSize=(long long)newHeight*lineByteNew+fileHead.bfOffBits; // 计算大小 
	bfSize=(bfSize+3)/4*4;
	
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
	
	pBmpBufNew=(unsigned char*)malloc(sizeof(unsigned char)*lineByteNew);
	fp=fopen(".//picture//buffer//after.bmp","wb");
	
	fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);
	fwrite(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);
	fwrite(pColorTable,sizeof(RGBQUAD),256,fp);

	for(i=0;i<height;i++)
	{
		for(j=0;j<newWidth;j++)
		{
			p=(unsigned char *)(pBmpBufNew+j);
			(*p)=255;
		}
		
		for(j=0;j<newWidth;j++)
		{
			p=(unsigned char *)(tempf+i*oldlineByte+j);
			pNew=(unsigned char *)(pBmpBufNew+j);
			(*pNew)=(*p);
		}
		fwrite(pBmpBufNew,1,lineByteNew,fp);
	}
	for(i=0;i<oldheight;i++)
	{
		for(j=0;j<newWidth;j++)
		{
			p=(unsigned char *)(pBmpBufNew+j);
			(*p)=255;
		}
		for(j=0;j<newWidth;j++)
		{
			p=(unsigned char *)(temp+i*lineByte+j);
			pNew=(unsigned char *)(pBmpBufNew+j);
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

void reflect(BMPHeader *head,unsigned char *pBmpBuf)
{
	BITMAPINFOHEADER t;
	BMPHeader oldhead;	
	unsigned char* tempold;
	int height=0,width=0,biCount,lineByte;	
	
	Pretreatment(head,pBmpBuf);
	
	mirror(head,pBmpBuf,2);

	inverted(head,pBmpBuf);
	
	zoom(head,pBmpBuf,1.0,0.5);
	free(pBmpBuf);
	ReadBMPHEAD(head,".//picture//buffer//after.bmp");
	t=head->infoHead;
	height=t.biHeight;
	width=t.biWidth;
	biCount=t.biBitCount;
	lineByte=(width*biCount/8+3)/4*4;
	pBmpBuf=(unsigned char*)malloc(sizeof(unsigned char)*height*lineByte);
	ReadPic(pBmpBuf,lineByte*height,".//picture//buffer//after.bmp");
	remove(".//picture//buffer//after.bmp");
	
	blur(head,pBmpBuf,2);
	ReadBMPHEAD(&oldhead,".//picture//buffer//brightness.bmp");
	t=oldhead.infoHead;
	height=t.biHeight;
	width=t.biWidth;
	biCount=t.biBitCount;
	lineByte=(width*biCount/8+3)/4*4;
	tempold=(unsigned char*)malloc(sizeof(unsigned char)*height*lineByte);
	ReadPic(tempold,lineByte*height,".//picture//buffer//brightness.bmp");
	remove(".//picture//buffer//brightness.bmp");	
	
	Splicing(head,&oldhead,pBmpBuf,tempold);
	
	free(tempold);
	return;
}


