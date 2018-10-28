#include "io.h"
#include "sys.h" 
#include "delay.h"

#define GPIOA_OUT_PP_PORTS			H595_RCLK_PIN|H595_SRCLK_PIN|H595_DAT_PIN|\
									LCD_BL_PIN|AD_EN_PIN|RUN_PIN	
#define GPIOA_IN_FLOATING_PORTS		

#define GPIOB_OUT_PP_PORTS			A595_RCLK_PIN|E595_SRCLK_PIN|E595_DAT_PIN|\
									PWR595_RCLK_PIN|PWR595_SRCLK_PIN|TM7705_NSS1_PIN
#define GPIOB_IN_FLOATING_PORTS		KEY3_PIN|KEY4_PIN
#define GPIOB_IPU_PORTS				TM7705_DRDY1_PIN
#define SPI3_PORTS	                TM7705_SCK_PIN|TM7705_MISO_PIN|TM7705_MOSI_PIN

#define GPIOC_OUT_PP_PORTS			C595_RCLK_PIN|G595_RCLK_PIN|G595_SRCLK_PIN|G595_DAT_PIN
#define GPIOC_IN_FLOATING_PORTS		KEY1_PIN|KEY2_PIN|IN3_PIN|IN4_PIN|IN5_PIN|IN6_PIN

#define GPIOD_OUT_PP_PORTS			C595_SRCLK_PIN|C595_DAT_PIN|D595_RCLK_PIN|D595_SRCLK_PIN|\
									D595_DAT_PIN|E595_RCLK_PIN|T595_DAT_PIN|T595_RCLK_PIN|\
									T595_SRCLK_PIN|TM7705_NSS0_PIN
#define GPIOD_IN_FLOATING_PORTS		IN0_PIN|IN1_PIN|IN2_PIN
#define GPIOD_IPU_PORTS				TM7705_DRDY0_PIN

#define GPIOE_OUT_PP_PORTS			F595_RCLK_PIN|F595_SRCLK_PIN|F595_DAT_PIN|TEST_EN1_PIN|\
									TEST_EN2_PIN|TEST_EN3_PIN|TEST_EN4_PIN|A595_SRCLK_PIN|\
									A595_DAT_PIN|B595_RCLK_PIN|B595_SRCLK_PIN|B595_DAT_PIN|\
									SW_1D8V_PIN|SW_3D3V_PIN|SW_5V_PIN|PWR595_DAT_PIN
#define GPIOE_IN_FLOATING_PORTS

void io_init(void) 
{ 
 	GPIO_InitTypeDef  GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
    //GPIOA	
	GPIO_InitStructure.GPIO_Pin = GPIOA_OUT_PP_PORTS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					
	GPIO_ResetBits(GPIOA,GPIOA_OUT_PP_PORTS);

	GPIO_InitStructure.GPIO_Pin = IN7_PIN;				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	
	GPIO_Init(GPIOA, &GPIO_InitStructure);

//GPIOB
	GPIO_InitStructure.GPIO_Pin = GPIOB_OUT_PP_PORTS;				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);					
	GPIO_ResetBits(GPIOB,GPIOB_OUT_PP_PORTS);

	GPIO_InitStructure.GPIO_Pin = GPIOB_IN_FLOATING_PORTS;				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIOB_IPU_PORTS;				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIOB_IPU_PORTS);
    
    GPIO_InitStructure.GPIO_Pin = SPI3_PORTS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOB, SPI3_PORTS);

//GPIOC	
	GPIO_InitStructure.GPIO_Pin = GPIOC_OUT_PP_PORTS;				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);					
	GPIO_ResetBits(GPIOC,GPIOC_OUT_PP_PORTS);

	GPIO_InitStructure.GPIO_Pin = GPIOC_IN_FLOATING_PORTS;				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
//GPIOD
	GPIO_InitStructure.GPIO_Pin = GPIOD_OUT_PP_PORTS;				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);					
	GPIO_ResetBits(GPIOD,GPIOD_OUT_PP_PORTS);

	GPIO_InitStructure.GPIO_Pin = GPIOD_IN_FLOATING_PORTS;				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIOD_IPU_PORTS;				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	
	GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_SetBits(GPIOD,GPIOD_IPU_PORTS);
	
//GPIOE
	GPIO_InitStructure.GPIO_Pin = GPIOE_OUT_PP_PORTS;				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);					
	GPIO_ResetBits(GPIOE,GPIOE_OUT_PP_PORTS);
}


