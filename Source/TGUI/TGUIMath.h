/* ----------------------------------------------------------------------------
 *                TGUI��ѧ������غ���
 * --------------------------------------------------------------------------*/

#ifndef __T_GUI_MATH_H 
#define __T_GUI_MATH_H

#include "TGUIBase.h"

//��λ�ò鱶��,�˱�TUnSigned_t�仯ʱ���޸�
extern const TUnSigned_t MutiTUnigned[];

//----------------�õ�һ���з������ľ���ֵ--------------------
TSigned_t GetAbs(TSigned_t Value);

//----------------����ֵ�õ�ռλ����,��������--------------------
unsigned char GetNumLen(TSigned_t Min,TSigned_t Max);   //Сֵ���ֵ

//----------------�õ�ָ��λ����ֵ����------------------------
TUnSigned_t GetDigitalInPos(TUnSigned_t Value,
                           unsigned char Pos);

//-----------------����־��ת��Ϊ�ַ�������------------------
//����������ĩδ�û�����λ��
char *pNum2StringFlag(TSigned_t Value,   //��ǰ��ֵ
                      char *pBuf,    //���ջ�����
                      unsigned char Len,    //��ʾ����
                      //��־,����Ϊ����3bit:С����λ��,0x80:��ʾ������
                      unsigned char Flag);

#endif

