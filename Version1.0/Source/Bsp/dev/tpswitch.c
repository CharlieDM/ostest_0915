#include "tpswitch.h"
#include "74HC595.h"

u8 test_point[97] = 
{
     0,
     1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
    51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
    61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
    71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
    81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
    91, 92, 93, 94, 95, 96
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




