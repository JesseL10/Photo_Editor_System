#include "edit.h"
#include "inout.h"
#include "function.h"
#include "head.h"
#include "mmouse.h"
#include "help.h"
#include "HANZI.H"
#include "menu.h"
#include "draw.h" 


int edit(int mode)
{
	int page = 2;
	int key;									//��ֵ
	int COLOR;									//��Ӧģʽ�»�ͼ��ɫ
	int func = 0;  								//��Ӧ����
	int ffunc = 0;								//�ж�ͼƬ�Ƿ��״̬����
	int openjv = 0;								//״̬�������ж�ͼƬ�Ƿ��, open judgement value
	int savejv = 0;								//״̬�������ж��Ƿ񱣴�ɹ���save judgement value
	int flag = 0;								//״̬�������жϱ༭����ǿ���˾��˵�֮һ�Ƿ��
	int flag1;									//�ü��ж�״̬�������ж��Ƿ�����ȷ
	int flag2=0;								//�ü���ʾ���һ��ʹ�øù�����ʾ
	short flag3;								//�˳������жϱ���
	long long size;								//��ǰͼƬ��С
	long long memojg;							//�жϵ�Ӱ�˾�ռ�ÿռ��С
	char *temp;									//ͼƬ���ش�����
	BMPHeader head;								//ͼƬ��Ϣͷ
	int height=0,width=0,biCount,lineByte;		//ͼƬ��Ϣ
	BITMAPINFOHEADER t;							//BMPͷt
	double lx=0.0,ly=0.0;						//���ű���x,y
	int level=0;								//��ǿ�˵�������ָ���ȼ�
	int direction;								//ͼƬ��ת����
	int number = 0;								//�ü����������ĵ������
	
	char openname[50];  						//���ļ�����
	char savename[50];  						//�����ļ�����
	
	POINT a,b;									//�ü�������ѡ�����ص�������Ϣ

	MOUSE M;									//���ṹ��M

	(mode == LIGHT) ? (COLOR = BLACK) : (COLOR = WHITE);//���ݶ�Ӧ����ģʽ���ø�����ɫ
	interface(mode);

	while( page == 2 )
	{
		MouseXYB(&M);
		MouseStoreBk(M.x, M.y);
		MouseDraw(M);
		delay(20);
		MousePutBk(M.x, M.y);
		
		/***************************************
		���ѡ��������֣������ť������Ӧ����
		***************************************/
		if(M.x>764 && M.x<865 && M.y>0 && M.y<27)					//��������
		{
			shape = 1;
			if(Mousepress(764,0,865,27) == 1)
			{
				delay(100);
				COLOR = mode;
				(mode == LIGHT) ? (mode = DARK) : (mode = LIGHT);
				(mode == LIGHT) ? (COLOR = BLACK) : (COLOR = WHITE);
				interface(mode);
				if(openjv == 1)							
				{
					display(&head,temp);
					func=ffunc;
				}
				if(flag !=0)
				{
					ui(mode, flag, 0);
				}
			}
		}	
		
		else if(M.x>990 && M.x<1024 && M.y>0 && M.y<30)				//�رճ���
		{
			shape=1;
			if(Mousepress(984,1,1023,23) == 1)
			{
				func=EXIT;
			}
		}

		else if( kbhit() )											//������ֵ��������Ӧ��Ӧ
		{
			key=bioskey(0);
			switch(key)
			{
				case ESC:											//�˳�����
				{
					func = EXIT;
				}
				break;
				
				case F1:											//�򿪰���
				{
					func = HELP;
				}
				break;
				
				case F2:											//�򿪿�����Ա��Ϣ
				{
					func = DEVINFO;
				}
				break;
			}
		}
		
		else if(M.x>260 && M.x<320 && M.y>0 && M.y<30)				//�ָ�
		{
			shape = 1;	
			if(Mousepress(260,0,320,30) == 1)
			{
				delay(100);
				if(openjv == 1)
				{
					func = RECOVER;
				}
			}
		}
		
		else if(M.x>15 && M.x<85 && M.y>0 && M.y<30)				//����
		{
			shape = 1;
			if(Mousepress(15,0,85,30) == 1)
			{
				func = HELP;
			}
		}
		
		else if(M.x>105 && M.x<235 && M.y>0 && M.y<30)				//������Ա��Ϣ
		{
			shape = 1;
			if(Mousepress(105,0,235,30) == 1)
			{
				func = DEVINFO;
			}
		}

		else if(M.x>20 && M.x<175 && M.y>690 && M.y<735) 			//��ͼƬ
		{
			shape = 1;
			if(Mousepress(20,690,175,735) == 1)
			{
				func = OPEN;
			}
		}
		
		else if(M.x>255 && M.x<305 && M.y>690 && M.y<750)  			//�༭
		{
			shape=1;
			if(Mousepress(225,690,305,750) == 1)
			{
				delay(100);
				if(openjv == 1)
				{
					if(flag != EDIT)								//�����ظ�����˹���ʱ���ˢ��
					{
						Clear(flag,mode);
						ui(mode, EDIT, 0);
					}
					flag = EDIT;
					func = EDIT;
				}
			}
		}
		
		else if(M.x>375&& M.x<440 && M.y>690 && M.y<750)    		//������
		{
			shape = 1;	
			if(Mousepress(375,690,440,750) == 1)
			{
				if(openjv == 1)
				{
					if(flag != MOSIAC)
					{
						Clear(flag,mode);
						ui(mode, MOSIAC, 0);
					}
					func = MOSIAC;
					flag = 0;
					ui(mode, MOSIAC, 0);
					if(ffunc!=0)
					{
						ffunc=0;
					}
				}
			}
		}
		
		else if(M.x>520 && M.x<570 && M.y>690 && M.y<750)			//��ǿ
		{
			shape = 1;	
			if(Mousepress(520,690,570,750) == 1)
			{
				delay(100);
				if(openjv == 1)
				{
					if(flag != ADJUST)
					{
						Clear(flag,mode);
						ui(mode, ADJUST, 0);
					}

					if(func != ADJUST)
					{
						Pretreatment(&head,temp);
					}

					flag = ADJUST;
					func = ADJUST;
					
				}
			}
		}
		
		else if(M.x>650 && M.x<700 && M.y>690 && M.y<750)			//�˾�
		{
			shape = 1;
			if(Mousepress(650,690,700,750) == 1)
			{
				delay(100);
				if(openjv == 1)
				{
					if(flag != FILTER)
					{
						Clear(flag,mode);
						ui(mode, FILTER, 0);
					}

					flag = FILTER;
					func = FILTER;
				}
			}
		}
		
		else if(M.x>780 && M.x<830 && M.y>690 && M.y<750)			//����
		{
			shape = 1;
			if(Mousepress(780,360,830,750) == 1)
			{
				func = SAVE;
			}
		}
		
		else if(M.x>900&& M.x<970 && M.y>690 &&M.y<750)				//�ر�ͼƬ
		{
			shape = 1;
			if(Mousepress(900,690,970,750) == 1)
			{
				if(openjv == 1)
				{
					free(temp);
					Close(0,40,1024,665,mode);
					/*��������״̬����*/
					openjv = 0;
					flag = 0;
					func = 0;
					size = 0;
					memojg = 0;
					flag2=0;
				}
			}			
		}
		
		else
		{
			shape = 0;
		}
		//�Ƴ������ļ�
		if(func != BRIGHT && func !=ADJUST && access(".//picture//buffer//brightness.bmp",0)==0)
		{
			remove(".//picture//buffer//brightness.bmp");
		}
		
		/*****************************************
		����ʵ�ֲ��֣�ͨ��func�Ĵ���ʵ�ֶ�Ӧ����
		*****************************************/
		switch(func)
		{
			case OPEN:  											//��ͼƬ
			{
				if(openjv == 0)//ͼƬδ��״̬��
				{
					if(opendialog(openname, OPEN, mode) == 1)//�򿪳ɹ�
					{
						ReadBMPHEAD(&head,openname);
						t=head.infoHead;
						height=t.biHeight;
						width=t.biWidth;
						biCount=t.biBitCount;
						lineByte=(width*biCount/8+3)/4*4;
						size = sizeof(unsigned char)*height*lineByte;
						memojg=3*size/2;
						temp=(unsigned char*)malloc(sizeof(unsigned char)*height*lineByte);
						ReadPic(temp,lineByte*height,openname);
						delay(20);
						display(&head,temp);
						openjv=1;
						func = 0;
					}
					else
					{
						func=0;
						break;
					}
				}
				else
				{
					func = ffunc;
				}
			}
			break;
	
			case SAVE:  											//����ͼƬ
			{
				if(openjv == 1)
				{	
					if(savedialog(savename, SAVE, mode) == 1);
					{
						savejv = SAVEPIC(&head,temp,savename);
						if(savejv == 1)
						{
							Close(665,440,990,665,mode);
							ui(mode,ffunc,0);
							func = ffunc;
							break;
						}
						
						else 
						{
							func = 0;
							break;
						}
					}
				}
			}
			break;
			
			case EXIT:												//�˳�����
			{
				flag3 = exit_exe();
				//delay(100);
				if(flag3 == -1)
				{
					delay(100);
					page = -1;
					return page;
				}
				else
				{
					delay(100);
					Close(360,295,660,445,mode);
					if(openjv == 1)
					{
						display(&head,temp);
					}
					func = ffunc;
					flag3 = 0;
				}
			}
			break;
			case HELP:												//����
			{
				if(openjv == 1)
				{
					Close(512-(width/2),384-(height/2),512+(width/2),384+(height/2),mode);
				}
				if(flag!=0)
				{
					Clear(flag,mode);
				}
				help(mode);
				Close(0,40,1024,665,mode);
				if(openjv == 1)							
				{
					display(&head,temp);
					func=ffunc;
				}
				else
				{
					func = 0;
				}
				if(flag !=0)
				{
					ui(mode, flag, 0);
				}
			}
			break;
			
			case DEVINFO:											//������Ա��Ϣ
			{

				devinfo(COLOR);
				Close(10,38,1014,650,mode);
				//func=0;
				if(openjv == 1)							
				{
					display(&head,temp);
					func=ffunc;
				}
				else
				{
					func = 0;
				}
				if(flag !=0)
				{
					ui(mode, flag, 0);
				}
			}	
			break;
			
			case EDIT:												//�༭
			{
				ffunc = func;
				if(M.x>935 && M.x<1005 && M.y>70 && M.y<135)				//������ת
				{
					shape=1;
					if(Mousepress(935,70,1005,135) == 1)
					{
						delay(100);
						direction = -1;
						rotation(&head,temp,direction);
						Close(512-(width/2),384-(height/2),512+(width/2),384+(height/2),mode);
						free(temp);

						ReadBMPHEAD(&head,".//picture//buffer//after.bmp");
						t=head.infoHead;
						height=t.biHeight;
						width=t.biWidth;
						biCount=t.biBitCount;
						lineByte=(width*biCount/8+3)/4*4;
						temp=(unsigned char*)malloc(sizeof(unsigned char)*height*lineByte);
						ReadPic(temp,lineByte*height,".//picture//buffer//after.bmp");
						display(&head,temp);
						remove(".//picture//buffer//after.bmp");
					}
					break;
				}
				
				else if(M.x>935 && M.x<1005 && M.y>160 && M.y<230)			//������ת	
				{
					shape=1;
					if(Mousepress(935,160,1005,230) == 1)
					{
						delay(100);
						direction = 1;
						rotation(&head,temp,direction);
						Close(512-(width/2),384-(height/2),512+(width/2),384+(height/2),mode);
						free(temp);

						ReadBMPHEAD(&head,".//picture//buffer//after.bmp");
						t=head.infoHead;
						height=t.biHeight;
						width=t.biWidth;
						biCount=t.biBitCount;
						lineByte=(width*biCount/8+3)/4*4;
						temp=(unsigned char*)malloc(sizeof(unsigned char)*height*lineByte);
						ReadPic(temp,lineByte*height,".//picture//buffer//after.bmp");
						display(&head,temp);
						remove(".//picture//buffer//after.bmp");
					}
					break;
				}
				
				else if(M.x>935 && M.x<1005 && M.y>250 && M.y<320)			//ˮƽ����		
				{
					shape=1;
					if(Mousepress(935,250,1005,320) == 1)
					{
						delay(100);
						direction = 1;
						mirror(&head,temp,direction);
						Close(512-(width/2),384-(height/2),512+(width/2),384+(height/2),mode);
						display(&head,temp);
					}
					break;
				}
				
				else if(M.x>935 && M.x<1005 && M.y>335 && M.y<405)			//��ֱ����		
				{
					shape=1;
					if (Mousepress(935,335,1005,405) == 1)
					{
						delay(100);
						direction = 2;
						mirror(&head,temp,direction);
						Close(512-(width/2),384-(height/2),512+(width/2),384+(height/2),mode);
						display(&head,temp);
					}
					break;
				}
				
				else if(M.x>935 && M.x<1005 && M.y>425 && M.y<485)			//�ü�		
				{
					shape=1;
					if(Mousepress(935,425,1005,485) == 1)
					{
						if(flag2 == 0)
						{
							Close(360,295,660,400,MATCHA);
							Square(360,295,660,400,2,COLOR);
							printHZ16(400,340,"�����ͼƬ����������ü�",BLOODRED,1,1,0);
							printHZ16(401,340,"�����ͼƬ����������ü�",BLOODRED,1,1,0);
							delay(1000);
							Close(360,295,660,400,mode);
							display(&head,temp);
							flag2++;									//��ǰ��ʾ������ʾ
						}
						func = CUT;
					}
					break;
				}
				
				else if(M.x>935 && M.x<1005 && M.y>505 && M.y<570)			// ����			
				{
					shape=1;
					if(Mousepress(935,505,1005,570) == 1)
					{
						Close(360,295,660,400,MATCHA);
						Square(360,295,660,400,2,COLOR);
						printHZ12(420,340,"��ѡ�����ű���",BLACK,2,2,1);
						printHZ12(421,340,"��ѡ�����ű���",BLACK,2,2,1);
						delay(1000);
						Close(360,295,660,400,mode);
						display(&head,temp);

						pzoom(&lx,&ly,COLOR);
						Close(250,635,740,660,mode);
						if(lx != 0 && ly != 0)
						{
							delay(100);
							zoom(&head,temp,lx,ly);
							Close(512-(width/2),384-(height/2),512+(width/2),384+(height/2),mode);
							free(temp);

							ReadBMPHEAD(&head,".//picture//buffer//after.bmp");
							t=head.infoHead;
							height=t.biHeight;
							width=t.biWidth;
							biCount=t.biBitCount;
							lineByte=(width*biCount/8+3)/4*4;
							size = sizeof(unsigned char)*height*lineByte;
							memojg=3*size/2;
							temp=(unsigned char*)malloc(sizeof(unsigned char)*height*lineByte);
							ReadPic(temp,lineByte*height,".//picture//buffer//after.bmp");
							display(&head,temp);
							remove(".//picture//buffer//after.bmp");
							lx=0;ly=0;
						}	
					}
					break;
				}
				
				else if(M.x>935 && M.x<1005 && M.y>585 && M.y<640)			//Ϳѻ��
				{
					shape = 1;
					if(Mousepress(935,585,1005,640) == 1)
					{
						ui(mode, GRAFFITI, 0);
						func = GRAFFITI;
					}
				}
			}
			break;
			
			case ADJUST:											//��ǿ
			{
				ffunc=func;
				if(M.x>0 && M.x<60 && M.y>170 && M.y<250)			//����
				{	
					shape = 1;
					if(Mousepress(0,170,60,250) == 1)  
					{
						if(access(".//picture//buffer//brightness.bmp",0)==-1)//��ǰͼƬ��δ��������л���
						{
							Pretreatment(&head,temp);
						}
						func=BRIGHT;
					}
				}

				else if(M.x>0 && M.x<60 && M.y>315 && M.y<385)		//��
				{
					shape = 1;
					if(Mousepress(0,315,60,385) == 1)
					{
						func=SHARPEN;
					}
				}

				else if(M.x>0 && M.x<60 && M.y>440 && M.y<515)		//ģ��
				{
					shape = 1;
					if(Mousepress(0,440,60,515) == 1)
					{
						func=BLUR;
					}
				}	
			}
			break;

			case RECOVER:											//�ָ�
			{
				//�ͷŵ�ǰͼƬ���棬����ͼƬ��Ϣ
				free(temp);
				Close(512-(width/2),384-(height/2),512+(width/2),384+(height/2),mode);
				width=0,height=0;
				//���¶�ȡ֮ǰ�Ĵ򿪵�ͼƬ
				ReadBMPHEAD(&head,openname);
				t=head.infoHead;
				height=t.biHeight;
				width=t.biWidth;
				biCount=t.biBitCount;
				lineByte=(width*biCount/8+3)/4*4;
				size = sizeof(unsigned char)*height*lineByte;
				memojg=3*size/2;
				temp=(unsigned char*)malloc(sizeof(unsigned char)*height*lineByte);
				ReadPic(temp,lineByte*height,openname);
				delay(20);
				display(&head,temp);
				func = ffunc;
			}
			break;
			
			case MOSIAC:											//������
			{
				pmosiac(&head,temp,mode);
				func = 0;
			}
			break;
			
			case GRAFFITI:											//Ϳѻ��
			{
				pgraffiti(&head,temp,mode);
				func = EDIT;
			}
			break;
			
			case CUT:												//�ü�
			{
				if(M.x>512-width/2 && M.x<512+width/2 && M.y>384-height/2 && M.y<384+height/2 && M.but == 1)
				{
					while(number<2)
					{
						MouseXYB(&M);
						MouseStoreBk(M.x, M.y);
						MouseDraw(M);
						delay(20);
						MousePutBk(M.x, M.y);
						if(M.but == 1 && number == 0)
						{
							a.x = M.x;
							a.y = M.y;
							number++;
						}
						else if(M.but == 1 && number == 1)
						{
							if(M.x == a.x && M.y == a.y)
							{
								continue;
							}
							b.x = M.x;
							b.y = M.y;
							
							flag1=cutJudge(&head,a,b);
							if(flag1==0)
							{
								continue;
							}
							else
							{	
								number++;
							}
						}
					}	
					number=0;
					delay(100);
					cut(&head,temp,a,b);
					Close(512-(width/2),384-(height/2),512+(width/2),384+(height/2),mode);
					free(temp);
					delay(50);
					ReadBMPHEAD(&head,".//picture//buffer//after.bmp");
					t=head.infoHead;
					height=t.biHeight;
					width=t.biWidth;
					biCount=t.biBitCount;
					lineByte=(width*biCount/8+3)/4*4;
					size = sizeof(unsigned char)*height*lineByte;
					memojg=3*size/2;
					temp=(unsigned char*)malloc(sizeof(unsigned char)*height*lineByte);
					ReadPic(temp,lineByte*height,".//picture//buffer//after.bmp");
					display(&head,temp);
					remove(".//picture//buffer//after.bmp");
					func=ffunc;
				}
				
			}
			break;
			
			case BRIGHT:											//����
			{
				//����ȼ�ѡ��˵�������ѡ��ȼ�
				level=menu(mode,BRIGHT);
				if(level != 0)
				{
					free(temp);
					ReadBMPHEAD(&head,".//picture//buffer//brightness.bmp");
					temp=(unsigned char*)malloc(sizeof(unsigned char)*height*lineByte);
					ReadPic(temp,lineByte*height,".//picture//buffer//brightness.bmp");
					brightness(&head,temp,level);
					Close(512-(width/2),384-(height/2),512+(width/2),384+(height/2),mode);
					free(temp);
					ReadBMPHEAD(&head,".//picture//buffer//after.bmp");
					t=head.infoHead;
					height=t.biHeight;
					width=t.biWidth;
					biCount=t.biBitCount;
					lineByte=(width*biCount/8+3)/4*4;
					temp=(unsigned char*)malloc(sizeof(unsigned char)*height*lineByte);
					ReadPic(temp,lineByte*height,".//picture//buffer//after.bmp");
					display(&head,temp);
					remove(".//picture//buffer//after.bmp");
					level=0;
					Close(70,100,140,300,mode);//�رմ˲˵�
					func=ADJUST;
				}
				
			}
			break;
			
			case SHARPEN:											//��
			{
				level=menu(mode,SHARPEN);
				if(level != 0)
				{
					sharpen(&head,temp,level);
					Close(512-(width/2),384-(height/2),512+(width/2),384+(height/2),mode);
					free(temp);
					ReadBMPHEAD(&head,".//picture//buffer//after.bmp");
					t=head.infoHead;
					height=t.biHeight;
					width=t.biWidth;
					biCount=t.biBitCount;
					lineByte=(width*biCount/8+3)/4*4;
					temp=(unsigned char*)malloc(sizeof(unsigned char)*height*lineByte);
					ReadPic(temp,lineByte*height,".//picture//buffer//after.bmp");
					display(&head,temp);
					remove(".//picture//buffer//after.bmp");
					level = 0;
					Close(70,240,140,445,mode);
					func = ADJUST;
				}
			}
			break;
			
			case BLUR:												//ģ��
			{
				level=menu(mode,BLUR);
				if(level != 0)
				{
					blur(&head,temp,level);
					Close(512-(width/2),384-(height/2),512+(width/2),384+(height/2),mode);
					free(temp);
					ReadBMPHEAD(&head,".//picture//buffer//after.bmp");
					t=head.infoHead;
					height=t.biHeight;
					width=t.biWidth;
					biCount=t.biBitCount;
					lineByte=(width*biCount/8+3)/4*4;
					temp=(unsigned char*)malloc(sizeof(unsigned char)*height*lineByte);
					ReadPic(temp,lineByte*height,".//picture//buffer//after.bmp");
					display(&head,temp);
					remove(".//picture//buffer//after.bmp");
					level = 0;
					Close(70,365,140,565,mode);
					func = ADJUST;
				}
			}
			break;
			
			case FILTER:											//�˾�
			{
				ffunc=func;
				if(M.x>935 && M.x<1015 && M.y>173 && M.y<223)		//����
				{
					shape = 1;
					//��ʾ��Ӧѡ���
					Square(935, 173, 1015, 223, 2, COLOR);
					if(Mousepress(930,170,1010,220) == 1)
					{
						delay(100);
						black(&head,temp);
						Close(512-(width/2),384-(height/2),512+(width/2),384+(height/2),mode);
						display(&head,temp);
					}
				}
				
				else if(M.x>935 && M.x<1015 && M.y>253 && M.y<303)	//�ͻ�
				{
					shape = 1;
					Square(935, 253, 1015, 303, 2, COLOR);
					if(Mousepress(935,253,1015,303) == 1)
					{
						oilpaint(&head,temp);
						Close(512-(width/2),384-(height/2),512+(width/2),384+(height/2),mode);
						display(&head,temp);
					}	
				}
				else if(M.x>935 && M.x<1015 && M.y>333 && M.y<383)	//����
				{
					shape = 1;
					Square(935, 333, 1015, 383, 2, COLOR);
					if(Mousepress(935,333,1015,383) == 1)
					{
						rollfilm(&head,temp);
						Close(512-(width/2),384-(height/2),512+(width/2),384+(height/2),mode);
						display(&head,temp);
					}	
				}
				else if(M.x>935 && M.x<1015 && M.y>414 && M.y<464)	//����
				{
					shape = 1;
					Square(935, 414, 1015, 464, 2, COLOR);
					if(Mousepress(935,414,1015,464) == 1)
					{
						embossment(&head,temp);
						Close(512-(width/2),384-(height/2),512+(width/2),384+(height/2),mode);
						display(&head,temp);
					}	
				}
				else if(M.x>935 && M.x<1015 && M.y>495 && M.y<545)	//��Ӱ
				{
					shape = 1;
					Square(935, 495, 1015, 545, 2, COLOR);
					if(Mousepress(935,495,1015,545) == 1)
					{
						if(memojg>42000)							//ͼƬ�ߴ�������޷�ʹ�øù���
						{
							Close(360,295,660,400,MATCHA);
							Square(360,295,660,400,2,COLOR);
							printHZ16(400,340,"ͼƬ�ߴ�����޷�ʹ�ø��˾�",BLOODRED,1,1,0);
							printHZ16(401,340,"ͼƬ�ߴ�����޷�ʹ�ø��˾�",BLOODRED,1,1,0);
							delay(1200);
							Close(360,295,660,400,mode);
							display(&head,temp);
							break;	
						}
						else
						{						
							reflect(&head,temp);
							Close(512-(width/2),384-(height/2),512+(width/2),384+(height/2),mode);
							free(temp);

							ReadBMPHEAD(&head,".//picture//buffer//after.bmp");
							t=head.infoHead;
							height=t.biHeight;
							width=t.biWidth;
							biCount=t.biBitCount;
							lineByte=(width*biCount/8+3)/4*4;
							//�����´�ʹ�øù�������ռ��С
							size = sizeof(unsigned char)*height*lineByte;
							memojg=3*size/2;
							
							temp=(unsigned char*)malloc(sizeof(unsigned char)*height*lineByte);
							ReadPic(temp,lineByte*height,".//picture//buffer//after.bmp");
							display(&head,temp);
							remove(".//picture//buffer//after.bmp");
						}
					}	
				}
				else
				{
					//ɾ����Ӧ��ѡ���
					Square(935, 173, 1015, 223, 2, mode);
					Square(935, 253, 1015, 303, 2, mode);
					Square(935, 333, 1015, 383, 2, mode);
					Square(935, 414, 1015, 464, 2, mode);
					Square(935, 495, 1015, 545, 2, mode);
				}
			}
		}

	}
}

void interface(int mode)
{
	switch(mode)
	{
		case LIGHT:
		{
			Putbmp256(0,0,"picture\\bk.bmp");
			Line(0,667,1024,667,BLACK);
			Line(0,668,1024,668,BLACK);
		}
		break;
		
		case DARK:
		{
			Putbmp256(0,0,"picture\\bkdark.bmp");
			Line(0,667,1024,667,WHITE);
			Line(0,668,1024,668,WHITE);			
		}
		break;
	}
}

int exit_exe(void)
{
	int page;
	int key;
	MOUSE M;
	shape = 0;
	
	Putbmp256(360,295,"picture\\exit.bmp");
	while(1)
	{
		MouseXYB(&M);
		MouseStoreBk(M.x, M.y);
		MouseDraw(M);
		delay(20);
		MousePutBk(M.x, M.y);
		
		if(kbhit())
		{
			key=bioskey(0);
			if(key == Enter)
			{
				return -1;
			}
			else if(key == ESC)
			{
				return 1;
			}
		}
		else if(M.x>380 && M.x<500 && M.y>400 && M.y<430)
		{
			shape = 1;
			if(Mousepress(380,400,500,430) == 1)
			{
				return -1;
			}
		}
		else if(M.x>515 && M.x<640 && M.y>400 && M.y<430)
		{
			shape = 1;
			if(Mousepress(515,400,640,430) == 1)
			{
				return 1;
			}
		}
		
		else 
		{
			shape = 0;
		}
	}
}
