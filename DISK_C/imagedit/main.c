#include "head.h"
#include "mmouse.h"
#include "SVGAmode.h"
#include "draw.h"
#include "enter.h"
#include "edit.h"
#include "inout.h"
#include "HANZI.H"
#include "function.h"
#include "menu.h"

void main()
{
	
	MOUSE M;									//�������ṹ�� M
	int page = 0;								//��ӭ����
	int mode;									//��ʼģʽ
	SetSVGA256();    	 						//0x105ģʽ��256ɫ
	MouseInit();								//����ʼ��
	MouseRange(0,0,1024,768);

	while(1)
	{	
		switch(page)
		{
			case 0:								//��ӭ����
			{
				page = enter();						
			}
			break;
			
			case 1:								//ģʽѡ�����
			{
				page = Mode(&mode);				
			}
			break;
			
			case 2:								//�༭����
			{
				page = edit(mode);				
			}
			break;
			
			default:							//�˳�����
			{
				delay(50);						//��ֹ�������
				exit(0);
			}
			break;
		}
	}
}