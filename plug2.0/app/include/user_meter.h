/*
 * user_meter.h
 *
 *  Created on: 2019��11��17��
 *      Author: lenovo
 */

#ifndef __USER_METER_H__
#define __USER_METER_H__


typedef struct tagMeter
{
	float 	fCurrent;		//��ѹ(��λA)
	float 	fVoltage;		//����(��λV)
	float	fPower;			//�й�����(��λW)
	float	fApparentPower;	//���ڹ���
	float	fPowerFactor;	//��������
	float	fElectricity;	//����(��λW)
	float	fRunTime;		//����ʱ��

}METER_MerterInfo;


VOID METER_Init();
UINT METER_MarshalJsonMeter( CHAR* pcBuf, UINT uiBufLen );
VOID METER_RestartHandle( VOID );

VOID METER_DeinitData( VOID );
UINT METER_GetMeterData( VOID );

UINT METER_ParseMeterData( CHAR* pDataStr);

#endif /* __USER_METER_H__ */
