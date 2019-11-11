/*
 * user_key.c
 *
 *  Created on: 2018��10��21��
 *      Author: lenovo
 */
#include "esp_common.h"
#include "user_common.h"


VOID KEY_GetKeyTimerHandle( VOID *pPara )
{
	UINT32 uiKeyStatus = 0;
	static UINT32 uiPressCount = 0;

	uiKeyStatus = LED_GetKeyStatus();
	if ( uiKeyStatus == 0 )
	{
		uiPressCount++;

		/* �г���:����3s-6s ����apģʽ */
		if ( uiPressCount > 150 && uiPressCount < 300 )
		{
			LED_SetWifiStatus(LED_WIFI_STATUS_SET_AP);
		}
		/* ����:>6s  ����stationģʽ  */
		else if ( uiPressCount >= 300 )
		{
			LED_SetWifiStatus(LED_WIFI_STATUS_SET_STA);
		}
	}
	else
	{
		/* �̰�:����40ms-1s ���ؼ̵��� */
		if ( uiPressCount > 2 && uiPressCount < 50 )
		{
			PLUG_SetRelayReversal(TRUE);
			//LOG_OUT(LOGOUT_INFO, "replay reversal!!!");
		}
		/* �г���:����3s-6s ����apģʽ */
		else if ( uiPressCount > 150 && uiPressCount < 300 )
		{
			PLUG_SetWifiMode(WIFI_MODE_SOFTAP);
			LOG_OUT(LOGOUT_INFO, "switch ap mode, system restart!!!");
			UPGRADE_SetReboot();
		}
		/* ����:>6s  ����stationģʽ  */
		else if ( uiPressCount >= 300 )
		{
			PLUG_SetWifiMode(WIFI_MODE_STATION);
			PLUG_SetSmartConfig(FALSE);
			LOG_OUT(LOGOUT_INFO, "switch station mode, system restart!!!");
			UPGRADE_SetReboot();
		}
		uiPressCount = 0;
	}
}


VOID KEY_StartKeyHanderTimer( VOID )
{
	static xTimerHandle xKeyTimers = NULL;
	UINT32 uiKeyTimerId = 0;

	xKeyTimers = xTimerCreate("KEY_GetKeyTimerHandle", 20/portTICK_RATE_MS, TRUE, &uiKeyTimerId, KEY_GetKeyTimerHandle);
	if ( !xKeyTimers )
	{
		LOG_OUT(LOGOUT_ERROR, "xTimerCreate KEY_StartKeyHanderTimer failed.");
	}
	else
	{
		if(xTimerStart(xKeyTimers, 1) != pdPASS)
	    {
			LOG_OUT(LOGOUT_ERROR, "xTimerCreate xKeyTimers start failed.");
		}
	}
}




