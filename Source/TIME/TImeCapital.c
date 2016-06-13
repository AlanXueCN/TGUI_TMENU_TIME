/*****************************************************************************
                         TGUI�ϵ����뷨ģ��-�������뷨����
*****************************************************************************/

#include "TImeCapital.h"
#include <string.h>

//===================��д��ĸת���========================
//�����ּ�0-9
static const char _CapitalLUT[10][5] = {
  {' ','+','-','_','0'},
  {'.',',','?','!','1'}, {'A','B','C','@','2'},
  {'D','E','F','#','3'}, {'G','H','I','@','4'},
  {'J','K','L','%','5'}, {'M','N','O','^','6'},
  {'P','Q','R','S','7'}, {'T','U','V','*','8'},
  {'W','X','Y','Z','9'}
};

/*****************************************************************************
                        ��غ���
*****************************************************************************/

//---------------------------��ʼ������---------------------------------
//�л����������뷨ʱ����
void TImeCapital_Init(struct _TImeCapital *pCapital,//���뷨�ṹ
                      unsigned char CapitalFlag)   //��д����ģʽ��־
{
  memset(pCapital, 0, sizeof(struct _TImeCapital));
  
  pCapital->CapitalFlag = CapitalFlag;
}

//----------------------�õ���ǰ�û�ѡ���ַ�����---------------------------
//���ص�ǰ�û�ѡ����ַ�
char TImeCapital_GetChar(struct _TImeCapital *pCapital)
{
  char Char = _CapitalLUT[pCapital->Num][pCapital->NumCount];
  if(!pCapital->CapitalFlag){//Сд��ĸģʽʱ��ת����дΪСд
    if((Char >= 'A') && (Char <= 'Z'))
      Char += 32; //��Ӧ��32��ֵ
  }
  return Char;
}

//-----------------------���ּ���Ӧ����---------------------------------
//���û������ּ�0-9ʱ��Ӧ�û�����
//�����Ƿ����л�����������������
signed char TImeCapital_KeyNum(struct _TImeCapital *pCapital,
                               char KeyNum)//��ֵ��Ӧȷ��Ϊ'0'-'9'
{
  unsigned char Num = KeyNum -= '0';
  
  //�й�����������������ͬʱ���е��¸��ַ�
  if((pCapital->SameKeyIndex) && (pCapital->Num == Num)){
    if(pCapital->SameKeyIndex < 255) pCapital->SameKeyIndex++;
    pCapital->NumCount++;
    if(pCapital->NumCount >= 5)//������
      pCapital->NumCount = 0;
    return 0;  //���ڵ�ǰ��������
  }
  else{//�ϴ��ް������л�����������ʱ
    pCapital->SameKeyIndex = 1;
    pCapital->Num = Num;
    pCapital->NumCount = 0;
  }
  return -1;  //�л�������
}


