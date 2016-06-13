/* ----------------------------------------------------------------------------
 *               AVR GCC�Ĳ˵���Դ�ļ�
 * --------------------------------------------------------------------------*/

#include "string.h"

#include "TMenuBase.h"

/*******************************************************************************
                      �ⲿ�˵����������
********************************************************************************/
/* 1 */extern code TMenu_t PassWord;
/* 1 */extern code TMenu_t TopMenu;
/* 2 */extern code TMenu_t MSpraySet;
/* 3 */extern code TMenu_t MDeviceIdSet;
/* 4 */extern code TMenu_t MDelaySet;
/* 5 */extern code TMenu_t MOtherSet;
/* 6 */extern code TMenu_t MAC220Set;
/* 7 */extern code TMenu_t MTCh12Adjust;				
/* 8 */extern code TMenu_t MTCh34Adjust;
/* 9 */extern code TMenu_t MRecoverSet;
/* 10*/extern code TMenu_t MHandCtrl;

/*******************************************************************************
                 �ɲ˵�ID�ŵõ��˵��洢�ṹͷ�ص�����ʵ��
********************************************************************************/

const TMenu_t *cbTM_pGet(TMenuMemSize_t TMenuID)
{
  switch(TMenuID){
  case 0: return NULL;      //�˵�Ϊ0��ʾΪ��
  case 1: return  &PassWord;
  case 2: return  &TopMenu;
  case 3: return  &MSpraySet;
  case 4: return  &MDeviceIdSet;
  case 5: return  &MDelaySet;
  case 6: return  &MOtherSet;
    case 7:  return &MAC220Set;
    case 8: return  &MTCh12Adjust;
    case 9: return  &MTCh34Adjust;
    case 10: return  &MRecoverSet;
  case 11: return  &MHandCtrl;

  default:break;
  }
  return NULL;
}




