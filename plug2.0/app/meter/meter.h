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
    float     fCurrent;        //��ѹ(��λA)
    float     fVoltage;        //����(��λV)
    float    fPower;            //�й�����(��λW)
    float    fApparentPower;    //���ڹ���(��λW)
    float    fPowerFactor;    //��������
    float    fElectricity;    //����(��λWh)
    float    fRunTime;        //����ʱ��(Сʱh)

    float    fUnderVoltage;        //Ƿѹ������ѹ
    float    fOverVoltage;        //��ѹ������ѹ
    float    fOverCurrent;        //����������ѹ
    float    fOverPower;            //���ر�������
    float    fUnderPower;        //��籣�������ڸɹ���ʱ�ر�

    BOOL    bUnderVoltageEnable;    //�Ƿ���Ƿѹ����
    BOOL    bOverVoltageEnable;        //�Ƿ�����ѹ����
    BOOL    bOverCurrentEnable;        //�Ƿ�����������
    BOOL    bOverPowerEnable;        //�Ƿ��������ʱ���
    BOOL    bUnderPowerEnable;         //�Ƿ�����籣�����ֻ����豸��������Զ��ϵ�

}METER_MerterInfo;


VOID METER_Init();
UINT METER_MarshalJsonMeter( CHAR* pcBuf, UINT uiBufLen );
VOID METER_RestartHandle( VOID );

VOID METER_DeinitData( VOID );
UINT METER_ReadMeterDataFromFlash( VOID );

UINT METER_ParseMeterData( CHAR* pDataStr);

float METER_GetMeterVoltage( VOID );
float METER_GetMeterCurrent( VOID );
float METER_GetMeterPower( VOID );
float METER_GetMeterApparentPower( VOID );
float METER_GetMeterPowerFactor( VOID );
float METER_GetMeterElectricity( VOID );


#endif /* __USER_METER_H__ */
