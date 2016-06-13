/* ----------------------------------------------------------------------------
 *                TWinMngģ��
 * --------------------------------------------------------------------------*/

#include "TWinMng_Row.h"
#include "string.h"

TWinMng_t *pCurTWinMng;    //��ǰ������


/**********************************************************************
                          ��Ϊ����ʵ��
**********************************************************************/

//------------------����ָ��GUI������Ϊ��ǰ����-----------------------
//����ʱ���ô˺�����ʼ��
void TWinMng_SetCur(TWinMng_t *pTWinMng)
{
  pCurTWinMng = pTWinMng;
}

//-------------------------���ڹ�������ʼ������----------------------------
void TWinMng_Init(TWinMng_t *pTWinMng,
                  unsigned char Lcd,    //��ǰ�����Ǹ���ʾ��
                  TWin_t *pTWinAry,     //��ǰ��������ͷ
                  unsigned char Count) //��ǰ�������д�С,<=TWIN_MAX_COUNT
{
  memset(pTWinMng,0,sizeof(TWinMng_t));
  pTWinMng->Lcd = Lcd;
  pTWinMng->pTWinAry = pTWinAry;
  pTWinMng->Count = Count;
}

//-------------------------�õ������к���----------------------------
static unsigned char _GetUpdatedRow(void)
{
  unsigned char Row;
  RowMask_t RowUpdate = pCurTWinMng->RowUpdate;
  unsigned char PrvUpdatedRow = pCurTWinMng->PrvUpdatedRow;
  //�����Ҫ���µ���Ч��,�����п�ʼ���ȸ���
  for(Row = PrvUpdatedRow + 1; Row < TLCD_HIGH; Row++){
    if(RowUpdate & RowShiftLUT[Row]) break; 
  }
  if(Row >= TLCD_HIGH){  //�ػ�
    for(Row = 0; Row < PrvUpdatedRow; Row++){
      if(RowUpdate & RowShiftLUT[Row]) break; 
    }
  }
  //ָ�������Ѹ���
  pCurTWinMng->RowUpdate = RowUpdate & (~(RowShiftLUT[Row]));
  pCurTWinMng->PrvUpdatedRow = Row;//ָ���Ѹ��µ�����
  return Row;
}


//--------------------�õ���ǰ�е���Ч���ں���-------------------------
static unsigned char _GetValidWinMask(unsigned char Row)
{
  WinMask_t ValidWinMask = 0;         //��Ч����
  TWin_t *pWin = pCurTWinMng->pTWinAry;
  WinMask_t i;
  unsigned char Count = pCurTWinMng->Count;
  for(i = 0; i < Count; i++){
   //û������������ʾ��Χ��ʱ����
   if((!TWin_IsHidden(pWin)) && (TWin_GetY(pWin)<= Row) && 
      ((TWin_GetY(pWin) + TWin_GetH(pWin)) > Row)){
        ValidWinMask |= WinShiftLUT[i];
    }
   pWin++;
  }
  return ValidWinMask;
}

//-------------------------�����л���������----------------------------
//�˺���һ�ν�����һ�л�����
//���ڵ��ô˺���������ʾTWinMng���ݵ��л�����
//����0�������,����1��Ҫ����
signed char TWinMng_UpdateRow(void)
{
  unsigned char Row;
  WinMask_t ValidWinMask;         //��ǰ����ЧӰ��Ĵ���
  unsigned char x,WinX;		     //���λ��,�����ڵ�λ��
  TWin_t *pWin;	                 //��ǰ���ڣ��´���Ч����
  unsigned char WinCount = pCurTWinMng->Count;
  unsigned char i;
  
  //���ȫ�Ƕ����������ӣ�
  unsigned char Index;       //ȫ���ַ�������
  char Sign;                     //�ַ� 
  TWin_t *pPrvWin = NULL;	 //�ϴ���Ч����  
  
  WinCount = pCurTWinMng->Count;
  if(pCurTWinMng->Flag & TWINMNG_CONTEXT_BUF_RDY) return 0;  //���л�δ�����أ��ݲ�����
  if(!pCurTWinMng->RowUpdate) return 0;  //������Ҫ����

  Row = _GetUpdatedRow();		//�ҵ�������
  ValidWinMask = _GetValidWinMask(Row); //�ҵ�λ�ڸ����ϵĴ���
  
  //======================�����ص��㷨==========================
  //��һ��һ�������ַ�
  for(x = 0; x < TLCD_WIDTH; x++){
    //�ҵ���ǰ�洰�ڵ��ַ�
    pWin = pCurTWinMng->pTWinAry + (WinCount - 1);
    for(i = WinCount; i > 0; i--){
      if(ValidWinMask & WinShiftLUT[i - 1]){//��Ч�Ĵ���ʱ
        //�õ����ַ���,ת��Ϊ�������  
        Sign = TWin_GetChar(pWin,x - TWin_GetX(pWin),
                            Row - TWin_GetY(pWin));
        WinX = TWin_GetX(pWin);
        if((x >= WinX) && (x < (WinX + TWin_GetW(pWin)))){//�ڷ�Χ��
          //���ȫ�Ƕ�����
          if(pPrvWin != pWin){//�細����
            if(Index & 0x01)//�ϸ��������һ��ȫ��δ����
              pCurTWinMng->RowBuf[x - 1] = ' ';
            pPrvWin = pWin;
            Index = 0x80; //���¿�ʼ,���б�־
          }
          //ȫ��ͳ��
          if(Sign >= 0x80) Index++;
          else{
            //����һ�ο細�����׸�ȫ����δ����ʱ����
            if((Index >= 0x80) && (Index & 0x01))
              pCurTWinMng->RowBuf[x - (Index - 0x80)] = ' ';
            Index = 0; //������¿�ʼ
          }
          
          if(!TWin_IsLattice(pWin)){
            //�õ����ַ���,ת��Ϊ�������  
            pCurTWinMng->RowBuf[x] = Sign;
            pCurTWinMng->RowFlagBuf[x] = 
               DISP_CMD_NOR | TWin_IsFocus(pWin,x - TWin_GetX(pWin),
                                                Row - TWin_GetY(pWin));
          }
          //����ģʽ�������û�����
          else pCurTWinMng->RowFlagBuf[x] = DISP_CMD_DIS_UPDATE;
          break;//�ҵ���
        }
      }
      pWin--;
    }//end i;
  }//end x;
  pCurTWinMng->Flag |= TWINMNG_CONTEXT_BUF_RDY;//������׼������
  return 1;
}

//-------------------------������ʾ����----------------------------
//���л����������ͳ�
//���ڵ��ô˺�������TWinMng�л��������ݵ���ʾ��
void TWinMng_UpdateLcd(void)
{
  if(!(pCurTWinMng->Flag & TWINMNG_CONTEXT_BUF_RDY)) return;//������δ׼����
  
  //�����Ϊȫ����ʱ�����ȫ�����Ƿ񱻽ص������������0
  if(pCurTWinMng->RowBuf[0] >= 0x80){
   for(unsigned char i = 1; i < TLCD_WIDTH; i++){
     if(pCurTWinMng->RowBuf[i] < 0x80){
       if(i & 0x01) pCurTWinMng->RowBuf[0] = ' ';
       break;
     }
   }
  }
  
  //���ûص���������
  TWinMng_cbUpdateRow(pCurTWinMng->Lcd,0, pCurTWinMng->PrvUpdatedRow,
                      TLCD_WIDTH,pCurTWinMng->RowBuf,pCurTWinMng->RowFlagBuf);
  
  pCurTWinMng->Flag &= ~TWINMNG_CONTEXT_BUF_RDY;//�������
}

/**********************************************************************
                      TWin�ص�����ʵ��
**********************************************************************/


//---------------------ͨ������ĳЩ���򱻸��º���----------------------
void TWin_cbUpdateNotify(signed char x,signed char y, 
                         signed char w, signed char h)
{
  //�ı�ʱ,���о�����
  RowMask_t RowUpdate = 0;

  x = x; w = w;//��ֹ���ֱ���������
  if(y < 0){//������ʾ�����ֲ�����
    if(h <= y) return;//����ʾ����
    h -= y;
    y = 0; 
  }
    
  h += y;//����λ��
  if(h > TLCD_HIGH) h = TLCD_HIGH;
  for(; y < h; y++)
    RowUpdate |= RowShiftLUT[y];
  pCurTWinMng->RowUpdate |= RowUpdate; //�и��±�־
}

//---------------------ͨ������������������ʵ��----------------------------
void TWin_cbClrNowNotify(signed char x,signed char y, 
                         signed char w, signed char h)
{
  unsigned char i;
  unsigned char *pRowFlagBuf;
  if(y < 0){//������ʾ�����ֲ�����
    if(h <= y) return;//����ʾ����
    h -= y;
    y = 0; 
  }
  h += y;//����ʾ����λ��
  if(h > TLCD_HIGH) h = TLCD_HIGH;

  if(x < 0){//������ʾ�����ֲ�����
    if(w <= x) return;//����ʾ����
    w -= x;
    x = 0; 
  }
  if((w + x) > TLCD_WIDTH) w = TLCD_WIDTH - x;

  //���ý�ֹ���±�־,���������������
  //pRowFlagBuf = &pCurTWinMng->RowFlagBuf; 
  //i = TLCD_WIDTH;
  //while(i--) *pRowFlagBuf++ = DISP_CMD_DIS_UPDATE;
  //����������־
  pRowFlagBuf = &pCurTWinMng->RowFlagBuf[x];
  i = w;
  while(i--) *pRowFlagBuf++ = DISP_CMD_CLR;
  //�������������������
  pRowFlagBuf = pCurTWinMng->RowFlagBuf;
  for(; y < h; y++){
    //���ûص���������
    TWinMng_cbUpdateRow(pCurTWinMng->Lcd,x, y, w,
                        pCurTWinMng->RowBuf,pRowFlagBuf);
     
  }
}

