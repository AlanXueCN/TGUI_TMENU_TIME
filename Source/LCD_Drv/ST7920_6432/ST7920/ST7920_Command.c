//*********************************************************************
//
//			ST7920�ײ���������ʵ��
//
//*********************************************************************/
				 
#include "ST7920_Command.h"

//-------------------�ײ�IO�ڳ�ʼ��------------------------
//���û���ʼ����IO�ڵ�Ĭ��״̬
void Lcd_HwInit(void)
{
	//�õ���IO�ڣ�
	//����->P4 
	//E1->PC2
	//E2->PC3
	//RS->PD2
	//RW->PD1

	//����Ԥ��Ϊ����״̬
	Lcd_Set_In();

	clear_bit(LCD_CTRLPORT,LCD_E);
	clear_bit(LCD_CTRLPORT,LCD_RS);
	clear_bit(LCD_CTRLPORT,LCD_R_W);
	set_bit(LCD_CTRLPORT,LCD_RST);
	//clear_bit(LCD_CTRLPORT,LCD_RST);

	//���ƶ˿�ȫ����Ϊ����͵�ƽ
	set_bit(LCD_CTRLDDR,LCD_RS);
	set_bit(LCD_CTRLDDR,LCD_R_W);
	set_bit(LCD_CTRLDDR,LCD_E);
	set_bit(LCD_CTRLDDR,LCD_RST);
	//vDelayMs(10);
	//set_bit(LCD_CTRLPORT,LCD_RST);
}


//-------------------�ȴ�����---------------------------
//�ɷ��ص�ǰѡ��λ��ֵ

//�ȴ��ϰ�������
static void Lcd_WaitUpperIdie(void)
{
	unsigned char Data;
	Lcd_RD_Select();	//��ѡ��
	Lcd_I_Select();		//ָ��
	Lcd_Set_In();			//����Ϊ����
	do{
	 	Lcd_OnUpperScreen();	//Eʹ��(ѡͨ)
		Lcd_RdDelay();
	 	Data = Lcd_Get_Data(); 
		Lcd_OffUpperScreen();
	}while(Data & BF_BIT);
} 

/*/�ȴ��°�������
static void Lcd_WaitUnderIdie(void)
{
	unsigned char Data;
 	Lcd_RD_Select();
	Lcd_I_Select();
	Lcd_Set_In();
	do{
	 	Lcd_OnUnderScreen();
		Lcd_RdDelay();
	 	Data = Lcd_Get_Data();  
		Lcd_OffUnderScreen();
	}while(Data & BF_BIT);
}*/



//-------------------LCDдָ��---------------------------		
//�ϰ���дָ��
void Lcd_UpperWrCommand(unsigned char Command)
{
	Lcd_WaitUpperIdie();
 	Lcd_WR_Select();
	Lcd_I_Select();
	Lcd_Set_Out();						

	Lcd_Set_Data(Command);
	Lcd_OnUpperScreen();
	Lcd_WrDelay();	  //��ʱ�ȴ�����д��
	Lcd_OffUpperScreen();
}

/*/�°���дָ��
void Lcd_UnderWrCommand(unsigned char Command)
{			
	Lcd_WaitUnderIdie();
 	Lcd_WR_Select();
	Lcd_I_Select();	
	Lcd_Set_Out();						

	Lcd_Set_Data(Command);
	Lcd_OnUnderScreen();
	Lcd_WrDelay();	 //��ʱ�ȴ�����д��
	Lcd_OffUnderScreen();
}*/

//-------------------LCDд����׼��---------------------------
//�ϰ���д����ǰ���ô˺���
void Lcd_UpperWrDataRdy(void) 
{
	Lcd_WaitUpperIdie();
	Lcd_D_Select();	
 	Lcd_WR_Select();
	Lcd_Set_Out();						
}
/*/�°���д����ǰ���ô˺���
void Lcd_UnderWrDataRdy(void) 
{
	Lcd_WaitUnderIdie();
	Lcd_D_Select();	
 	Lcd_WR_Select();
	Lcd_Set_Out();						
}*/

//-------------------LCDд����---------------------------
//д��������������,д��һ������ǰ�������д׼������

//�ϰ���д����
void Lcd_UpperWrData(unsigned char uData)
{
	Lcd_WrDelay();	  //��ʱ�ȴ�����д��//�Ƿ�Ӧ��ΪLcd_UpperWrDataRdy()?�񣡿��ܻ�����д2�ֽ�

	Lcd_Set_Data(uData);
	Lcd_OnUpperScreen();
	Lcd_WrDelay();	  //��ʱ�ȴ�����д��
	Lcd_OffUpperScreen();	
}

/*/�°���д����
void Lcd_UnderWrData(uData) 
{
	Lcd_Set_Data(uData);
	Lcd_OnUnderScreen();
	Lcd_WrDelay();	 //��ʱ�ȴ�����д��
	Lcd_OffUnderScreen();
}*/


