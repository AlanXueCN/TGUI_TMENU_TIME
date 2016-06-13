/* ----------------------------------------------------------------------------
 *                TMenu�û���Ϣͨ��ģ��
 * --------------------------------------------------------------------------*/

#ifndef __T_MENU_NOTIFY_H 
#define __T_MENU_NOTIFY_H 

#include"TMenuCfg.h"
/**********************************************************************
                     ˵��
**********************************************************************/
//TMenuʹ��ֱ��ʹ�ûص�����������Ϣͨ��,��TMenu_t�ṹ��ֱ��Ƕ��
//һ��ͨ������ָ��,�ʵ���ʱ�򽫵��øú������û��ռ佻��

//��ģ������ڱ�������Ƭ����֧�ֻ�����ȷ������ָ��ʱ���滻

//Ϊʵ��֧�ֻ�֧�ֺ���ָ���ļ���,���һ���ص���ִ����������:
//1:��֧�ֺ���ָ��,��˵��ṹֱ��Ƕ��ص���������,�����û���Ϊ�ò˵��ṹ
//ָ��һ��Ψһ�ı��(�����лص�����ID�ŷ�����ͳһ����)��
//3:��TMenuNotify��ʵ��ID����ص���������ڶ�Ӧ

//������һ���ص�����ʱ,ʹ��TMenu_NOTIFY_RUN�����Ԥ����

//-------------------------TMenuͨ������ԭ��--------------------------
//����:����ͨ�����ͷ��ص�����
//void  TMenuNotify(unsigned char Type,//ͨ������
//                  //���ݲ˵�����������������������
//                  //������ṹ�ڿؼ��ﶨ��,ֱ��ָ��ת������
//                  void *pv);

//--------------------------ͨ�����Ͷ���--------------------------------------
//����:ͨ������0-63Ϊͨ��ͨ��,����Ϊ:
//���ݲ˵����ʹ��û��ռ�������
#define     TM_NOTIFY_GET_DATA    1   
//�û����ݲ˵����ʹӲ˵�ϵͳ������ݽ��к�̴���(�����)
#define     TM_NOTIFY_SET_DATA    2 
//֪ͨ�����ݱ��ı�
#define     TM_NOTIFY_CHANGED     3
//���˵�ϵͳ���ܻ�ò˵�ͷ(phHeader == NULL)ʱ,�Ӻ����ݵõ��˵�ͷ
//ͨ��ͨ������pv�βλ�ã�������һ�������ַ�
#define     TM_NOTIFY_GET_HEADER  4
//���˵�ϵͳ���ܻ����(pv == NULL)ʱ,�Ӻ����ݵõ�������
//��ʱ��ͨ������pv�β�ָ��ĵ�һ�����ݼ�ΪΪָ����
#define     TM_NOTIFY_GET_ITEM    5

//�ؼ���չͨ����ʼ,
//ͨ������64-127Ϊ�ؼ�������չ��ͨ��,���Ƽ�ͨ������һ����ظ������ظ�
#define     TM_NOTIFY_WIDGET_BASE  64

//�û���չͨ����ʼ
//ͨ������128-255Ϊ�����Զ���ͨ��,���û�������һ�㲻�����ظ�
#define     TM_NOTIFY_USER_BASE    128


/**********************************************************************
                      �ص�����ID�ŷ���
//��Χ:0-255,��ִ��ʱ��Ч�ʷ���:,Խ��ǰִ��Ч��Խ��
**********************************************************************/

//�ڲ��ؼ��ص�����ID�ŷ���,
#define   TMENU_CBFUNID_NULL_MENU           0		//��ID��,�ڲ�����,Ϊ�Ӳ˵��Ȳ���Ҫ�ص�����ʱʹ��
#define   TMENU_CBFUNID_TOP_MENU            1   //����˵�ͨ��
#define   TMENU_CBFUNID_SET_TIME            2   //ʱ������
#define   TMENU_CBFUNID_SET_POINT_GLOBAL    3   //���ȫ�ֲ�������
#define   TMENU_CBFUNID_SEL_POINT           4   //���ѡ��
#define   TMENU_CBFUNID_POINT_ITEM_MENU     5   //�����Ŀѡ��
#define   TMENU_CBFUNID_SET_POINT_PARA      6   //����������
#define   TMENU_CBFUNID_POINT_HIDDEN_MENU   7   //�����������
#define   TMENU_CBFUNIDPOINT_STATUS_PARA    8   //���״̬
#define   TMENU_CBFUNID_SYS_INFO            9   //ϵͳ��Ϣ
#define   TMENU_CBFUNID_REC_MENU            10   //��¼�˵�
#define   TMENU_CBFUNID_REC_MENU_PER        11   //��¼���Բ˵�
#define   TMENU_CBFUNID_SYS_PARA            12   //ϵͳ�������ò˵�
#define   TMENU_CBFUNID_IN_SPECTRUM         13   //�������ģʽ�˵�
#define   TMENU_CBFUNID_SET_PASS            14   //�޸ĵ�ǰ����
#define   TMENU_CBFUNID_VALID_CHANNEL       15   //��Чͨ������
#define   TMENU_CBFUNID_GET_POWER           16   //���Ȩ��
#define   TMENU_CBFUNID_FORCE_ACT           17   //ǿ�ƶ���
#define   TMENU_CBFUNID_HAND_ALARM          18   //�ֶ�����
#define   TMENU_CBFUNID_SET_SLAVE           19   //�ֶ�����
#define   TMENU_CBFUNID_POINT_USED_MENU     20   //�ֶ�����




/**********************************************************************
                         TMenu��Ϣͨ�����滻
**********************************************************************/
//���ǵ��൥Ƭ����������Ժ���ָ��֧�ֲ����������֧��,ʹ�����к�ʵ������:

//ʹ�����к괦��ͨ�������Ĵ�������ִ��:
#ifdef TMENU_DIS_P_FUN //��ֹʹ�ú���ָ��ʱ
  //1:����TMenuͨ����������,��ID�������滻ͨ������:
  typedef unsigned char TMenuNotify_t ;
  //2:����ͨ��������Ԥ����,TMenuNotifyFunΪͨ���������
  //IDΪΪÿһ���ؼ���(�û�����ģ��)�����Ψһ���
  #define TMENU_NOTIFY_PASS(TMenuNotifyFun,ID) (ID) 
  //3:ͨ��������ִ�к�
  #define TMENU_NOTIFY_RUN(TMenuNotifyFun,Type,pv) \
    TMenupFunReplace(Type,pv,TMenuNotifyFun)
    
#else   //֧�ֺ���ָ��ʱ
  //1:����TMenuͨ����������
  typedef void(*TMenuNotify_t)(unsigned char Type,//ͨ������
                              //���ݲ˵�����������������������
                              //������ṹ�ڿؼ��ﶨ��,ֱ��ָ��ת������
                              void *pv);
  //2:����ͨ��������Ԥ����,TMenuNotifyFunΪͨ���������
  //IDΪΪÿһ���ؼ���(�û�����ģ��)�����Ψһ���
  #define TMENU_NOTIFY_PASS(TMenuNotifyFun,ID) (TMenuNotifyFun) 
  //3:ͨ��������ִ�к�
  #define TMENU_NOTIFY_RUN(TMenuNotifyFun,Type,pv) \
    TMenuNotifyFun(Type,pv)
#endif

//----------------TMenu��Ϣ���ݲ�֧�ֺ���ָ����滻����------------------

#ifdef TMENU_DIS_P_FUN //��ֹʹ�ú���ָ��ʱ

void TMenupFunReplace(unsigned char Type,//ͨ������
                      //���ݲ˵�����������������������
                      //������ṹ�ڿؼ��ﶨ��,ֱ��ָ��ת������
                      void *pv,
                       TMenuNotify_t ID);   // �ص�����ID��

#else //����ʹ�ú���ָ��ʱ,�ú���������

#define TMenupFunReplace(Type,pv,ID) do{}while(0)

#endif


#endif

