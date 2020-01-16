/*
 * user_common.h
 *
 *  Created on: 2018��10��21��
 *      Author: lenovo
 */

#ifndef __USER_COMMON_H__
#define __USER_COMMON_H__


#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "../driver/uart.h"
#include "../driver/gpio.h"
#include "../esp8266/upgrade.h"

#include "type.h"
#include "../log/log.h"

#include "../esp8266/wifi.h"
#include "../device/led.h"
#include "../socket/socket.h"
#include "../httpserver/http.h"
#include "../httpserver/server.h"
#include "../httpserver/handle.h"
#include "../config/config.h"
#include "../device/temp.h"
#include "../common/flash.h"
#include "../esp8266/upgrade.h"
#include "../bigiot/bigiot.h"
#include "../device/infrared.h"
#include "../meter/meter.h"
#include "../websocket/websocket.h"

#ifndef GIT_COMMIT_SHA1
    #define GIT_COMMIT_SHA1 "NULL"
#endif

#define EXTIINT_NAME_LEN    (64)

typedef VOID(*fn)(VOID);


typedef struct tagExtiInt
{
    UINT            uiGPIO;            //GPIO num
    fn                 fInit;            //�жϳ�ʼ������
    fn                 fDeInit;        //�ж�ȥ��ʼ������
    fn                 fHandle;        //�жϴ�����
    CHAR            szHandleName[EXTIINT_NAME_LEN]; //�жϴ���������

}COMM_ExtiInt;

VOID COMM_ExtiIntInit(VOID);
UINT COMM_ExtiIntRegister(UINT uiNum, fn fInit, fn fDeInit, fn fHandle, CHAR *pcName);
UINT COMM_ExtiIntUnregister(UINT uiNum);



#endif /* APP_INCLUDE_USER_COMMON_H_ */
