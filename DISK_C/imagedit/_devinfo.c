#include "head.h"
#include "HANZI.H"
#include "draw.h"
#include "mmouse.h"
#include "menu.h"

void devinfo(int color)
{
	int key;		//��ֵ
	MOUSE M;		//���ṹ��
	shape = 0;
	
	Square(10,38,1014,650, 3, color);
	Close(13,41,1011,647,MATCHA);

	printHZ16(416,60,"������Ա��Ϣ",BLACK,2,2,0);
	printHZ16(417,60,"������Ա��Ϣ",BLACK,2,2,0);
	printHZ12(120,130,"������Ա�����пƼ���ѧ�˹��������Զ���ѧԺ",BLACK,2,2,0);
	printHZ12(240,165,"�Զ�����",BLACK,2,2,0);
	put_asc(336,160,"1910",BLACK, 2, 2);
	printHZ12(405,165,"��",BLACK,2,2,0);
	printHZ12(442,165,"����",BLACK,2,2,0);
	printHZ12(502,165,"���Ҷ�",BLACK,2,2,0);

	printHZ12(120,230,"ָ����ʦ���ܴ��ܡ��ζ��¡���ա��߳��Ρ����ҡ��ܿ�����",BLACK,2,2,0);
	printHZ12(240,265,"ɣũ������ɡ�������",BLACK,2,2,0);

	printHZ12(120,320,"���������",BLACK,2,2,0);
	printHZ12(168,365,"�����Ϊ",BLACK,2,2,0);
	put_asc(265,362,"C",BLACK, 2, 2);
	printHZ12(285,365,"����ר�ã���ֹ�����κ���ҵ��;��",BLACK,2,2,0);

	printHZ12(168,410,"��������û�����ο��������ͼ���㼰",BLACK,2,2,0);
	put_asc(600,406,"VSCO",BLACK, 2, 2);
	printHZ12(666,410,"��ͼ��༭���",BLACK,2,2,0);

	printHZ12(168,455,"�ڴˣ���",BLACK,2,2,0);
	put_asc(264,452,"C",BLACK, 2, 2);
	printHZ12(279,455,"���Կγ���Ƶ�������ʦ�����̣��Լ��ڳ����д�����и���",BLACK,2,2,0);
	printHZ12(120,490,"���ǰ�������е�ѧ��ѧ���ͬѧ��л��������кܶ಻�����Ľ��ĵط���",BLACK,2,2,0);
	printHZ12(120,525,"���ڿ�����ѧ����һ�У��ؽ����պ������ڱ����ƺ���������ĵ�·�ϲ���",BLACK,2,2,0);
	printHZ12(120,560,"��Զ��Ӱ�죡",BLACK,2,2,0);

	put_asc(300,630,"School", BLUE, 1, 1);
	put_asc(356,630,"of", BLUE, 1, 1);
	put_asc(380,630,"Artificial", BLUE, 1, 1);
	put_asc(468,630,"Intelligence", BLUE, 1, 1);
	put_asc(572,630,"and", BLUE, 1, 1);
	put_asc(604,630,"Automation,", BLUE, 1, 1);
	put_asc(700,630,"HUST", BLUE, 1, 1);

	while(1)
	{
		MouseXYB(&M);
		MouseStoreBk(M.x, M.y);
		MouseDraw(M);
		delay(20);
		MousePutBk(M.x, M.y);
		
		if(M.x>487 && M.x<537 && M.y>590 && M.y<620)
		{
			shape = 1;
			Close(487,590,537,620,BLUE);
			printHZ16(496,598,"����",WHITE,1,1,0);
			printHZ16(497,598,"����",WHITE,1,1,0);
			if(Mousepress(487,590,537,620) == 1)
			{
				return;
			}
		}
		
		else if( kbhit() )		//ESC�˳����ر༭����
		{
			key=bioskey(0);
			if(key == ESC)
			{
				return;
			}
		}	

		else
		{
			shape = 0;
			Close(487,590,537,620,GRAY);
			printHZ16(496,598,"����",BLACK,1,1,0);
			printHZ16(497,598,"����",BLACK,1,1,0);
		}
	}
}

void help(int mode)
{
	int key;
	MOUSE M;
	int color;
	int flag;
	shape = 0;
	(mode == LIGHT) ? (color = BLACK) : (color = WHITE);
	printHZ16(272,50,"����·��˵��鿴������ʹ�÷���",color,2,2,1);
	printHZ16(272,51,"����·��˵��鿴������ʹ�÷���",color,2,2,1);
	printHZ16(273,50,"����·��˵��鿴������ʹ�÷���",color,2,2,1);
	printHZ16(273,51,"����·��˵��鿴������ʹ�÷���",color,2,2,1);
	put_asc(425, 90,"(Esc", color ,1, 1);
	printHZ16(460,90,"������������)",color,1,1,1);

	while(1)
	{
		MouseXYB(&M);
		MouseStoreBk(M.x, M.y);
		MouseDraw(M);
		delay(20);
		MousePutBk(M.x, M.y);
		
		if( kbhit() )				//ESC�˳����ر༭����
		{
			key=bioskey(0);
			if(key == ESC)
			{
				return ;
			}
		}
		
		else if(M.x>20 && M.x<175 && M.y>690 && M.y<735)//��ͼƬ
		{
			shape=1;
			if(Mousepress(20,690,175,735) == 1)
			{
				Close(250,210,850,490,mode);
				Clear(flag,mode);
				flag=OPEN;
				ui(mode, DIALOG, OPEN);
				printHZ16(300,250,"�ڶԻ��������뽫�༭ͼƬ������,��",color,1,1,1);
				put_asc(595, 250,"\"flo.bmp\"", color ,1, 1);
				
				printHZ16(300,300,"�����ȷ�ϡ���ť���¡��س��������ɴ�ͼƬ��",color,1,1,1);
				
				printHZ16(300,350,"����رհ�ť����",color,1,1,1);
				put_asc(455, 350,"\"Esc\"", color ,1, 1);
				printHZ16(500,350,"���ɹرնԻ���",color,1,1,1);
				
				printHZ16(299,400,"ע",color,1,1,1);
				printHZ16(300,400,"ע����ͼƬǰ���Ȳ鿴ʹ�ð������л���ϲ����ģʽ",color,1,1,1);
				printHZ16(335,425,"��ͼƬ�ӹ�����Ĺ��ܶ����ڳɹ���ͼƬ����ܽ��в���Ŷ~",color,1,1,1);
			}
		}
		
		else if(M.x>255 && M.x<305 && M.y>690 && M.y<750) 			//�༭
		{
			shape=1;
			if(Mousepress(225,690,305,750) == 1)
			{
				Close(250,210,850,490,mode);
				if(flag != 0)
				{
					Clear(flag,mode);
				}

				ui(mode, EDIT, 0);
				flag = EDIT;
				printHZ16(269,220,"��ת",color,1,1,1);
				printHZ16(270,220,"��ת������������ʮ�ȡ������Ҿ�ʮ�ȡ���ͼƬ�����Ӧ������ת",color,1,1,1);
				printHZ16(269,270,"����",color,1,1,1);
				printHZ16(270,270,"���񣺵����ˮƽ���򡰴�ֱ����ͼƬ�������Ӧ������ת",color,1,1,1);
				printHZ16(269,320,"�ü�",color,1,1,1);
				printHZ16(270,320,"�ü���������ü�����ͨ�������ͼƬ�����е�λ�ã����ɲü��ɹ���",color,1,1,1);
				printHZ16(269,370,"����",color,1,1,1);
				printHZ16(270,370,"���ţ���������š���ѡ�����ű�����ͼƬ����������ţ�",color,1,1,1);
				printHZ16(253,420,"Ϳѻ��",color,1,1,1);
				printHZ16(254,420,"Ϳѻ�ʣ������Ϳѻ�ʡ��󣬳��ֻ�����ɫ�̣�ѡ��ϲ������ɫ�󣬼���ͨ��",color,1,1,1);
				printHZ16(320,445,"�����ͼƬ�����ڿ�ʼ��Ĵ�����������ɺ󣬵������ɡ�����",color,1,1,1);
				printHZ16(320,470,"���س��������������ɽ��������༭����",color,1,1,1);
			}
		}	
		
		else if(M.x>375&& M.x<440 && M.y>690 && M.y<750)    		//������
		{
			shape=1;
			if(Mousepress(375,690,440,750) == 1)
			{
				Close(250,210,850,490,mode);
				if(flag != 0)
				{
					Clear(flag,mode);
				}
				
				ui(mode, MOSIAC, 0);
				Close(525,633,575,659,GRAY);
				printHZ16(534,638,"���",BLACK,1,1,0);
				printHZ16(535,638,"���",BLACK,1,1,0);
				
				flag = MOSIAC;
				
				printHZ16(300,250,"ѡ�������˵ķ�Χ��С������ͨ�������ͼƬ����ʼ������",color,1,1,1);
				printHZ16(300,275,"������ɺ󣬵������ɡ��򰴡��س��������������ɽ��������༭����",color,1,1,1);
				printHZ16(299,325,"С��ʿ",color,1,1,1);
				printHZ16(300,325,"С��ʿ��ͼƬ����������ȫ���룬�����Χѡ��˵��е�������ͼ�꼴�ɣ�",color,1,1,1);
				printHZ16(300,350,"�����ֿ�ݣ�",color,1,1,1);
			}
		}
		
		else if(M.x>520 && M.x<570 && M.y>690 && M.y<750)			//��ǿ	
		{
			shape=1;
			if(Mousepress(520,690,570,750) == 1)
			{
				Close(250,210,850,490,mode);
				delay(100);
				if(flag != 0)
				{
					Clear(flag,mode);
				}

				ui(mode, ADJUST, 0);
				flag = ADJUST;
				printHZ16(279,250,"����",color,1,1,1);
				printHZ16(280,250,"���ȣ���������ȡ���ѡ������Ҫ���ع�̶ȣ����ɸ���ͼƬ���ȣ�",color,1,1,1);
				printHZ16(279,300,"��",color,1,1,1);
				printHZ16(280,300,"�񻯣�������񻯡���ѡ������Ҫ���񻯳̶ȣ����ɶ���Ƭ�����񻯣�",color,1,1,1);
				printHZ16(279,350,"ģ��",color,1,1,1);
				printHZ16(280,350,"ģ���������ģ������ѡ������Ҫ��ģ���̶ȣ���Ƭ���ɳ��ֳ����ʵĸо���",color,1,1,1);
			}
		}
		
		else if(M.x>650 && M.x<700 && M.y>690 && M.y<750)			//�˾�	
		{
			shape=1;
			if(Mousepress(650,690,700,750) == 1)
			{
				Close(250,210,850,490,mode);
				delay(100);
				if(flag != 0)
				{
					Clear(flag,mode);
				}

				ui(mode, FILTER, 0);
				flag = FILTER;
				printHZ16(300,250,"���˾��˵����ḻ�ֺÿ����˾����ܹ���ѡ��",color,1,1,1);
				printHZ16(325,300,"�������������ͻ���������ɫ���������񡱡�����Ӱ��",color,1,1,1);
				printHZ16(374,350,"ע",color,1,1,1);
				printHZ16(375,350,"ע���ߴ�̫�����Ƭ�޷�ʹ�õ�Ӱ����Ŷ~",color,1,1,1);
			}
		}	
		
		else if(M.x>780 && M.x<830 && M.y>690 && M.y<750)			//����
		{
			shape=1;
			if(Mousepress(780,360,830,750) == 1)
			{
				Close(250,210,850,490,mode);
				Clear(flag,mode);
				flag=SAVE;
				ui(mode, DIALOG, SAVE);
				printHZ16(300,250,"�༭��ɺ��ڶԻ����и�ͼƬ����һ���Լ�ϲ�������ְɣ�",color,1,1,1);
				
				printHZ16(300,300,"�����ȷ�ϡ���ť���¡��س��������ɱ��棡",color,1,1,1);
				
				printHZ16(300,350,"����رհ�ť����",color,1,1,1);
				put_asc(455, 350,"\"Esc\"", color ,1, 1);
				printHZ16(500,350,"���ɹرնԻ���",color,1,1,1);
				printHZ16(299,400,"ע",color,1,1,1);
				printHZ16(300,400,"ע��ͼƬ�����Ʋ����С��ո񡱻򡰵㡱�ַ�Ŷ~",color,1,1,1);
			}
		}
		
		else if(M.x>900&& M.x<970 && M.y>690 &&M.y<750)				//�ر�ͼƬ
		{
			shape=1;
			if(Mousepress(900,690,970,750) == 1)
			{
				Close(250,210,850,490,mode);
				Clear(flag,mode);
				printHZ16(325,250,"������ɣ�������Ʒ�������������",color,1,1,1);
				printHZ16(350,300,"����ر�ͼƬ,�رյ�ǰͼƬ�󣬼��ɴ��µ�ͼƬ",color,1,1,1);
				printHZ16(375,350,"���ڵ�ʲô���Ͽ쿪ʼ��Ĵ���֮�ðɣ�",color,1,1,1);
			}
		}
		else
		{
			shape=0;
		}
	}
}
