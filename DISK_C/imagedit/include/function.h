#ifndef _FUNCTION_H_
#define _FUNCTION_H_ 
#pragma pack(1) 

#include "SVGAmode.h"
#include "mmouse.h"

void rotation(BMPHeader *head,char *pBmpBuf,int direction);									//旋转函数

void mirror(BMPHeader *head,char *pBmpBuf,int direction);									//镜像函数

void swapdot(unsigned char *a,unsigned char *b);											//像素交换函数

int getIndex(RGBQUAD *pColorTable,unsigned char r,unsigned char g,unsigned char b);			//索引值查找函数

void brightness(BMPHeader *head,unsigned char *pBmpBuf,int level);							//亮度函数

void sharpen(BMPHeader *head,unsigned char *pBmpBuf,int level);								//锐化函数

void blur(BMPHeader *head,unsigned char *pBmpBuf,int level);								//模糊函数

void pmosiac(BMPHeader *head,unsigned char *pBmpBuf,int mode);								//马赛克菜单

void mosaic(BMPHeader *head,unsigned char *pBmpBuf,int Diameter, struct point click);		//马赛克函数

void cut(BMPHeader *head,char *pBmpBuf,struct point fclick,struct point sclick);			//裁剪函数

void rollfilm(BMPHeader *head,unsigned char *pBmpBuf);										//胶卷滤镜函数

void black(BMPHeader *head,unsigned char *pBmpBuf);											//漫画函数

void embossment(BMPHeader *head,unsigned char *pBmpBuf);									//浮雕函数

void oilpaint(BMPHeader *head,unsigned char *pBmpBuf);										//油画函数

void zoom(BMPHeader *head,unsigned char *pBmpBuf, double lx, double ly);					//缩放函数

int cutJudge(BMPHeader *head,struct point fclick,struct point sclick);						//裁剪判断函数

void pen(BMPHeader *head,unsigned char *pBmpBuf,int color, struct point click);				//涂鸦笔函数

void pgraffiti(BMPHeader *head,unsigned char *pBmpBuf,int mode);							//涂鸦笔菜单

void reflect(BMPHeader *head,unsigned char *pBmpBuf);										//倒影滤镜函数

void Splicing(BMPHeader *head,BMPHeader *oldhead,unsigned char *tempf,unsigned char *temp);	//拼接函数

void inverted(BMPHeader *head,unsigned char *pBmpBuf);										//图像反转函数

void pzoom(double *lx, double *ly, int color);												//缩放选择函数

void Pretreatment(BMPHeader *head,unsigned char *pBmpBuf);									//预处理，缓存图片当前图片


#endif
