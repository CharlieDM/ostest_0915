#include "tpswitch.h"
#include "74HC595.h"

u8 test_point[97] = 
{
     0,
     1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    31, 32, 76, 65, 66, 67, 68, 69, 70, 71,
    72, 73, 74, 75, 34, 61, 35, 60, 36, 59,
    37, 58, 38, 57, 39, 56, 40, 55, 41, 54,
    42, 53, 43, 52, 44, 51, 45, 50, 46, 49,
    33, 62, 47, 48, 95, 88, 94, 89, 93, 90,
    96, 87, 92, 91, 85, 86 
};  

void switch_testpoint(TP_TYPE tp_type , uint16_t point)
{
	uint16_t tp = test_point[point];
	
	if(tp_type == TPA)
	{
		if(tp == 0)
		{
			HC595SendData(SW1_A , PIN_ALL_OFF);
			HC595SendData(SW2_A , PIN_ALL_OFF);
			HC595SendData(SW3_A , PIN_ALL_OFF);
			HC595SendData(SW4_A , PIN_ALL_OFF);		
		}
		else if((tp > 0) && (tp <= 32))
		{
			HC595SendData(SW1_A , tp);
			HC595SendData(SW2_A , PIN_ALL_OFF);
			HC595SendData(SW3_A , PIN_ALL_OFF);
			HC595SendData(SW4_A , PIN_ALL_OFF);
		}
		else if((tp > 32) && (tp <= 64))
		{
			HC595SendData(SW1_A , PIN_ALL_OFF);
			HC595SendData(SW2_A , tp - 32);
			HC595SendData(SW3_A , PIN_ALL_OFF);
			HC595SendData(SW4_A , PIN_ALL_OFF);			
		}
		else if((tp > 64) && (tp <= 96))
		{
			HC595SendData(SW1_A , PIN_ALL_OFF);
			HC595SendData(SW2_A , PIN_ALL_OFF);
			HC595SendData(SW3_A , tp - 64);
			HC595SendData(SW4_A , PIN_ALL_OFF);			
		}
		else
		{
			HC595SendData(SW1_A , PIN_ALL_OFF);
			HC595SendData(SW2_A , PIN_ALL_OFF);
			HC595SendData(SW3_A , PIN_ALL_OFF);
			HC595SendData(SW4_A , tp - 96);				
		}
	}
	else if(tp_type == TPB)
	{
		if(tp == 0)
		{
			HC595SendData(SW1_B , PIN_ALL_OFF);
			HC595SendData(SW2_B , PIN_ALL_OFF);
			HC595SendData(SW3_B , PIN_ALL_OFF);
			HC595SendData(SW4_B , PIN_ALL_OFF);		
		}
		else if((tp > 0) && (tp <= 32))
		{
			HC595SendData(SW1_B , tp);
			HC595SendData(SW2_B , PIN_ALL_OFF);
			HC595SendData(SW3_B , PIN_ALL_OFF);
			HC595SendData(SW4_B , PIN_ALL_OFF);
		}
		else if((tp > 32) && (tp <= 64))
		{
			HC595SendData(SW1_B , PIN_ALL_OFF);
			HC595SendData(SW2_B , tp - 32);
			HC595SendData(SW3_B , PIN_ALL_OFF);
			HC595SendData(SW4_B , PIN_ALL_OFF);			
		}
		else if((tp > 64) && (tp <= 96))
		{
			HC595SendData(SW1_B , PIN_ALL_OFF);
			HC595SendData(SW2_B , PIN_ALL_OFF);
			HC595SendData(SW3_B , tp - 64);
			HC595SendData(SW4_B , PIN_ALL_OFF);			
		}
		else
		{
			HC595SendData(SW1_B , PIN_ALL_OFF);
			HC595SendData(SW2_B , PIN_ALL_OFF);
			HC595SendData(SW3_B , PIN_ALL_OFF);
			HC595SendData(SW4_B , tp - 96);				
		}
	}
	else if(tp_type == ADDITIONAL_TP)
	{
		HC595SendData(SW_OTHER , ADDITIONAL_TP);	
	}

}




