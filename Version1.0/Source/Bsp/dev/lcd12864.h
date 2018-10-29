#ifndef __LCD12864_H
#define __LCD12864_H	

#include "sys.h"

void lcd12864_init(void);
void lcd12864_display_char(u8 row, u8 col,u8 *data);
void lcd12864_clear(void);
void lcd12864_clear_line(u8 line);

u8 number_to_str(u8 *str, u16 num);
void str_reverse(u8 *src, u8 *tar, u8 len);

#endif 
