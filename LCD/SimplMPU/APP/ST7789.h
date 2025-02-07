#ifndef __ST7789_H__
#define __ST7789_H__


#define LCD_VPIX  320
#define LCD_HPIX  240


void ST7789_Init(void);
void ST7789_Clear(uint16_t rgb);
void ST7789_SetCursor(uint16_t x, uint16_t y);
void ST7789_DrawPoint(uint16_t x, uint16_t y, uint16_t rgb);


void ST7789_DMAClear(uint16_t x, uint16_t y, uint16_t rgb, uint16_t n_rgb);
uint32_t ST7789_DMADone(void);

#endif //__ST7789_H__
