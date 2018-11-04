
#include "bsp.h"
#include "data.h"
#include "ostest.h"
#include "string.h"
#include "show.h"

/* gobal var */
error_result_t error_result[200] = {0};
error_result_t upload_result[200] = {0};
Test_result_t test_result = {0};

/*2 40 10pin 30pin 40pad*/
OsChain_t painchain[PANEL_2_LEN] = 
{
    {1,{85,52}},
    {1,{86,52}},
};	/* pain 2*/

OsChain_t open_40_chain[CHAIN_50_LEN] = 
{
    {2,{1,65}}, {2,{2,12}}, {2,{12,71}},{2,{71,72}}, //1
    {2,{3,56}}, {2,{4,55}}, {2,{5,46}}, {2,{6,8}},   //2
    {2,{8,19}}, {2,{19,32}},{2,{32,66}},{2,{66,52}}, //3
    {2,{52,35}},{2,{35,40}},{2,{40,43}},{2,{43,44}}, //4
    {2,{44,76}},{2,{76,75}},{2,{7,47}}, {2,{9,79}},  //5
    {2,{10,80}},{2,{11,67}},{2,{13,63}},{2,{14,59}}, //6
    {2,{15,57}},{2,{16,54}},{2,{17,51}},{2,{18,45}}, //7
    {2,{20,77}},{2,{21,78}},{2,{22,68}},{2,{23,73}}, //8
    {2,{73,74}},{2,{74,36}},{2,{24,64}},{2,{25,60}}, //9
    {2,{26,58}},{2,{27,50}},{2,{29,49}},{2,{30,41}}, //10
    {2,{41,82}},{2,{82,81}},{2,{31,42}},{2,{42,84}}, //11
    {2,{84,83}},{2,{61,38}},{2,{69,34}},{2,{70,33}}, //12
    {2,{62,37}},{2,{48,39}},
};
/* 40 point 1 to 1 test*/

OsChain_t short_10_chain[1] = 
{
    {30,{71,45,47,49,51,53,55,57,59,61,63,65,67,69,73,72,46,48,50,52,54,56,58,60,62,64,66,68,70,74}},
};		/* 10 connet */
OsChain_t short_30_chain[1] = 
{
    {10,{82,76,78,80,84,81,75,77,79,83}},
};		/* 30 connet */
OsChain_t short_40_chain[1] = 
{
    {44,{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,
        35,36,37,38,39,40,41,42,43,44}},
};		/* 40 pad */

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
    u8 j=0,temp_tresult;
    u16 tp1=0,tp2=0,adcx=0;
    float w4_v=0,w4_cur=0,w4_res=0,value=0;
    
    fct_swtich(FCT_100R_EN3);
    tp1 = painchain[0].point[0];
	tp2 = painchain[0].point[1];
    switch_testpoint(TPA,tp1);
    switch_testpoint(TPB,tp2);
    delay_ms(10);
    value = fct_get_data(FCT_ADC3_IN);
    if(value < 20)
    {
        fct_swtich(FCT_4W_EN5);
        /* panel 1 */
        isolate_switch(ISOLATE_1);
        for(j=0; j<TEST_TIMES; j++)
        {
            adcx = tm7705_read_data(CHIP0,CHANNEL0);
            if(adcx >= 32767)
                w4_v = (adcx-32767)*5000/65535; /* mv */
            else
                w4_v = (32767 - adcx)*5000/65535; /* mv */
                         
            adcx = tm7705_read_data(CHIP0,CHANNEL1);
            w4_cur = (adcx-32767)*50/65535; /* ma */
            w4_res = w4_v/w4_cur;
                  
            if(w4_res > THRESHOLD_PANEL + compensate.open_offset[0])
            {
                temp_tresult = 1;
                delay_ms(10);
            }
            else
            {
                temp_tresult = 0;
                break;
            }
        }
    }
    else
    {
        temp_tresult = 1; 
    }
    if(temp_tresult)
    {
        error_result[test_result.err_times].data = value;
        error_result[test_result.err_times].tp1 = tp1;
        error_result[test_result.err_times].tp2 = tp2;
        error_result[test_result.err_times].result = FAIL;
        error_result[test_result.err_times].res_uint = UINT_0R;
        test_result.err_times++;
    }
    upload_result[test_result.times].data = value;
    upload_result[test_result.times].tp1 = tp1;
    upload_result[test_result.times].tp2 = tp2;
    upload_result[test_result.times].result = FAIL;
    upload_result[test_result.times].res_uint = UINT_0R;
    test_result.times++;
     
    /* panel 2 */
    fct_swtich(FCT_100R_EN3);
    tp1 = painchain[1].point[0];
	tp2 = painchain[1].point[1];
    switch_testpoint(TPA,tp1);
    switch_testpoint(TPB,tp2);
    delay_ms(10);
    value = fct_get_data(FCT_ADC3_IN);
    if(value < 20)
    {
        fct_swtich(FCT_4W_EN5);        
        /* panel 1 */
        isolate_switch(ISOLATE_2);
        for(j=0; j<TEST_TIMES; j++)
        {
            adcx = tm7705_read_data(CHIP0,CHANNEL0);
            if(adcx >= 32767)
                w4_v = (adcx-32767)*5000/65535; /* mv */
            else
                w4_v = (32767 - adcx)*5000/65535; /* mv */
            
            adcx = tm7705_read_data(CHIP0,CHANNEL1);
            w4_cur = (adcx-32767)*50/65535; /* ma */
            w4_res = w4_v/w4_cur;
                            
            if(w4_res > THRESHOLD_PANEL + compensate.open_offset[0])
            {
                temp_tresult = 1;
                delay_ms(10);
            }
            else
            {
                temp_tresult = 0;
                break;
            }
        }
    }
    else
    {
        temp_tresult = 1; 
    }
    if(temp_tresult)
    {
        error_result[test_result.err_times].data = value;
        error_result[test_result.err_times].tp1 = tp1;
        error_result[test_result.err_times].tp2 = tp2;
        error_result[test_result.err_times].result = FAIL;
        error_result[test_result.err_times].res_uint = UINT_0R;
        test_result.err_times++;
    }
    upload_result[test_result.times].data = value;
    upload_result[test_result.times].tp1 = tp1;
    upload_result[test_result.times].tp2 = tp2;
    upload_result[test_result.times].result = FAIL;
    upload_result[test_result.times].res_uint = UINT_0R;
    test_result.times++;
    
    isolate_switch(ISOLATE_OFF);
    fct_swtich(FCT_OFF);
}

void os_test(void)
{
	u8 i=0,j=0,temp_tresult=0;
	u16 tp1=0,tp2=0,value=0;
	
	/* open test 40pad <-> 10,30connector */
	fct_swtich(FCT_100R_EN3);
	for(i=0; i<CHAIN_50_LEN; i++)
	{
		tp1 = open_40_chain[i].point[0];
		tp2 = open_40_chain[i].point[1];
		switch_testpoint(TPA,tp1);
		switch_testpoint(TPB,tp2);
        delay_ms(8);
		for(j=0; j<TEST_TIMES; j++)
		{
			value = fct_get_data(FCT_ADC3_IN);
			if( value > THRESHOLD_OPEN + compensate.open_offset[test_result.err_times])
			{ 
                temp_tresult = 1;
                delay_ms(10);  
			}
			else
			{
                temp_tresult = 0;
                break;
			}
		}
        if(temp_tresult)
        {
            error_result[test_result.err_times].data = value;
            error_result[test_result.err_times].tp1 = tp1;
            error_result[test_result.err_times].tp2 = tp2;
            error_result[test_result.err_times].result = FAIL;
            error_result[test_result.err_times].res_uint = UINT_0R;
            test_result.err_times++;
        }
        upload_result[test_result.times].data = value;
        upload_result[test_result.times].tp1 = tp1;
        upload_result[test_result.times].tp2 = tp2;
        upload_result[test_result.times].result = FAIL;
        upload_result[test_result.times].res_uint = UINT_0R;
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
        delay_ms(8);
		for(j=0; j<TEST_TIMES; j++)
		{
			value = fct_get_data(FCT_ADC2_IN);
			if( value < THRESHOLD_SHORT + compensate.short_offset)
			{
                temp_tresult = 1;
                delay_ms(10);  
			}
			else
			{
                temp_tresult = 0;
                break;
			}
		}
        if(temp_tresult)
        {
            error_result[test_result.err_times].data = value;
            error_result[test_result.err_times].tp1 = tp1;
            error_result[test_result.err_times].tp2 = tp2;
            error_result[test_result.err_times].result = FAIL;
            error_result[test_result.err_times].res_uint = UINT_0R;
            test_result.err_times++;
        }
        upload_result[test_result.times].data = value;
        upload_result[test_result.times].tp1 = tp1;
        upload_result[test_result.times].tp2 = tp2;
        upload_result[test_result.times].result = FAIL;
        upload_result[test_result.times].res_uint = UINT_0R;
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
        delay_ms(8);
		for(j=0; j<TEST_TIMES; j++)
		{
			value = fct_get_data(FCT_ADC2_IN);
			if( value < THRESHOLD_SHORT + compensate.short_offset)
			{
				temp_tresult = 1;
                delay_ms(10);  
			}
			else
			{
                temp_tresult = 0;
                break;
			}
		}
        if(temp_tresult)
        {
            error_result[test_result.err_times].data = value;
            error_result[test_result.err_times].tp1 = tp1;
            error_result[test_result.err_times].tp2 = tp2;
            error_result[test_result.err_times].result = FAIL;
            error_result[test_result.err_times].res_uint = UINT_0R;
            test_result.err_times++;
        }
        upload_result[test_result.times].data = value;
        upload_result[test_result.times].tp1 = tp1;
        upload_result[test_result.times].tp2 = tp2;
        upload_result[test_result.times].result = FAIL;
        upload_result[test_result.times].res_uint = UINT_0R;
        test_result.times++;
	}

	/* short test 40pad */
    fct_swtich(FCT_1M_EN2);
	for(i=0; i<CONNECT_30_LEN; i+=2)
	{
		tp1 = short_40_chain[0].point[i];
		tp2 = short_40_chain[0].point[i+1];
		switch_testpoint(TPA,tp1);
		switch_testpoint(TPB,tp2);        
		for(j=0; j<TEST_TIMES; j++)
		{
			value = fct_get_data(FCT_ADC2_IN);
			if( value < THRESHOLD_SHORT + compensate.short_offset)
			{
				temp_tresult = 1;
                delay_ms(10);  
			}
			else
			{
                temp_tresult = 0;
                break;
			}
		}
        if(temp_tresult)
        {
            error_result[test_result.err_times].data = value;
            error_result[test_result.err_times].tp1 = tp1;
            error_result[test_result.err_times].tp2 = tp2;
            error_result[test_result.err_times].result = FAIL;
            error_result[test_result.err_times].res_uint = UINT_0R;
            test_result.err_times++;
        }
        upload_result[test_result.times].data = value;
        upload_result[test_result.times].tp1 = tp1;
        upload_result[test_result.times].tp2 = tp2;
        upload_result[test_result.times].result = FAIL;
        upload_result[test_result.times].res_uint = UINT_0R;
        test_result.times++;
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
		adcx = get_adc(FCT_ADC3_IN);
		if(adcx < 500)
		{
			*(data++) = test_point[tp1];
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
    PWR24V_CTR(CYLINDER_3_ON, ON);
    delay_ms(200);
    PWR24V_CTR(CYLINDER_1_ON, ON);    
    while(1)
    {
        if(Din_Status(KEY_PLACE1)) break;
        if(Din_Status(KEY_PLACE2)) 
        {   
            show_init(); 
            PWR24V_CTR(CYLINDER_3_OFF, OFF);
            delay_ms(100);
            PWR24V_CTR(CYLINDER_2_OFF, OFF);
            delay_ms(100);
            PWR24V_CTR(CYLINDER_1_OFF, OFF);            
            return; 
        }
        if(times++ > 2000) { break; } 
        delay_ms(1);
    }    
    PWR24V_CTR(CYLINDER_2_ON, ON);
    delay_ms(100);
    /* hold inhale */
   
	test_result.complete_flag = 0;
	test_result.err_times = 0;
	test_result.all_result = PASS;
    
    /* panel test */
    panel_test();
    
    /* start open&short test */        
    os_test();
      
    /* release inhale */
    PWR24V_CTR(CYLINDER_2_OFF, OFF);
    delay_ms(100);
    PWR24V_CTR(CYLINDER_1_OFF, OFF);
    delay_ms(100);
    PWR24V_CTR(CYLINDER_3_OFF, OFF);
    
    /* show the result */
	test_result.complete_flag = 1;
    show_result();
}

