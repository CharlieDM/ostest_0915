
#include "io.h"
#include "delay.h"
#include "lcd12864.h"

#define LCD_PORTS       GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7

#define LCD_CS          LCD_NSS_PORT,LCD_NSS_PIN 
#define LCD_DATA        LCD_MOSI_PORT,LCD_MOSI_PIN 
#define LCD_CLK         LCD_SCK_PORT,LCD_SCK_PIN
#define LCD_BL          LCD_BL_PORT,LCD_BL_PIN

const u8 TABLE[]=
{   
0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,         
0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,         
0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,        
0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,       
};

void lcd18264_sendbyte(u8 data)   
{   
    u8 i;   
    for(i=0;i<8;i++)   
    {   
        GPIO_ResetBits(LCD_CLK); 
        if(data&0x80)
            GPIO_SetBits(LCD_DATA);
        else
            GPIO_ResetBits(LCD_DATA);
        data=data<<1;       
        delay_us(10);        
        GPIO_SetBits(LCD_CLK); 
        delay_us(10);        
        GPIO_ResetBits(LCD_CLK);
        delay_us(10);
    }   
}  

void lcd12864_wcmd(u8 cmd)
{
    GPIO_SetBits(LCD_CS);
    delay_ms(1);
    lcd18264_sendbyte(0xF8);
    lcd18264_sendbyte(cmd&0xF0);
    lcd18264_sendbyte((cmd<<4)&0xF0);
    GPIO_ResetBits(LCD_CS);  
    delay_ms(2);
}

void lcd12864_wdata(u8 data)
{
    GPIO_SetBits(LCD_CS);
    delay_ms(1);
    lcd18264_sendbyte(0xFA);
    lcd18264_sendbyte(data&0xF0);
    lcd18264_sendbyte((data<<4)&0xF0);
    GPIO_ResetBits(LCD_CS); 
    delay_ms(2);
}

void lcd12864_io_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );

	GPIO_InitStructure.GPIO_Pin = LCD_PORTS; 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_ResetBits(GPIOB,LCD_PORTS);
    GPIO_SetBits(LCD_BL);
}

void lcd12864_init(void)
{    
    delay_ms(100);
    lcd12864_io_config();

    lcd12864_wcmd(0x30);
    lcd12864_wcmd(0x0C);
    lcd12864_wcmd(0x01);
    delay_ms(20);
    lcd12864_wcmd(0x06); 
}

void lcd12864_clear(void)
{
    u8 i=0;
    lcd12864_wcmd(0x30);
    lcd12864_wcmd(0x80);
    for(i=0;i<64;i++)   
      lcd12864_wdata(0x20);
}

void lcd12864_clear_line(u8 line)
{
    u8 i=0,row=0;
    lcd12864_wcmd(0x30);    
    switch(line)
    {
        case 0:row = 0X80;break;
        case 1:row = 0X90;break;
        case 2:row = 0X88;break;
        case 3:row = 0X98;break;
    }
    lcd12864_wcmd(row);
    for(i=0;i<16;i++)   
      lcd12864_wdata(0x20);
}

void lcd12864_display_char(u8 row, u8 col,u8 *data)
{
    lcd12864_wcmd(0x30);       
    lcd12864_wcmd(TABLE[8*row+col]);      
    while(*data != '\0')     
    {   
        if(col==8)             
        {              
            col=0;   
            row++;   
        }   
        if(row==4) row=0;       
        lcd12864_wcmd(TABLE[8*row+col]);   
        lcd12864_wdata(*data);      
        data++;   
        lcd12864_wdata(*data);   
        data++;   
        col++;   
    }   
}

u8 number_to_str(u8 *str, u32 num)
{
    u8 len=0;
    u32 temp_mod=0;
    do
    {
        temp_mod = num%10;
        num = num/10;
        *(str++) = temp_mod + 0x30;
        len++;
    }while(num);
        
    return len;
}

void str_reverse(u8 *src, u8 *tar, u8 len)
{
	u8 i=0;
	for(i=0; i<len; i++)
	{
		*(tar+i) = *(src+len-i-1);
	}
}

