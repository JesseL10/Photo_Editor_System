#ifndef	INOUT_H
#define	INOUT_H

#include "SVGAmode.h"

int opendialog(char *filename, int status, int mode);//打开图片对话框

int Inputjudge(char*code,char*filename, int status);//判断输入打开及保存文件名规范

int savedialog(char *filename, int status, int mode);//保存图片对话框

int ReadBMPHEAD(BMPHeader* head,char *address);//读取BMP图像文件头

int ReadPic(unsigned char* p,int size,char *address);//读取BMP图像

int SAVEPIC(BMPHeader* head,unsigned char *pBmpBuf,char *address);//保存BMP图像

void display(BMPHeader* head,char *pBmpBuf);//将所打开BMP图像写入显存

int compare(char *code);

int sizejudge(BMPHeader* head);

void cue(int recev, int status);
#endif