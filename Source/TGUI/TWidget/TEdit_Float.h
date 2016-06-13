/* ----------------------------------------------------------------------------
 *                TGUI�༭��-����������������ظ�������
 * --------------------------------------------------------------------------*/

#ifndef __T_EDIT_FLOAT_H 
#define __T_EDIT_FLOAT_H

//----------------�༭����������ʼ������--------------------
void TEditFloat(TEdit_t *pEdit,
              TWinHandle_t hWin,    //�����Ĵ���,���ݻ�����>Len
              float Value,            //��ʼ��ֵ
              float Max,              //���ֵ
              float Min,              //��Сֵ
              unsigned char DotPos,  //��ȷ��С����λ��
              unsigned char Flag,  //�������
              TGUINotify_t cbGUINotify); //ͨ������

/**********************************************************************
                          ��������
**********************************************************************/

//----------------������ת��ΪTSigned_t����ռλ����--------------------
//�˺�����Data2Float�ɶ�ʹ��,TSigned_tռλӦ>=floatռλ
TSigned_t Float2Data(float Value);

//-----------TSigned_t���͸�����ռλת���ظ���������--------------------
//�˺�����Float2Data�ɶ�ʹ��,TSigned_tռλӦ>=floatռλ
float Data2Float(TSigned_t Data);

//----------------�ɸ�������ֵ�õ�ռλ����,��������--------------------
unsigned char GetFloatLen(float Min,float Max,
                          unsigned char DotPos);  //��ȷ��С����λ��

//-----------------����־������ת��Ϊ�ַ�������------------------
//����������ĩδ�û�����λ��
char *pFloat2StringFlag(float Value,   //��ǰ��ֵ
                      char *pBuf,    //���ջ�����
                      unsigned char Len,    //��ʾ����
                      //��־,����Ϊ����3bit:С����λ��,0x80:��ʾ������
                      unsigned char Flag);

#endif

