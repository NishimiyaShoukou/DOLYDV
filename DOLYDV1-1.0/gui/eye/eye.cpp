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
#include <chrono>
#include "animation.h"
#include "efont.h"
#include "love.h"

#define TEST 1
int FillBuffer(uint8_t *left_buff, uint8_t *right_buff);
int FillBufferExample();
// void eye_clear(void);
// int draw_point (int x, int y, uint32_t color);

static uint8_t* g_GuiVram[2]; 
static uint32_t g_RamSize;
uint8_t flgExtVram;
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
void gui_task(void)
{
	char timr_str[20];
	gui_init(LCD_18BIT);
	// LcdControl::init(LCD_18BIT);
    LcdColorDepth depth = LcdControl::getColorDepth();
#if TEST 


	// // Fill with buffer example
	// FillBufferExample();

	// // wait 2 seconds
	// std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	// // fill with color example
	// LcdControl::LcdColorFill(LcdLeft, 0, 0, 255);
	// LcdControl::LcdColorFill(LcdRight, 255, 0, 0);
	// for (int i = 0; i <240; i++)
	// {
	// 	draw_point (i, i, 0X00FF00, LcdLeft);
	// }
	// draw_char(40, 60, 'H', 0XFFFFFF, LcdLeft, 32);

	memset(g_GuiVram[LcdRight], 0xFF, g_RamSize);
    // draw_allcircle(120, 120, 50, 0X000000, LcdRight);
	show_eye(120, 120, 90, 0X000000, LcdRight);
	show_eye(120, 120, 90, 0X000000, LcdLeft);
	FillBuffer((uint8_t*)g_GuiVram[LcdLeft], (uint8_t*)g_GuiVram[LcdRight]);

#else
    FillBuffer((uint8_t*)gImage_love, (uint8_t*)gImage_love);

#endif
	
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

void draw_char(uint16_t x,uint16_t y,uint8_t num, uint32_t color, uint8_t lcd_side, uint8_t sizey)
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
		else if(sizey==128)temp=ascii_12864[num][i];		 //调用16x32字体
		else return;
		for(t=0;t<8;t++)
		{


			if(temp&(0x01<<t))draw_point (x, y, color, lcd_side);//画一个点
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

void draw_string(uint16_t x,uint16_t y,const char *p, uint32_t color, uint8_t lcd_side,uint8_t sizey)
{         
	while(*p!='\0')
	{       
		draw_char(x, y, *p, color, lcd_side, sizey);
		x+=sizey/2;
		p++;
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


// show local time
void show_time(void)
{
	char timr_str[20];
	gui_init(LCD_18BIT);
	// LcdControl::init(LCD_18BIT);

    auto current_time_point = std::chrono::system_clock::now(); // 捕获当前时间
    auto current_time_t = std::chrono::system_clock::to_time_t(current_time_point); // 转换为 time_t
	std::tm now_tm = *std::localtime(&current_time_t);
    sprintf(timr_str, "%d", now_tm.tm_hour);
	draw_string(50,70, timr_str, 0XFFFFFF, LcdRight,128);
	sprintf(timr_str, "%d", now_tm.tm_min);
    draw_string(50,70, timr_str, 0XFFFFFF, LcdLeft,128);	
}