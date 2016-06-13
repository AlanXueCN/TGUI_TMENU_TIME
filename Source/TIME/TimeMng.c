/*****************************************************************************
                         TGUI�ϵ����뷨ģ����ʵ��
ע:�ݲ�֧���Դ��ֿ�ȫ�Ƕ���LCD��ʾ������ʾ
*****************************************************************************/

#include "TImeMng.h"
#include <string.h>

/*****************************************************************************
                           �ڲ���������
*****************************************************************************/
//-------------------------�õ���һ����Ч���뷨����---------------------------------
//���ݿ��������л�����һ����Ч���뷨
//������һ����Ч���뷨
static unsigned char _SwitchType(const struct _TImeMng *pIme);

//--------------------------���뷨�л�����---------------------------------
//�л�����Ӧ���뷨����ʼ��
static void _SwitchIme(struct _TImeMng *pIme,
                       unsigned char Type);//���е������뷨,0-4

//-----------------------���뷨�ڲ�����������---------------------------------
//pIme->Flag�е�TIME_FLAG_STATE��λʱ���ô˺���
//����ֵ����Ϊ0δ��Ӧ
//2:���뷨�ڲ��˳����н������
//3:���뷨�ڲ��˳�����Ч����
static signed char _KeyInType(struct _TImeMng *pIme,
                              char Key);

//-----------------------�༭״̬���ּ�0��9������-----------------------------
//pIme->Flag�е�TIME_FLAG_STATEδ��λʱ���ô˺���
//����ֵ����Ϊ:
//0δ��Ӧ,
//1:�������뷨�ڲ����޽������
//2:δ�����뷨�ڲ����н������
static signed char _NumKeyInEdit(struct _TImeMng *pIme,
                                   char NumKey);//��ֵ'0'-'9'

//------------------�õ����뷨�ڲ����ź���------------------------------
//�����뷨�������ʱ���õ������±༭������
static void _GetImeChar(struct _TImeMng *pIme);

//------------------ˢ�´�����ʾ����---------------------------------
//ˢ��pWin���ڵ���ʾ����
static void _Refresh(struct _TImeMng *pIme);

/*****************************************************************************
                           ���⺯��ʵ��
*****************************************************************************/

//----------------------------------��ʼ������---------------------------------
//�����Ƿ�ɹ���ʼ��
signed char TImeMng_Init(struct _TImeMng *pIme,  //��������뷨�ṹ����
                         TWin_t *pWin,             //��ǰ�ҽӵĴ���
                         char *pString,            //�û��Ѵ��ڵ��ַ���,������'\0'��β
                         TIme_String_t Size,     //�ַ��������������С+1
                         unsigned char DefaultType,   //Ĭ�����뷨<4
                         unsigned char TypeMask,      //��ʹ�õ����뷨���� 
                         const char *pSignTbl) //�ҽӵķ��ű�,Ϊ��ʱʹ��Ĭ��
{
  unsigned char Data;
  //��鴰���Ƿ���ʾ
  if(TWin_GetW(pWin) < 16) return -1;//������ʾ
  if(TWin_GetH(pWin) < 4) return -1;//������ʾ
  
  memset(pIme, 0, sizeof(struct _TImeMng));
  //��Ч��ȳ�ʼ��
  Data = TWin_GetW(pWin);
  if(Data >= 18) Data-= 2;//ȥ�����ұ߽����"|"
  pIme->w = Data;
  //��Ч�߶ȳ�ʼ��
  Data = TWin_GetH(pWin);
  pIme->h = Data;
  //��ʼ����Data����ĳ�Ա
  pIme->pWin = pWin;
  TImeEdit_Init(&pIme->Edit,pString,Size,pIme->w);//��ʼ���༭��  
  pIme->pSignTbl = pSignTbl;  
  if(DefaultType >= 4) DefaultType = 0;//ǿ�ƾ���
  pIme->TypeMask = TypeMask;
  
  _SwitchIme(pIme,DefaultType);//����Ĭ�����뷨���ͳ�ʼ��Data��
  
  //�����ƴ�����ʾ

  _Refresh(pIme);      //������ʾ
  return 0;
}

//----------------------------����������---------------------------------
//�û������ּ����뵼������ʱ���ô˺���
//����ֵ����Ϊ: 0����״̬,-1:�˳���ֱ���˳�;-2:ȷ�ϼ��˳�
signed char TImeMng_Key(struct _TImeMng *pIme,
                        char Key)          //��ֵ
{
  //ֻҪ�������ּ�����ǿ��ֹͣ��Сд��ʱ��
  if((Key < '0') || (Key > '9'))  pIme->CapitalTimer = 0;
  
  if(!(pIme->Flag & TIME_FLAG_STATE)){//�ڱ༭״̬,���б༭�ַ�������
    switch(Key){
    case TGUI_KEY_LEFT:  TImeEdit_CursorLeft(&pIme->Edit); break;
    case TGUI_KEY_RIGHT: TImeEdit_CursorRight(&pIme->Edit); break;
    case TGUI_KEY_DELETE:TImeEdit_Clr(&pIme->Edit); break;
    case TGUI_KEY_ENTER:  return-2;//ȷ�ϼ��˳��༭״̬
    case TGUI_KEY_ESCAPE: return-1;//�˳���ֱ���˳��༭״̬
    case '*': //�л�����������ģʽ,���������ڲ�
      _SwitchIme(pIme, TIME_TYPE_SIGN);
      pIme->Flag |= TIME_FLAG_STATE;
      break;
    case '#'://���л����뷨
      _SwitchIme(pIme, _SwitchType(pIme));
    default:
      //���ּ����뷨��Ӧ
      if((Key >= '0') && (Key <= '9')){
        switch(_NumKeyInEdit(pIme, Key)){
        //case 0:break;// 0δ��Ӧ
        case 1://�������뷨�ڲ����ñ�־
          pIme->Flag |= TIME_FLAG_STATE;
          break;
        case 2: _GetImeChar(pIme);//�н������,ȡ�ý��
          break;
        default:break;
        }
      }
      break;
    }
  }
  else{//�����뷨�ڲ�ʱ
    switch(_KeyInType(pIme, Key)){
        //case 0:break;// 0δ��Ӧ
        case 1: //1:���뷨�ڲ����˳����н������
          _GetImeChar(pIme);
          break;
        case 2: //���뷨�ڲ��˳����н������
          _GetImeChar(pIme);
        case 3: //���뷨�ڲ��˳�����Ч����
          pIme->Flag &= ~TIME_FLAG_STATE;
          //��Ϊ�������뷨�˳�����ǿ���˵�����ǰ���뷨״̬
          if(pIme->Type == TIME_TYPE_SIGN)
            _SwitchIme(pIme, pIme->Flag & TIME_PRV_TYPE_MASK);
          break;
        default:break;
    }
  }
  
  _Refresh(pIme);      //������ʾ
  return 0;
}


//--------------------------������---------------------------------
//�������뷨ʱ���ô˺���ʵ��ʱ��Ҫ��
void TImeMng_Task(struct _TImeMng *pIme)
{
  if(!pIme->CapitalTimer) return ;//��ʱ��ֹͣ״̬
  pIme->CapitalTimer--;
  if(pIme->CapitalTimer) return;//������
  //��ʱʱ�䵽ʱ:
  if((pIme->Type == TIME_TYPE_LOWERCASE) || //��ֹ�쳣����
     (pIme->Type == TIME_TYPE_CAPITAL)){
       TImeCapital_SampReset(&pIme->Data.Capital);//ͬ��ֵʱ��λ
       _Refresh(pIme);//����ˢ����ʾ
  }
}

//-----------------------------�˳�����---------------------------------
//�û������ַ�ȷ���˳�����ô˺���
void TImeMng_Quit(struct _TImeMng *pIme)
{
  TWin_Hidden(pIme->pWin);     //�ر���ʾ
}


/*****************************************************************************
                           �ڲ�����ʵ��
*****************************************************************************/

//-------------------------�õ���һ����Ч���뷨����---------------------------------
//���ݿ��������л�����һ����Ч���뷨
//������һ����Ч���뷨
static unsigned char _SwitchType(const struct _TImeMng *pIme)
{
  unsigned char Type = pIme->Type + 1;//��һ���뷨
  unsigned char TypeMask = 1 << Type;
  for(; Type < TIME_TYPE_SIGN; Type++,TypeMask <<= 1){
    if(TypeMask & pIme->TypeMask) return Type; //�ҵ���
  }
  //û�ҵ����ػ�����һ����ʼ��
  Type = 0;
  TypeMask = 1;
  for(; Type <= pIme->Type; Type++,TypeMask <<= 1){
    if(TypeMask & pIme->TypeMask) break;
  }
  return Type; //�ҵ���
}

//--------------------------���뷨�л�����---------------------------------
//�л�����Ӧ���뷨����ʼ��
static void _SwitchIme(struct _TImeMng *pIme,
                       unsigned char Type)//���е������뷨,0-4
{
  switch(Type){
  case TIME_TYPE_PINYIN:
    TImePinYin_Init(&pIme->Data.PinYin, pIme->w);
    break;
  case TIME_TYPE_NUM:
    TImeNum_Init(&pIme->Data.Num);
    break;
  case TIME_TYPE_LOWERCASE:
    TImeCapital_Init(&pIme->Data.Capital, 0);
    break;
  case TIME_TYPE_CAPITAL:
    TImeCapital_Init(&pIme->Data.Capital, 1);
    break;
  default://�������뷨��
    pIme->Flag &= ~TIME_PRV_TYPE_MASK;//��ס�ϴ����뷨״̬
    pIme->Flag |= pIme->Type;
    TImeSign_Init(&pIme->Data.Sign, 
                  pIme->pSignTbl,
                  pIme->w,
                  3);
    break;
  }
  pIme->Type = Type;
}

//-----------------------���뷨�ڲ�����������---------------------------------
//pIme->Flag�е�TIME_FLAG_STATE��λʱ���ô˺���
//����ֵ����Ϊ0δ��Ӧ
//1:���뷨�ڲ����˳����н������
//2:���뷨�ڲ��˳����н������
//3:���뷨�ڲ��˳�����Ч����
static signed char _KeyInType(struct _TImeMng *pIme,
                              char Key)
{
  if(pIme->Type == TIME_TYPE_PINYIN){
    switch(TImePinYin_eKey(&pIme->Data.PinYin, Key)){
    case eTImePinYin_Idie://�˳���ƴ�����뷨
       return 3;
    case eTImePinYin_Final://ƴ�����뷨���
       return 2;
    default: break;  //ƴ�����뷨����������
    }
  }
  else if(pIme->Type == TIME_TYPE_SIGN){
    if((Key >= '1') && (Key <= '9')){
      if(TImeSign_KeyNum(&pIme->Data.Sign, Key) == 1)//�������ʱ
        return 1;
    }
    else if((Key == TGUI_KEY_DELETE) || (Key == TGUI_KEY_ESCAPE)){
      if(TImeSign_KeyClr(&pIme->Data.Sign))//����Ӧʱ�˳����뷨
        return 3;
    }
    if((Key == TGUI_KEY_PAGEUP) || (Key == TGUI_KEY_UP))//��һҳ����
      TImeSign_KeyPage(&pIme->Data.Sign, 0);
    else if((Key == TGUI_KEY_PAGEDOWN) || (Key == TGUI_KEY_DOWN))//��һҳ����
      TImeSign_KeyPage(&pIme->Data.Sign, 1);
    else if(Key == TGUI_KEY_ENTER)//ȷ�ϼ��������˳�
      return 3;
  }
  //TIME_TYPE_NUM://�������뷨����������뷨�ڲ����޴�״̬
  //TIME_TYPE_LOWERCASE://Сд���뷨����������뷨�ڲ����޴�״̬
  //TIME_TYPE_CAPITAL://��д���뷨����������뷨�ڲ����޴�״̬
  return 0;
}

//-----------------------�༭״̬���ּ�0��9������-----------------------------
//pIme->Flag�е�TIME_FLAG_STATEδ��λʱ���ô˺���
//����ֵ����Ϊ:
//0δ��Ӧ,
//1:�������뷨�ڲ����޽������
//2:δ�����뷨�ڲ����н������
static signed char _NumKeyInEdit(struct _TImeMng *pIme,
                                   char NumKey)//��ֵ'0'-'9'
{
  signed char Resume = 0;
  switch(pIme->Type){
  case TIME_TYPE_PINYIN:
    if(NumKey >= '2'){//����ƴ���ڲ�����Ӧ�׸�����
       TImePinYin_eKey(&pIme->Data.PinYin, NumKey);
       Resume =  1;
    }
    break;
  case TIME_TYPE_NUM://ȫ��Ӧ,�������ڲ�����Ӧ����
    TImeNum_KeyNum(&pIme->Data.Num, NumKey);
    Resume =  2;
    break;
  case TIME_TYPE_LOWERCASE:
  case TIME_TYPE_CAPITAL:
    TImeCapital_KeyNum(&pIme->Data.Capital, NumKey);
    pIme->CapitalTimer = TIME_CAPITAL_TIME_OV;//���¸�λ��������ʱ��
    Resume =  2; //�������Ȼ���ַ���
    break;
  default:
    break;
  }
  return Resume;
}

//------------------�õ����뷨�ڲ����ź���------------------------------
//�����뷨�������ʱ���õ������±༭������
static void _GetImeChar(struct _TImeMng *pIme)
{
  const char *pChar;
  unsigned short String;
  
  switch(pIme->Type){
  case TIME_TYPE_PINYIN://ƴ����������뷨ʱ
  case TIME_TYPE_SIGN:
    if(pIme->Type == TIME_TYPE_PINYIN)
      pChar = TImePinYin_pGetChar(&pIme->Data.PinYin);
    else
      pChar = TImeSign_pGetChar(&pIme->Data.Sign);
    if(*pChar >= 0x80)//ȫ���ַ�ʱ
      String = (unsigned short)(*pChar << 8) | *(pChar + 1);
    else
      String = (unsigned short)*(pChar + 1);
    break;
  case TIME_TYPE_NUM:  //����ʱ��ֱ�ӻ��
    String = (unsigned short)TImeNum_GetNum(&pIme->Data.Num);
    break;
  case TIME_TYPE_LOWERCASE://��Сдʱ,ֱ�ӻ��
  case TIME_TYPE_CAPITAL:
    String = (unsigned short)TImeCapital_GetChar(&pIme->Data.Capital);
    //ͬһ�����ж��ʱ�������ַ��滻��ǰλ���ַ�(�����֮ǰ)
    if(TImeCapital_GetSameKeyIndex(&pIme->Data.Capital) >= 2)
      TImeEdit_Clr(&pIme->Edit);
    break;
  default: break;
  }
  TImeEdit_Add(&pIme->Edit, String);//���Ӽ�ֵ
}

//------------------ˢ�´�����ʾ�����ڲ���Դ---------------------------------
//��ʾ���ַ���
static const char *const _pTypeDisp[] = {
 "ƴ��",
 "123 ",
 "abc ",
 "ABC ",
};

//ƴ��������ʾ�������ַ���
static const char *const _pPinYinTypeDisp[] = {
 "->ƴ������",
 "->ƴ��ѡ��",
 "->����ѡ��",
};

//------------------������ұ߽纯��---------------------------------
//�������߽���λ��
static char *_pFullVLine(char *pBuf,
                         unsigned char VFlag,//��ָ���־
                         unsigned char w)
{
  if(VFlag){
    *(pBuf + w - 1) = '|';   
    *pBuf++ = '|';
  }
  return pBuf;
}


//------------------ˢ�´�����ʾ����---------------------------------
//ˢ��pWin���ڵ���ʾ����
static void _Refresh(struct _TImeMng *pIme)
{
  unsigned char v;//��λ��
  unsigned char VSpace;//�б߽������ռλ��־
  unsigned char DispW,DispH;//��ʾ���,��ʾ�߶�
  char *pBuf;
  TWin_t *pWin = pIme->pWin;  //��ǰ�ҽӵĴ���
  
  DispW = TWin_GetW(pWin);
  if(DispW >= 18) VSpace = 2;//�б߽������ռ����
  else VSpace = 0;
  
  //==================��ʾ���±߽�=====================
  //IME��4��,>6�������ʾ�߽�
  if(pIme->h >= 6){
    pBuf = TWin_pGetString(pWin, 0);
    memset(pBuf,'-',DispW);
    *pBuf = ' '; //ǰ�ո�
    *(pBuf + DispW -1) = ' ';//��ո�
    
    pBuf = TWin_pGetString(pWin, 5);
    memset(pBuf,'-',DispW);
    *pBuf = ' '; //ǰ�ո�
    *(pBuf + DispW -1) = ' ';//��ո�
    
    //>6ֱ�����ո�
    for(v = 6; v < pIme->h; v++){
      pBuf = TWin_pGetString(pWin, v);
      memset(pBuf,' ',DispW);
    }
    v = 1; 
  }
  else{//�ޱ߽�
    v = 0; 
  }
  
  //==================���б༭����䲢�ý���=====================
  pBuf = TWin_pGetString(pWin, v);
  TImeEdit_FullBuf(&pIme->Edit, _pFullVLine(pBuf,VSpace,DispW));
  //��Сд���뷨ʱ,����������״̬,����ռ������ʾ�������������
  if(pIme->CapitalTimer){
    TWin_SetFocus(pWin,
                  TImeEdit_GetCursor(&pIme->Edit) + VSpace - 2,
                  v,2);//����ռ2��
  }
  else{
    TWin_SetFocus(pWin,
                  TImeEdit_GetCursor(&pIme->Edit) + VSpace - 1,
                  v,1);//����ռ1��
  }
  //==================��ʾ�и��ݵ�ǰ���뷨״̬���=================
  v++;
  if(pIme->Type < TIME_TYPE_SIGN){
    pBuf = TWin_pGetString(pWin, v);
    pBuf = _pFullVLine(pBuf,VSpace,DispW);
    memcpy(pBuf, _pTypeDisp[pIme->Type], 4);
    pBuf += 4;//ָ����ʾ����
    memset(pBuf, ' ', DispW - VSpace - 4);
    v++;
  }
  //============�ڱ༭���ڲ�ʱ,�������ɾ���ģ��������򲹳�=========
  if(pIme->Flag & TIME_FLAG_STATE){
    if(pIme->Type == TIME_TYPE_PINYIN){
      //������ʾ���ַ�
      enum _eTImePinYin ePinYin = TImePinYin_eGetState(&pIme->Data.PinYin);
      if((ePinYin >= eTImePinYin_Input) && (ePinYin <= eTImePinYin_ChSel))
        memcpy(pBuf,_pPinYinTypeDisp[ePinYin - 1],10);
      //�ڲ��и���      
      pBuf = TWin_pGetString(pWin, v);
      pBuf = _pFullVLine(pBuf,VSpace,DispW);
      TImePinYin_pGetPinYinChar(&pIme->Data.PinYin, pBuf);
      pBuf = TWin_pGetString(pWin, v + 1);
      pBuf = _pFullVLine(pBuf,VSpace,DispW);
      TImePinYin_pGetChChar(&pIme->Data.PinYin,pBuf);
     return;
    }
    //�������뷨�����
    if(pIme->Type == TIME_TYPE_SIGN){
      DispH = 0; //����
      for(; DispH  < 3; v++, DispH++){//�̶�Ϊ����
        pBuf = TWin_pGetString(pWin, v);
        pBuf = _pFullVLine(pBuf,VSpace,DispW);
        TImeSign_pGetDispChar(&pIme->Data.Sign, pBuf, DispH);
      }
      return;
    }
  }
  //============�������뷨�ڲ����������뷨ʱ���������ո�=========
  if(pIme->h >= 6) DispH = 5; //��Ч������
  else DispH = pIme->h;//�ޱ߽�
  for(; v < DispH; v++){
    pBuf = TWin_pGetString(pWin, v);
    pBuf = _pFullVLine(pBuf,VSpace,DispW);
    memset(pBuf, ' ', DispW - VSpace);
  }
}
