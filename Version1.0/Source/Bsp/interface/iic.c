#include "iic.h"
#include "delay.h"

//��ʼ��IIC
void iic_init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD,GPIO_Pin_10|GPIO_Pin_11); 	//PB10,PB11 �����
}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(100);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(100);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(100);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	delay_us(100);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
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
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
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
//������ACKӦ��		    
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		delay_us(10);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		delay_us(10); 
		IIC_SCL=0;	
		delay_us(10);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
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
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}
//��IICоƬָ����ַ����һ������(type1)
//Slavewriteaddr:������ַ+д����λ
//Registeraddr:�Ĵ�����ַ 1byte  
//����ֵ  :����������
u8 IIC_ReadOneBytetype1(u8 Slavewriteaddr,u8 Registeraddr)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();  
	IIC_Send_Byte(Slavewriteaddr);	   //����д����
	IIC_Wait_Ack();
	IIC_Send_Byte(Registeraddr);//���ͼĴ�����ַ
	IIC_Wait_Ack();		  
	IIC_Start();  	 	   
	IIC_Send_Byte(Slavewriteaddr+1);           //�������ģʽ			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//����һ��ֹͣ����	    
	return temp;
}
//��IICоƬָ����ַ����һ������(type2)
//Slavewriteaddr:������ַ+д����λ
//Registeraddr:�Ĵ�����ַ 2byte  
//����ֵ  :����������
u8 IIC_ReadOneBytetype2(u8 Slavewriteaddr,u16 Registeraddr)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();  
	IIC_Send_Byte(Slavewriteaddr);	    		//����slave address
	IIC_Wait_Ack();
	IIC_Send_Byte(Registeraddr>>8);				//���͸ߵ�ַ
	IIC_Wait_Ack();
    IIC_Send_Byte(Registeraddr%256);   			//���͵͵�ַ
	IIC_Wait_Ack(); 	 							
	IIC_Start();  	 	   
	IIC_Send_Byte(Slavewriteaddr+1);			//�������ģʽ			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//����һ��ֹͣ����	    
	return temp;
}
//��IICָ����ַд��һ������(type1)
//Slavewriteaddr:������ַ+д����λ    
//Registeraddr:�Ĵ�����ַ
void IIC_WriteOneBytetype1(u8 Slavewriteaddr,u8 Registeraddr)
{				   	  	    																 
    IIC_Start();  
	IIC_Send_Byte(Slavewriteaddr);	    //����д����
	IIC_Wait_Ack();
	IIC_Send_Byte(Registeraddr);//���͸ߵ�ַ
	IIC_Wait_Ack();	   
    IIC_Stop();//����һ��ֹͣ���� 
	delay_ms(10);	 
}
//��IICָ����ַд��һ������(type2)
//Slavewriteaddr:������ַ+д����λ    
//Registeraddr:�Ĵ�����ַ
//Command:д��Ĳ���������
void IIC_WriteOneBytetype2(u8 Slavewriteaddr,u8 Registeraddr,u8 Command)
{				   	  	    																 
    IIC_Start();  
    IIC_Send_Byte(Slavewriteaddr);	    //����д����
    IIC_Wait_Ack();
    IIC_Send_Byte(Registeraddr);//���͸ߵ�ַ
	IIC_Wait_Ack();	
	IIC_Send_Byte(Command);     //�����ֽ�	
	IIC_Wait_Ack(); 
    IIC_Stop();//����һ��ֹͣ���� 
	delay_ms(10);	 
}
//��IICָ����ַд��һ������(type3)
//Slavewriteaddr:������ַ+д����λ    
//Registeraddr:�Ĵ�����ַ
//Command:д��Ĳ���������
void IIC_WriteOneBytetype3(u8 Slavewriteaddr,u16 Registeraddr,u8 Command)
{				   	  	    																 
    IIC_Start();  
	IIC_Send_Byte(Slavewriteaddr);	    //����slave address
	IIC_Wait_Ack();
	IIC_Send_Byte(Registeraddr>>8);		//���͸ߵ�ַ
	IIC_Wait_Ack();
    IIC_Send_Byte(Registeraddr%256);   	//���͵͵�ַ
	IIC_Wait_Ack(); 	 							
	IIC_Send_Byte(Command);     //��������	
	IIC_Wait_Ack(); 
    IIC_Stop();//����һ��ֹͣ���� 
	delay_ms(10);	 
}

//��IICָ����ַд��һ������(type4)
//Slavewriteaddr:������ַ+д����λ    
//Registeraddr:�Ĵ�����ַ 2byte
//Command:д��Ĳ���������	6byte
void IIC_WriteOneBytetype4(u8 Slavewriteaddr,u16 Registeraddr,u8 Command1,u8 Command2,u8 Command3,u8 Command4,u8 Command5,u8 Command6)
{				   	  	    																 
    IIC_Start();  
	IIC_Send_Byte(Slavewriteaddr);	    //����slave address
	IIC_Wait_Ack();
	IIC_Send_Byte(Registeraddr>>8);		//���͸ߵ�ַ
	IIC_Wait_Ack();
    IIC_Send_Byte(Registeraddr%256);   	//���͵͵�ַ
	IIC_Wait_Ack(); 	 							
	IIC_Send_Byte(Command1);     //��������1	
	IIC_Wait_Ack(); 
	IIC_Send_Byte(Command2);     //��������2	
	IIC_Wait_Ack(); 
	IIC_Send_Byte(Command3);     //��������3	
	IIC_Wait_Ack(); 
	IIC_Send_Byte(Command4);     //��������4	
	IIC_Wait_Ack(); 
	IIC_Send_Byte(Command5);     //��������5	
	IIC_Wait_Ack(); 
	IIC_Send_Byte(Command6);     //��������6	
	IIC_Wait_Ack(); 
    IIC_Stop();//����һ��ֹͣ���� 
	delay_ms(10);	 
}

//��IICоƬָ����ַ��������һ������(Burst Read)
//Slavewriteaddr:������ַ+д����λ
//Registeraddr:�Ĵ�����ַ  
//����ֵ  :����������
u16 IIC_BurstReadOneByte(u8 Slavewriteaddr,u16 Registeraddr)
{				  
	u16 temp=0;	
	u16 temp1=0;	  	    																 
    IIC_Start();  
	IIC_Send_Byte(Slavewriteaddr);	   //����д����
	IIC_Wait_Ack();
	IIC_Send_Byte(Registeraddr);//���ͼĴ�����ַ
	IIC_Wait_Ack();		   
	IIC_Start();  	 	   
	IIC_Send_Byte(Slavewriteaddr+1);           //�������ģʽ			   
	IIC_Wait_Ack();	
		delay_ms(10);
 
    temp=IIC_Read_Byte(0);
	IIC_Stop();//����һ��ֹͣ����

	IIC_Start();  
	IIC_Send_Byte(Slavewriteaddr);	   //����д����
	IIC_Wait_Ack();
	IIC_Send_Byte(Registeraddr+1);//���ͼĴ�����ַ
	IIC_Wait_Ack();		   
	IIC_Start();  	 	   
	IIC_Send_Byte(Slavewriteaddr+1);           //�������ģʽ			   
	IIC_Wait_Ack();	 
	delay_ms(10);
    temp1=IIC_Read_Byte(0);
	temp1<<=8;
	IIC_Stop();//����һ��ֹͣ����
	temp=temp+temp1;
			delay_ms(10);	    
	return temp;
}






																			  



















