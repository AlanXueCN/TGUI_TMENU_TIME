/* ----------------------------------------------------------------------------
 *               AVR GCC���ַ�����Դ�ļ�
 * --------------------------------------------------------------------------*/

#include "string.h"

#include "TMenuBase.h"

/*******************************************************************************
                      �ַ�������
********************************************************************************/

/* 1 */static code const char LC_PassWord_Ch[]={"����"};
/* 1 */static code const char LC_TopMenu_Ch[]={"ϵͳ�˵�"};

/* 2 */static code const char LC_SprayPaintSet_Ch[]={"�翾����"};
/* 3 */static code const char LC_SprayPaintTemp_Ch[]={"�����¶�"};

/* 4 */static code const char LC_DeviceIdSet_Ch[]={"�����ַ"};
/* 5 */static code const char LC_ShirPaintTemp_Ch[]={"�����¶�"};
/* 6 */static code const char LC_ReturnTemp_Ch[]={"�²��趨"};
/* 7 */static code const char LC_HiTempProtect_Ch[]={"���±���"};
/* 8 */static code const char LC_ShirTime_Ch[]={"����ʱ��"};

/* 9 */static code const char LC_DelaySet_Ch[]={"��ʱ����"};
/* 10 */static code const char LC_DoorTime_Ch[]={"����ת��"};
/* 11 */static code const char LC_ActDelay_Ch[]={"������ʱ"};
/* 12 */static code const char LC_V_H_Ch[]={"��ѹ����"};
/* 13 */static code const char LC_V_L_Ch[]={"��ѹ����"};

/* 14 */static code const char LC_OtherSet_Ch[]={"��������"};
/* 15 */static code const char LC_TCh1Adjust_Ch[]={"�¶�1 У׼"};
/* 16 */static code const char LC_RecoverSet_Ch[]={"�ָ���������"};
/* 15 */static code const char LC_TCh2Adjust_Ch[]={"�¶�2 У׼"};

/* 17 */static code const char LC_HandCtrl_Ch[]={"�ֶ�����"};
/* 18 */static code const char LC_HandCtrl1_Ch[]={"�ͷ�1"};
/* 19 */static code const char LC_HandCtrl2_Ch[]={"�ͷ�2"};
/* 20 */static code const char LC_HandCtrl3_Ch[]={"����1"};
/* 21 */static code const char LC_HandCtrl4_Ch[]={"����2"};
/* 22 */static code const char LC_HandCtrl5_Ch[]={"�ŷ�"};
/* 23 */static code const char LC_HandCtrl6_Ch[]={"������"};
/* 24 */static code const char LC_HandCtrl7_Ch[]={"����"};
/* 25 */static code const char LC_HandCtrl8_Ch[]={"����"};


/* 26 */static code const char LC_DeviceId_Ch[]={"�����"};
/* 26 */static code const char LC_NewPassWord_Ch[]={"������"};


/*******************************************************************************
                 ���ַ���ID�ŵõ��ַ���ͷ�����ص�����ʵ��
********************************************************************************/

const char *cbTM_pGetString(TStringSize_t StringID)
{
  switch(StringID){
  	case 0: return  NULL;    //�̶����ַ���
    case 1: return  LC_PassWord_Ch;
  	case 2: return  LC_TopMenu_Ch;

  	case 3: return  LC_SprayPaintSet_Ch;
  	case 4: return  LC_SprayPaintTemp_Ch;

  	case 5: return  LC_DeviceIdSet_Ch;

  	case 6: return  LC_ShirPaintTemp_Ch;
  	case 7: return  LC_ReturnTemp_Ch;
  	case 8: return  LC_HiTempProtect_Ch;
	case 9: return  LC_ShirTime_Ch;

	case 10: return  LC_DelaySet_Ch;
	case 11: return  LC_DoorTime_Ch;
  	case 12: return  LC_ActDelay_Ch;
	case 13: return  LC_V_H_Ch;
    case 14: return  LC_V_L_Ch;

	case 15: return  LC_OtherSet_Ch;
    case 16: return  LC_TCh1Adjust_Ch;
    case 17: return  LC_TCh2Adjust_Ch;
    case 18: return  LC_RecoverSet_Ch;

  	case 19: return  LC_HandCtrl_Ch;
  	case 20: return  LC_HandCtrl1_Ch;
  	case 21: return  LC_HandCtrl2_Ch;
  	case 22: return  LC_HandCtrl3_Ch;
  	case 23: return  LC_HandCtrl4_Ch;
  	case 24: return  LC_HandCtrl5_Ch;
  	case 25: return  LC_HandCtrl6_Ch;
  	case 26: return  LC_HandCtrl7_Ch;
  	case 27: return  LC_HandCtrl8_Ch;

    case 28: return  LC_DeviceId_Ch;
    case 29: return  LC_NewPassWord_Ch;

  	default:break;
  }
  return NULL;
}




