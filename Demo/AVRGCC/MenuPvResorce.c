/* ----------------------------------------------------------------------------
 *               AVR GCC�Ĳ˵���Ӧ��Pv���нṹʵ��
 * --------------------------------------------------------------------------*/

#include "string.h"

#include "TMenuBase.h"

/*******************************************************************************
                     Pv����ʵ��
********************************************************************************/
/* 1 TopMenu;*/static code const TMenuMemSize_t PassWordPv[] =  {1};  //�ַ���
/* 1 TopMenu;*/static code const TMenuMemSize_t TopMenuPv[] =  {3,4,5,11,6};  //�Ӳ˵�
/* 2 MTempSet*/static code const TMenuMemSize_t MSpraySetPv[] = {4,6,7,8,9};//�ַ���
/* 3 MSysInfo*/static code const TMenuMemSize_t MDeviceIdSetPv[] = {28};  //�ַ���
/* 4 MSysInfo*/static code const TMenuMemSize_t MDelaySetPv[] = {11,12,13,14,29};  //�ַ���
/* 5 MSysInfo*/static code const TMenuMemSize_t MOtherSetPv[] = {7,8,9,10};  //�Ӳ˵�

/* 6 MSysTest*/static code const TMenuMemSize_t MMHandCtrlPv[] = {20,21,22,23,24,25,26,27};//�ַ���



/*******************************************************************************
                 �ɲ˵�pvID�ŵõ�pv����ͷ�ص�����ʵ��
********************************************************************************/

const unsigned char *cbTM_pGetPvAry(TMenuMemSize_t pvID)
{
  switch(pvID){
  	case 0: return  NULL;    //��ʾΪ��
    case 1: return  PassWordPv;
  	case 2: return  TopMenuPv;
  	case 3: return  MSpraySetPv;
  	case 4: return  MDeviceIdSetPv;
  	case 5: return  MDelaySetPv;
	case 6: return  MOtherSetPv;
	case 7: return  MMHandCtrlPv;
  	default:break;
  }
  return NULL;
}



