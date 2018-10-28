
#include "show.h"
#include "data.h"
#include "string.h"
#include "ostest.h"
#include "bsp.h"

#define WELCOME_STR         (u8*)"准备测试"
#define TEST_STR            (u8*)"测试中.."
#define FIND_STR            (u8*)"找点："
#define TP1_STR     		(u8*)"TP1:"
#define TP2_STR     		(u8*)"TP2:"
#define DATA_STR    		(u8*)"Data:"

static u8 page = 0;

u8 show_key_scan(void)
{
	u16 pressedtimes = 0;
	if(Din_Status(KEY_MENU) == 1)
	{
		delay_ms(10);
		while(Din_Status(KEY_MENU) == 1)
		{
			pressedtimes++;
			delay_ms(1);
		}
		if(pressedtimes > 1500)	return KEY_MENU_LONG;
		else return KEY_MENU_SHORT;
	}
	return 0;
}

void show_page(u8 page)
{
    u8 temp[6] = {0};
    lcd12864_clear_line(0);
    lcd12864_clear_line(1);
	lcd12864_clear_line(2);
    
    /* tp1 */
    lcd12864_display_char(0,0,TP1_STR);  
    number_to_str(temp,10);
    lcd12864_display_char(0,3,temp); 
    memset(temp,0,6);
    
    /* tp2 */
    lcd12864_display_char(1,0,TP2_STR);
    number_to_str(temp,33);
    lcd12864_display_char(1,3,temp); 
    memset(temp,0,6);
    
    /* data */
    lcd12864_display_char(2,0,DATA_STR);
    number_to_str(temp,545);
    lcd12864_display_char(2,3,temp); 
}

void show_error(u16 type)
{
	/* show error */
}

void show_result(void)
{
    if(test_all_result == 0xFF)
    {
        /* pass */
        show_pass();
    }
    else
    {
        /* fail */
        show_fail();
    }	
	page = 0;
}

void show_find_point(void)
{
	u8 key=0;
    u8 i=0,j=0,num=0,len=0,pos=0;
	u8 point[86] = {0};    
    u8 temp[3] = {0};
    u8 temp_str[48] = {0x20};
    
    lcd12864_clear();
    lcd12864_display_char(0,0,FIND_STR); 
    
	while (1)
	{
		/* find point */
		num = find_point(point);
		if(point[0])
		{
            /* clear show */
			/* show number */
			for(i=0;i<num;i++)
            {
                len = number_to_str(temp,point[i]);
                for(j=0; j<len; j++)
                {
                    pos += j;
                    temp_str[pos] = temp[len-j-1];
                }
                temp_str[++pos] = 0x20;
                ++pos;
                memset(temp,0,3);
            }  
            lcd12864_display_char(1,0,temp_str); 
            pos = 0;
            /* clear */
            memset(temp_str,0x20,48);			
			memset(point,0,86);
		}
		/* check key */
		key = show_key_scan();
		if(key == KEY_MENU_SHORT) break;
	}
}

void show_main(void)
{
	u8 key = 0;
	/* check key */
	key = show_key_scan();
	switch(key)
	{
		case KEY_MENU_SHORT:
			if(test_all_result)
			{
				show_page(page);
				if(page++ > test_times) page = 0;
			}
			break;

		case KEY_MENU_LONG:
			show_find_point();
			break;
			
		default: break;
	}	
}


void show_init(void)
{
    lcd12864_clear_line(1);
    lcd12864_display_char(1,2,WELCOME_STR);
}

void show_test(void)
{
    lcd12864_clear_line(1);
    lcd12864_display_char(1,2,TEST_STR);
}

void show_pass(void)
{
    lcd12864_clear_line(1);
    lcd12864_display_char(1,3,PASS_STR);
}

void show_fail(void)
{
    lcd12864_clear_line(1);
    lcd12864_display_char(1,3,FAIL_STR);
}

