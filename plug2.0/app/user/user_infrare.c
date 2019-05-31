/*
 * user_infrare.c
 *
 *  Created on: 2018��11��17��
 *      Author: lenovo
 */

#include "esp_common.h"
#include "user_common.h"

#define INFRA_GPIO_NUM			15

UINT32 uiInfreadValue = 0;



VOID INFRA_InfrareHandle( VOID );

/*
VOID INFRA_InfrareInit( VOID )
{
	GPIO_ConfigTypeDef stGpioConf;

	LOG_OUT(LOGOUT_INFO, "");vTaskDelay( 100/portTICK_RATE_MS );

	_xt_isr_mask(1 << ETS_GPIO_INUM);
	LOG_OUT(LOGOUT_INFO, "");vTaskDelay( 100/portTICK_RATE_MS );

	stGpioConf.GPIO_IntrType 	= GPIO_PIN_INTR_NEGEDGE;
	stGpioConf.GPIO_Mode 		= GPIO_Mode_Input;
	stGpioConf.GPIO_Pullup 		= GPIO_PullUp_EN;
	stGpioConf.GPIO_Pin 		= GPIO_ID_PIN(INFRA_GPIO_NUM);

	gpio_config( &stGpioConf );
	LOG_OUT(LOGOUT_INFO, "");vTaskDelay( 100/portTICK_RATE_MS );

	GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, TRUE);
	LOG_OUT(LOGOUT_INFO, "");vTaskDelay( 100/portTICK_RATE_MS );

	gpio_intr_handler_register(INFRA_InfrareHandle, NULL);
	LOG_OUT(LOGOUT_INFO, "");vTaskDelay( 100/portTICK_RATE_MS );

	_xt_isr_unmask(1 << ETS_GPIO_INUM);
	printf("INFRA_InfrareInit\r\n");
}
*/


VOID INFRA_InfrareInit( VOID )
{

    GPIO_ConfigTypeDef pGPIOConfig;
    printf("111\r\n");
    gpio_intr_handler_register(INFRA_InfrareHandle, NULL);
    printf("222\r\n");
	pGPIOConfig.GPIO_IntrType = GPIO_PIN_INTR_NEGEDGE;
	pGPIOConfig.GPIO_Pullup = GPIO_PullUp_EN;
	pGPIOConfig.GPIO_Mode = GPIO_Mode_Input;
	pGPIOConfig.GPIO_Pin = GPIO_ID_PIN(INFRA_GPIO_NUM);
	gpio_config(&pGPIOConfig);
	printf("33\r\n");
    //enable gpio iterrupt
    _xt_isr_unmask(1<<ETS_GPIO_INUM);
    printf("444\r\n");
}


VOID INFRA_InfrareHandle( VOID )
{
	static UINT32 infreadValue = 0;	/* ����ĺ���ֵ */
	static UINT32 uiCurTime = 0;
	static UINT32 uiLastTime = 0;
	static UINT8  Step = 0;
	static UINT uiPluse = 0;
	static uint8_t  BitCount = 0;   	/* BitCount����32ʱ������� */

	//GPIO_INPUT_GET( GPIO_ID_PIN(INFRA_GPIO_NUM) );
	_xt_isr_mask(1 << ETS_GPIO_INUM);
	GPIO_REG_WRITE( GPIO_STATUS_W1TC_ADDRESS, TRUE );

	printf("INFRA_InfrareHandle\r\n");

	uiCurTime = system_get_time();

	/* ����2���½�������ʱ�� */
	if ( uiCurTime > uiLastTime )
	{
		uiPluse = uiCurTime - uiLastTime;
	}
	else
	{
		uiPluse = 0xFFFFFFFF + uiCurTime - uiLastTime;
	}

	uiLastTime = uiCurTime;

    switch ( Step )
    {
        case 0 :
            /* ������ߵ�ƽ9ms���͵�ƽ4.5ms  �ж��Ƿ������ɹ� */
            if ( 13000 < uiPluse && 14000 > uiPluse )
            {
                Step = 1;
                BitCount = 0;
            }
            else
            {
                Step = 0;
            }
            break;
        case 1 :
			/* ��ʼ���� */
			infreadValue <<= 1;
            BitCount ++;
            /* ����1 �á��ߵ�ƽ0.56ms���͵�ƽ1.69ms=2.25ms����ʾ */
            if ( 2000 < uiPluse && 2500 > uiPluse )
            {
            	/* ��λΪ1 */
                infreadValue |= 0x01;
            }
            /* ��������ʱ0 �á�0.56ms �ߵ�ƽ��0.565ms �͵�ƽ=1.125ms����ʾ */
            else if ( 1000 < uiPluse && 1300 > uiPluse )
            {
            	/* ��λΪ0 */
            }
            else
            {
            	/* ���ܱ�ʶ�����ó�ʼ���� */
                BitCount = 0;
                Step = 0;
            }

			/* ������� */
            if ( 32 <= BitCount )
            {
                Step = 0;
                uiInfreadValue = infreadValue;
            }
            break;
        default:
            break;
    }

    _xt_isr_unmask(1 << ETS_GPIO_INUM);
}







