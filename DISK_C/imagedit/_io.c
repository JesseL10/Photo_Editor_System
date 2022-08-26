#include "head.h"
#include "inout.h"
#include "SVGAmode.h"
#include "mmouse.h"
#include "draw.h"
#include "HANZI.H"
#include "menu.h"

int opendialog(char *filename, int status, int mode);

int Inputjudge(char*code,char*filename, int status);

int savedialog(char *filename, int status, int mode);

/*打开图片对话框*/
int opendialog(char *filename, int status, int mode)
{
	int key;								//键值
	int recev;								//返回值，receive的缩写
	char code[50] ;							//输入字符串
	int letter = 0;							//输入字符的位序
	int cor=0;								//输入字符的坐标
	int flag = 0;							//判断键值输入与否
	
	MOUSE M;								//鼠标结构体变量

	ui(mode, DIALOG, status);				//画出对应的对话框

	while(1)
	{
		MouseXYB(&M);
		MouseStoreBk(M.x, M.y);
		MouseDraw(M);
		delay(20);
		MousePutBk(M.x, M.y);
		shape = 0;
		
		if(M.x>125 && M.x<200 && M.y>580 && M.y<610)			//确定按钮
		{
			if(Mousepress(125,580,200,610) == 0)
			{
				shape=1;
			}
			else if(Mousepress(125,580,200,610) == 1)
			{
				recev=Inputjudge(code,filename,status);
				switch(recev)
				{
					case 1:										//打开成功
					{
						Close(0,440,325,665,mode);
						delay(1000);
						return 1;
					}
					
					default:
					{											//打开失败，输出对应提示
						cue(recev,OPEN);
					}
					break;
				}
			}
		}

		if(M.x>223 && M.x<273 && M.y>495 && M.y<520)			//退出按钮
		{
			if(Mousepress(223,495,273,520) == 0) 
			{
				shape=1;
			}
			else if(Mousepress(223,495,273,520) == 1)
			{
				Close(0,440,325,665,mode);
				return 0;
			}
		}
		
		if(status == 1)											//输入框 传入的box的类型  1：打开文件 2:保存
		{
			flag=bioskey(1);

			if(flag)											//若监测到键盘有输入值
			{
				key = bioskey(0);
				switch(key)
				{
					case Enter:
					{
						recev=Inputjudge(code,filename,status);
						switch(recev)
						{
							case 1:								//打开成功
							{
								Close(0,440,325,665,mode);
								delay(100);
								return 1;
							}
							
							default:
							{
								cue(recev,OPEN);
							}
							break;	
						}
					}
					break;
					
					case Backspace: 							//退格
					{
						if(letter>=1)
						{
							code[letter-1] = '\0';
							delay(50);
							cor-=16;
							letter --;
							Close(40+cor, 530, 56+cor, 565, WHITE);
						}
					}
					break;
					
					case ESC:									//退出当前对话框
					{
						Close(0,440,325,665,mode);
						return 0;
					}
					
					default:									//输入字母和数字
					{
						if(letter<=14)
						{
							code[letter] = key;
							code[letter+1] = '\0';
							letter++;
							Put_Asc16_Size(40+cor,535,2, 2, key, BLACK);
							cor+=16;	
							break;
						}
						
						else
						{
							printHZ12(40,475,"输入字符达上限！",BLOODRED,2,2,1);
							getch();
							Close(40, 475, 225, 500, MATCHA);
							break;
						}
					}
				}
			}
		}
	}
}

/*打开与保存提示语，recev为输入判断返回值，status为状态（打开或保存）*/
void cue(int recev, int status)
{
	switch(status)
	{
		case OPEN:
		{
			switch(recev)
			{
				case -1:									//打开失败
				{
					printHZ12(40,475,"打开文件失败！",BLOODRED,2,2,1);
					getch();
					Close(40,475,200,500,MATCHA);
					return;
				}
				
				case -2:
				{
					printHZ12(40,475,"打开图片过大！",BLOODRED,2,2,1);
					getch();
					Close(40,475,200,500,MATCHA);	
					return;
				}
				
				case -3:
				{
					printHZ12(40,475,"图片格式错误！",BLOODRED,2,2,1);
					getch();
					Close(40,475,200,500,MATCHA);	
					return;	
				}
				
				case -4:
				{
					printHZ12(40,475,"图片不存在！",BLOODRED,2,2,1);
					getch();
					Close(40,475,200,500,MATCHA);	
					return;		
				}
			}
		}
		break;
		
		case SAVE:
		{
			switch(recev)
			{
				case -1:									//保存失败
				{
					printHZ12(705,475,"图片保存失败！",BLOODRED,2,2,1);
					getch();
					Close(705,475,865,500,MATCHA);
					return;
				}
				
				case -2:
				{
					printHZ12(705,475,"存在非法字符！",BLOODRED,2,2,1);
					getch();
					Close(705,475,865,500,MATCHA);
					return;					
				}
				
				case -3:
				{
					printHZ12(705,475,"文件名已存在！",BLOODRED,2,2,1);
					getch();
					Close(705,475,875,500,MATCHA);
					return;	
				}
			}
		}
		break;
	}
}

/*查找输入名称中是否含有空格*/
int compare(char *code)
{
	int i;
	if(strlen(code) == 0)
	{
		return 0;
	}
	
	for(i=0;i<strlen(code);i++)							//遍历字符串，查找是否有非法字符
	{
		if(code[i] == ' ')
		{
			return 0;
		}
		else
			continue;
	}
	
	return 1;
}

/*判断输入字符串*/
int Inputjudge(char*code, char*filename, int status)	//status，OPEN为打开图片，SAVE为保存图片
{		
	int i;												//循环变量
	int flag;
	BMPHeader head;
	char prefix[50]=".//PhotoLib//";
	//char *prefixs=".//album//";
	char *affix = ".bmp";
	flag=compare(code);
	switch(status)
	{
		case OPEN:
		{
			if(strlen(code)<5)
			{
				return -1;
			}
			/*判断后缀，非bmp格式保存失败*/
			for(i = strlen(code)-1;i >= strlen(code)-4;i--)
			{
				if(code[i] != affix[4-strlen(code)+i])
				{
					return -3;
				}
			}
			strcat(prefix,code);
			//判断图片是否存在，不存在则返回-4显示相应提示	
			if(access(prefix, 0)==-1)
			{
				return -4;												
			}
			
			//如果指定文件夹该文件存在且可读
			else if(access(prefix, 4)==0 && code!=NULL && strcmp(code,"\0")!=0 && flag!=0)			
			{
				strcpy(filename,prefix);
				delay(100);
				ReadBMPHEAD(&head,filename);
				if(sizejudge(&head) == 1)			//判断图片大小，图片大于设定值则返回-2提示图片过大
				{
					return 1;
				}
				else
				{
					return -2;
				}
			}
			else
			{
				return -1;
			}	
		}
		
		case SAVE:
		{
			/*文件名至少5个字符，.bmp占4个长度*/
			/*if(strlen(code)<5)
			{
				return -1;
			}*/
			
			/*输入文件名称大写转换小写*/
			for(i=0;i<strlen(code);i++)
			{
				if(code[i] >= 'A' && code[i] <= 'Z')
				{
					code[i] += 32;
				}
			}
			
			/*输入字符串中不能有space或dot字符，防止输入".jpg"等后缀*/
			for(i=0;i<strlen(code);i++)
			{
				if(code[i] == ' ' || code[i] == '.' )
				{
					return -2;
				}
			}
			
			/*加入保存路径*/
			strcat(prefix,code);
			strcat(prefix,affix);
			/**********************************************************************
			access(address,status)函数,判断存取方式是否有效，有则返回0，否则返回-1
			address:文件路径
			status:4 只判断是否有读权限
				   2 只判断是否有写权限
			       1 判断是否有执行权限
			       0 只判断是否存在
			***********************************************************************/
			if(access(prefix,0) == 0)
			{
				return -3;
			}
			
			else if(strcmp(code,"\0")!=0 && access(prefix,0) == -1 && code!= NULL)		//如果指定文件夹中不存在同名文件
			{
				strcpy(filename,prefix);
				delay(100);
				return 1;
			}

			else 
			{
				return -1;
			}	
		}
	}
}

/*保存图片对话框*/
int savedialog(char *filename,int status, int mode)
{
	
	int key;													//键值
	int recev;													//返回值，receive的缩写
	char code[30] = {'\0'};										//输入字符串
	int letter = 0;												//输入字符的位序
	int cor=0;													//输入字符的坐标
	int flag = 0;												//判断键值输入与否
	MOUSE M;													//鼠标结构体变量

	ui(mode, DIALOG, status);									//对应的对话框与提示语

	while(1)
	{
		MouseXYB(&M);
		MouseStoreBk(M.x, M.y);
		MouseDraw(M);
		delay(20);
		MousePutBk(M.x, M.y);
		shape = 0;
		
		if(M.x>790 && M.x<860 && M.y>580 && M.y<610)			//确定按钮
		{
			if(Mousepress(790,580,860,610) == 0)
			{
				shape=1;
			}
			else if(Mousepress(790,580,860,610) == 1)
			{
				recev=Inputjudge(code,filename,status);
				switch(recev)
				{
					case 1:										//保存成功		
					{
							Close(697,490,938,525,MATCHA);		//清除关闭按钮
							Close(697,525,956,570,MATCHA);		//清除对话框
							Close(785,575,865,615,MATCHA);		//清除确定按钮
							
							printHZ12(730,525,"保存成功！",BLOODRED,3,3,5);
							printHZ16(835,590,"按任意键继续",BLACK,1,1,1);
							getch();
							return 1;
					}
					
					default:									//保存失败，输出对应提示
					{
						cue(recev,SAVE);
					}
					break;	
				}
			}
		}
		
		if(M.x>888 && M.x<935 && M.y>495 && M.y<520)			//退出按钮
		{
			if(Mousepress(888,495,935,520) == 0) 
			{
				shape=1;
			}
			else if(Mousepress(888,495,935,520) == 1)
			{
				Close(665,440,990,665,mode);
				return 0;
			}
		}
		
		if(status == 2)											//输入框 传入的box的类型  1：打开文件 2:保存
		{
			flag=bioskey(1);

			if(flag)											//若监测到键盘有输入值
			{
				key = bioskey(0);
				switch(key)
				{
					case Enter:
					{
						recev=Inputjudge(code,filename,status);
						switch(recev)
						{
							case 1:								//保存成功
							{
								Close(697,490,938,525,MATCHA);	//清除关闭按钮
								Close(697,525,956,570,MATCHA);	//清除对话框
								Close(785,575,865,615,MATCHA);	//清除确定按钮
								
								printHZ12(730,525,"保存成功！",BLOODRED,3,3,5);
								printHZ16(835,590,"按任意键继续",BLACK,1,1,1);
								getch();
								return 1;
							}
							
							default:							//保存失败，输出对应提示
							{
								cue(recev,SAVE);
							}
							break;
						}
					}
					break;
					
					case Backspace: 							//退格
					{
						if(letter>=1)
						{
							code[letter-1] = '\0';
							delay(50);
							cor-=16;
							letter --;
							Close(700+cor, 530, 716+cor, 565, WHITE);
						}
					}
					break;
					
					case ESC:									//退出当前对话框
					{
						Close(665,440,990,665,mode);
						return 0;
					}
					
					default:									//输入字母和数字
					{
						if(letter<=14)
						{
							code[letter] = key;
							code[letter+1] = '\0';
							letter++;
							Put_Asc16_Size(700+cor,533,2, 2, key, BLACK);
							cor+=16;	
							break;
						}
						
						else
						{
							printHZ12(705,475,"输入字符达上限！",BLOODRED,2,2,1);
							getch();
							Close(705,475,890,500,MATCHA);
						}
					}
				}
			}
		}
	}
}

/*读取BMP图像文件头*/
int ReadBMPHEAD(BMPHeader* head,char *address)
{
	int i;
	FILE *fp;
	unsigned char *p,*pNew;
	unsigned char *pBmpBuf;
	BITMAPFILEHEADER fileHead;
	BITMAPINFOHEADER infoHead;
	RGBQUAD palette[256];

	fp=fopen(address,"rb");
	if (fp==0)
	{
		return 0;
	}

	fread(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);
	fread(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);

	fread(palette,sizeof(RGBQUAD),256,fp);

	head->fileHead=fileHead;
	head->infoHead=infoHead;
	for(i=0; i<256; i++)
	{
		head->palette[i].b=palette[i].b;
		head->palette[i].g=palette[i].g;
		head->palette[i].r=palette[i].r;
		head->palette[i].reserved=palette[i].reserved;
	}

	fclose(fp);
	return 1;
}

/*读取BMP图像*/
int ReadPic(unsigned char* p,int size,char *address)
{
	FILE *fp;
	unsigned char *pBmpBuf;
	BITMAPFILEHEADER fileHead;
	BITMAPINFOHEADER infoHead;
	RGBQUAD *palette;
	int height,width,lineByte,biCount,offset;
	fp=fopen(address,"rb");
	if (fp==NULL)
	{
		printf("error");
		return 0;
	}

	// 计算偏移距离 
	offset=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256;
	fseek(fp,offset,0);

	fread(p,size,1,fp);
	
	fclose(fp);
	return 1; 
}

/*保存图片*/
int SAVEPIC(BMPHeader* head,unsigned char *pBmpBuf,char *address)
{
	
	FILE *fp;
	unsigned char *p,*pNew;
	BITMAPFILEHEADER fileHead;
	BITMAPINFOHEADER infoHead;
	RGBQUAD *pColorTable;
	int height,width,lineByte,biCount;

	fp=fopen(address,"wb");

	fileHead=head->fileHead;
	infoHead=head->infoHead;
	pColorTable=head->palette;

	width=infoHead.biWidth;
	height=infoHead.biHeight;
	biCount=infoHead.biBitCount;
	lineByte=(width*biCount/8+3)/4*4;

	fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);
	fwrite(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);
	fwrite(pColorTable,sizeof(RGBQUAD),256,fp);
	fwrite(pBmpBuf,lineByte*height,1,fp);

	fclose(fp);

	return 1;
}

/*将所打开BMP图像写入显存*/
void display(BMPHeader* head,char *pBmpBuf)
{
	int i,j;
	char oldPage=0,newPage=0;
	int height,width,lineByte,biCount;
	BITMAPINFOHEADER infoHead;
	unsigned long pos;
	int x,y;
	short *buffer;

	infoHead=head->infoHead;

	width=infoHead.biWidth;
	height=infoHead.biHeight;
	biCount=infoHead.biBitCount; 
	lineByte=(width*biCount/8+3)/4*4;
	
	x=512-(width>>1);
	y=384-(height>>1);
	
	// 显存的逻辑宽度为1600 
	oldPage=((height-1+y)*1600l+x)>>15; 
    newPage=oldPage;
    Select_Page(oldPage);
    
    for (i=0;i<height;i++)
	{
		for (j=0;j<width;j++)
		{
			pos=(i+y)*(long)1024+(j+x);
			newPage=pos/65536; // 计算页数 
			if(newPage!=oldPage)  // SVGA显示换页
			{
				Select_Page(newPage);
				oldPage=newPage;
			}
			// 写入显存 
			// 容量为65535故要取模 
			pokeb(0xa000,pos%65536,*(pBmpBuf+(height-i-1)*lineByte+j));
		}
	}
}

int sizejudge(BMPHeader* head)
{
	int width,height,biCount,lineByte; 
	long long Size,Max=45000;
	BITMAPINFOHEADER infoHead;
	infoHead=head->infoHead;
	width=infoHead.biWidth;
	height=infoHead.biHeight;
	biCount=infoHead.biBitCount;
	lineByte=(width*biCount/8+3)/4*4;
	Size=(long long)height*lineByte; // 计算缩放后大小 
	Size=(Size+3)/4*4;
	
	if(Size>Max)
	{
		return 0;					//打开失败
	}
	
	else 
	{
		return 1; 					//打开成功
	}
}