/**************************************************************************
                        TMenu��س�Ա��������ʵ��
  ��û�ж���TMENU_USE_CONST_BUFʱ��غ�����ʵ��,�����û���ʵ�����к���
  Menu_t�ṹ�е�ʹ��ָ������г�Աͨ���˺�����������Ϣ
**************************************************************************/
#include "TMenuCfg.h"
#include "TMenu.h"
#include "string.h"

extern code TMenu_t MGetPower; //������code���Ķ���˵�

#ifdef TM_EN_LUT
static unsigned char _ItemLUT[TM_ITEM_MAX + 1];//���嵱ǰ���ұ�
#endif

//----------------------������ұ�----------------------------
#ifdef TM_EN_LUT
#define _GetItemLUT(pMenu) \
do{\
  if((pMenu)->Size & TM_TYPE_ITEM_LUT)\
    TMENU_NOTIFY_RUN((pMenu)->cbNotify,TM_NOTIFY_USER_GET_LUT,_ItemLUT);\
}while(0)

#else
#define _GetItemLUT(pMenu) do{ }while(0)
#endif

//--------------------�õ�����˵��ṹ--------------------------
const TMenu_t *TM_pGetTopMenu(void)
{
  _GetItemLUT(&MGetPower); //������ұ�
  return &MGetPower;      //ָ�򻺴�
}

//---------------------�õ����˵��ṹ����----------------------------
const TMenu_t *TM_pGetParent(const TMenu_t *pMenu)
{
  pMenu = pMenu->pParent;
  _GetItemLUT(pMenu); //������ұ�
  return pMenu;
}

//-------------------------����Ӳ˵��ṹ����------------------------
const TMenu_t *TM_pGetSubMenu(const TMenu_t *pMenu,
                              unsigned char SubMenuID)
{
  TMenu_t code *code *PAry = (TMenu_t code *code *)pMenu->pv;  //C51�ķ�ʽ

  #ifdef TM_EN_LUT//�б�ʱ�Ȳ��
  if(pMenu->Size & TM_TYPE_ITEM_LUT) SubMenuID = _ItemLUT[SubMenuID + 1];
  #endif

  pMenu = *(PAry + SubMenuID);
  _GetItemLUT(pMenu); //������ұ�
  return pMenu;
}


//-------------------------���ָ���˵��ṹ����------------------------
const TMenu_t *TM_pGetMenu(const TMenu_t *pMenu,   //ǿ����ת�Ĳ˵��ṹ
                           unsigned short MenuID) //���ɲ���,�����ڲ˵�ʶ��
{
  MenuID = MenuID;
  _GetItemLUT(pMenu); //������ұ�
  return pMenu;   //�ýṹ����ָ���Ĳ˵�
}

//-------------------�Ӳ˵��ṹ��ò˵�ͷ����-------------------
const char *TM_GetHeader(const TMenu_t *pMenu)
{
  char *pBuf;
  if(pMenu->pgHeader)
    return pMenu->pgHeader->pLan[GetLan()];

  //�˵���û��,���û��ռ��ȡ:
  pBuf = TMenu_pGetBuf();
  TMENU_NOTIFY_RUN(pMenu->cbNotify,TM_NOTIFY_GET_HEADER,pBuf);
  return pBuf;
}

//-------------------�Ӳ˵��ṹ������ͺ���------------------------
unsigned char TM_GetType(const TMenu_t *pMenu)
{
  return pMenu->Type;
}

//-------------------�Ӳ˵��ṹ��ô�С����------------------------
unsigned char TM_GetSize(const TMenu_t *pMenu)
{
  #ifdef TM_EN_LUT  //�в��ұ�ʱ�ض��򵽲��ұ��С:
  if(pMenu->Size & TM_TYPE_ITEM_LUT) return _ItemLUT[0];
  #endif  

  return pMenu->Size;
  
}

//----------------�õ�ָ���Ӳ˵���ͷ����-------------------
const char *TM_GetSubMenuHeader(const TMenu_t *pMenu,
                                unsigned char Item)
{
  //�õ��Ӳ˵��ṹ
  TMenu_t code *code *PAry = (TMenu_t code *code *)pMenu->pv;  //C51�ķ�ʽ

  #ifdef TM_EN_LUT//�б�ʱ�Ȳ��
  if(pMenu->Size & TM_TYPE_ITEM_LUT) Item = _ItemLUT[Item + 1];
  #endif

  pMenu = *(PAry + Item);
  return TM_GetHeader(pMenu);
}

//-------------------�Ӳ˵��ṹ������ַ�������-------------------
const char *TM_GetItemString(const TMenu_t *pMenu,
                             unsigned char Item)
{
  char *pBuf;

  #ifdef TM_EN_LUT  //�в��ұ�ʱ�ض��򵽲��ұ�
  if(pMenu->Size & TM_TYPE_ITEM_LUT) Item = _ItemLUT[Item + 1];
  #endif

  if(pMenu->pv)
    return (((const LanCode_t *)pMenu->pv) + Item)->pLan[GetLan()];

  //���û��ռ�������
  pBuf = TMenu_pGetBuf();
  *pBuf = Item;
  TMENU_NOTIFY_RUN(pMenu->cbNotify,TM_NOTIFY_GET_ITEM,pBuf);
  return pBuf;
}

//-------------------ͳ�Ʋ˵�������Ⱥ���-----------------------
TItemSize_t TM_GetItemMaxLen(const TMenu_t *pMenu)
{
  //���ұ�֧��
  unsigned char Size = TM_GetSize(pMenu);
  unsigned char i;
  TItemSize_t ItemW = 0,CurW;
  if((pMenu->Type & TMTYPE_MASK) == TMTYPE_SUBMENU){//�Ӳ˵�ģʽ���Ӳ˵���ȡ����
    for(i = 0; i < Size; i++){
      CurW = strlen(TM_GetSubMenuHeader(pMenu,i));
      if(CurW > ItemW) ItemW = CurW;
    }
  }
  else{//ֱ����Ϊ��pv�Ｔ���ַ���
    for(i = 0; i < Size; i++){
      CurW = strlen(TM_GetItemString(pMenu,i));
      if(CurW > ItemW) ItemW = CurW;
    }
  }
  return ItemW;
}



