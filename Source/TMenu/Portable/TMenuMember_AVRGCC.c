/**************************************************************************
             TMenu��س�Ա����������AVR GCC�е�ʵ��
**************************************************************************/
//��AVR GCC��֧�ִ�����ָ�����,��ʹ�û���ʵ��

#include "TMenuCfg.h"
#include "TMenu.h"

#include "string.h"

//��ӣ��õ���Աƫ��
#define struct_offset(type, member) ((unsigned char)(&((type *)0)->member))      


//#define memcpy_P(pv,pv1,size) memcpy(pv,pv1,size) //����
//#define strcpy_P(pv,pv1) strcpy(pv,pv1) //����

#define   TMENU_MEM_ID_NULL    0   //�޲˵���ʱ�̶�Ϊ0
#define   TMENU_MEM_STRING_ID_NULL    0   //�ַ���IDΪ0��ʾΪ��

//----------------------������ұ�----------------------------
#ifdef TM_EN_LUT
static unsigned char _ItemLUT[TM_ITEM_MAX + 1];//���嵱ǰ���ұ�
#endif

#ifdef TM_EN_LUT
#define _GetItemLUT(pMenu) \
do{\
  if((pMenu)->Size & TM_TYPE_ITEM_LUT)\
    TMENU_NOTIFY_RUN((pMenu)->cbNotify,TM_NOTIFY_USER_GET_LUT,_ItemLUT);\
}while(0)

#else
#define _GetItemLUT(pMenu) do{ }while(0)
#endif



/**********************************************************************
                       AVR GCC�˵��������
**********************************************************************/


static TMenu_t _MenuBuf;              //��ǰ�˵��ṹ����
static char _StringBuf[TLCD_WIDTH + 10];  //һ�е��ַ�������

//--------------------�õ�ָ��ID�ŵĲ˵��ṹ-------------------
static const TMenu_t *_pGetTMenu(TMenuMemSize_t TMenuID)
{
  memcpy_P(&_MenuBuf,cbTM_pGet(TMenuID),
             sizeof(TMenu_t));  //���ڴ�ṹ
  _GetItemLUT(&_MenuBuf); //������ұ�
  return &_MenuBuf;
}

//--------------------�õ��Ӳ˵��洢�ṹID��-------------------
static TMenuMemSize_t _GetSubMenuID(unsigned char Item)
{
  TMenuMemSize_t TMenuID;
  //�õ��ڳ���洢��������ͷ
  const unsigned char *pPvAry = 
    (const unsigned char *)cbTM_pGetPvAry(_MenuBuf.pvAryID);                 
  //�ҵ���ǰ��λ��
  pPvAry += Item * sizeof(TMenuMemSize_t);
  //��ȡ�˵��洢�ṹID��
  memcpy_P(&TMenuID,pPvAry,sizeof(TMenuMemSize_t));
  return TMenuID;
}

//--------------------�õ�����˵��ṹ--------------------------
//�����ڶ�����˵�ʱ�����޸Ĵ˺�������ϵͳӦ����ת��ͬ�����˵�
#include "AKeyState.h"
const TMenu_t *TM_pGetTopMenu(void)
{
  //if((ePKState == PKS_PManual) || (ePKState == PKS_KManual)) return _pGetTMenu(11);
  return _pGetTMenu(1);
}

//---------------------�õ����˵��ṹ����----------------------------
const TMenu_t *TM_pGetParent(const TMenu_t *pMenu)
{
  pMenu = pMenu;//��ֹ���뾯��
  if(!_MenuBuf.ParentID) return NULL;//������
	return _pGetTMenu(_MenuBuf.ParentID);
}

//-------------------�Ӳ˵��ṹ����Ӳ˵��ṹ����-------------------
const TMenu_t *TM_pGetSubMenu(const TMenu_t *pMenu,
                               unsigned char SubMenuID)
{
  pMenu = pMenu;//��ֹ���뾯��
  
  #ifdef TM_EN_LUT//�б�ʱ�Ȳ��
  if(pMenu->Size & TM_TYPE_ITEM_LUT) SubMenuID = _ItemLUT[SubMenuID + 1];
  #endif
  
  return _pGetTMenu(_GetSubMenuID(SubMenuID));
}


//-------------------------���ָ���˵��ṹ����------------------------
const TMenu_t *TM_pGetMenu(const TMenu_t *pMenu,   //ǿ����ת�Ĳ˵��ṹ
                           unsigned short MenuID) //���ɲ���,����Ϊ�˵���ID��
{
  pMenu = pMenu;
  return _pGetTMenu(MenuID); 
}

//-------------------�Ӳ˵��ṹ��ò˵�ͷ����-------------------
const char *TM_GetHeader(const TMenu_t *pMenu)
{
  TStringSize_t StringID = _MenuBuf.HeaderID[GetLan()];
  
  pMenu = pMenu;//��ֹ���뾯��
  if(!StringID){//�ַ�Ϊ��ʱ,���û��ռ��ȡ:
    TMENU_NOTIFY_RUN(pMenu->cbNotify,TM_NOTIFY_GET_HEADER,_StringBuf);
    return _StringBuf;
  }
  //���ַ����ж�ȡ
  strcpy_P(_StringBuf,cbTM_pGetString(StringID));
  return _StringBuf;
}

//-------------------�Ӳ˵��ṹ������ͺ���------------------------
unsigned char TM_GetType(const TMenu_t *pMenu)
{
  pMenu = pMenu;
  return _MenuBuf.Type;
}

//-------------------�Ӳ˵��ṹ��ô�С����------------------------
unsigned char TM_GetSize(const TMenu_t *pMenu)
{
  pMenu = pMenu;
  
  #ifdef TM_EN_LUT  //�в��ұ�ʱ�ض��򵽲��ұ��С:
  if(_MenuBuf.Size & TM_TYPE_ITEM_LUT) return _ItemLUT[0];
  #endif
  
  return _MenuBuf.Size; 
}

//----------------�õ�ָ���Ӳ˵���ͷ����-------------------
const char *TM_GetSubMenuHeader(const TMenu_t *pMenu,
                                unsigned char Item)
{
  TStringSize_t StringID;
  const unsigned char *pPos;
  TMenuNotify_t cbCurNotify;
  
  #ifdef TM_EN_LUT//�б�ʱ�Ȳ��
  if(pMenu->Size & TM_TYPE_ITEM_LUT) Item = _ItemLUT[Item + 1];
  #endif
  
  //�õ��Ӳ˵��洢λ��
  const TMenu_t *pTMenuMem = cbTM_pGet(_GetSubMenuID(Item));
  //�õ�HeaderID��������ʼλ��
  pPos = (unsigned char*)pTMenuMem + struct_offset(TMenu_t,HeaderID);
  //�õ���ǰ���ֶ�Ӧλ��
  pPos += GetLan() * sizeof(TStringSize_t);
  //�õ��ַ���ID
  memcpy_P(&StringID,pPos,sizeof(TStringSize_t));

  if(!StringID){//���û��ռ��ȡ
    pPos = (unsigned char*)pTMenuMem + struct_offset(TMenu_t,cbNotify);
    memcpy_P(&cbCurNotify,pPos,sizeof(TMenuNotify_t));
    TMENU_NOTIFY_RUN(cbCurNotify,TM_NOTIFY_GET_HEADER,_StringBuf);
  }
  //�õ��ַ���
  else{
    strcpy_P(_StringBuf,cbTM_pGetString(StringID));
    pMenu = pMenu;//��ֹ���뾯��
  }
  return _StringBuf;
}

//-------------------�Ӳ˵��ṹ������ַ�������-------------------
const char *TM_GetItemString(const TMenu_t *pMenu,
                             unsigned char Item)
{
  TStringSize_t StringID;
  
  #ifdef TM_EN_LUT  //�в��ұ�ʱ�ض��򵽲��ұ�
  if(pMenu->Size & TM_TYPE_ITEM_LUT) Item = _ItemLUT[Item + 1];
  #endif
  
  //�õ��ڳ���洢��������ͷ
  const unsigned char *pPvAry = 
    (const unsigned char *)cbTM_pGetPvAry(_MenuBuf.pvAryID); 
  //�ҵ���ǰ��λ��
  pPvAry += Item * (LAN_COUNT * sizeof(TStringSize_t));
  //��ȡ�ַ���ID�Ŷ�Ӧ�ַ�
  memcpy_P(&StringID,pPvAry,sizeof(TStringSize_t));
  //�õ��ַ���
  strcpy_P(_StringBuf,cbTM_pGetString(StringID));
  pMenu = pMenu;//��ֹ���뾯��

  return _StringBuf;
}

//-------------------ͳ�Ʋ˵�������Ⱥ���-----------------------
TItemSize_t TM_GetItemMaxLen(const TMenu_t *pMenu)
{
  unsigned char Size = pMenu->Size;
  unsigned char i;
  TItemSize_t ItemW = 0,CurW;

  //��ǰ�˵�Ϊ�Ӳ˵�����ʱ���Ӳ˵�ͷ���ǵ�ǰ��
  if((pMenu->Type & TMTYPE_MASK) == TMTYPE_SUBMENU){
    for(i = 0; i < Size; i++){
      CurW = strlen(TM_GetSubMenuHeader(pMenu,i));
      if(CurW > ItemW) ItemW = CurW;
    }
  }
  //����ֱ�Ӿ����ַ��нṹ
  else{
    for(i = 0; i < Size; i++){
      CurW = strlen(TM_GetItemString(pMenu,i));
      if(CurW > ItemW) ItemW = CurW;
    }
  } 
  return ItemW;
}









