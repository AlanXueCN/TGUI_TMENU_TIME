/* ----------------------------------------------------------------------------
 *                �û��Զ�����ģ�����ʵ��
 * --------------------------------------------------------------------------*/

#include "TWord.h"
#include "string.h"


//-------------�õ���GB2312��׼��λ��ת��Ϊ�Զ�������ֵ����------------------
//�˺���������û��Զ�����ģ��ز����������ܵõ���ģ
//����0xffff��ʾδ�ҵ�
unsigned short TWord_Word2UserID(unsigned short Word,//ǰ���������ֱ���>=128
                                 const char *pLUT,         //���ֶ�Ӧ���Զ����ַ�
                                 unsigned short Count)//�Զ����ַ���С
{
  unsigned short Left  = 0;    //��߽�
  unsigned short Center = Count >> 1;//����м�λ��
  unsigned short CurPos;       //��ǰλ��
  unsigned short Condition;       //��ǰ����ֵ
  
  do{
    Center >>= 1;      //����������λ��
    CurPos = Center + Left;
    Condition = *((unsigned short*)pLUT + CurPos);//�õ��������
    //����Ƿ��ڷ�Χ
    if(Word > Condition)Left = CurPos;  //�ں���
    else if(Word == Condition) return CurPos;//�ҵ���
    //else ��ǰ�棬����
  }while(Center);
  
  //û�ҵ�ʱ,Ҳ��������λ����!
  if((Condition > Word) && (Word == *((unsigned short*)pLUT + CurPos - 1)))
    return CurPos;
  //��û�ҵ�ʱ,Ҳ������λ����!
  if((Condition < Word) && (Word == *((unsigned short*)pLUT + CurPos + 1)))
    return CurPos;
  //�Ҳ�����û���ˣ���������
  return 0xffff;
}

//--------------------�õ�16X16�ı�һ�л�����ģ����--------------------------
//��ֱ��ͨ���˺������һ���ֵ�GB2312ͼ�ε���
void TWord_GetLineBuf_GB2312(char *pString,       //���ַ�
                             unsigned char w,     //�п�
                             unsigned char *pLine)//�������л�����,>=w * 32
{
  char Code;
  unsigned short Word;
  unsigned short WordCount = TWord_GetGB2312LUTSize();//�Զ����ַ���С
  
  for(unsigned char i = 0; i < w; i++){
    Code = *pString++;
    if(Code < 0x80){//ASCII��
      //��֧�ֿ����ַ�ʱ����ʾ�ո�
      #ifndef TWORD_ASC_EN_CTRL 
      if(Code < 32) Code = 32;
      #endif
      memcpy(pLine,TWord_pGetAsciiModule(Code),16);
      pLine += 16;
    }
    else{//ȫ���ַ�
      Word = (unsigned short)Code << 8 + *pString++;
      Word = TWord_Word2UserID(Word,TWord_GB2312LUT,WordCount);
      if(Word < 0xffff){ //�ҵ���
        memcpy(pLine,TWord_pGetWordModule(Word),32);
        pLine += 16;
      }
      else{//δ�ҵ�ʱ����Ϊ�����ո�
        memcpy(pLine,TWord_pGetAsciiModule(32),16);
        pLine += 16;
        memcpy(pLine,TWord_pGetAsciiModule(32),16);
        pLine += 16;
      }
    }
  }
}

