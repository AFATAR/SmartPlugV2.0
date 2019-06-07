/*
 * user_http.h
 *
 *  Created on: 2018��11��11��
 *      Author: lenovo
 */

#ifndef __USER_HTTP_H__
#define __USER_HTTP_H__

#define HTTP_HOST_MAX_LEN 		30
#define HTTP_URL_MAX_LEN 		50
#define HTTP_HANDLE_MAX_LEN 	50

#define HTTP_ROUTER_MAP_MAX 	40

#define HTTP_FILE_NAME_MAX_LEN	50
#define HTTP_FILE_NUM_MAX		20


#define HTTP_Malloc(ctx, len) 											\
do{																		\
	if ( ctx->stResp.pcResponBody == NULL )								\
	{																	\
		ctx->stResp.pcResponBody = ( CHAR* )malloc( len );				\
		if ( NULL == ctx->stResp.pcResponBody ){						\
			LOG_OUT(LOGOUT_ERROR, "malloc buf size:%d failed, Free heap:%d",\
					len, system_get_free_heap_size());				\
			return FAIL;												\
		}																\
		ctx->stResp.uiSendBufLen = len;									\
	}																	\
}while(0);


#define HTTP_IS_SEND_FINISH(ctx) (ctx->stResp.uiSendTotalLen > 0 && ctx->stResp.uiSentLen >= ctx->stResp.uiSendTotalLen)


typedef enum {
	HTTP_METHOD_GET = 0,
	HTTP_METHOD_POST,
	HTTP_METHOD_HEAD,
	HTTP_METHOD_PUT,
	HTTP_METHOD_DELETE,

	HTTP_METHOD_BUFF
}HTTP_METHOD_E;


typedef enum {
	HTTP_USERAGENT_WINDOWNS = 0,	/* windowns ƽ̨������������������IE��chrome��*/
	HTTP_USERAGENT_ANDROID,			/* ��׿�ֻ��˷�������� */
	HTTP_USERAGENT_CURL,			/* curl���������� */
	HTTP_USERAGENT_WGET,			/* wget���������� */

	HTTP_USERAGENT_BUFF
}HTTP_USERAGENT_E;


typedef enum {
	HTTP_PROCESS_None = 0,		//����״̬
	HTTP_PROCESS_Invalid,		//�յ����������޷�������http header��Ϣ���������ֱ�ӷ���400
	HTTP_PROCESS_GotHeader,		//http header�������
	HTTP_PROCESS_GetBody,		//httpЯ����body������޷�һ��recv�����Ҫ�ֶ�ν���
	HTTP_PROCESS_Finished,		//��ɽ���,��ʼ���ͳɹ�����Ӧ

	HTTP_PROCESS_Buff
}HTTP_PROCESS_E;


typedef enum {
	HTTP_CODE_Ok = 0,
	HTTP_CODE_Created,
	HTTP_CODE_Found,
	HTTP_CODE_BadRequest,
	HTTP_CODE_NotFound,
	HTTP_CODE_InternalServerError,

	HTTP_CODE_Buff
}HTTP_CODE_E;

typedef enum {
	HTTP_CONTENT_TYPE_Html = 0,
	HTTP_CONTENT_TYPE_Js,
	HTTP_CONTENT_TYPE_Css,
	HTTP_CONTENT_TYPE_Json,
	HTTP_CONTENT_TYPE_Icon,
	HTTP_CONTENT_TYPE_Png,
	HTTP_CONTENT_TYPE_Gif,

	HTTP_CONTENT_TYPE_Stream,
	HTTP_CONTENT_TYPE_Buff
}HTTP_CONTENT_TYPE_E;

typedef enum {
	HTTP_CACHE_CTL_TYPE_No = 0,
	HTTP_CACHE_CTL_TYPE_MaxAge_1h,
	HTTP_CACHE_CTL_TYPE_MaxAge_1d,
	HTTP_CACHE_CTL_TYPE_MaxAge_1w,
	HTTP_CACHE_CTL_TYPE_MaxAge_1m,
	HTTP_CACHE_CTL_TYPE_MaxAge_1y,

	HTTP_CACHE_CTL_TYPE_Buff
}HTTP_CACHE_CTL_TYPE_E;


typedef struct tagHttpResponseHead
{
	HTTP_CODE_E				eHttpCode;
	HTTP_CONTENT_TYPE_E 	eContentType;
	HTTP_CACHE_CTL_TYPE_E	eCacheControl;

	UINT 					uiSendBufLen;					// ���ͻ�������С

	UINT 					uiHeaderLen;					// ��Ӧͷ����
	UINT 					uiBodyLen;						// ��Ӧ�峤��
	UINT 					uiPos;							// λ��

	UINT 					uiSendTotalLen;					// Ӧ�����ܳ��ȳ���
	UINT 					uiSentLen;						// �ѷ��ͳ���
	UINT					uiSendCurLen;					// ����Ӧ���ͳ���
	CHAR*					pcResponBody;					// Ӧ����
	BOOL					bIsCouldSend;

}HTTP_RESP_S;

typedef struct tagHttpRequest
{
	HTTP_METHOD_E 		eMethod;						// GET, POST PUT DELETE
	CHAR 				szURL[HTTP_URL_MAX_LEN];       	// /index.html
	HTTP_USERAGENT_E 	eUserAgent;	    				// windows, Android,
	CHAR 				szHost[HTTP_HOST_MAX_LEN];     	// 192.168.0.102:8080

	CHAR*               pcRouter;						//ƥ�䵽��Router

	HTTP_PROCESS_E		eProcess;
	UINT 				uiRecvTotalLen;					// ����body�峤�ȣ�������head����
	UINT 				uiRecvLen;						// ���յ�body�ĳ���
	UINT 				uiRecvCurLen;					// �����յ�body�ĳ���
	CHAR*				pcResqBody;						// ������

}HTTP_REQ_S;

typedef struct tagHttpCtx
{
	INT				iClientFd;
	UINT			uiCostTime;
	HTTP_REQ_S     	stReq;
	HTTP_RESP_S		stResp;

}HTTP_CTX;

typedef enum {
	RESULT_Fail = 0,
	RESULT_Success,
	RESULT_Finish,

	RESULT_Buff
}HTTP_FILE_RESULT_E;

typedef enum {
	STATUS_Close = 0,
	STATUS_Open,

	STATUS_Buff
}HTTP_FILE_STATUS_E;

typedef struct tagHttpFile
{
	CHAR*				pcName;
	UINT				uiLength;
	UINT				uiAddr;
	UINT				uiPos;
	HTTP_FILE_STATUS_E	eStatus;
	HTTP_CONTENT_TYPE_E	eType;
}HTTP_FILE_S;

typedef UINT (*ROUTER_FUN)(HTTP_CTX *pstCtx);

typedef struct tagHttpRouterMap
{
	HTTP_METHOD_E 		eMethod;									/* GET, POST PUT DELETE */
	CHAR 				szURL[HTTP_URL_MAX_LEN];    				/* URL��ַ */
	ROUTER_FUN 			pfHttpHandler;								/* �ص����� */
}HTTP_ROUTER_MAP_S;


typedef struct tagHttpFileList
{
	CHAR 				szName[HTTP_FILE_NAME_MAX_LEN];	//�ļ�����
	BOOL				bIsUpload;						//�����Ƿ����ϴ�
	UINT32				uiAddr;							//������FLASH�еĴ�ŵ�ַ
	UINT32				uiLength;						//���ݳ���
	HTTP_CONTENT_TYPE_E eType;							//��������
}HTTP_FILE_LIST_S;


extern const CHAR szHttpMethodStr[][10];
extern const CHAR szHttpUserAgentStringmap[][10];
extern const CHAR szHttpContentTypeStr[][25];

VOID HTTP_RouterInit( VOID );
//extern VOID HTTP_RouterHandle( HTTP_CTX *pstCtx );
//extern INT32 HTTP_ParsingHttpHead( CHAR * pcData, UINT32 uiLen,  HTTP_CTX *pstCtx );
HTTP_FILE_LIST_S* HTTP_GetFileList( CHAR* pcName );
UINT32 HTTP_GetFileListLength();


#endif /* __USER_HTTP_H__ */
