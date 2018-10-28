
#include "bsp.h"
#include "ostest.h"
#include "data.h"
#include "string.h"
#include "show.h"
#include "fct.h"

/* 40 point */
OsChain_t openchain[OPENCHAIN_LEN] = {0};

/* 10pin */
OsChain_t shortchain[SHORTCHAIN_LEN] = {0};
OsChain_t painchain[PANELCHAIN_LEN] = {0};

Compensate_t oscompensate[30] = {0};
Compensate_t panelcompensate[2] = {0};
u8 test_all_result = 0;
Testresult_t result[1000] = {0};
u16 test_times = 0;

u8 array_judge(u16 temp,u8 arraytemp[],u8 chainlength)
{
	u8 temp1=0;
	u8 i;

	for(i=0;i<chainlength;i++)
	{
		if(temp==arraytemp[i])
		temp1=1;	
	}
	return temp1;
}

u8 wait_start_sign(void)
{
    if(Din_Status(KEY_START))
    {
        delay_ms(10);
        if(Din_Status(KEY_START))
        {
            return KEY_START_SHORT;
        }
    }
    return 0;
}

void panel_test(void)
{
//    u32 adcx = 0;
//    u8 i = 0;
//    u8 times = 0;
//    TEST_EN1 = 1;
//    for(i=0; i<2; i++)
//    {
//        tp1_switch(painchain[i].point[0]);
//        delay_us(5);
//        tp2_switch(painchain[i].point[1]);
//        for(times=0; times<3; times++)
//        {
//            adcx = res_value();
//            if(adcx > (THRESHOLD_PANEL+ panelcompensate[i].dir*panelcompensate[i].offset))
//            {
//                result[test_times].result = 0x01;
//            }
//            else
//            {
//                result[test_times].result = 0x00;
//                break;
//            }
//        }        
//        result[test_times].tp1 = painchain[i].point[0];
//        result[test_times].tp2 = painchain[i].point[1];
//        result[test_times].data = adcx;
//        test_times++;
//    }
//    TEST_EN1 = 0;
//    tp_switch_off();
}

void os_test(void)
{
//    u8 i=0,k=0,tp1=0,tp2=0,compensate_pos=0;
//    u32 adcx = 0;
//    
//    /* open test */
//    TEST_EN1 = 1;
//    for(i=0; i<OPENCHAIN_LEN; i++)
//    {
//        tp1_switch(openchain[i].point[0]);
//        delay_us(5);
//        tp2_switch(openchain[i].point[1]);
//        delay_us(5);
//        for(k=0; k<3; k++)
//        {
//            adcx = res_value();
//            if(adcx > (THRESHOLD_OPEN  + oscompensate[compensate_pos].dir*oscompensate[compensate_pos].offset))
//            {
//                result[test_times].result = 0x01;
//            }
//            else
//            {
//                result[test_times].result = 0x00;
//                break;
//            }
//        }
//        result[test_times].tp1 = openchain[i].point[0];
//        result[test_times].tp2 = openchain[i].point[1];
//        result[test_times].data = adcx;
//        compensate_pos++;
//    }
//    tp_switch_off();
//    TEST_EN1 = 0;
//    
//    /* short test */
//    TEST_EN2 = 1;
//    for(i=0; i<SHORTCHAIN_LEN; i++)
//    {
//        for(tp1=0; tp1<shortchain[i].len; tp1++)
//        {
//            tp1_switch(shortchain[i].point[tp1]);
//			delay_us(5);
//            for(tp2=tp1+1; tp2<shortchain[i].len; tp2++)
//            {
//                tp2_switch(shortchain[i].point[tp2]);
//                delay_us(5);
//                for(k=0; k<3; k++)
//                {
//                    adcx = res_value();
//                    if(adcx < THRESHOLD_OPEN)
//                    {
//                        result[test_times].result = 0x01;
//                        result[test_times].tp1 = tp1;
//                        result[test_times].tp2 = tp2;
//                        result[test_times].data = adcx;
//                    }
//                    else
//                    {
//                        result[test_times].result = 0x00;
//                        break;
//                    }
//                }
//                test_times++;                
//            }
//        }
//    }
//    tp_switch_off();
//    TEST_EN2 = 0;
}


u8 find_point(u8 *data)
{
	u8 tp1=0,num=0;
	u32 adcx=0;
    fct_swtich(FCT_100R_EN3);     
	for(tp1=1; tp1<97; tp1++)
    {
        switch_testpoint(TPA,tp1);
		adcx = fct_get_data(FCT_ADC3_IN);
		if(adcx < 500)
		{
			*(data++) = tp1;
            num++;
		}
        delay_us(100);
	}
    fct_swtich(FCT_OFF); 
    return num;
}

void start_test(void)
{
    u16 num=0,i=0;
	
    /* update UI */
    show_test();
    
    /* move */
    PWR24V_CTR(CYLINDER_1_ON, ON);
    PWR24V_CTR(CYLINDER_2_ON, ON);
    while(1)
    {
        if(Din_Status(KEY_PLACE1)) break;
        if(Din_Status(KEY_PLACE2)) { show_init(); PWR24V_CTR(CYLINDER_1_OFF, OFF); PWR24V_CTR(CYLINDER_2_OFF, OFF); return; }
        if(num++ > 2000) { break; } 
        delay_ms(1);
    }    
    
    /* hold inhale */
    PWR24V_CTR(CYLINDER_3_ON, ON);
    test_all_result = 0;
    test_times = 0;
    
    /* panel test */
    panel_test();
    
    /* start open&short test */        
    os_test();
      
    /* release inhale */
    PWR24V_CTR(CYLINDER_3_OFF, OFF);
    delay_ms(100);
    PWR24V_CTR(CYLINDER_2_OFF, OFF);
    delay_ms(100);
    PWR24V_CTR(CYLINDER_1_OFF, OFF);
    
    /* show the result */
    for(i=0; i<test_times; i++)
    {
       if(result[i].result)
       {
            test_all_result = 0x01;
            break;
       }
    }
    show_result();
}

