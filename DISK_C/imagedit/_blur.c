#include "head.h"
#include "function.h"
#include "SVGAmode.H"
#include "mmouse.h"
#pragma pack(1)
/********************************
ģ������
�ữ�����ԭ���ǽ�ͼƬ��ÿһ������
����������Χ���ص�ƽ��ֵ�����档
�ữ�뾶��ȡֵ��������ģ���̶�
********************************/

void blur(BMPHeader *head,unsigned char *pBmpBuf,int level)
{
	FILE *fp;
	int i,j,width,height,biCount,lineByte;
	int dx,dy;
	long long R,G,B;
	int cnt;
	int Radius;
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

	Radius = level +1;
	
	pBmpBufNew=(unsigned char*)malloc(sizeof(unsigned char)*lineByte);	
	
	fp=fopen(".//picture//buffer//after.bmp","wb");
	fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);
	fwrite(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);
	fwrite(pColorTable,sizeof(RGBQUAD),256,fp);
	
	if(level!=0)
	{
	for(i=0;i<height;i++)
		{
			for(j=0;j<width;j++)
			{
				R=G=B=0;
				pNew=(unsigned char *)(pBmpBufNew+j);
				
				cnt=0;
				
				for(dx=-Radius;dx<=Radius;dx++)                // ��ȡ�ữ�뾶�ڵĵ� 
				{
					for(dy=-Radius;dy<=Radius;dy++)
					{
						if(i+dy<0||i+dy>height-1) continue;    // �ж��Ƿ���ͼƬ��
						if(j+dx<0||j+dx>width-1) continue;
						p=pBmpBuf+(i+dy)*lineByte+(j+dx);
						R+=(long long)(pColorTable[(*p)].r);
						G+=(long long)(pColorTable[(*p)].g);
						B+=(long long)(pColorTable[(*p)].b);
						cnt++;
					}
				}
				
				// �ữ��ʽ 
				R/=cnt;	
				G/=cnt;
				B/=cnt;
				
				
				(*pNew)=getIndex(pColorTable,R,G,B);
			}
			fwrite(pBmpBufNew,1,lineByte,fp);
		}
	}
	else
	{
		Radius += 1;
		for(i=0;i<height;i++)
		{
			for(j=0;j<width;j++)
			{
				R=G=B=0;
				pNew=(unsigned char *)(pBmpBufNew+j);
				
				cnt=0;
				
				for(dx=-Radius;dx<=Radius;dx++)                // ��ȡ�ữ�뾶�ڵĵ� 
				{
							// �ж��Ƿ���ͼƬ��
						if(j+dx<0||j+dx>width-1) continue;
						p=pBmpBuf+i*lineByte+(j+dx);
						R+=(long long)(pColorTable[(*p)].r);
						G+=(long long)(pColorTable[(*p)].g);
						B+=(long long)(pColorTable[(*p)].b);
						cnt++;
					
				}
				
				R/=cnt;	
				G/=cnt;
				B/=cnt;
				
				
				(*pNew)=getIndex(pColorTable,R,G,B);
			}
			
		}
	}
	fclose(fp);
	head->fileHead=fileHead;
	head->infoHead=infoHead;
	
	
	free(pBmpBufNew);
	free(pColorTable);
	return ;
}
