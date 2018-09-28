#include "tpswitch.h"
#include "data.h"

u8 test_point[TEST_POINT_NUMBER] = 
{
     1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
    51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
    61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
    71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
    81, 82, 83, 84, 85, 86,
};

Switch_t swa_a[] = 
{
    {GPIOD,GPIO_Pin_6},
    {GPIOD,GPIO_Pin_7},
    {GPIOB,GPIO_Pin_3},
    {GPIOB,GPIO_Pin_4},
    {GPIOB,GPIO_Pin_5},
};

Switch_t swa_en[] = 
{
    {GPIOD,GPIO_Pin_5},
    {GPIOD,GPIO_Pin_4},
    {GPIOD,GPIO_Pin_3},
    {GPIOD,GPIO_Pin_2},
};

Switch_t swb_a[] = 
{
    {GPIOE,GPIO_Pin_0},
    {GPIOE,GPIO_Pin_1},
    {GPIOE,GPIO_Pin_2},
    {GPIOE,GPIO_Pin_3},
    {GPIOE,GPIO_Pin_4},
};

Switch_t swb_en[] = 
{
    {GPIOD,GPIO_Pin_0},
    {GPIOD,GPIO_Pin_1},
    {GPIOC,GPIO_Pin_12},
    {GPIOC,GPIO_Pin_15},
};

void tp_switch_init(void) 
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;   
    
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD| \
                           RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF,ENABLE);
    /* SWA_A0 ~ SWA_A4 : PD6,PD7,PB3,PB4,PB5 */
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_ResetBits(GPIOB,GPIO_Pin_3);
    
    /* SWA_EN1 ~ SWA_EN4 : PD5,PD4,PD3,PD2 */
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure);
        
    /* SWB_A0 ~ SWB_A4 : PE0 ~ PE4 */
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOE, &GPIO_InitStructure);
    
    /* SWB_EN1 ~ SWB_EN4 : PD0,PD1,PC12,PA15 */
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);  
    
    /* disable all io */
    tp_switch_off();
}

void tp1_point(u8 enable_chip, u8 port)
{
    u8 i = 0;    
    /* select enbale port */
    for(i=0; i<5; i++)
    {
        if( (port>>i)&0x01 )
        {
            swa_a[i].GPIOx->BSRR = swa_a[i].GPIO_Pin;
        }
        else
        {
            swa_a[i].GPIOx->BRR = swa_a[i].GPIO_Pin;
        }
    }
    
    /* select enbale chip */
    for(i=0; i<4; i++)
    {
        if(i == enable_chip)
        {
            swa_en[i].GPIOx->BSRR = swa_en[i].GPIO_Pin;
        }
        else
        {
            swa_en[i].GPIOx->BRR = swa_en[i].GPIO_Pin;
        }
    }
}

void tp2_point(u8 enable_chip, u8 port)
{
    u8 i = 0;  
    /* select enbale port */
    for(i=0; i<5; i++)
    {
        if( (port>>i)&0x01 )
        {
            swb_a[i].GPIOx->BSRR = swb_a[i].GPIO_Pin;
        }
        else
        {
            swb_a[i].GPIOx->BRR = swb_a[i].GPIO_Pin;
        }
    }
    
    /* select enbale chip */
    for(i=0; i<4; i++)
    {
        if(i == enable_chip)
        {
            swb_en[i].GPIOx->BSRR = swb_en[i].GPIO_Pin;
        }
        else
        {
            swb_en[i].GPIOx->BRR = swb_en[i].GPIO_Pin;
        }
    }
}

void tp_switch_off(void)
{
     u8 i = 0;
    /* disale all chip */
    for(i=0; i<4; i++)
    {
        swa_en[i].GPIOx->BRR = swa_en[i].GPIO_Pin;
        swb_en[i].GPIOx->BRR = swb_en[i].GPIO_Pin;
    }
    
    /* disabe port */
    for(i=0; i<5; i++)
    {
        swa_a[i].GPIOx->BRR = swb_a[i].GPIO_Pin;
        swb_a[i].GPIOx->BRR = swb_a[i].GPIO_Pin;
    }  
}

void tp1_switch(u16 tp1)
{		
    u8 temp = test_point[tp1-1];
    u8 chip = temp/32;
    tp1_point(chip,temp%32-1);
}

void tp2_switch(u16 tp2)
{					  
    u8 temp = test_point[tp2-1];
	u8 chip = temp/32;
    tp1_point(chip,temp%32-1);
}













