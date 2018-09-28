#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"

//IO方向设置
#define SDA_IN()  {GPIOD->CRH&=0XFFFF0FFF;GPIOD->CRH|=8<<12;}
#define SDA_OUT() {GPIOD->CRH&=0XFFFF0FFF;GPIOD->CRH|=3<<12;}

//IO操作函数	 
#define IIC_SCL    PDout(10) //SCL
#define IIC_SDA    PDout(11) //SDA	 
#define READ_SDA   PDin(11)  //输入SDA 

//IIC所有操作函数
void iic_init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号


u8 IIC_ReadOneBytetype1(u8 Slavewriteaddr,u8 Registeraddr);
u8 IIC_ReadOneBytetype2(u8 Slavewriteaddr,u16 Registeraddr);
void IIC_WriteOneBytetype1(u8 Slavewriteaddr,u8 Registeraddr);
void IIC_WriteOneBytetype2(u8 Slavewriteaddr,u8 Registeraddr,u8 Command);
void IIC_WriteOneBytetype3(u8 Slavewriteaddr,u16 Registeraddr,u8 Command);
void IIC_WriteOneBytetype4(u8 Slavewriteaddr,u16 Registeraddr,u8 Command1,u8 Command2,u8 Command3,u8 Command4,u8 Command5,u8 Command6);
u16 IIC_BurstReadOneByte(u8 Slavewriteaddr,u16 Registeraddr);	  

#endif
