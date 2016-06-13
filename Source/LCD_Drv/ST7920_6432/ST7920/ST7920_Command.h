//*********************************************************************
//
//			ST7920�ײ���������ͷ�ļ�
//
//��ͷ�ļ���װ��ST7920�Ĳ����ӿڣ����û�LCD�������
//�����Ʒ�ʽ�ı�ʱ,���޸Ĵ��ļ���ʵ��
//*********************************************************************/

#ifndef __ST7920__COMMAND_H
#define __ST7920__COMMAND_H

/*-----------------------------------------------------------------------------------------

					LCD����IO�ӿڲ�ʵ��
 .�޸Ĵ˽ӿ���ʵ�ʶ�������Ӧ
 .���޸�Ӳ����ʼ��IO����
----------------------------------------------------------------------------------------*/
#include "Apublic.h"//LCD-CMD,set_bit,_nop
#include "Delay.h"



//���ϰ���
#define		Lcd_OnUpperScreen()	do{set_bit(LCD_CTRLPORT,LCD_E);}while(0)	//��дʹ���ź�E1��1��Ч
//���°���
//#define		Lcd_OnUnderScreen()	do{PSD8xx_reg.DATAOUT_C |= 0x08;}while(0)	//��дʹ���ź�E2��1��Ч
#define		Lcd_OnUnderScreen()	Lcd_OnUpperScreen()
//���ϰ���
#define		Lcd_OffUpperScreen()	do{clear_bit(LCD_CTRLPORT,LCD_E);}while(0)	//��дʹ���ź�E1��1��Ч
//���°���
//#define		Lcd_OffUnderScreen()	do{PSD8xx_reg.DATAOUT_C &= ~0x08;}while(0)	//��дʹ���ź�E2��1��Ч
#define		Lcd_OffUnderScreen()		Lcd_OffUpperScreen()
//ѡ������
#define		Lcd_D_Select()   do{set_bit(LCD_CTRLPORT,LCD_RS);}while(0)	//����ָ��ѡ���ź�RS��1Ϊ���ݲ���
//ѡ��ָ��
#define		Lcd_I_Select()   do{clear_bit(LCD_CTRLPORT,LCD_RS);}while(0)	//����ָ��ѡ���ź�RS��0Ϊдָ����״̬
//��ѡ���ź�
#define		Lcd_RD_Select()		do{set_bit(LCD_CTRLPORT,LCD_R_W);}while(0)	//��дѡ���ź�RW��1Ϊ��ѡͨ
//дѡ���ź�
#define		Lcd_WR_Select()		do{clear_bit(LCD_CTRLPORT,LCD_R_W);}while(0)	//��дѡ���ź�RW��0Ϊдѡͨ

//��Ϊ���
#define		Lcd_Set_Out()		do{BUS_DDR = 0xFF;}while(0)	//P4��ʵ�֣������ر���Ϊ���
//д����
#define		Lcd_Set_Data(Data)		do{BUS_PORT = Data;}while(0)
//��Ϊ����
#define		Lcd_Set_In()		do{BUS_DDR = 0x00;BUS_PORT = 0xff;}while(0)	//P4��ʵ�֣�0xff��Ϊ����
//������
#define		Lcd_Get_Data()			(BUS_PIN)

/*-----------------------------------------------------------------------------------------

					LCD���ƶ�д��ʱʱ��ʵ��

----------------------------------------------------------------------------------------*/
#define		Lcd_RdDelay()		do{vDelayUs(20);}while(0)		//��������ʱʱ��	
#define		Lcd_WrDelay()		do{vDelayUs(20);}while(0)		//д������ʱʱ��


/*-----------------------------------------------------------------------------------------

										������ʵ��

----------------------------------------------------------------------------------------*/
#include "ST7920_Drv.h"

//-------------------�ײ�IO�ڳ�ʼ��------------------------
//���û���ʼ����IO�ڵ�Ĭ��״̬
void Lcd_HwInit(void);

//-------------------LCDдָ��---------------------------		
//�ϰ���дָ��
void Lcd_UpperWrCommand(unsigned char Command);

//�°���дָ��
//void Lcd_UnderWrCommand(unsigned char Command) ;
#define	Lcd_UnderWrCommand(Command) Lcd_UpperWrCommand(Command) 	

//-------------------LCDд����׼��---------------------------
//�ϰ���д����ǰ���ô˺���
void Lcd_UpperWrDataRdy(void);

//�°���д����ǰ���ô˺���
//void Lcd_UnderWrDataRdy(void);
#define	Lcd_UnderWrDataRdy()	Lcd_UpperWrDataRdy()

//-------------------LCDд����---------------------------
//д��������������,д��һ������ǰ�������д׼������

//�ϰ���д����
void Lcd_UpperWrData(unsigned char uData);
//�°���д����
//void Lcd_UnderWrData(uData);
#define	Lcd_UnderWrData(uData) Lcd_UpperWrData(uData)

#endif
