/* ----------------------------------------------------------------------------
 *                TGUI��������
 * --------------------------------------------------------------------------*/

#ifndef __T_GUI_BASE_H 
#define __T_GUI_BASE_H

#include "TGUICfg.h"      //TGUI����
#include "TGUINotify.h"   //TGUI��Ϣͨ��

/**********************************************************************
                         ��ؽṹ����
**********************************************************************/
//����������
typedef struct{
  signed char x;     //x����
  signed char y;     //y����  
  signed char w;    //���,ȡ��ֵ  
  signed char h;    //�߶�,ȡ��ֵ     
}TRect_t;

//����������,�������߶ȹ̶�Ϊ1
typedef struct{
  signed char x;     //x����
  signed char y;    //y����  
  signed char w;    //���,ȡ��ֵ    
}TFocus_t;


//��Ŀ����������
typedef struct{
  TItemSize_t x;    //x����
  TItemSize_t y;    //y����  
  TItemSize_t w;    //���  
  TItemSize_t h;    //�߶�    
}TItemsRect_t;

//��Ŀ����������,�������߶ȹ̶�Ϊ1
typedef struct{
  TItemSize_t x;     //x����
  TItemSize_t y;    //y����  
  TItemSize_t w;    //���,ȡ��ֵ    
}TItemsFocus_t;

/**********************************************************************
                         ����
**********************************************************************/
//��ֵ//��ӦASCII����ӡ�ַ�,��Χ0-31,���Ƽ�����Ϊ:
#define TGUI_KEY_BACKSPACE        20 
#define TGUI_KEY_TAB              21
#define TGUI_KEY_ENTER            22    //����
  
#define TGUI_KEY_LEFT             16    //����
#define TGUI_KEY_UP               17    //����
#define TGUI_KEY_RIGHT            18    //����
#define TGUI_KEY_DOWN             19    //����
#define TGUI_KEY_PAGEUP           23
#define TGUI_KEY_PAGEDOWN         24
#define TGUI_KEY_SHIFT            25
#define TGUI_KEY_CONTROL          26
#define TGUI_KEY_ESCAPE           27
#define TGUI_KEY_INSERT           29
#define TGUI_KEY_DELETE           30

/**********************************************************************
                         ��ع�����
**********************************************************************/

//-----------------------���������õ�ռλ����-----------------------
unsigned char GetItemsPlace(TItemSize_t Items);

//-----------------------�õ����ַ��Ҷ����ĳ��Ⱥ���-----------------------
unsigned char GetAlignLenR(unsigned char Len,     //ԭ�ַ�����,<128
                          unsigned char Append); //�����ַ�����,<128

//-----------------------�õ����ַ�������ĳ��Ⱥ���-----------------------
unsigned char GetAlignLenL(unsigned char Len,     //ԭ�ַ�����,<128,> 1
                          unsigned char Append); //�����ַ�����,<128

//-----------------------ת��Ϊ�ַ���-��ʾΪ�����----------------------
unsigned char Value2StringMin(TSigned_t Value,
                            char *pString,//���ջ���
                            unsigned char Min);//��֤����Сλ��

//-----------------------�õ����ַ������ĳ��Ⱥ���-----------------------
//����Ҫ˫�ֽڶ���ʱ,δ����ʱ�ڸ�λ�����' '
//��������Ļ���
char *pAlignString(TItemSize_t ItemLen,//�ַ�����
                   char *pString);//���ջ���  

//------------------�ַ������Һ���-----------------------
//��C++�������,��string������,���轫��ע�͵�
//const char *strchr(const char *s, char ch);

//------------------�ַ�����չ��������-----------------------
//1:��Ӧ�����뻻���ַ�,
//2:���ؽ�����λ��
char *strcpy_ex(char *s1, const char *s2);


#endif
