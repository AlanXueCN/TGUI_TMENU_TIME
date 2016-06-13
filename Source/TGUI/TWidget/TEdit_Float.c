/* ----------------------------------------------------------------------------
 *                TGUI�ı༭��ĸ���������ʵ��
 * --------------------------------------------------------------------------*/

#include "TEdit.h"
#include "string.h"
#include "TEditPrv.h"  //�ڲ�����,�����ڲ�ʹ��
#include "TEdit_Float.h"
#include <math.h>       //floor

/**********************************************************************
                          ֧�ָ���������ʱ
**********************************************************************/
#if TGUI_EDIT_FLOAT_SUPPORT 

//----------------�༭����������ʼ��Ϊ����--------------------
void TEditFloat(TEdit_t *pEdit,
                TWinHandle_t hWin,    //�����Ĵ���,���ݻ�����>Len
                float Value,            //��ʼ��ֵ
                float Max,              //���ֵ
                float Min,              //��Сֵ
                unsigned char DotPos,  //��ȷ��С����λ��
                unsigned char Flag,  //�������
                TGUINotify_t cbGUINotify) //ͨ������
{
  //��������ת��Ϊ��������,ֱ��ʹ����������
  float Muti = (float)MutiTUnigned[DotPos];  
  //ת��Ϊ��������
  TEditDec(pEdit,hWin,
           floor(Muti * Value + 0.5),
           floor(Muti * Max + 0.5),
           floor(Muti * Min + 0.5),
           DotPos,Flag,cbGUINotify);

  pEdit->eType = TEditType_Float;//��������
}

//----------------������ת��ΪTSigned_t����ռλ����--------------------
//�˺�����Data2Float�ɶ�ʹ��,TSigned_tռλӦ>=floatռλ
TSigned_t Float2Data(float Value)
{
  TSigned_t Data;
  memcpy(&Data,&Value,sizeof(float));
  return Data;  
}

//-----------TSigned_t���͸�����ռλת���ظ���������--------------------
//�˺�����Float2Data�ɶ�ʹ��,TSigned_tռλӦ>=floatռλ
float Data2Float(TSigned_t Data)
{
  float Value;
  memcpy(&Value,&Data,sizeof(float));
  return Value; 
}


//----------------�ɸ�������ֵ�õ�ռλ����,��������--------------------
unsigned char GetFloatLen(float Min,float Max,
                          unsigned char DotPos)  //��ȷ��С����λ��
{
  float Muti = (float)MutiTUnigned[DotPos & 0x07]; 
  return GetNumLen(floor(Muti * Min + 0.5),floor(Muti * Max + 0.5));
}

//-----------------����־������ת��Ϊ�ַ�������------------------
//����������ĩδ�û�����λ��
char *pFloat2StringFlag(float Value,   //��ǰ��ֵ
                      char *pBuf,    //���ջ�����
                      unsigned char Len,    //��ʾ����
                      //��־,����Ϊ����3bit:С����λ��,0x80:��ʾ������
                      unsigned char Flag)
{
  //ת��Ϊ����
  float Muti = (float)MutiTUnigned[Flag & 0x07]; 
  Muti = Muti * Value + 0.5;
  return pNum2StringFlag(floor(Muti),pBuf,Len,Flag);
}


/**********************************************************************
    ��֧�ָ���������ʱ,Ϊ��ֹʹ�ÿպ�����ʱ���ܵı��뾯��,��������Ϊ��
**********************************************************************/
#else

//----------------�༭����������ʼ��Ϊ����--------------------
void TEditFloat(TEdit_t *pEdit,
                TWinHandle_t hWin,    //�����Ĵ���,���ݻ�����>Len
                float Value,            //��ʼ��ֵ
                float Max,              //���ֵ
                float Min,              //��Сֵ
                unsigned char DotPos,  //��ȷ��С����λ��
                unsigned char Flag,  //�������
                TGUINotify_t cbGUINotify) //ͨ������
{
  pEdit = pEdit;
  hWin = hWin;
  Value = Value;
  Max = Max;
  Min = Min;
  DotPos = DotPos;
  Flag = Flag;
  cbGUINotify = cbGUINotify;
}

//----------------������ת��ΪTSigned_t����ռλ����--------------------
//�˺�����Data2Float�ɶ�ʹ��,TSigned_tռλӦ>=floatռλ
TSigned_t Float2Data(float Value)
{
  return Value;  
}

//-----------TSigned_t���͸�����ռλת���ظ���������--------------------
//�˺�����Float2Data�ɶ�ʹ��,TSigned_tռλӦ>=floatռλ
float Data2Float(TSigned_t Data)
{
  return Data; 
}


//----------------�ɸ�������ֵ�õ�ռλ����,��������--------------------
unsigned char GetFloatLen(float Min,float Max,
                          unsigned char DotPos)  //��ȷ��С����λ��
{
  Max = Max;
  Min = Min;
  DotPos = DotPos;
  return 0;
}

//-----------------����־������ת��Ϊ�ַ�������------------------
//����������ĩδ�û�����λ��
char *pFloat2StringFlag(float Value,   //��ǰ��ֵ
                      char *pBuf,    //���ջ�����
                      unsigned char Len,    //��ʾ����
                      //��־,����Ϊ����3bit:С����λ��,0x80:��ʾ������
                      unsigned char Flag)
{
  //ת��Ϊ����
  Value = Value;
  Len = Len;
  Flag = Flag;
  return pBuf;
}
#endif



