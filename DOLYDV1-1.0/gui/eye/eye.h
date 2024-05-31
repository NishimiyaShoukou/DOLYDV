#pragma once
#include "LcdControl.h"



#define WHITE         	 0xFFFFFF
#define BLACK         	 0x000000	 
void gui_init(LcdColorDepth depth = LCD_12BIT);
void* gui_task(void *);
void eye_clear(void);
void set_piontcolor(uint32_t f_color,uint32_t b_color, uint8_t mode);
int draw_point (int x, int y, uint32_t color, uint8_t lcd_side);
void draw_char(uint16_t x,uint16_t y,uint8_t num, uint8_t lcd_side,uint8_t sizey);
void draw_string(uint16_t x,uint16_t y,const char *p, uint8_t lcd_side,uint8_t sizey);
void draw_line(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint32_t color, uint8_t lcd_side);
void draw_allrectangle(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint32_t color, uint8_t lcd_side);
void draw_allcircle(uint16_t x0,uint16_t y0,uint8_t r, uint32_t color, uint8_t lcd_side);
void show_eye(uint16_t x0,uint16_t y0,uint8_t r, uint32_t color, uint8_t lcd_side);
void show_time(void);
void set_eyestate(uint8_t state);
