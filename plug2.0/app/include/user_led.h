/*
 * user_gpio.h
 *
 *  Created on: 2018��10��21��
 *      Author: lenovo
 */

#ifndef __LED_GPIO_H__
#define __LED_GPIO_H__

#include "user_type.h"


typedef enum tagLED_WIFI_STATUS
{
	LED_WIFI_STATUS_OFF				= 0,	/* wifi����ʧ�ܣ����� */
	LED_WIFI_STATUS_ON				= 1, 	/* wifi������/APģʽ��ʱ����ͬ�������� */
	LED_WIFI_STATUS_FIND_WIFI		= 2, 	/* Ѱ��wifi�ȵ�,��˸���2s */
	LED_WIFI_STATUS_SYNC_TIME		= 3, 	/* APģʽ�µȴ�ͬ��ʱ��,��˸���2s */
	LED_WIFI_STATUS_CONNECTTING		= 4, 	/* ��������wifi�ȵ�,��˸���1s*/
	LED_WIFI_STATUS_SET_AP			= 5,    /* ͨ��������wifiģʽ����ΪAPģʽ����˸���0.2s */
	LED_WIFI_STATUS_SET_STA			= 6,    /* ͨ��������wifiģʽ����Ϊstationģʽ������  */


	LED_WIFI_STATUS_BUFF          	= 0xFF
}LED_WIFI_STATUS_E;


VOID LED_GpioInit( VOID );
UINT32 LED_GetKeyStatus( VOID );

VOID LED_RelayOn( VOID );
VOID LED_RelayOff( VOID );


#endif /* __LED_GPIO_H__ */
