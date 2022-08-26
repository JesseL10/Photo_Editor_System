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

/*��ͼƬ�Ի���*/
int opendialog(char *filename, int status, int mode)
{
	int key;								//��ֵ
	int recev;								//����ֵ��receive����д
	char code[50] ;							//�����ַ���
	int letter = 0;							//�����ַ���λ��
	int cor=0;								//�����ַ�������
	int flag = 0;							//�жϼ�ֵ�������
	
	MOUSE M;								//���ṹ�����

	ui(mode, DIALOG, status);				//������Ӧ�ĶԻ���

	while(1)
	{
		MouseXYB(&M);
		MouseStoreBk(M.x, M.y);
		MouseDraw(M);
		delay(20);
		MousePutBk(M.x, M.y);
		shape = 0;
		
		if(M.x>125 && M.x<200 && M.y>580 && M.y<610)			//ȷ����ť
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
					case 1:										//�򿪳ɹ�
					{
						Close(0,440,325,665,mode);
						delay(1000);
						return 1;
					}
					
					default:
					{											//��ʧ�ܣ������Ӧ��ʾ
						cue(recev,OPEN);
					}
					break;
				}
			}
		}

		if(M.x>223 && M.x<273 && M.y>495 && M.y<520)			//�˳���ť
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
		
		if(status == 1)											//����� �����box������  1�����ļ� 2:����
		{
			flag=bioskey(1);

			if(flag)											//����⵽����������ֵ
			{
				key = bioskey(0);
				switch(key)
				{
					case Enter:
					{
						recev=Inputjudge(code,filename,status);
						switch(recev)
						{
							case 1:								//�򿪳ɹ�
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
					
					case Backspace: 							//�˸�
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
					
					case ESC:									//�˳���ǰ�Ի���
					{
						Close(0,440,325,665,mode);
						return 0;
					}
					
					default:									//������ĸ������
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
							printHZ12(40,475,"�����ַ������ޣ�",BLOODRED,2,2,1);
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

/*���뱣����ʾ�recevΪ�����жϷ���ֵ��statusΪ״̬���򿪻򱣴棩*/
void cue(int recev, int status)
{
	switch(status)
	{
		case OPEN:
		{
			switch(recev)
			{
				case -1:									//��ʧ��
				{
					printHZ12(40,475,"���ļ�ʧ�ܣ�",BLOODRED,2,2,1);
					getch();
					Close(40,475,200,500,MATCHA);
					return;
				}
				
				case -2:
				{
					printHZ12(40,475,"��ͼƬ����",BLOODRED,2,2,1);
					getch();
					Close(40,475,200,500,MATCHA);	
					return;
				}
				
				case -3:
				{
					printHZ12(40,475,"ͼƬ��ʽ����",BLOODRED,2,2,1);
					getch();
					Close(40,475,200,500,MATCHA);	
					return;	
				}
				
				case -4:
				{
					printHZ12(40,475,"ͼƬ�����ڣ�",BLOODRED,2,2,1);
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
				case -1:									//����ʧ��
				{
					printHZ12(705,475,"ͼƬ����ʧ�ܣ�",BLOODRED,2,2,1);
					getch();
					Close(705,475,865,500,MATCHA);
					return;
				}
				
				case -2:
				{
					printHZ12(705,475,"���ڷǷ��ַ���",BLOODRED,2,2,1);
					getch();
					Close(705,475,865,500,MATCHA);
					return;					
				}
				
				case -3:
				{
					printHZ12(705,475,"�ļ����Ѵ��ڣ�",BLOODRED,2,2,1);
					getch();
					Close(705,475,875,500,MATCHA);
					return;	
				}
			}
		}
		break;
	}
}

/*���������������Ƿ��пո�*/
int compare(char *code)
{
	int i;
	if(strlen(code) == 0)
	{
		return 0;
	}
	
	for(i=0;i<strlen(code);i++)							//�����ַ����������Ƿ��зǷ��ַ�
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

/*�ж������ַ���*/
int Inputjudge(char*code, char*filename, int status)	//status��OPENΪ��ͼƬ��SAVEΪ����ͼƬ
{		
	int i;												//ѭ������
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
			/*�жϺ�׺����bmp��ʽ����ʧ��*/
			for(i = strlen(code)-1;i >= strlen(code)-4;i--)
			{
				if(code[i] != affix[4-strlen(code)+i])
				{
					return -3;
				}
			}
			strcat(prefix,code);
			//�ж�ͼƬ�Ƿ���ڣ��������򷵻�-4��ʾ��Ӧ��ʾ	
			if(access(prefix, 0)==-1)
			{
				return -4;												
			}
			
			//���ָ���ļ��и��ļ������ҿɶ�
			else if(access(prefix, 4)==0 && code!=NULL && strcmp(code,"\0")!=0 && flag!=0)			
			{
				strcpy(filename,prefix);
				delay(100);
				ReadBMPHEAD(&head,filename);
				if(sizejudge(&head) == 1)			//�ж�ͼƬ��С��ͼƬ�����趨ֵ�򷵻�-2��ʾͼƬ����
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
			/*�ļ�������5���ַ���.bmpռ4������*/
			/*if(strlen(code)<5)
			{
				return -1;
			}*/
			
			/*�����ļ����ƴ�дת��Сд*/
			for(i=0;i<strlen(code);i++)
			{
				if(code[i] >= 'A' && code[i] <= 'Z')
				{
					code[i] += 32;
				}
			}
			
			/*�����ַ����в�����space��dot�ַ�����ֹ����".jpg"�Ⱥ�׺*/
			for(i=0;i<strlen(code);i++)
			{
				if(code[i] == ' ' || code[i] == '.' )
				{
					return -2;
				}
			}
			
			/*���뱣��·��*/
			strcat(prefix,code);
			strcat(prefix,affix);
			/**********************************************************************
			access(address,status)����,�жϴ�ȡ��ʽ�Ƿ���Ч�����򷵻�0�����򷵻�-1
			address:�ļ�·��
			status:4 ֻ�ж��Ƿ��ж�Ȩ��
				   2 ֻ�ж��Ƿ���дȨ��
			       1 �ж��Ƿ���ִ��Ȩ��
			       0 ֻ�ж��Ƿ����
			***********************************************************************/
			if(access(prefix,0) == 0)
			{
				return -3;
			}
			
			else if(strcmp(code,"\0")!=0 && access(prefix,0) == -1 && code!= NULL)		//���ָ���ļ����в�����ͬ���ļ�
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

/*����ͼƬ�Ի���*/
int savedialog(char *filename,int status, int mode)
{
	
	int key;													//��ֵ
	int recev;													//����ֵ��receive����д
	char code[30] = {'\0'};										//�����ַ���
	int letter = 0;												//�����ַ���λ��
	int cor=0;													//�����ַ�������
	int flag = 0;												//�жϼ�ֵ�������
	MOUSE M;													//���ṹ�����

	ui(mode, DIALOG, status);									//��Ӧ�ĶԻ�������ʾ��

	while(1)
	{
		MouseXYB(&M);
		MouseStoreBk(M.x, M.y);
		MouseDraw(M);
		delay(20);
		MousePutBk(M.x, M.y);
		shape = 0;
		
		if(M.x>790 && M.x<860 && M.y>580 && M.y<610)			//ȷ����ť
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
					case 1:										//����ɹ�		
					{
							Close(697,490,938,525,MATCHA);		//����رհ�ť
							Close(697,525,956,570,MATCHA);		//����Ի���
							Close(785,575,865,615,MATCHA);		//���ȷ����ť
							
							printHZ12(730,525,"����ɹ���",BLOODRED,3,3,5);
							printHZ16(835,590,"�����������",BLACK,1,1,1);
							getch();
							return 1;
					}
					
					default:									//����ʧ�ܣ������Ӧ��ʾ
					{
						cue(recev,SAVE);
					}
					break;	
				}
			}
		}
		
		if(M.x>888 && M.x<935 && M.y>495 && M.y<520)			//�˳���ť
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
		
		if(status == 2)											//����� �����box������  1�����ļ� 2:����
		{
			flag=bioskey(1);

			if(flag)											//����⵽����������ֵ
			{
				key = bioskey(0);
				switch(key)
				{
					case Enter:
					{
						recev=Inputjudge(code,filename,status);
						switch(recev)
						{
							case 1:								//����ɹ�
							{
								Close(697,490,938,525,MATCHA);	//����رհ�ť
								Close(697,525,956,570,MATCHA);	//����Ի���
								Close(785,575,865,615,MATCHA);	//���ȷ����ť
								
								printHZ12(730,525,"����ɹ���",BLOODRED,3,3,5);
								printHZ16(835,590,"�����������",BLACK,1,1,1);
								getch();
								return 1;
							}
							
							default:							//����ʧ�ܣ������Ӧ��ʾ
							{
								cue(recev,SAVE);
							}
							break;
						}
					}
					break;
					
					case Backspace: 							//�˸�
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
					
					case ESC:									//�˳���ǰ�Ի���
					{
						Close(665,440,990,665,mode);
						return 0;
					}
					
					default:									//������ĸ������
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
							printHZ12(705,475,"�����ַ������ޣ�",BLOODRED,2,2,1);
							getch();
							Close(705,475,890,500,MATCHA);
						}
					}
				}
			}
		}
	}
}

/*��ȡBMPͼ���ļ�ͷ*/
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

/*��ȡBMPͼ��*/
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

	// ����ƫ�ƾ��� 
	offset=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256;
	fseek(fp,offset,0);

	fread(p,size,1,fp);
	
	fclose(fp);
	return 1; 
}

/*����ͼƬ*/
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

/*������BMPͼ��д���Դ�*/
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
	
	// �Դ���߼����Ϊ1600 
	oldPage=((height-1+y)*1600l+x)>>15; 
    newPage=oldPage;
    Select_Page(oldPage);
    
    for (i=0;i<height;i++)
	{
		for (j=0;j<width;j++)
		{
			pos=(i+y)*(long)1024+(j+x);
			newPage=pos/65536; // ����ҳ�� 
			if(newPage!=oldPage)  // SVGA��ʾ��ҳ
			{
				Select_Page(newPage);
				oldPage=newPage;
			}
			// д���Դ� 
			// ����Ϊ65535��Ҫȡģ 
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
	Size=(long long)height*lineByte; // �������ź��С 
	Size=(Size+3)/4*4;
	
	if(Size>Max)
	{
		return 0;					//��ʧ��
	}
	
	else 
	{
		return 1; 					//�򿪳ɹ�
	}
}