#pragma once
#include "LcdControl.h"
void gui_init(LcdColorDepth depth = LCD_12BIT);
void* gui_task(void *);
void eye_clear(void);
int draw_point (int x, int y, uint32_t color, uint8_t lcd_side);
void draw_char(uint16_t x,uint16_t y,uint8_t num, uint32_t color, uint8_t lcd_side,uint8_t sizey);
void draw_string(uint16_t x,uint16_t y,const char *p, uint32_t color, uint8_t lcd_side,uint8_t sizey);
void draw_allcircle(uint16_t x0,uint16_t y0,uint8_t r, uint32_t color, uint8_t lcd_side);
void show_eye(uint16_t x0,uint16_t y0,uint8_t r, uint32_t color, uint8_t lcd_side);
