
#include "show.h"
#include "data.h"
#include "string.h"
#include "ostest.h"
#include "bsp.h"

#define WELCOME_STR         (u8*)"׼������"
#define TEST_STR            (u8*)"������.."
#define FIND_STR            (u8*)"�ҵ㣺"
#define TP1_STR     		(u8*)"TP1:"
#define TP2_STR     		(u8*)"TP2:"
#define DATA_STR    		(u8*)"Data:"
#define TITLE               (u8*)"TP1 TP2 DATA RES"

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

void show_item(u8 line, u8 page)
{
    u8 temp[10] = {0};
	u8 len=0,temp_str[10] = {0};
    
    len = number_to_str(temp,error_result[page].tp1);
	str_reverse(temp,temp_str,len);
    lcd12864_display_char(line,0,temp_str); 
    memset(temp,0,6);
    
    len = number_to_str(temp,error_result[page].tp2);
	str_reverse(temp,temp_str,len);
    lcd12864_display_char(line,2,temp_str); 
    memset(temp,0,6);
    
    len = number_to_str(temp,error_result[page].data);
	str_reverse(temp,temp_str,len);
    lcd12864_display_char(line,4,temp_str);
}

void show_page1(u8 page)
{
    
    lcd12864_clear_line(0);
    lcd12864_clear_line(1);
	lcd12864_clear_line(2);
    lcd12864_clear_line(3);
    
    lcd12864_display_char(0,0,TITLE);
    show_item(1,page);
    show_item(2,page+1);
    show_item(3,page+2);
}

void show_page(u8 page)
{
    u8 temp[10] = {0};
	u8 len=0,temp_str[10] = {0};
    lcd12864_clear_line(0);
    lcd12864_clear_line(1);
	lcd12864_clear_line(2);
    lcd12864_clear_line(3);
    
    /* tp1 */
    lcd12864_display_char(0,0,TP1_STR);  
    len = number_to_str(temp,error_result[page].tp1);
	str_reverse(temp,temp_str,len);
    lcd12864_display_char(0,3,temp_str); 
    memset(temp,0,6);
    
    /* tp2 */
    lcd12864_display_char(1,0,TP2_STR);
    len = number_to_str(temp,error_result[page].tp2);
	str_reverse(temp,temp_str,len);
    lcd12864_display_char(1,3,temp_str); 
    memset(temp,0,6);
    
    /* data */
    lcd12864_display_char(2,0,DATA_STR);
    len = number_to_str(temp,error_result[page].data);
	str_reverse(temp,temp_str,len);
    lcd12864_display_char(2,3,temp_str); 
    
    if(error_result[page].res_uint == UINT_0R)
    {
        lcd12864_display_char(3,0,(u8*)"Uint: ŷ"); 
    }
    else
    {
        lcd12864_display_char(3,0,(u8*)"Uint: ǧŷ"); 
    }
}

void show_error(u16 type)
{
	/* show error */
}

void show_result(void)
{
    if(test_result.all_result == PASS)
    {
        /* pass */
        show_pass();
		PWR24V_CTR(LED_FAIL_OFF, OFF);
		PWR24V_CTR(LED_PASS_ON, ON);
    }
    else
    {
        /* fail */
        show_fail();
		PWR24V_CTR(LED_PASS_OFF, OFF);
		PWR24V_CTR(LED_FAIL_ON, ON);
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
    
    PWR24V_CTR(CYLINDER_3_ON, ON);
    delay_ms(200);
    PWR24V_CTR(CYLINDER_1_ON, ON); 
    delay_ms(200);
    PWR24V_CTR(CYLINDER_2_ON, ON); 
    PWR24V_CTR(CYLINDER_3_OFF, OFF);
    
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
        else
        {
            lcd12864_clear_line(1);
            lcd12864_clear_line(2);
            lcd12864_clear_line(3);
        }
		/* check key */
		key = show_key_scan();
		if(key == KEY_MENU_SHORT) break;
	}
    
    /* release inhale */
    PWR24V_CTR(CYLINDER_2_OFF, OFF);
    delay_ms(100);
    PWR24V_CTR(CYLINDER_1_OFF, OFF);
    delay_ms(100);
    PWR24V_CTR(CYLINDER_3_OFF, OFF);
}

void show_main(void)
{
	u8 key = 0;
	/* check key */
	key = show_key_scan();
	switch(key)
	{
		case KEY_MENU_SHORT:
			if(test_result.complete_flag)
			{
				show_page(page);
				if(++page >= test_result.err_times) page = 0;
			}
			break;

		case KEY_MENU_LONG:
			show_find_point();
            show_init();
			break;
			
		default: break;
	}	
}


void show_init(void)
{
    lcd12864_clear_line(0);
    lcd12864_clear_line(1);
    lcd12864_clear_line(2);
    lcd12864_clear_line(3);
    lcd12864_display_char(1,2,WELCOME_STR);
}

void show_test(void)
{
    lcd12864_clear_line(0);
    lcd12864_clear_line(1);
    lcd12864_clear_line(2);
    lcd12864_clear_line(3);
    lcd12864_display_char(1,2,TEST_STR);
	PWR24V_CTR(LED_PASS_OFF, OFF);
	PWR24V_CTR(LED_FAIL_OFF, OFF);
}

void show_pass(void)
{
    lcd12864_clear_line(0);
    lcd12864_clear_line(1);
    lcd12864_clear_line(2);
    lcd12864_clear_line(3);
    lcd12864_display_char(1,3,PASS_STR);
}

void show_fail(void)
{
    lcd12864_clear_line(0);
    lcd12864_clear_line(1);
    lcd12864_clear_line(2);
    lcd12864_clear_line(3);
    lcd12864_display_char(1,3,FAIL_STR);
}

