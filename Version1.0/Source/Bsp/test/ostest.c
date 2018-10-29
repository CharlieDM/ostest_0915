
#include "bsp.h"
#include "data.h"
#include "ostest.h"
#include "string.h"
#include "show.h"

/* gobal var */
Item_result_t item_result[1000] = {0};
Test_result_t test_result = {0};

/*2 40 10pin 30pin 40pad*/
OsChain_t painchain[PANEL_2_LEN] = {0};		/* pain 2*/
OsChain_t open_40_chain[CHAIN_40_LEN] = {0};/* 40 point 1 to 1 test*/
OsChain_t short_10_chain[1] = {0};		/* 10 connet */
OsChain_t short_30_chain[1] = {0};		/* 30 connet */
OsChain_t short_40_chain[1] = {0};		/* 40 pad */

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
    u8 j=0;
    u16 tp1=0,tp2=0,adcx=0;
    float w4_v=0,w4_cur=0,w4_res=0;
    
    fct_swtich(FCT_4W_EN5);
	/* panel 1 */
    isolate_switch(ISOLATE_1);
    tp1 = painchain[0].point[0];
	tp2 = painchain[0].point[1];
    switch_testpoint(TPA,tp1);
    switch_testpoint(TPB,tp2);
    for(j=0; j<3; j++)
	{
        adcx = tm7705_read_data(CHIP0,CHANNEL0);
        w4_cur = (adcx-32767)*50/65535; /* ma */
        adcx = tm7705_read_data(CHIP0,CHANNEL1);
        w4_v = (adcx-32767)*5000/65535; /* mv */
        w4_res = w4_v/w4_cur;
        if(w4_res > THRESHOLD_PANEL + compensate.open_offset[0])
        {
            item_result[test_result.times].data = w4_res;
            item_result[test_result.times].tp1 = tp1;
            item_result[test_result.times].tp2 = tp2;
            item_result[test_result.times].result = FAIL;
            test_result.all_result = FAIL;
        }
        else
        {
            item_result[test_result.times].data = w4_res;
            item_result[test_result.times].tp1 = tp1;
            item_result[test_result.times].tp2 = tp2;
            item_result[test_result.times].result = PASS;
        }
    }
    test_result.times++;
    
    /* panel 2 */
    isolate_switch(ISOLATE_2);
    tp1 = painchain[1].point[0];
	tp2 = painchain[1].point[1];
    switch_testpoint(TPA,tp1);
    switch_testpoint(TPB,tp2);
    for(j=0; j<3; j++)
	{
        adcx = tm7705_read_data(CHIP0,CHANNEL0);
        w4_cur = (adcx-32767)*50/65535; /* ma */
        adcx = tm7705_read_data(CHIP0,CHANNEL1);
        w4_v = (adcx-32767)*5000/65535; /* mv */
        w4_res = w4_v/w4_cur;
        if(w4_res > THRESHOLD_PANEL + compensate.open_offset[1])
        {
            item_result[test_result.times].data = w4_res;
            item_result[test_result.times].tp1 = tp1;
            item_result[test_result.times].tp2 = tp2;
            item_result[test_result.times].result = FAIL;
            test_result.all_result = FAIL;
        }
        else
        {
            item_result[test_result.times].data = w4_res;
            item_result[test_result.times].tp1 = tp1;
            item_result[test_result.times].tp2 = tp2;
            item_result[test_result.times].result = PASS;
        }
    }
    test_result.times++;
    
    isolate_switch(ISOLATE_OFF);
    fct_swtich(FCT_OFF);
}

void os_test(void)
{
	u8 i=0,ia=0,j=0;
	u16 tp1=0,tp2=0,value=0;
	
	/* open test 40pad <-> 10,30connector */
	fct_swtich(FCT_100R_EN3);
	for(i=0; i<CHAIN_40_LEN; i++)
	{
		tp1 = open_40_chain[i].point[0];
		tp2 = open_40_chain[i].point[1];
		switch_testpoint(TPA,tp1);
		switch_testpoint(TPB,tp2);
		for(j=0; j<3; j++)
		{
			value = fct_get_data(FCT_ADC3_IN);
			if( value > THRESHOLD_OPEN + compensate.open_offset[test_result.times])
			{
				item_result[test_result.times].data = value;
				item_result[test_result.times].tp1 = tp1;
				item_result[test_result.times].tp2 = tp2;
				item_result[test_result.times].result = FAIL;
				test_result.all_result = FAIL;
			}
			else
			{
				item_result[test_result.times].data = value;
				item_result[test_result.times].tp1 = tp1;
				item_result[test_result.times].tp2 = tp2;
				item_result[test_result.times].result = PASS;
			}
		}
		test_result.times++;	
	}

	/* short test 10connector */
	fct_swtich(FCT_1M_EN2);
	for(i=0; i<CONNECT_10_LEN; i+=2)
	{
		tp1 = short_10_chain[0].point[i];
		tp2 = short_10_chain[0].point[i+1];
		switch_testpoint(TPA,tp1);
		switch_testpoint(TPB,tp2);
		for(j=0; j<3; j++)
		{
			value = fct_get_data(FCT_ADC2_IN);
			if( value < THRESHOLD_SHORT + compensate.short_offset)
			{
				item_result[test_result.times].data = value;
				item_result[test_result.times].tp1 = tp1;
				item_result[test_result.times].tp2 = tp2;
				item_result[test_result.times].result = FAIL;
				test_result.all_result = FAIL;
			}
			else
			{
				item_result[test_result.times].data = value;
				item_result[test_result.times].tp1 = tp1;
				item_result[test_result.times].tp2 = tp2;
				item_result[test_result.times].result = PASS;
			}
		}
		test_result.times++;
	}

	/* short test 30connector */
	fct_swtich(FCT_1M_EN2);
	for(i=0; i<CONNECT_30_LEN; i+=2)
	{
		tp1 = short_30_chain[0].point[i];
		tp2 = short_30_chain[0].point[i+1];
		switch_testpoint(TPA,tp1);
		switch_testpoint(TPB,tp2);
		for(j=0; j<3; j++)
		{
			value = fct_get_data(FCT_ADC2_IN);
			if( value < THRESHOLD_SHORT + compensate.short_offset)
			{
				item_result[test_result.times].data = value;
				item_result[test_result.times].tp1 = tp1;
				item_result[test_result.times].tp2 = tp2;
				item_result[test_result.times].result = FAIL;
				test_result.all_result = FAIL;
			}
			else
			{
				item_result[test_result.times].data = value;
				item_result[test_result.times].tp1 = tp1;
				item_result[test_result.times].tp2 = tp2;
				item_result[test_result.times].result = PASS;
			}
		}
		test_result.times++;
	}

	/* short test 40pad */
	fct_swtich(FCT_1M_EN2);
	for(i=0; i<PAD_40_LEN; i++)
	{
		tp1 = short_40_chain[0].point[i];
		for(ia=i+1; ia<PAD_40_LEN; ia++)
		{
			tp2 = short_40_chain[0].point[ia];
			switch_testpoint(TPA,tp1);
			switch_testpoint(TPB,tp2);
			for(j=0; j<3; j++)
			{
				value = fct_get_data(FCT_ADC2_IN);
				if( value < THRESHOLD_SHORT + compensate.short_offset)
				{
					item_result[test_result.times].data = value;
					item_result[test_result.times].tp1 = tp1;
					item_result[test_result.times].tp2 = tp2;
					item_result[test_result.times].result = FAIL;
					test_result.all_result = FAIL;
				}
				else
				{
					item_result[test_result.times].data = value;
					item_result[test_result.times].tp1 = tp1;
					item_result[test_result.times].tp2 = tp2;
					item_result[test_result.times].result = PASS;
				}
			}
			test_result.times++;
		}
	}
	
    /* fct off */
	fct_swtich(FCT_OFF);
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
    u16 times=0;
	
    /* update UI */
    show_test();
    
    /* move */
    PWR24V_CTR(CYLINDER_1_ON, ON);
    PWR24V_CTR(CYLINDER_2_ON, ON);
    while(1)
    {
        if(Din_Status(KEY_PLACE1)) break;
        if(Din_Status(KEY_PLACE2)) { show_init(); PWR24V_CTR(CYLINDER_1_OFF, OFF); PWR24V_CTR(CYLINDER_2_OFF, OFF); return; }
        if(times++ > 2000) { break; } 
        delay_ms(1);
    }    
    
    /* hold inhale */
    PWR24V_CTR(CYLINDER_3_ON, ON);
	test_result.complete_flag = 0;
	test_result.times = 0;
	test_result.all_result = PASS;
    
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
	test_result.complete_flag = 1;
    show_result();
}

