/*
 * user_infrare.h
 *
 *  Created on: 2018��11��17��
 *      Author: lenovo
 */

#ifndef __USER_INFRARE_H__
#define __USER_INFRARE_H__

#define INFRAED_MAX    		10
#define INFRAED_NAME_MAX_LEN	32

#define INFRAED_ALL    		(INFRAED_MAX + 1)

typedef struct tagINFRAED_VALUE							/* ��������  */
{
	UINT				uiNum;							/* ��ʱ����� */
	CHAR    			szName[INFRAED_NAME_MAX_LEN];	/* ���� 		*/
	BOOL				bEnable;						/* ʹ�� 		*/
	UINT				uiOnValue;						/* ������ֵ 	*/
	UINT				uiOffValue;						/* �ر���ֵ 	*/
}INFRAED_VALUE_S;

typedef struct tagINFRAED_Set
{
	BOOL				bIsSetting;					/* ��set����get	*/
	BOOL				bIsRefresh;					/* �Ƿ��ȡ���µ�ֵ 	*/
	UINT				uiValue;					/* ��ֵ 			*/
}INFRAED_SET_S;

extern INFRAED_SET_S g_stINFRAED_Set;

extern VOID INFRAED_InfraedInit( VOID );
extern VOID INFRAED_JudgeInfraed( VOID );

INFRAED_VALUE_S* INFRAED_GetInfraedData( UINT8 ucNum );
UINT32 INFRAED_GetInfraedDataSize();
UINT INFRARED_SaveInfraredData( INFRAED_VALUE_S* pstData );
UINT INFRAED_SetInfraed( UINT8 ucNum, UINT8 ucSwitch, UINT uiTimeOut_s );
VOID INFRARED_InfraredDataDeInit( VOID );


VOID INFRA_InfrareInit( VOID );

#endif /* __USER_INFRARE_H__ */
