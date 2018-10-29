#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"

//IO��������
#define SDA_IN()  {GPIOD->CRH&=0xFFFFFF0F;GPIOD->CRH|=0x00000080;GPIOD->ODR=1<<9;}
#define SDA_OUT() {GPIOD->CRH&=0xFFFFFF0F;GPIOD->CRH|=0x00000030;}

//IO��������	 
#define IIC_SCL    PDout(8) //SCL
#define IIC_SDA    PDout(9) //SDA	 
#define READ_SDA   PDin(9)  //����SDA 

//IIC���в�������
void iic_init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

#endif
