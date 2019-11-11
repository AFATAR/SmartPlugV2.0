/*
 * user_plug.h
 *
 *  Created on: 2018��11��2��
 *      Author: lenovo
 */

#ifndef __USER_PLUG_H__
#define __USER_PLUG_H__



#define PLUG_NAME_MAX_LEN 		32
#define PLUG_WIFI_SSID_LEN 		32
#define PLUG_WIFI_PASSWD_LEN 	64

#define PLUG_MQTT_PRODUCTKEY_LEN 	20
#define PLUG_MQTT_DEVNAME_LEN 		32
#define PLUG_MQTT_DEVSECRET_LEN 	64

#define PLUG_BIGIOT_DEVID_LEN 		64
#define PLUG_BIGIOT_APIKEY_LEN 		20
#define PLUG_BIGIOT_IFID_LEN 		20

#define PLUG_TIMER_MAX    		10
#define PLUG_DELAY_MAX    		10

#define PLUG_TIMER_ALL    		(PLUG_TIMER_MAX + 1)
#define PLUG_DELAY_ALL    		(PLUG_DELAY_MAX + 1)

#define PLUG_WEBSET_LEN 		32

#define PLUG_NAME  	"SmartPlug"



typedef struct tagPLUG_DATE
{
	INT32 	iYear;						/*  ��    */
	INT8 	iMonth;						/*  ��    */
	INT8 	iDay;						/*  ��    */
	INT8    iWeek;						/*  ����  */
	INT8 	iHour;						/*  ʱ    */
	INT8 	iMinute;					/*  ��    */
	INT8 	iSecond;					/*  ��    */

}PLUG_DATE_S;

typedef struct tagPLUG_TIME_POINT
{
	INT8 	iDay;						/*  �ڶ���    */
	INT8 	iHour;						/*  ʱ    */
	INT8 	iMinute;					/*  ��    */

}PLUG_TIME_POINT_S;


typedef enum
{
	REPET_ONCE		= 0x00,		/* ִ��һ�� */
	REPET_MON		= 0x01,		/* ÿ��һ */
	REPET_TUE		= 0x02,		/* ÿ�ܶ� */
	REPET_WED		= 0x04,		/* ÿ���� */
	REPET_THU		= 0x08,		/* ÿ���� */
	REPET_FRI		= 0x10,		/* ÿ���� */
	REPET_SAT		= 0x20,		/* ÿ���� */
	REPET_SUN		= 0x40,		/* ÿ���� */
	REPET_ALL		= 0x7F,		/* ÿ�� */

	REPET_BUFF
}PLUG_REPETITION_E;


typedef struct tagPLUG_TIMER							/*  ��ʱģ��    */
{
	UINT				uiNum;							/* ��ʱ����� */
	CHAR    			szName[PLUG_NAME_MAX_LEN];		/* ���� 		*/
	BOOL				bEnable;						/* ʹ�� 		*/
	BOOL				bOnEnable;						/* ����ʱ��ʹ��	*/
	BOOL				bOffEnable;						/* �ر�ʱ��ʹ��	*/
	PLUG_TIME_POINT_S 	stOnTime;						/* ����ʱ��		*/
	PLUG_TIME_POINT_S 	stOffTime;						/* �ر�ʱ��		*/
	PLUG_REPETITION_E	eWeek;							/* �ظ�����		*/
	BOOL				bCascode;						/* ����ʹ�� 	*/
	UINT				uiCascodeNum;					/* ���Ǹ���ʱ���� */

}PLUG_TIMER_S;



typedef struct tagPLUG_DELAY							/*  ��ʱģ��    */
{
	UINT				uiNum;							/* ��ʱ��� */
	CHAR    			szName[PLUG_NAME_MAX_LEN];		/* ���� 		*/
	BOOL				bEnable;						/* ʹ�� 		*/
	BOOL				bOnEnable;						/* ����ʱ��ʹ��	*/
	BOOL				bOffEnable;						/* �ر�ʱ��ʹ��	*/
	PLUG_TIME_POINT_S	stOnInterval;					/* ����ʱ���� */
	PLUG_TIME_POINT_S	stOffInterval;					/* �ر�ʱ���� */
	UINT				uiCycleTimes;					/* ѭ������     */
	UINT				uiTmpCycleTimes;				/* �����ʱѭ������     */
	BOOL				bCascode;						/* ����ʹ�� 	*/
	UINT				uiCascodeNum;					/* ���Ǹ���ʱ���� */
	UINT8				ucSwFlag;						/* ��ǰ��Ҫ���㿪��ʱ�仹�ǹر�ʱ�䣬2:off,1:on,0:���� */
	PLUG_TIME_POINT_S stTimePoint;						/* �������ǹر�ʱ��� */

}PLUG_DELAY_S;



typedef struct tagPLUG_SYSSET							/*  ϵͳģ��    */
{
	BOOL 	bRelayStatus;								/*  �̵���״̬    */
	BOOL 	bSmartConfigFlag;							/*  smart config�Ƿ�����    */
	UINT8 	ucWifiMode;									/* esp8266����ģʽ  1:station 2:ap */
	CHAR 	szPlugName[PLUG_NAME_MAX_LEN+1];			/* hostname  */
	CHAR    szWifiSSID[PLUG_WIFI_SSID_LEN+1];			/* wifi���� */
	CHAR    szWifiPasswd[PLUG_WIFI_PASSWD_LEN+1];		/* wifi���� */

}PLUG_SYSSET_S;

typedef struct tagPLUG_WebSet							/*  web���������    */
{
	CHAR    szModelTab[PLUG_WEBSET_LEN+1];				/* tab��ǩ */
	CHAR    szMeterRefresh[PLUG_WEBSET_LEN+1];		/* meterˢ�¼�� */

}PLUG_WEBSET_S;


typedef enum
{
	PLATFORM_NONE		= 0,		/* ���Խ� */
	PLATFORM_ALIYUN		= 1,		/* �ԽӰ����� */
	PLATFORM_BIGIOT		= 2,		/* �Խӱ������� */

	PLATFORM_BUFF
}PLATFORM_E;

typedef enum
{
	DEVTYPE_LIGHT = 0,      //��
	DEVTYPE_SOCKET,			//����
	DEVTYPE_SWITCH,			//����
	DEVTYPE_TV,				//����
	DEVTYPE_FAN,			//����
	DEVTYPE_HUMI,			//��ʪ��
	DEVTYPE_HEATER,			//ȡů��
	DEVTYPE_WATER,			//��ˮ��
	DEVTYPE_KETTLR,			//����ˮ��
	DEVTYPE_OTHER,			//����

	DEVTYPE_BUFF
}DEVTYPE_E;

typedef struct tagPLUG_PLATFORM									/*  ��ƽ̨    */
{
	PLATFORM_E 	ucCloudPlatform;								/* �Խӵ�������ƽ̨  1:�ԽӰ����� 2:�Խӱ������� */

	CHAR    	szMqttProductKey[PLUG_MQTT_PRODUCTKEY_LEN+1];	/* �ԽӰ����� mqtt��product key */
	CHAR    	szMqttDevName[PLUG_MQTT_DEVNAME_LEN+1];			/* �ԽӰ����� mqtt���豸���� */
	CHAR    	szMqttDevSecret[PLUG_MQTT_DEVSECRET_LEN+1];		/* �ԽӰ����� mqtt��Device Secret */

	DEVTYPE_E	eDevType;										/* �Խӱ��������豸���� */
	CHAR    	szBigiotDevId[PLUG_BIGIOT_DEVID_LEN+1];			/* �Խӱ��������豸id */
	CHAR    	szBigiotApiKey[PLUG_BIGIOT_APIKEY_LEN+1];		/* �Խӱ�������api key */
	CHAR		szSwitchId[PLUG_BIGIOT_IFID_LEN+1];				/* �Խӱ�����������״̬�ӿ�ID */
	CHAR		szTempId[PLUG_BIGIOT_IFID_LEN+1];				/* �Խӱ��������¶Ƚӿ�ID */
	CHAR		szHumidityId[PLUG_BIGIOT_IFID_LEN+1];			/* �Խӱ�������ʪ�Ƚӿ�ID */

}PLUG_PLATFORM_S;

typedef enum
{
	ACTION_REBOOT		= 0,		/* ���� */
	ACTION_RESET		= 1,		/* �ָ��������� */

	ACTION_BUFF
}PLUG_ACTION_E;


typedef struct tagPLUG_DevCtl							/* �����豸����     */
{
	UINT8 	ucAction;									/* �����豸���� */

}PLUG_DEVCTL_S;

typedef enum
{
	TIME_SYNC_NONE		= 0,		/* δͬ�� */
	TIME_SYNC_NET		= 1,		/* ��ͬ����ʱ�� */
	TIME_SYNC_MAN		= 2,		/* ��ͨ���ֹ�ͬ�� */

	TIME_SYNC_BUFF
}PLUG_TIME_SYNC_E;


UINT8 PLUG_GetWifiMode( VOID );
VOID PLUG_SetWifiMode( UINT8 ucWifiMode );
CHAR* PLUG_GetWifiSsid( VOID );
UINT PLUG_GetWifiSsidLenth( VOID );
VOID PLUG_SetWifiSsid( CHAR* pcWifiSsid );
CHAR* PLUG_GetWifiPasswd( VOID );
VOID PLUG_SetWifiPasswd( CHAR* pcWifiPasswd );
UINT PLUG_GetWifiPasswdLenth( VOID );

CHAR* PLUG_GetPlugName( VOID );
VOID PLUG_SetPlugName( CHAR* pcPlugName );
UINT PLUG_GetPlugNameLenth( VOID );

UINT8 PLUG_GetCloudPlatform( VOID );
VOID PLUG_SetCloudPlatform( UINT8 ucCloudPlatform );
CHAR* PLUG_GetMqttProductKey( VOID );
CHAR* PLUG_GetMqttDevName( VOID );
CHAR* PLUG_GetMqttDevSecret( VOID );
CHAR* PLUG_GetBigiotDevId( VOID );
CHAR* PLUG_GetBigiotApiKey( VOID );
CHAR* PLUG_GetBigiotSwitchId( VOID );
CHAR* PLUG_GetBigiotTempId( VOID );
CHAR* PLUG_GetBigiotHumidityId( VOID );
VOID PLUG_SetBigiotDevId( CHAR* pcDevId );
VOID PLUG_SetBigiotApiKey( CHAR* pcKey );
UINT PLUG_GetMqttDevSecretLenth( VOID );
VOID PLUG_SetMqttProductKey( CHAR* pcProductKey );
VOID PLUG_SetMqttDevName( CHAR* pcDevName );
VOID PLUG_SetMqttDevSecret( CHAR* DevSecret );

VOID PLUG_SetRelayReversal( UINT uiSaveFlag );
VOID PLUG_SetRelayOff( UINT uiSaveFlag );
VOID PLUG_SetRelayOn( UINT uiSaveFlag );
UINT8 PLUG_GetRelayStatus( VOID );
//BOOL PLUG_GetSmartConfig( VOID );
//VOID PLUG_SetSmartConfig( BOOL bStatus );


PLUG_TIMER_S* PLUG_GetTimerData( UINT8 ucNum );
PLUG_DELAY_S* PLUG_GetDelayData( UINT8 ucNum );
PLUG_SYSSET_S* PLUG_GetSystemSetData( VOID );
PLUG_PLATFORM_S* PLUG_GetPlatFormData( VOID );
UINT32 PLUG_GetTimerDataSize();
UINT32 PLUG_GetDelayDataSize();
UINT32 PLUG_GetSystemSetDataSize();

VOID PLUG_TimerDataDeInit( VOID );
VOID PLUG_DelayDataDeInit( VOID );
VOID PLUG_SystemSetDataDeInit( VOID );

UINT PLUG_MarshalJsonTimer( CHAR* pcBuf, UINT uiBufLen, UINT uiTimerNum );
UINT PLUG_MarshalJsonDelay( CHAR* pcBuf, UINT uiBufLen, UINT uiTimerNum);
UINT PLUG_MarshalJsonInfrared( CHAR* pcBuf, UINT uiBufLen, UINT uiNum );
UINT PLUG_MarshalJsonSystemSet( CHAR* pcBuf, UINT uiBufLen );
UINT PLUG_MarshalJsonHtmlData( CHAR* pcBuf, UINT uiBufLen );
UINT PLUG_MarshalJsonRelayStatus( CHAR* pcBuf, UINT uiBufLen );
UINT PLUG_MarshalJsonDate( CHAR* pcBuf, UINT uiBufLen );
UINT PLUG_MarshalJsonWebSet( CHAR* pcBuf, UINT uiBufLen );

INT32 PLUG_GetTimeFromInternet();
VOID PLUG_GetDate(PLUG_DATE_S * pstDate );
VOID PLUG_SetDate(PLUG_DATE_S * pstDate );

UINT PLUG_ParseDate( CHAR* pDateStr);
UINT PLUG_ParseTimerData( CHAR* pData );
UINT PLUG_ParseRelayStatus( CHAR* pDataStr);
UINT PLUG_ParseWebSetData( CHAR* pData );

VOID PLUG_StartJudgeTimeHanderTimer( VOID );


UINT PLUG_GetRunTime( VOID );



#endif /* __USER_PLUG_H__ */
