#include "iic.h"
#include "delay.h"

//初始化IIC
void iic_init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD,GPIO_Pin_10|GPIO_Pin_11); 	//PB10,PB11 输出高
}
//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(100);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(100);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(100);
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	delay_us(100);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	IIC_SDA=1;delay_us(100);	   
	IIC_SCL=1;delay_us(100);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(100);
	IIC_SCL=1;
	delay_us(100);
	IIC_SCL=0;
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(100);
	IIC_SCL=1;
	delay_us(100);
	IIC_SCL=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		delay_us(10);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		delay_us(10); 
		IIC_SCL=0;	
		delay_us(10);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(50);

		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(50); 
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}
//在IIC芯片指定地址读出一个数据(type1)
//Slavewriteaddr:器件地址+写操作位
//Registeraddr:寄存器地址 1byte  
//返回值  :读到的数据
u8 IIC_ReadOneBytetype1(u8 Slavewriteaddr,u8 Registeraddr)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();  
	IIC_Send_Byte(Slavewriteaddr);	   //发送写命令
	IIC_Wait_Ack();
	IIC_Send_Byte(Registeraddr);//发送寄存器地址
	IIC_Wait_Ack();		  
	IIC_Start();  	 	   
	IIC_Send_Byte(Slavewriteaddr+1);           //进入接收模式			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//产生一个停止条件	    
	return temp;
}
//在IIC芯片指定地址读出一个数据(type2)
//Slavewriteaddr:器件地址+写操作位
//Registeraddr:寄存器地址 2byte  
//返回值  :读到的数据
u8 IIC_ReadOneBytetype2(u8 Slavewriteaddr,u16 Registeraddr)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();  
	IIC_Send_Byte(Slavewriteaddr);	    		//发送slave address
	IIC_Wait_Ack();
	IIC_Send_Byte(Registeraddr>>8);				//发送高地址
	IIC_Wait_Ack();
    IIC_Send_Byte(Registeraddr%256);   			//发送低地址
	IIC_Wait_Ack(); 	 							
	IIC_Start();  	 	   
	IIC_Send_Byte(Slavewriteaddr+1);			//进入接收模式			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//产生一个停止条件	    
	return temp;
}
//在IIC指定地址写入一个数据(type1)
//Slavewriteaddr:器件地址+写操作位    
//Registeraddr:寄存器地址
void IIC_WriteOneBytetype1(u8 Slavewriteaddr,u8 Registeraddr)
{				   	  	    																 
    IIC_Start();  
	IIC_Send_Byte(Slavewriteaddr);	    //发送写命令
	IIC_Wait_Ack();
	IIC_Send_Byte(Registeraddr);//发送高地址
	IIC_Wait_Ack();	   
    IIC_Stop();//产生一个停止条件 
	delay_ms(10);	 
}
//在IIC指定地址写入一个数据(type2)
//Slavewriteaddr:器件地址+写操作位    
//Registeraddr:寄存器地址
//Command:写入的参数或命令
void IIC_WriteOneBytetype2(u8 Slavewriteaddr,u8 Registeraddr,u8 Command)
{				   	  	    																 
    IIC_Start();  
    IIC_Send_Byte(Slavewriteaddr);	    //发送写命令
    IIC_Wait_Ack();
    IIC_Send_Byte(Registeraddr);//发送高地址
	IIC_Wait_Ack();	
	IIC_Send_Byte(Command);     //发送字节	
	IIC_Wait_Ack(); 
    IIC_Stop();//产生一个停止条件 
	delay_ms(10);	 
}
//在IIC指定地址写入一个数据(type3)
//Slavewriteaddr:器件地址+写操作位    
//Registeraddr:寄存器地址
//Command:写入的参数或命令
void IIC_WriteOneBytetype3(u8 Slavewriteaddr,u16 Registeraddr,u8 Command)
{				   	  	    																 
    IIC_Start();  
	IIC_Send_Byte(Slavewriteaddr);	    //发送slave address
	IIC_Wait_Ack();
	IIC_Send_Byte(Registeraddr>>8);		//发送高地址
	IIC_Wait_Ack();
    IIC_Send_Byte(Registeraddr%256);   	//发送低地址
	IIC_Wait_Ack(); 	 							
	IIC_Send_Byte(Command);     //发送命令	
	IIC_Wait_Ack(); 
    IIC_Stop();//产生一个停止条件 
	delay_ms(10);	 
}

//在IIC指定地址写入一个数据(type4)
//Slavewriteaddr:器件地址+写操作位    
//Registeraddr:寄存器地址 2byte
//Command:写入的参数或命令	6byte
void IIC_WriteOneBytetype4(u8 Slavewriteaddr,u16 Registeraddr,u8 Command1,u8 Command2,u8 Command3,u8 Command4,u8 Command5,u8 Command6)
{				   	  	    																 
    IIC_Start();  
	IIC_Send_Byte(Slavewriteaddr);	    //发送slave address
	IIC_Wait_Ack();
	IIC_Send_Byte(Registeraddr>>8);		//发送高地址
	IIC_Wait_Ack();
    IIC_Send_Byte(Registeraddr%256);   	//发送低地址
	IIC_Wait_Ack(); 	 							
	IIC_Send_Byte(Command1);     //发送命令1	
	IIC_Wait_Ack(); 
	IIC_Send_Byte(Command2);     //发送命令2	
	IIC_Wait_Ack(); 
	IIC_Send_Byte(Command3);     //发送命令3	
	IIC_Wait_Ack(); 
	IIC_Send_Byte(Command4);     //发送命令4	
	IIC_Wait_Ack(); 
	IIC_Send_Byte(Command5);     //发送命令5	
	IIC_Wait_Ack(); 
	IIC_Send_Byte(Command6);     //发送命令6	
	IIC_Wait_Ack(); 
    IIC_Stop();//产生一个停止条件 
	delay_ms(10);	 
}

//在IIC芯片指定地址连续读出一个数据(Burst Read)
//Slavewriteaddr:器件地址+写操作位
//Registeraddr:寄存器地址  
//返回值  :读到的数据
u16 IIC_BurstReadOneByte(u8 Slavewriteaddr,u16 Registeraddr)
{				  
	u16 temp=0;	
	u16 temp1=0;	  	    																 
    IIC_Start();  
	IIC_Send_Byte(Slavewriteaddr);	   //发送写命令
	IIC_Wait_Ack();
	IIC_Send_Byte(Registeraddr);//发送寄存器地址
	IIC_Wait_Ack();		   
	IIC_Start();  	 	   
	IIC_Send_Byte(Slavewriteaddr+1);           //进入接收模式			   
	IIC_Wait_Ack();	
		delay_ms(10);
 
    temp=IIC_Read_Byte(0);
	IIC_Stop();//产生一个停止条件

	IIC_Start();  
	IIC_Send_Byte(Slavewriteaddr);	   //发送写命令
	IIC_Wait_Ack();
	IIC_Send_Byte(Registeraddr+1);//发送寄存器地址
	IIC_Wait_Ack();		   
	IIC_Start();  	 	   
	IIC_Send_Byte(Slavewriteaddr+1);           //进入接收模式			   
	IIC_Wait_Ack();	 
	delay_ms(10);
    temp1=IIC_Read_Byte(0);
	temp1<<=8;
	IIC_Stop();//产生一个停止条件
	temp=temp+temp1;
			delay_ms(10);	    
	return temp;
}






																			  



















