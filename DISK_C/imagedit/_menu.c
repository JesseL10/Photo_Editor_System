#include "head.h"
#include "menu.h"
#include "mmouse.h"
#include "SVGAmode.h"
#include "draw.h"
#include "HANZI.H"


int menu(int mode, int status)
{
	int level;											//强度等级
	int COLOR;											//对应模式下的颜色
	MOUSE M;											//鼠标结构体变量M
	(mode == LIGHT)?(COLOR = BLACK):(COLOR = WHITE);
	shape=0;
	
	switch(status)
	{
		case BRIGHT:									//亮度等级菜单
		{
			draw_degree(70,198,mode);
			put_asc(110,185,"0%",COLOR,1,2);
			put_asc(106,95,"-50%",COLOR,1,2);								
			put_asc(106,140,"-25%",COLOR,1,2);					
			put_asc(108,230,"25%",COLOR,1,2);					
			put_asc(108,270,"50%",COLOR,1,2);
		}
		break;
		
		case SHARPEN:									//锐化等级菜单
		{
			draw_degree(70,345,mode);
			put_asc(108,242,"20%",COLOR,1,2);					
			put_asc(108,287,"40%",COLOR,1,2);
			put_asc(108,332,"60%",COLOR,1,2);					
			put_asc(108,377,"80%",COLOR,1,2);					
			put_asc(106,417,"100%",COLOR,1,2);	
		}
		break;
			
		case BLUR:										//模糊等级菜单
		{
			draw_degree(70,464,mode);				
			put_asc(108,361,"20%",COLOR,1,2);				
			put_asc(108,406,"40%",COLOR,1,2);
			put_asc(108,451,"60%",COLOR,1,2);
			put_asc(108,496,"80%",COLOR,1,2);					
			put_asc(106,536,"100%",COLOR,1,2);
			
		}
		break;
	}

	while(1)											//鼠标选择部分
	{
		MouseXYB(&M);
		MouseStoreBk(M.x, M.y);
		MouseDraw(M);
		delay(20);
		MousePutBk(M.x, M.y);

		switch(status)
		{
			case BRIGHT:
			{
				if(M.x>105 && M.x<136 && M.y>98 && M.y<118)
				{
					shape=1;
					if(Mousepress(105,97,136,118) == 1)
					{
						level=1;
						return level;
					}
				}

				else if(M.x>105 && M.x<136 && M.y>142 && M.y<162)
				{
					shape=1;
					if(Mousepress(105,142,136,162) == 1)
					{
						level=2;
						return level;
					}
				}

				else if(M.x>105 && M.x<136 && M.y>188 && M.y<208)
				{
					shape=1;
					if(Mousepress(105,188,136,208) == 1)
					{
						level=3;
						return level;
					}
				}

				else if(M.x>105 && M.x<136 && M.y>234 && M.y<254)
				{
					shape = 1;
					if(Mousepress(105,234,136,254) == 1)
					{
						level=4;
						return level;
					}
				}

				else if(M.x>105 && M.x<136 && M.y>273 && M.y<293)
				{
					shape = 1;
					if(Mousepress(105,273,136,293) == 1)
					{
						level=5;
						return level;
					}
				}
				else
				{
					shape=0;
				}
			}
			break;
			
			case SHARPEN:
			{
				if(M.x>105 && M.x<130 && M.y>245 && M.y<265)
				{
					shape=1;
					if(Mousepress(105,245,130,265) == 1)
					{
						level=1;
						return level;
					}
				}
	
				else if(M.x>105 && M.x<130 && M.y>290 && M.y<310)
				{
					shape=1;
					if(Mousepress(105,290,130,310) == 1)
					{
						level=2;
						return level;
					}
				}

				else if(M.x>105 && M.x<130 && M.y>334 && M.y<354)
				{
					shape=1;
					if(Mousepress(105,334,130,354) == 1)
					{
						level=3;
						return level;
					}
				}

				else if(M.x>105 && M.x<130 && M.y>380 && M.y<400)
				{
					shape = 1;
					if(Mousepress(105,380,130,400) == 1)
					{
						level=4;
						return level;
					}
				}

				else if(M.x>105 && M.x<135 && M.y>420 && M.y<440)
				{
					shape = 1;
					if(Mousepress(105,420,135,440) == 1)
					{
						level=5;
						return level;
					}
				}
				else
				{
					shape=0;
				}
			}
			break;
			
			case BLUR:
			{
				if(M.x>105 && M.x<130 && M.y>364 && M.y<384)
				{
					shape=1;
					if(Mousepress(105,364,130,384) == 1)
					{
						level=1;
						return level;
					}
				}
	
				else if(M.x>105 && M.x<130 && M.y>410 && M.y<430)
				{
					shape=1;
					if(Mousepress(105,410,130,430) == 1)
					{
						level=2;
						return level;
					}
				}

				else if(M.x>105 && M.x<130 && M.y>454 && M.y<474)
				{
					shape=1;
					if(Mousepress(105,454,130,474) == 1)
					{
						level=3;
						return level;
					}
				}

				else if(M.x>105 && M.x<130 && M.y>500 && M.y<520)
				{
					shape = 1;
					if(Mousepress(105,500,130,520) == 1)
					{
						level=4;
						return level;
					}
				}
	
				else if(M.x>105 && M.x<135 && M.y>540 && M.y<560)
				{
					shape = 1;
					if(Mousepress(105,540,135,560) == 1)
					{
						level=5;
						return level;
					}
				}
				
				else
				{
					shape=0;
				}
			}
			break;
		}
	}	
}

void ui(int mode, int flag, int status)
{
	char *s1 = "请输入打开文件名称：";
	char *s2 = "请设置保存文件名称：";
	char *ch[5]={"漫画","油画","反色","浮雕","倒影"};
	int i,y,x=950;
	
	switch(mode)
	{
		case LIGHT:																//白天模式
		{
			switch(flag)
			{
				case EDIT:														//编辑菜单
				{
					Putbmp256(910,61,"picture\\edit.bmp");
				}
				break;
						
				case ADJUST:													//增强菜单
				{
					Putbmp256(0,160,"picture\\adjust.bmp");
				}
				break;
				
				case MOSIAC:
				{
					Putbmp256(310,635,"picture\\pensz.bmp");
				}
				break;
					
				case DIALOG:													//对话框
				{
					switch(status)
					{
						case OPEN:												//打开图片
						{
							Putbmp256(0,440,"picture\\lightlog.bmp");
							printHZ16(40,505,s1,0,1,1,1);	
						}
						break;
						
						case SAVE:												//保存图片
						{
							Putbmp256(665,440,"Picture\\lightlog.bmp");
							printHZ16(700,505,s2,0,1,1,1);
						}
						break;
						
						default:
							break;
					}
				}
				break;
				
				case FILTER:													//滤镜菜单
					for(i=0,y=189;i<5;i++,y+=80)
					{
						printHZ12(x,y,ch[i],BLACK,2,2,1);
						printHZ12(x+1,y,ch[i],BLACK,2,2,1);	
					}
				break;
				
				case GRAFFITI:													//涂鸦笔菜单
				{
					Putbmp256(370,630,"picture\\palette.bmp");
				}
				
				default:
					break;
			}
		}
		break;
		
		case DARK:																//夜间模式
		{
			switch(flag)
			{
				case EDIT:														//编辑菜单
				{
					Putbmp256(910,61,"picture\\editdark.bmp");
				}
				break;
						
				case ADJUST:													//增强
				{
					Putbmp256(0,160,"picture\\adjdark.bmp");
				}
				break;
				
				case MOSIAC:													//马赛克
				{
					Putbmp256(310,635,"picture\\penszdk.bmp");				
				}
				break;
					
				case DIALOG:													//对话框
				{
					switch(status)
					{
						case OPEN:												//打开图片
						{
							Putbmp256(0,440,"picture\\darklog.bmp");
							printHZ16(40,505,s1,0,1,1,1);	
						}
						break;
						
						case SAVE:												//保存图片
						{
							Putbmp256(665,440,"Picture\\darklog.bmp");
							printHZ16(700,505,s2,0,1,1,1);
						}
						break;
							
						default:
							break;
					}
				}
				break;
				
				case FILTER:													//滤镜
					for(i=0,y=189;i<5;i++,y+=80)
					{
						printHZ12(x,y,ch[i],WHITE,2,2,1);
						printHZ12(x+1,y,ch[i],WHITE,2,2,1);	
					}
				break;
					
				case GRAFFITI:													//涂鸦笔
				{
					Putbmp256(370,630,"picture\\paledk.bmp");
				}
				break;
					
				default:
					break;
			}	
		}
		break;
	}	
}

void Clear(int flag, int color)//关闭菜单函数
{
	switch(flag)
	{
		case EDIT:
		{
			Close(910,61,1020,645,color);
		}
		break;
		
		case ADJUST:
		{
			Close(0,160,65,537,color);
		}
		break;
		
		case FILTER:
		{
			Close(930,180,1010,540,color);
		}
		break;
		
		case OPEN:
		{
			Close(0,440,325,665,color);
		}
		break;
		
		case SAVE:
		{
			Close(665,440,990,665,color);
		}
		break;
		
		case MOSIAC:
		{
			Close(310,630,575,660,color);
		}
		
		default:
			break;
	}
}