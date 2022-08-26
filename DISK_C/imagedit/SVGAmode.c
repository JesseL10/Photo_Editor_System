#include "head.h"
#include "SVGAmode.h"
#include "draw.h"

/**********************************************************
Function：		SetSVGA256

Description：	SVGA显示模式设置函数，设为0x105

Calls：			int86
				delay
				printf
				exit

Called By：		AutoSimulate
				HandOperate
				
Input：			None

Output：		错误信息

Return：		None				
Others：		None
**********************************************************/
void SetSVGA256(void)
{
	/*****************************************************
	在dos.h中REGS的定义如下：
	struct WORDREGS
	{
		unsigned int ax, bx, cx, dx, si, di, cflag, flags;
	};
	
	struct BYTEREGS
	{
		unsigned char al, ah, bl, bh, cl, ch, dl, dh;
	};
	
	union REGS
	{
		struct WORDREGS x;
		struct BYTEREGS h;
	};
	这样al对应ax的低八位，ah对应ax的高八位，以此类推。
	调用时需要查表决定各入口参数取值,获取返回值表示的信息。
	*****************************************************/
	union REGS graph_regs;
	
	/*设置VESA VBE模式的功能号*/
	graph_regs.x.ax = 0x4f02;
	graph_regs.x.bx = 0x105;
	int86(0x10, &graph_regs, &graph_regs);
	
	/*ax != 0x004f意味着初始化失败，输出错误信息见上,下同*/
	if (graph_regs.x.ax != 0x004f)
	{
		printf("Error in setting SVGA mode!\nError code:0x%x\n", graph_regs.x.ax);
		delay(5000);
		exit(1);
	}
}

/**********************************************************
Function：		SetSVGA64k

Description：	SVGA显示模式设置函数，设为0x117

Calls：			int86
				delay
				printf
				exit

Called By：		AutoSimulate
				HandOperate
				
Input：			None

Output：		错误信息
**********************************************************/
void SetSVGA64k(void)
{
	/*REGS联合体见上*/
	union REGS graph_regs;
	
	/*设置VESA VBE模式的功能号*/
	graph_regs.x.ax = 0x4f02;
	graph_regs.x.bx = 0x117;
	int86(0x10, &graph_regs, &graph_regs);
	
	/*ax != 0x004f意味着初始化失败，输出错误信息见上,下同*/
	if (graph_regs.x.ax != 0x004f)
	{
		printf("Error in setting SVGA mode!\nError code:0x%x\n", graph_regs.x.ax);
		delay(5000);
		exit(1);
	}
}

/**********************************************************
Function：		GetSVGA

Description：	获取SVGA显示模式号bx。摘录常用的模式号如下：
				模式号		分辨率		颜色数		颜色位定义
				0x101		640*480		256				-
				0x103		800*600		256				-
				0x104		1024*768	16				-
				0x105		1024*768	256				-
				0x110		640*480		32K			1:5:5:5
				0x111		640*480		64K			5:6:5
				0x112		640*480		16.8M		8:8:8
				0x113		800*600		32K			1:5:5:5
				0x114		800*600		64K			5:6:5
				0x115		800*600		16.8M		8:8:8
				0x116		1024*768	32K			1:5:5:5
				0x117		1024*768	64K			5:6:5
				0x118		1024*768	16.8M		8:8:8

Calls：			int86
				delay
				printf
				exit

Output：		初始化失败时会屏幕输出错误号。

Return：		unsigned int graph_regs.x.bx	显示模式号
**********************************************************/
unsigned int GetSVGA(void)
{
	/*REGS联合体见上*/
	union REGS graph_regs;
	
	/*获取当前VESA VBE模式的功能号*/
	graph_regs.x.ax = 0x4f03;
	int86(0x10, &graph_regs, &graph_regs);
	
	/*显示错误信息*/
	if (graph_regs.x.ax != 0x004f)
	{
		printf("Error in getting SVGA mode!\nError code:0x%x\n", graph_regs.x.ax);
		delay(5000);
		exit(1);
	}
	
	return graph_regs.x.bx;
}

/**********************************************************
Function：		Selectpage

Description：	带判断功能的换页函数，解决读写显存时跨段寻址问题

Calls：			int86

Called By：		Putpixel256
				Putpixel64k
				Xorpixel
				Horizline
				Getpixel64k
				
Input：			register char page		需要换到的页面号
**********************************************************/
void Selectpage(register char page)
{
	/*REGS含义同上*/
	union REGS graph_regs;
	
	/*上一次的页面号,用于减少切换次数,是使用次数很多的重要变量*/
	static unsigned char old_page = 0;
	
	/*标志数，用于判断是否是第一次换页*/
	static int flag = 0;
	
	/*窗口页面控制功能号*/
	graph_regs.x.ax = 0x4f05;
	graph_regs.x.bx = 0;
	
	/*如果是第一次换页*/
	if (flag == 0)
	{
		old_page = page;
		graph_regs.x.dx = page;
		int86(0x10, &graph_regs, &graph_regs);
		flag++;
	}
	
	/*如果和上次页面号不同，则进行换页*/
	else if (page != old_page)
	{
		old_page = page;
		graph_regs.x.dx = page;
		int86(0x10, &graph_regs, &graph_regs);
	}
}

/**********************************************************
Function：		Putpixel256

Description：	画点函数，其他画图函数的基础，仅适用于0x105模式！

Calls：			Selectpage

Called By：		Putbmp256
				Line
				Circle
				
Input：			int x					像素横坐标，从左到右增加，0为最小值（屏幕参考系）
				int y					像素纵坐标，从上到下增加，0为最小值（屏幕参考系）
				unsigned char color		颜色数，共有256种

Output：		在屏幕上画指定颜色的点
**********************************************************/
void Putpixel256(int x, int y, unsigned char color)
{
	/*显存指针常量，指向显存首地址，指针本身不允许修改*/
	unsigned char far * const video_buffer = (unsigned char far *)0xa0000000L;
	
	/*要切换的页面号*/
	unsigned char new_page;
	
	/*对应显存地址偏移量*/
	unsigned long int page;
	
	/*判断点是否在屏幕范围内，不在就退出*/
	if(x < 0 || x > (SCR_WIDTH - 1) || y < 0 || y > (SCR_HEIGHT - 1))
	{
		return;
	}
	
	/*计算显存地址偏移量和对应的页面号，做换页操作*/
	page = ((unsigned long int)y << 10) + x;
	new_page = page >> 16;	/*64k个点一换页，除以64k的替代算法*/
	Selectpage(new_page);
	
	/*向显存写入颜色，对应点画出*/
	video_buffer[page] = color;	
}

/**********************************************************
Function：		Getpixel256

Description：	取点颜色函数，仅适用于0x105模式！

Return：		unsigned int	对应坐标点在显存里面的颜色			
**********************************************************/
unsigned char Getpixel256(int x, int y)
{
	/*显存指针常量，指向显存首地址，指针本身不允许修改*/
	unsigned char far * const video_buffer = (unsigned char far *)0xa0000000L;

	/*要切换的页面号*/
	unsigned char new_page;

	/*对应显存地址偏移量*/
	unsigned long int page;

	/*判断点是否在屏幕范围内，不在就退出*/
	if(x < 0 || x > (SCR_WIDTH - 1) || y < 0 || y > (SCR_HEIGHT - 1))
	{
		return 0;
	}

	/*计算显存地址偏移量和对应的页面号，做换页操作*/
	page = ((unsigned long int)y << 10) + x;
	new_page = page >> 16;	/*64k个点一换页，除以64k的替代算法*/
	Selectpage(new_page);


	return video_buffer[page];
}

/**********************************************************
Function：		Putpixel64k

Description：	画点函数，其他画图函数的基础，仅适用于0x117模式！

Calls：			Selectpage

Called By：		Putbmp64k
				MousePutBk
				MouseDraw
				
Input：			int x					像素横坐标，从左到右增加，0为最小值（屏幕参考系）
				int y					像素纵坐标，从上到下增加，0为最小值（屏幕参考系）
				unsigned int color		颜色数，共有64k种

Output：		在屏幕上画指定颜色的点
**********************************************************/
void Putpixel64k(int x, int y, unsigned int color)
{
	/*显存指针常量，指向显存首地址，指针本身不允许修改*/
	unsigned int far * const video_buffer = (unsigned char far *)0xa0000000L;
	
	/*要切换的页面号*/
	unsigned char new_page;
	
	/*对应显存地址偏移量*/
	unsigned long int page;
	
	/*判断点是否在屏幕范围内，不在就退出*/
	if(x < 0 || x > (SCR_WIDTH - 1) || y < 0 || y > (SCR_HEIGHT - 1))
	{
		return;
	}
	
	/*计算显存地址偏移量和对应的页面号，做换页操作*/
	page = ((unsigned long int)y << 10) + x;
	new_page = page >> 15;	/*32k个点一换页，除以32k的替代算法*/
	Selectpage(new_page);
	
	/*向显存写入颜色，对应点画出*/
	video_buffer[page] = color;	
}

/**********************************************************
Function：		Getpixel64k

Description：	取点颜色函数，仅适用于0x117模式！

Calls：			Selectpage
				
Called By：		MouseStoreBk

Input：			int x	像素横坐标，从左到右增加，0为最小值（屏幕参考系）
				int y	像素纵坐标，从上到下增加，0为最小值（屏幕参考系）

Return：		unsigned int	对应坐标点在显存里面的颜色
**********************************************************/
unsigned int Getpixel64k(int x, int y)
{
	/*显存指针常量，指向显存首地址，指针本身不允许修改*/
	unsigned int far * const video_buffer = (unsigned char far *)0xa0000000L;
	
	/*要切换的页面号*/
	unsigned char new_page;
	
	/*对应显存地址偏移量*/
	unsigned long int page;
	
	/*判断点是否在屏幕范围内，不在就退出*/
	if(x < 0 || x > (SCR_WIDTH - 1) || y < 0 || y > (SCR_HEIGHT - 1))
	{
		return 0;
	}
	
	/*计算显存地址偏移量和对应的页面号，做换页操作*/
	page = ((unsigned long int)y << 10) + x;
	new_page = page >> 15;	/*32k个点一换页，除以32k的替代算法*/
	Selectpage(new_page);
	
	/*返回颜色*/
	return video_buffer[page];	
}


/**********************************************************
Function：		Putbmp256

Description：	8位非压缩bmp图定位显示函数。
				只支持8位非压缩bmp图，宽度像素最大允许为1024！
				其余bmp类型均不支持！
				仅在0x105模式下使用！
				为了简化，没有设置文件类型检测功能检测功能，请勿读入不合要求的文件！
				此函数适合在不换位面条件下读取大型图片。
				虽然能设置了读取颜色表功能，并能兼容实际使用颜色表数不足最大数的图片，
				但统一要求使用Windows默认颜色表，否则影响其他图片显示！

Calls：			Putpixel256

				fseek
				fread
				fclose
				outportb
				malloc
				free

Called By：		AutoSimulate
				HandOperate
				
Input：			int x		图片左上角的横坐标（屏幕参考系）
				int y		图片左上角的纵坐标（屏幕参考系）
				const char * path	bmp图片路径

Output：		屏幕上显示图片

Return：		0	显示成功
				-1	显示失败
**********************************************************/
int Putbmp256(int x, int y, const char * path)
{
	/*指向图片文件的文件指针*/
	FILE * fpbmp;
	
	/*bmp颜色表结构指针*/
	RGBQUAD * pclr, *clr;
	
	/*行像素缓存指针*/
	unsigned char * buffer;
	
	/*实际使用的颜色表中的颜色数*/
	unsigned long int clr_used;
	
	/*图片的宽度、高度、一行像素所占字节数（含补齐空字节）*/
	long int width, height, linebytes;
	
	/*循环变量*/
	int i, j;
	
	/*图片位深*/
	unsigned int bit;
	
	/*压缩类型数*/
	unsigned long int compression;
	
	/*打开文件*/
	if ((fpbmp = fopen(path, "rb")) == NULL)
	{
		return -1;
	}
	
	/*读取位深*/
	fseek(fpbmp, 28L, 0);
	fread(&bit, 2, 1, fpbmp);
	
	/*非8位图则退出*/
	if (bit != 8U)
	{
		return -1;
	}
	
	/*读取压缩类型*/
	fseek(fpbmp, 30L, 0);
	fread(&compression, 4, 1, fpbmp);
	
	/*采用压缩算法则退出*/
	if (compression != 0UL)
	{
		return -1;
	}
	
	/*读取宽度、高度*/
	fseek(fpbmp, 18L, 0);
	fread(&width, 4, 1, fpbmp);
	fread(&height, 4, 1, fpbmp);
	
	/*宽度超限则退出*/
	if (width > SCR_WIDTH)
	{
		return -1;
	}

	/*计算一行像素占字节数，包括补齐的空字节*/
	linebytes = width % 4;
	
	if(!linebytes)
	{
		linebytes = width;
	}
	else
	{
		linebytes = width + 4 - linebytes;
	}
	
	/*读取实际使用的颜色表中的颜色数*/
	fseek(fpbmp, 46L, 0);
	fread(&clr_used, 4, 1, fpbmp);
	
	/*若颜色数为0，则使用了2的bit次方种颜色*/
	if (clr_used == 0L)
	{
		clr_used = 1U << bit;
	}
	
	/*开辟颜色表动态储存空间*/
	if ((clr = (RGBQUAD *)malloc(4L * clr_used)) == 0)
	{
		return -1;
	}
	
	/*颜色表工作指针初始化*/
	pclr = clr;
	
	/*读取颜色表*/
	fseek(fpbmp, 54L, 0);
	
	if ((fread((unsigned char *)pclr, 4L * clr_used, 1, fpbmp)) != 1)
	{
		return -1;
	}
	
	/*按照颜色表设置颜色寄存器值*/
	for (i = 0; i < clr_used; i++, pclr++) 
	{
		outportb(0x3c8, i);				/*设置要改变的颜色号*/
		outportb(0x3c9, pclr->r >> 2);
		outportb(0x3c9, pclr->g >> 2);
		outportb(0x3c9, pclr->b >> 2);
	}
	
	free(clr);
	
	/*开辟行像素数据动态储存空间*/
	if ((buffer = (unsigned char *)malloc(linebytes)) == 0)
	{
		return -1;
	}
	
	/*行扫描形式读取图片数据并显示*/
	fseek(fpbmp, 54L + 4L * clr_used, 0);
	for (i = height - 1; i > -1; i--)
	{
		fread(buffer, linebytes, 1, fpbmp);	/*读取一行像素数据*/
		
		for (j = 0; j < width; j++)
		{
			Putpixel256(j + x, i + y, buffer[j]);
		}
	}
	
	free(buffer);	
	fclose(fpbmp);
	
	return 0;	
}

/**********************************************************
Function：		Putbmp64k

Description：	24位非压缩bmp图定位显示函数。
				只支持24位非压缩bmp图，宽度像素最大允许为1024！
				其余bmp类型均不支持！
				仅在0x117模式下使用！
				为了简化，没有设置文件类型检测功能检测功能，请勿读入不合要求的文件！

Calls：			Putpixel64k

				fseek
				fread
				fclose
				outportb
				malloc
				free

Called By：		AutoSimulate
				HandOperate
				Menu
				
Input：			int x		图片左上角的横坐标（屏幕参考系）
				int y		图片左上角的纵坐标（屏幕参考系）
				const char * path	bmp图片路径

Output：		屏幕上显示图片

Return：		0	显示成功
				-1	显示失败
**********************************************************/
int Putbmp64k(int x, int y, const char * path)
{
	
	/*指向图片文件的文件指针*/
	FILE * fpbmp;
	
	/*行像素缓存指针*/
	COLORS24 * buffer;
	
	/*图片的宽度、高度、一行像素所占字节数（含补齐空字节）*/
	long int width, height, linebytes;
	
	/*循环变量*/
	int i, j;
	
	/*图片位深*/
	unsigned int bit;
	
	/*压缩类型数*/
	unsigned long int compression;
	
	/*打开文件*/
	if ((fpbmp = fopen(path, "rb")) == NULL)
	{
		printf("cannot open the file.");
		return -1;
	}
	
	/*读取位深*/
	fseek(fpbmp, 28L, 0);
	fread(&bit, 2, 1, fpbmp);
	
	/*非24位图则退出*/
	if (bit != 24U)
	{
		return -1;
	}
	
	/*读取压缩类型*/
	fseek(fpbmp, 30L, 0);
	fread(&compression, 4, 1, fpbmp);
	
	/*采用压缩算法则退出*/
	if (compression != 0UL)
	{
		return -1;
	}
	
	/*读取宽度、高度*/
	fseek(fpbmp, 18L, 0);
	fread(&width, 4, 1, fpbmp);
	fread(&height, 4, 1, fpbmp);
	
	/*宽度超限则退出*/
	if (width > SCR_WIDTH)
	{
		return -1;
	}

	/*计算一行像素占字节数，包括补齐的空字节*/
	linebytes = (3 * width) % 4;
	
	if(!linebytes)
	{
		linebytes = 3 * width;
	}
	else
	{
		linebytes = 3 * width + 4 - linebytes;
	}

	/*开辟行像素数据动态储存空间*/
	if ((buffer = (COLORS24 *)malloc(linebytes)) == 0)
	{
		return -1;
	}
	
	/*行扫描形式读取图片数据并显示*/
	fseek(fpbmp, 54L, 0);
		
		for (i = height - 1; i > -1; i--)
		{
			fread(buffer, linebytes, 1, fpbmp);	/*读取一行像素数据*/
		
			/*一行像素的数据处理和画出*/
			for (j = 0; j < width; j++)
			{
				/*0x117模式下，原图红绿蓝各8位分别近似为5位、6位、5位*/
				buffer[j].R >>= 3;
				buffer[j].G >>= 2;
				buffer[j].B >>= 3;
				Putpixel64k(j + x, i + y,
				((((unsigned int)buffer[j].R) << 11)
				| (((unsigned int)buffer[j].G) << 5)
				| ((unsigned int)buffer[j].B)));	/*计算最终颜色，红绿蓝从高位到低位排列*/
			}
		}	
		
	free(buffer);	
	fclose(fpbmp);
	
	return 0;	
}

/**********************************************************
Function：		Xorpixel

Description：	按位异或画点函数

Calls：			Selectpage

Called By：		XorCarBmp
				
Input：			int x					像素横坐标，从左到右增加，0为最小值（屏幕参考系）
				int y					像素纵坐标，从上到下增加，0为最小值（屏幕参考系）
				unsigned char color		颜色数，共有256种

Output：		在屏幕上画异或点
**********************************************************/
void Xorpixel(int x, int y, unsigned char color)
{
	/*显存指针常量，指向显存首地址，指针本身不允许修改*/
	unsigned char far * const video_buffer = (unsigned char far *)0xa0000000L;
	
	/*要切换的页面号*/
	unsigned char new_page;
	
	/*对应显存地址偏移量*/
	unsigned long int page;
	
	/*判断点是否在屏幕范围内，不在就退出*/
	if(x < 0 || x > (SCR_WIDTH - 1) || y < 0 || y > (SCR_HEIGHT - 1))
	{
		return;
	}
	
	/*计算显存地址偏移量和对应的页面号，做换页操作*/
	page = ((unsigned long int)y << 10) + x;
	new_page = page >> 16;
	Selectpage(new_page);
	
	/*按位异或方式向显存写入颜色，对应点画出*/
	video_buffer[page] ^= color;	
}


/**********************************************************
Function：		Close
Description：	画矩形块函数
				可以接收超出屏幕范围的数据，只画出在屏幕内部分
				因为没有防止整型变量溢出的判断，画超出屏幕的部分时应防止输入特大数据

Calls：			Horizline

Called By：		LightSW
				LightNE
				LightNW
				LightSE

Input：			int x1					对角点1的横坐标，从左到右增加，0为最小值（屏幕参考系）
				int y1					对角点1的纵坐标，从上到下增加，0为最小值（屏幕参考系）
				int x2					对角点2的横坐标，从左到右增加，0为最小值（屏幕参考系）
				int y2					对角点2的纵坐标，从上到下增加，0为最小值（屏幕参考系）
				unsigned char color		颜色数，共有256种

Output：		屏幕上画出矩形块
**********************************************************/
void Close(int x1, int y1, int x2, int y2, unsigned char color)
{
	/*temp为临时变量和循环变量*/
	/*width为矩形长*/
	int temp;
	
	/*x坐标排序*/
	if (x1 > x2)
	{
		temp = x1;
		x1 = x2;
		x2 = temp;
	}
	
	/*y坐标排序*/
	if (y1 > y2)
	{
		temp = y1;
		y1 = y2;
		y2 = temp;
	}
	
	/*逐行扫描画出矩形*/
	for (temp = y1; temp <= y2; temp++)
	{
		Line(x1, temp, x2, temp ,color);
	}
}

/**********************************************************
Function：		Circle
Description：	画圆圈函数
				可以接收超出屏幕范围的数据，只画出在屏幕内部分
				因为没有防止整型变量溢出的判断，画超出屏幕的部分时应防止输入特大数据

Calls：			Putpixel256

Called By：		LightSW
				LightNE
				LightNW
				LightSE

Input：			int xc					x_center的缩写，圆心横坐标（屏幕参考系）
				int yc					y_center的缩写，圆心纵坐标（屏幕参考系）
				int radius				半径，必须为正
				unsigned char color		颜色数，共有256种

Output：		屏幕上画出圆圈
**********************************************************/
void Circle(int xc, int yc, int radius, unsigned char color)
{
	/*画圆圈的定位变量和决策变量*/
	int x, y, d;
	
	/*半径必须为正，否则退出*/
	if (radius <= 0)
	{
		return;
	}
	
	/************************************
	以下运用Bresenham算法生成圆圈。
	该算法是得到公认的成熟的快速算法。
	具体细节略去。
	************************************/
	y = radius;
	d = 3 - radius << 1;
	
	for (x = 0; x <= y; x++)
	{
		Putpixel256(xc + x, yc + y, color);
		Putpixel256(xc + x, yc - y, color);
		Putpixel256(xc - x, yc - y, color);
		Putpixel256(xc - x, yc + y, color);
		Putpixel256(xc + y, yc + x, color);
		Putpixel256(xc + y, yc - x, color);
		Putpixel256(xc - y, yc - x, color);
		Putpixel256(xc - y, yc + x, color);
		
		if (d < 0)
		{
			d += x * 4 + 6;
		}
		
		else
		{
			d += (x - y) * 4 + 10;
			y--;
		}
	}
}


unsigned int Select_Page(unsigned char index)
{
	union REGS in, out;
	in.x.ax = 0x4f05;			//换页
	in.x.bx = 0;				//表示当前窗口
	in.x.dx = index;			//在显存中的位面号
	int86(0x10, &in, &out);
	return 0;
}


/*从屏幕上获取图片存入缓存区*/
void Getimage(int x1, int y1, int x2, int y2 , char *image)
{
	
	/*循环变量*/
	int i = 0;
	int j = 0;
	
	/*图像的宽度width 高度height*/
	int width = abs(x2 - x1);
	int height = abs(y2 - y1);
	
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			image[width*i+j] = Getpixel256(x1+j,y1+i);
		}
	}
}

/*将缓存区中的图片重新写入显寸*/
void Putimage(int x1, int y1, int x2, int y2, char *image)
{
	/*循环变量*/
	int i = 0;
	int j = 0;
	
	int width = abs(x2 - x1);
	int height = abs(y2 - y1);
	
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			Putpixel256(x1+j,y1+i,image[width*i+j]);
		}
	}
}

/*计算指定图像区域所占字节数大小*/
int Imagesize(int x1, int y1, int x2, int y2)
{
	/*返回值*/
	unsigned int size;
	
	/*图像宽和高*/
	int width = abs(x2 - x1);
	int height = abs(y2 - y1);
	
	size = width * height;
	
	return size;
}

void Circlefill(int xc, int yc, int radius, unsigned char color)
{
	/*画圆圈的定位变量和决策变量*/
	int x = 0,
		y = radius,
		dx = 3,
		dy = 2 - radius - radius,
		d = 1 - radius;
	
	/*半径必须为正，否则退出*/
	if (radius <= 0)
	{
		return;
	}
	
	/************************************
	以下运用Bresenham算法生成实心圆。
	该算法是得到公认的成熟的快速算法。
	具体细节略去。
	************************************/
	while (x <= y)
	{
		Horizline(xc - x, yc - y, x + x, color);
        Horizline(xc - y, yc - x, y + y, color);
        Horizline(xc - y, yc + x, y + y, color);
        Horizline(xc - x, yc + y, x + x, color);
        
        if (d < 0)
        {
            d += dx;
            dx += 2;
        }
        
        else
        {
            d += (dx + dy);
            dx += 2;
            dy += 2;
            y--;
		}

        x++;
	}
}

void Horizline(int x, int y, int width, unsigned char color)
{
	/*显存指针常量，指向显存首地址，指针本身不允许修改*/
	unsigned char far * const video_buffer = (unsigned char far *)0xa0000000L;
	
	/*要切换的页面号*/
	unsigned char new_page;
	
	/*对应显存地址偏移量*/
	unsigned long int page;
	
	/*i是x的临时变量，后作循环变量*/
	int i;
	
	/*判断延伸方向，让起始点靠左*/
	if (width < 0)
	{
		x = x + width;
		width = -width;
	}
	
	i = x;
	
	/*省略超出屏幕左边部分*/
	if (x < 0)
	{
		x = 0;
		width += i;
	}
	
	/*整条线在屏幕外时退出*/
	if (x >= SCR_WIDTH)
	{
		return;
	}
	
	/*整条线在屏幕外时退出*/
	if (y < 0 || y >= SCR_HEIGHT)
	{
		return;
	}
	
	/*省略超出屏幕右边部分*/
	if (x + width > SCR_WIDTH)
	{
		width = SCR_WIDTH - x;
	}
	
	/*计算显存地址偏移量和对应的页面号，做换页操作*/
	page = ((unsigned long int)y << 10) + x;
	new_page = page >> 16;
	Selectpage(new_page);
	
	/*向显存写入颜色，水平线画出*/
	for (i = 0; i < width; i++)
	{
		*(video_buffer + page + i) = color;
	}
}
