/*
 * @Author: Thoelc 623624394@qq.com
 * @Date: 2024-04-10 00:08:00
 * @LastEditors: Thoelc 623624394@qq.com
 * @LastEditTime: 2024-04-10 00:10:32
 * @FilePath: \DOLYDV1-1.0\gui\eye\eye.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "eye.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <time.h>
#include <ctime>
#include <chrono>
#include "animation.h"
#include "efont.h"
#include "love.h"
#include "app.h"
#include "commu.h"
#define TEST 1
int FillBuffer(uint8_t *left_buff, uint8_t *right_buff);
int FillBufferExample();
// void eye_clear(void);
// int draw_point (int x, int y, uint32_t color);

static uint8_t* g_GuiVram[2]; 
static uint32_t g_RamSize;
static uint8_t flgExtVram;
static uint8_t g_EyeState = 1;
static uint32_t g_DrawFc = 1;  // front color
static uint32_t g_DrawBc = 1;  // back color
static uint8_t g_DrawMode = 1;  // Whether or not to cover color

/*  显示数码管效果需要变量 */
// 数码管每段的位置和大小
struct Segment {
    int x;
	int y;
	int w;
	int h;
};

// 定义每个段的形状和位置
// 定义每个段的形状和位置
static Segment segments[7] = {
    {10, 5,  50, 10},  // a
    {60, 15, 10, 50},  // b
    {60, 75, 10, 50},  // c
    {10, 125, 50, 10}, // d
    {0,  75,  10, 50}, // e
    {0,  15,  10, 50}, // f
    {10, 65,  50, 10}  // g
};


// 每个数字对应的段（1表示点亮，0表示熄灭）
static uint8_t digits[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 0, 1, 1}  // 9
};

void gui_init(LcdColorDepth depth)
{
	LcdControl::init(depth);
	LcdColorDepth getdepth = LcdControl::getColorDepth();
	eye_clear();

	if (depth == LCD_12BIT)
	{
		g_RamSize = LCD_WIDTH * LCD_HEIGHT * 1.5;
	}
	else if (depth == LCD_18BIT)
	{
		g_RamSize = LCD_WIDTH * LCD_HEIGHT * 3;
	}

	flgExtVram = 0;


	g_GuiVram[LcdLeft] = (uint8_t*)malloc(g_RamSize);  // 申请显存大小
	g_GuiVram[LcdRight] = (uint8_t*)malloc(g_RamSize);  // 申请显存大小

    
	
}
void* gui_task(void *)
{
	
	static uint8_t ip_showtime = 6, last_eyeflg;
	string get_ip;
	char port[20];
	gui_init(LCD_18BIT);
	// LcdControl::init(LCD_18BIT);
    LcdColorDepth depth = LcdControl::getColorDepth();
	for (;;)
	{
		if(ip_showtime > 0)  // show local ip
        {
			set_piontcolor(0XFFFFFF, 0x000000, 0);	
			draw_string(60, 60, "IP_ADDR:", LcdLeft, 32);
			get_ip = tcp.get_local_ip();
			
			draw_string(30, 96, get_ip.c_str(), LcdLeft, 32);
            sprintf(port, "TCP PORT:%d", IP_PORT);
		    draw_string(30, 122, port, LcdLeft, 32);
		
		    draw_string(30, 122, "DOLYDV-V1.0", LcdRight, 32);
			ip_showtime --;
			FillBuffer((uint8_t*)g_GuiVram[LcdLeft], (uint8_t*)g_GuiVram[LcdRight]);
			memset(g_GuiVram[LcdLeft], 0x000000, g_RamSize);
			memset(g_GuiVram[LcdRight], 0x000000, g_RamSize);
			sleep(1);
			continue;
		}

	#if TEST 



		if (0 == g_EyeState)
		{
			memset(g_GuiVram[LcdLeft], 0XFFFFFF, g_RamSize);
			memset(g_GuiVram[LcdRight], 0XFFFFFF, g_RamSize);
			// draw_allcircle(120, 120, 50, 0X000000, LcdRight);
			show_eye(120, 120, 90, 0X000000, LcdRight);
			show_eye(120, 120, 90, 0X000000, LcdLeft);
			last_eyeflg = g_EyeState;
			

		}
		else 
		{
			// memset(g_GuiVram[LcdLeft], 0x00, g_RamSize);
			// memset(g_GuiVram[LcdRight], 0x00, g_RamSize);
			if (last_eyeflg == 0)
			{
				memset(g_GuiVram[LcdLeft], 0x00, g_RamSize);
				memset(g_GuiVram[LcdRight], 0x00, g_RamSize);				
			}
			set_piontcolor(WHITE, BLACK, 0);			
			show_time();
			last_eyeflg = g_EyeState;
		}
		FillBuffer((uint8_t*)g_GuiVram[LcdLeft], (uint8_t*)g_GuiVram[LcdRight]);
		

	#else
		FillBuffer((uint8_t*)gImage_love, (uint8_t*)gImage_love);

	#endif
	    usleep(200000);
	};
}

int FillBuffer(uint8_t *left_buff, uint8_t *right_buff)
{
	// get LCD buffer size 
	// buffer size depends on color depth
	// ex. Color depth 12 Bit frame size = 240px * 240px * 1.5
	// Color depth 18 Bit frame size = 240px * 240px * 3
	int buffer_size = LcdControl::getBufferSize();

	// allocate & clear buffer
	uint8_t buf[buffer_size];
	memset(&buf, 0xFF, buffer_size);

	// create data for each side
	LcdData frame_left;
	frame_left.buffer = left_buff;
	frame_left.side = LcdLeft;

	LcdData frame_right;
	frame_right.buffer = right_buff;
	frame_right.side = LcdRight;

	int retval = 0;
	// write buffer to LCD
	if (LcdControl::writeLcd(&frame_left) < 0)
	{
		printf("Left Lcd write failed! \n");
		retval = -1;
	}
	// write buffer to LCD
	if (LcdControl::writeLcd(&frame_right) < 0)
	{
		printf("Right Lcd write failed! \n");
		retval = -1;
	}

	return retval;
}

int FillBufferExample(void)
{
	// get LCD buffer size 
	// buffer size depends on color depth
	// ex. Color depth 12 Bit frame size = 240px * 240px * 1.5
	// Color depth 18 Bit frame size = 240px * 240px * 3
	int buffer_size = LcdControl::getBufferSize();

	// allocate & clear buffer
	uint8_t buf[buffer_size];
	memset(&buf, 0xFF, buffer_size);

	// create data for each side
	LcdData frame_left;
	frame_left.buffer = buf;
	frame_left.side = LcdLeft;

	LcdData frame_right;
	frame_right.buffer = buf;
	frame_right.side = LcdRight;

	int retval = 0;
	// write buffer to LCD
	if (LcdControl::writeLcd(&frame_left) < 0)
	{
		printf("Left Lcd write failed! \n");
		retval = -1;
	}
	// write buffer to LCD
	if (LcdControl::writeLcd(&frame_right) < 0)
	{
		printf("Right Lcd write failed! \n");
		retval = -1;
	}

	return retval;
}


void eye_clear(void)
{
	LcdControl::LcdColorFill(LcdLeft, 0, 0, 0);
	LcdControl::LcdColorFill(LcdRight, 0, 0, 0);
}

uint8_t* Eye_Vram(uint8_t lcd_side) {

  if (lcd_side > 1 )
	return 0;
  return (uint8_t*)g_GuiVram[lcd_side];  
}
void set_piontcolor(uint32_t f_color,uint32_t b_color, uint8_t mode)
{
	g_DrawFc = f_color;  // front color
	g_DrawBc = b_color;  // back color
	g_DrawMode = mode;  // Whether or not to cover color
}
int draw_point (int x, int y, uint32_t color, uint8_t lcd_side)
{

	uint8_t* ptr = &Eye_Vram(lcd_side)[y*(LCD_WIDTH * 3) + x * 3];
	memcpy(ptr, &color, sizeof(char) * 3);

	// *ptr = bit;

	return 0;
}



/*<FUNC+>************************************************************************/
/* Function name:        draw_char                             */
/* Function Description:  显示字符    */
/* Input parameters:                                                            */
/* Output parameters: None                                                      */
/* Return value: None                                                           */
/* Operation process:                                                           */
/* Other notes: None                                                            */
/* Modification record:                                                         */
/*  Modification Date     Version No.     Modified By      Modification Content */
/* ---------------------------------------------------------------------------- */
/*     2024/05/19           V1.00          wangwentao            Create           */
/*<FUNC->************************************************************************/

void draw_char(uint16_t x,uint16_t y,uint8_t num, uint8_t lcd_side, uint8_t sizey)
{
	uint8_t temp,sizex,t;
	uint16_t i,TypefaceNum;//一个字符所占字节大小
	uint16_t x0=x;
	sizex=sizey/2;
	TypefaceNum=(sizex/8+((sizex%8)?1:0))*sizey;
	num=num-' ';    //得到偏移后的值
	// LCD_Address_Set(x,y,x+sizex-1,y+sizey-1);  //设置光标位置 
	for(i=0;i<TypefaceNum;i++)
	{ 
		if(sizey==12)temp=ascii_1206[num][i];		       //调用6x12字体
		else if(sizey==16)temp=ascii_1608[num][i];		 //调用8x16字体
		else if(sizey==24)temp=ascii_2412[num][i];		 //调用12x24字体
		else if(sizey==32)temp=ascii_3216[num][i];		 //调用16x32字体
		else if(sizey==128)temp=ascii_12864[num][i];		 //调用64x128字体
		else return;
		for(t=0;t<8;t++)
		{
			if(!g_DrawMode)//非叠加模式
			{
				if(temp&(0x01<<t))draw_point (x, y, g_DrawFc, lcd_side);
				else draw_point (x, y, g_DrawBc, lcd_side);
				x++;
				if((x-x0)==sizex)
				{
					x=x0;
					y++;
					break;
				}
			}
			else//叠加模式
			{
				if(temp&(0x01<<t))draw_point (x, y, g_DrawFc, lcd_side);//画一个点
				x++;
				if((x-x0)==sizex)
				{
					x=x0;
					y++;
					break;
				}
			}


	
		}
	}   	 	  
}

void draw_string(uint16_t x,uint16_t y,const char *p, uint8_t lcd_side,uint8_t sizey)
{         
	while(*p!='\0')
	{       
		draw_char(x, y, *p, lcd_side, sizey);
		x+=sizey/2;
		p++;
	}  
}

/******************************************************************************
      函数说明：画线
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
                color   线的颜色
      返回值：  无
******************************************************************************/
void draw_line(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint32_t color, uint8_t lcd_side)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1;
	uRow=x1;//画线起点坐标
	uCol=y1;
	if(delta_x>0)incx=1; //设置单步方向 
	else if (delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;//水平线 
	else {incy=-1;delta_y=-delta_y;}
	if(delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		
		draw_point(uRow, uCol ,color , lcd_side);
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}

void draw_allrectangle(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint32_t color, uint8_t lcd_side)
{
	uint16_t i = 0;

	for(i=0;i< y2-y1;i++)

	{
		draw_line(x1, y1 + i, x2, y1 + i, color, lcd_side);

	}	
}
//在指定位置画一个实心圆
//(x,y):坐标
//r    :半径
// color:颜色 
void draw_allcircle(uint16_t x0,uint16_t y0,uint8_t r, uint32_t color, uint8_t lcd_side)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		int i = a,p = b;
		while(i>0){		
			draw_point(x0+b ,y0-i , color, lcd_side);
			draw_point(x0-i,y0+b , color, lcd_side);
			i--;
		}		
		while(p>0){		
			draw_point(x0-a,y0-p , color, lcd_side);
			draw_point(x0-p,y0-a , color, lcd_side);
			draw_point(x0+a,y0-p , color, lcd_side);
			draw_point(x0-p,y0+a , color, lcd_side);
			draw_point(x0+a,y0+p , color, lcd_side);
			draw_point(x0+p,y0+a , color, lcd_side);
			p--;
		}
		a++;
		//Bresenham算法画圆    
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
	draw_point(x0,y0 ,color , lcd_side); //圆心坐标
}

// show eye 
void show_eye(uint16_t x0,uint16_t y0,uint8_t r, uint32_t color, uint8_t lcd_side)
{
	memset(g_GuiVram[lcd_side], 0xFF, g_RamSize);
    draw_allcircle(x0, y0, r, color, lcd_side);
    draw_allcircle(x0, y0, (uint8_t)(0.9*r), 0xFFFFFF, lcd_side);
    draw_allcircle(x0, y0, (uint8_t)(0.7*r), color, lcd_side);
	draw_allcircle(x0 + (0.707 * 0.7 * r), y0 - (0.707 * 0.7 * r), (uint8_t)(0.2*r), 0xFFFFFF, lcd_side);

	
}

std::string getDayOfWeekAbbreviation(int wday) {
    const char* daysOfWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    if (wday < 0 || wday > 6) {
        return "Invalid day";  // 处理无效输入
    }
    return daysOfWeek[wday];
}
// 绘制单个数码管数字
void draw_digit(int digit, int x, int y, uint32_t color, uint8_t lcd_side) {
    for (int i = 0; i < 7; i++) {
        if (digits[digit][i]) {
            Segment seg = segments[i];
			draw_allrectangle(x + seg.x, y + seg.y, x + seg.x +seg.w,y + seg.y +seg.h,color, lcd_side);
        
        }
    }
}
// show local time
void show_time(void)
{
	char timr_str[50];

	// LcdControl::init(LCD_18BIT);

    auto current_time_point = std::chrono::system_clock::now(); // 捕获当前时间
    auto current_time_t = std::chrono::system_clock::to_time_t(current_time_point); // 转换为 time_t
	std::tm now_tm = *std::localtime(&current_time_t);

	sprintf(timr_str, "%02d", now_tm.tm_hour);
 	draw_digit(timr_str[0] - 0x30, 40, 40, 0xFFFFFF, LcdRight);
	draw_digit(timr_str[1] - 0x30, 120, 40, 0xFFFFFF, LcdRight);
	// draw_string(50, 50, timr_str, LcdRight,128);
	sprintf(timr_str, "%02d", now_tm.tm_min);
    // draw_string(50, 50, timr_str, LcdLeft,128);
 	draw_digit(timr_str[0] - 0x30, 40, 40, 0xFFFFFF, LcdLeft);
	draw_digit(timr_str[1] - 0x30, 120, 40, 0xFFFFFF, LcdLeft);
	for (int i = 0; i <= 3; i++)
	{
		draw_line(60, 185 + i, 180, 185 + i, 0xFFFFFF, LcdLeft);
		draw_line(60, 185 + i, 180, 185 + i, 0xFFFFFF, LcdRight);	
	}


	sprintf(timr_str, "%04d-%02d-%02d", now_tm.tm_year + 1900, now_tm.tm_mon, now_tm.tm_mday);
    draw_string(90, 190, timr_str, LcdRight,16);	

	sprintf(timr_str, "%s", getDayOfWeekAbbreviation(now_tm.tm_wday).c_str());
    draw_string(70, 190, timr_str, LcdLeft,16);	

	
    draw_string(110, 190, "doly robot", LcdLeft,16);	
	
}


void set_eyestate(uint8_t state)
{

	g_EyeState = state;
}