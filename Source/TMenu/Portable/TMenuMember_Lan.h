/* ----------------------------------------------------------------------------
 *       TMenuMember�Ķ�����Զ���
 * --------------------------------------------------------------------------*/

#ifndef __T_MENU_MEMBER_LAN_H 
#define __T_MENU_MEMBER_LAN_H

//ֱ���ض���Ϊʹ��Language.h�Ķ��壺
#include "Language.h"

#define     LAN_COUNT        LANGUAGE_COUNT

//������Զ���,����ʵ�ִ˹��ܣ�����붨�������Ի���
#define eLan_t eLanguage_t
#define eEn eEnglish
#define eCh eChinese


//������Ա��뾲̬�ṹ,���ڳ���洢����ʵ�ֵĽṹ
#define LanCode_t LanguageCode_t


//----------------------�ж��ַ����Ƿ�ȫ�Ƕ��뺯��-----------------
//δ����ʱ����0
int Lan_IsCheckSBCCaseAlign(const char *pString,unsigned int Len);


/********************************************************************
                       �ص�����
********************************************************************/
//-----------------------�õ�ϵͳ��ǰ����------------------------
//enum eLan_t GetLan(void); 
#include "GUI_Task.h"
#define GetLan() GetLanguage()


#endif

