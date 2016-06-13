/**************************************************************************
             TMenu�ṹʵ�ּ���س�Ա����������KeilC51�е�ʵ�����
//��ԭ��Ĭ�Ͻṹ�Ļ�����,������ǿ�ƶ������֧�����ѡ������ұ�֧��
**************************************************************************/

#ifndef __T_MENU_MEMBER_KEIL_C51
#define __T_MENU_MEMBER_KEIL_C51

#include "TMenuMember_Lan.h"        //ǿ�ƶ������֧��

//����Ӧ��,����˵���������:
struct _TMenu{
  unsigned char Type;      //�˵����ͼ���ر�־
  unsigned char Size;       //�ɲ˵����;�����������ݴ�С
  const LanCode_t *pgHeader; //�˵�ͷ,ΪNULLʱ�ӻص����ȡ
  const struct _TMenu *pParent;   //���ѵĸ��˵�
  const void *pv;           //���ݲ˵�����ȷ�������ɲ���ָ��
  TMenuNotify_t cbNotify;     //���û��ռ佻����ͨ������
};

/********************************************************************
                       ��ѡ������ұ�ṹ֧��
********************************************************************/

//Ϊ֧�������ݸ���ϵͳ��¼�û�Ȩ�޾����Ƿ���ʾ�Ĺ���,������������ұ�֧��
#define   TM_EN_LUT     //�Ƿ�֧�ֲ��ұ�(�ڲ�ʵ��ʹ��)

#ifdef TM_EN_LUT   //���ұ�֧��ʱ:
  //����Size�ṹ���λ��ʾ�ýṹ��������ұ�
  #define   TM_TYPE_ITEM_LUT     0x80
  
  //��������ұ�ʱ,�û�����������Ӧ�����û�ͨ����ȡ���ұ�ṹ(��䴫���pvָ��)
  #define    TM_NOTIFY_USER_GET_LUT    (TM_NOTIFY_USER_BASE + 0)
  //���ұ�ṹ����Ϊһ������:����
  //��λ: �˲��ұ��С,<= struct _TMenu�е�Size
  //����˲��С������,��
  //static code const unsigned char _LUT = {2,  0,3}; 
  
  //������������,���ڲ��ڽ����ұ���
  #define   TM_ITEM_MAX         10

  //-------------------���ݵ�ǰ�˵����ұ�����ѡλ��---------------------
  unsigned char TMenu_GetItemPosWithLUT(unsigned char Pos);

#endif


/********************************************************************
                       ��ѡ�Ķ�̬�˵�����֧��
********************************************************************/

#define   TM_DYNC_MENU     //��̬�˵�֧��

#ifdef TM_DYNC_MENU   //��̬�˵�֧��ʱ:  
  
  //���¸��˵�ͨ�� ���¸��˵��ṹ(pvָ������)
  #define    TM_NOTIFY_USER_UPDATE_PARENT    (TM_NOTIFY_USER_BASE + 1)

  //�����Ӳ˵�ͨ�� ����ָ���Ӳ˵��ṹ(pvָ��ָ��ǰ�Ӳ˵���ID��)
  #define    TM_NOTIFY_USER_UPDATE_SUB    (TM_NOTIFY_USER_BASE + 2)
  
#endif


#endif


