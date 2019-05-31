/*
 * user_flash.c
 *
 *  Created on: 2018��11��21��
 *      Author: lenovo
 */


#include "esp_common.h"
#include "user_common.h"


UINT FlASH_Write( UINT uiAddr, CHAR* pcBuf, UINT uiLen )
{
	UINT uiRet = 0;
	UINT uiLoop = 0;
	CHAR *pcFlashBuf = NULL;
	UINT uiSectorPos = 0;
	UINT uiSectorOff = 0;
	UINT uiRemain = 0;

	uiSectorPos = uiAddr / FLASH_SEC_SIZE;	//д�������
	uiSectorOff = uiAddr % FLASH_SEC_SIZE;	//�����ڵ�ƫ�Ƶ�ַ
	uiRemain = FLASH_SEC_SIZE - uiSectorOff;	//����ʣ���С

	if ( NULL == pcBuf )
	{
	    LOG_OUT(LOGOUT_ERROR, "FlASH_Write failed, pcBuf is NULL.");
		return FAIL;
	}

	if ( uiLen == 0 )
	{
		return OK;
	}

	pcFlashBuf = malloc( FLASH_SEC_SIZE );
	if ( NULL == pcFlashBuf )
	{
	    LOG_OUT(LOGOUT_ERROR, "malloc failed, pcFlashBuf is NULL.");
		return FAIL;
	}

	//�ж�д�����ݳ����Ƿ��������ʣ���С��������״�ֻд��ʣ��������Сʣ����´���д�룬�����д��Ҫд������ݳ���
	uiRemain = uiLen >= uiRemain ? uiRemain : uiLen;
	while( 1 )
	{
		//��Ϊֻ�ܰ�������СΪ��λ����������Ҫ������������������ԭ���ݲ���ֻ�޸�Ҫд�������
		uiRet = spi_flash_read((UINT)uiSectorPos*FLASH_SEC_SIZE, (UINT*)pcFlashBuf, FLASH_SEC_SIZE);
		if ( SPI_FLASH_RESULT_OK != uiRet )
		{
		    LOG_OUT(LOGOUT_ERROR, "spi_flash_read failed, addr:0x%X, uiRet:%d", uiSectorPos*FLASH_SEC_SIZE, uiRet);
		    FREE_MEM(pcFlashBuf);
		    return FAIL;
		}

		//�޸�Ҫд�������
		for ( uiLoop = 0; uiLoop < uiRemain; uiLoop ++ )
		{
			pcFlashBuf[uiSectorOff + uiLoop] = pcBuf[uiLoop];
		}

		//д��ǰ�Ȳ�����������
		uiRet = spi_flash_erase_sector(uiSectorPos);
		if ( SPI_FLASH_RESULT_OK != uiRet )
		{
		    LOG_OUT(LOGOUT_ERROR, "spi_flash_erase_sector failed, uiSectorPos:%d, uiRet:%d", uiSectorPos, uiRet);
		    FREE_MEM(pcFlashBuf);
		    return FAIL;
		}

		//д���޸ĺ������
		uiRet = spi_flash_write((UINT)uiSectorPos*FLASH_SEC_SIZE, (UINT*)pcFlashBuf, FLASH_SEC_SIZE);
		if ( SPI_FLASH_RESULT_OK != uiRet )
		{
		    LOG_OUT(LOGOUT_ERROR, "spi_flash_write failed, addr:0x%X, uiRet:%d", uiSectorPos*FLASH_SEC_SIZE, uiRet);
		    FREE_MEM(pcFlashBuf);
		    return FAIL;
		}

		if ( uiRemain == uiLen )
		{
			break;
		}
		else
		{
			uiSectorPos ++;
			uiSectorOff = 0;

			pcBuf 	+= uiRemain;
			uiAddr 	+= uiRemain;
			uiLen   -= uiRemain;

			uiRemain = uiLen > FLASH_SEC_SIZE ? FLASH_SEC_SIZE : uiLen;
		}
	}

	FREE_MEM(pcFlashBuf);
	return OK;
}



UINT FlASH_Read( UINT uiAddr, CHAR* pcBuf, UINT uiLen )
{
	UINT uiRet = 0;
	UINT uiLoop = 0;
	CHAR *pcFlashBuf = NULL;
	UINT uiSectorPos = 0;
	UINT uiSectorOff = 0;
	UINT uiRemain = 0;

	uiSectorPos = uiAddr / FLASH_SEC_SIZE;	//����������
	uiSectorOff = uiAddr % FLASH_SEC_SIZE;	//�����ڵ�ƫ�Ƶ�ַ
	uiRemain = FLASH_SEC_SIZE - uiSectorOff;	//����ʣ���С

	if ( NULL == pcBuf )
	{
	    LOG_OUT(LOGOUT_ERROR, "FlASH_Read failed, pcBuf is NULL.");
		return FAIL;
	}

	if ( uiLen == 0 )
	{
		return OK;
	}

	pcFlashBuf = malloc( FLASH_SEC_SIZE );
	if ( NULL == pcFlashBuf )
	{
	    LOG_OUT(LOGOUT_ERROR, "malloc failed, pcFlashBuf is NULL.");
		return FAIL;
	}

	//�ж϶������ݳ����Ƿ��������ʣ���С�������һ�ξͿ��Զ�����ɣ�������Ҫ������ȡ���
	uiRemain = uiLen >= uiRemain ? uiRemain : uiLen;
	while( 1 )
	{
		//��Ϊֻ�ܰ�������СΪ��λ����������Ҫ������������������
		uiRet = spi_flash_read((UINT)uiSectorPos*FLASH_SEC_SIZE, (UINT*)pcFlashBuf, FLASH_SEC_SIZE);
		if ( SPI_FLASH_RESULT_OK != uiRet )
		{
		    LOG_OUT(LOGOUT_ERROR, "spi_flash_read failed, addr:0x%X, uiRet:%d", uiSectorPos*FLASH_SEC_SIZE, uiRet);
		    FREE_MEM(pcFlashBuf);
		    return FAIL;
		}

		//��������
		for ( uiLoop = 0; uiLoop < uiRemain; uiLoop ++ )
		{
			pcBuf[uiLoop] = pcFlashBuf[uiSectorOff + uiLoop];
		}

		if ( uiRemain == uiLen )
		{
			break;
		}
		else
		{
			uiSectorPos ++;
			uiSectorOff = 0;

			pcBuf 	+= uiRemain;
			uiAddr 	+= uiRemain;
			uiLen   -= uiRemain;

			uiRemain = uiLen > FLASH_SEC_SIZE ? FLASH_SEC_SIZE : uiLen;
		}
	}

	FREE_MEM(pcFlashBuf);
	return OK;
}


UINT FlASH_Erase( UINT uiAddr, UINT uiLen )
{
	UINT uiRet = 0;
	UINT uiLoop = 0;
	CHAR *pcFlashBuf = NULL;
	UINT uiSectorPos = 0;
	UINT uiSectorOff = 0;
	UINT uiRemain = 0;

	uiSectorPos = uiAddr / FLASH_SEC_SIZE;	//����������
	uiSectorOff = uiAddr % FLASH_SEC_SIZE;	//�����ڵ�ƫ�Ƶ�ַ
	uiRemain = FLASH_SEC_SIZE - uiSectorOff;//����ʣ���С

	pcFlashBuf = malloc( FLASH_SEC_SIZE );
	if ( NULL == pcFlashBuf )
	{
	    LOG_OUT(pcFlashBuf, "malloc pcFlashBuf is NULL.");
		return FAIL;
	}

	//�ж�д�����ݳ����Ƿ��������ʣ���С��������״�ֻд��ʣ��������Сʣ����´���д�룬�����д��Ҫд������ݳ���
	uiRemain = uiLen >= uiRemain ? uiRemain : uiLen;
	while( 1 )
	{
		if ( uiRemain == FLASH_SEC_SIZE)
		{
			uiRet = spi_flash_erase_sector(uiSectorPos);
			if ( SPI_FLASH_RESULT_OK != uiRet )
			{
			    LOG_OUT(LOGOUT_ERROR, "spi_flash_erase_sector failed, uiSectorPos:%d, uiRet:%d", uiSectorPos, uiRet);
			    FREE_MEM(pcFlashBuf);
			    return FAIL;
			}
		}
		else
		{
			uiRet = spi_flash_read((UINT)uiSectorPos*FLASH_SEC_SIZE, (UINT*)pcFlashBuf, FLASH_SEC_SIZE);
			if ( SPI_FLASH_RESULT_OK != uiRet )
			{
			    LOG_OUT(LOGOUT_ERROR, "spi_flash_read failed, addr:0x%X, uiRet:%d", uiSectorPos*FLASH_SEC_SIZE, uiRet);
			    FREE_MEM(pcFlashBuf);
			    return FAIL;
			}

			//�޸�Ҫд�������
			for ( uiLoop = 0; uiLoop < uiRemain; uiLoop ++ )
			{
				pcFlashBuf[uiSectorOff + uiLoop] = 0xFF;
			}

			//д��ǰ�Ȳ�����������
			uiRet = spi_flash_erase_sector(uiSectorPos);
			if ( SPI_FLASH_RESULT_OK != uiRet )
			{
			    LOG_OUT(LOGOUT_ERROR, "spi_flash_erase_sector failed, uiSectorPos:%d, uiRet:%d", uiSectorPos, uiRet);
			    FREE_MEM(pcFlashBuf);
			    return FAIL;
			}

			//д���޸ĺ������
			uiRet = spi_flash_write((UINT)uiSectorPos*FLASH_SEC_SIZE, (UINT*)pcFlashBuf, FLASH_SEC_SIZE);
			if ( SPI_FLASH_RESULT_OK != uiRet )
			{
			    LOG_OUT(LOGOUT_ERROR, "spi_flash_write failed, addr:0x%X, uiRet:%d", uiSectorPos*FLASH_SEC_SIZE, uiRet);
			    FREE_MEM(pcFlashBuf);
			    return FAIL;
			}
		}

		if ( uiRemain == uiLen )
		{
			break;
		}
		else
		{
			uiSectorPos ++;
			uiSectorOff = 0;

			uiAddr 	+= uiRemain;
			uiLen   -= uiRemain;

			uiRemain = uiLen > FLASH_SEC_SIZE ? FLASH_SEC_SIZE : uiLen;
		}
	}

	FREE_MEM(pcFlashBuf);
	return OK;
}






