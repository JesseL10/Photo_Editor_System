#include "head.h"
#include "function.h"
#include "SVGAmode.H"
#include "mmouse.h"
#pragma pack(1)
/**************************************************
�񻯺���
����������˹�㷨���Ƚ���������Χ������ƽ��ֵ�������ʾ��������Χ���صĲ��
�ٽ����������������Ϊ�����صĻҶȡ����һƬ����������һ�����㣬��ô��
����Ľ������������ø�����������ͼ���������
�����صĻҶ�=ԭ�Ҷ�-�õ���Χ����ƽ��ֵ�Ĳ�+ԭ�Ҷ�
**************************************************/

void sharpen(BMPHeader *head,unsigned char *pBmpBuf,int level) //��������˹�㷨��ͼƬ
{
	FILE *fp;
	int i,j,width,height,biCount,lineByte;
	int x,y,dx,dy;
	int cnt;
	long long R,G,B;
	long long r,g,b;
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
	
	pBmpBufNew=(unsigned char*)malloc(sizeof(unsigned char)*lineByte);	
	
	fp=fopen(".//picture//buffer//after.bmp","wb");
	
	fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);
	fwrite(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);
	fwrite(pColorTable,sizeof(RGBQUAD),256,fp);
	
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			R=G=B=0;
			p=(unsigned char *)(pBmpBuf+i*lineByte+j);
			
			// ��ǰ���RGB 
			r=(int)pColorTable[(*p)].r;
			g=(int)pColorTable[(*p)].g;
			b=(int)pColorTable[(*p)].b;
			pNew=(unsigned char *)(pBmpBufNew+j);
			
			cnt=0;
 
			for(dx=-level;dx<=level;dx++)      // ��ȡ�񻯰뾶�ڵĵ� 
			{
				for(dy=-level;dy<=level;dy++)  
				{
				
					if(!dx&&!dy) continue;			// �ж��Ƿ���ͼƬ��
					if(i+dy<0||i+dy>height-1) continue;
					if(j+dx<0||j+dx>width-1) continue;
					
					
					p=pBmpBuf+(i+dy)*lineByte+(j+dx);   //����Χ��ƽ��ֵ
					R+=(long long)(pColorTable[(*p)].r);
					G+=(long long)(pColorTable[(*p)].g);
					B+=(long long)(pColorTable[(*p)].b);
					cnt++;
				}
			}
			
			
			R=r - R/cnt + r;	//���������ػҶȣ�����ͼ�������.
			G=g - G/cnt + g;
			B=b - B/cnt + b;
			
			
			R=R>255?255:R;     //RGB����
			G=G>255?255:G;
			B=B>255?255:B;
			
			R=R<0?0:R;
			G=G<0?0:G;
			B=B<0?0:B;
			
			(*pNew)=getIndex(pColorTable,R,G,B);
		}
		fwrite(pBmpBufNew,1,lineByte,fp);
	}
	head->fileHead=fileHead;
	head->infoHead=infoHead;
	
	fclose(fp);
	
	free(pBmpBufNew);
	free(pColorTable);
	return ;
}
