/*
 * user_http.h
 *
 *  Created on: 2018��11��11��
 *      Author: lenovo
 */

#ifndef __USER_HTTP_H__
#define __USER_HTTP_H__

#define HTTP_HOST_MAX_LEN 		30
#define HTTP_URL_MAX_LEN 		100
#define HTTP_HANDLE_MAX_LEN 	100

#define HTTP_ROUTER_MAP_MAX 	40

#define HTTP_HTML_NAME_MAX_LEN	100
#define HTTP_HTML_DATE_MAX		20


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
	HTTP_CODE_Ok 					= 200,
	HTTP_CODE_Created 				= 201,
	HTTP_CODE_Found 				= 302,
	HTTP_CODE_BadRequest			= 400,
	HTTP_CODE_NotFound				= 404,
	HTTP_CODE_InternalServerError	= 500,

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

}HTTP_RESPONSE_HEAD_S;

typedef struct tagHttpRequestHead
{
	HTTP_METHOD_E 		eMethod;						// GET, POST PUT DELETE
	CHAR 				szURL[HTTP_URL_MAX_LEN];       	// /index.html
	HTTP_USERAGENT_E 	eUserAgent;	    				// windows, Android,
	CHAR 				szHost[HTTP_HOST_MAX_LEN];     	// 192.168.0.102:8080
	UINT 				uiContentLenth;					// ����body�峤�ȣ�������head����

	CHAR*               pcRouter;						//ƥ�䵽��Router

	HTTP_PROCESS_E		eProcess;
	UINT 				uiRecvPresentLenth;				// ���յ�body�ĳ���
	UINT 				uiRecvCurLenth;					// �����յ�body�ĳ���
	CHAR*				pcResqBody;						// ������

	BOOL				bIsCouldSend;
	UINT 				uiSendTotalLength;				// Ӧ�����ܳ��ȳ���
	UINT 				uiSentLength;					// �ѷ��ͳ���
	UINT				uiSendCurLength;				// ����Ӧ���ͳ���
	CHAR*				pcResponBody;					// Ӧ����
}HTTP_REQUEST_HEAD_S;

typedef VOID(*ROUTER)(HTTP_REQUEST_HEAD_S*);

typedef struct tagHttpRouterMap
{
	HTTP_METHOD_E 		eMethod;									/* GET, POST PUT DELETE */
	CHAR 				szURL[HTTP_URL_MAX_LEN];    				/* URL��ַ */
	CHAR 				szHttpHandlerStr[HTTP_HANDLE_MAX_LEN];    	/* ·������ */
	ROUTER 				pfHttpHandler;								/* �ص����� */
}HTTP_ROUTER_MAP_S;



typedef struct tagHttpHtmlData
{
	CHAR 				szName[HTTP_HTML_NAME_MAX_LEN];	//html����
	BOOL				bIsUpload;						//�����Ƿ����ϴ�
	UINT32				uiAddr;							//������FLASH�еĴ�ŵ�ַ
	UINT32				uiLength;						//���ݳ���
	HTTP_CONTENT_TYPE_E eType;							//��������
}HTTP_HTMLDATA_S;


extern const CHAR szHttpMethodStringmap[][10];
extern const CHAR szHttpUserAgentStringmap[][10];
extern const CHAR szHttpContentTypeStr[][30];

VOID HTTP_RouterInit( VOID );
VOID HTTP_RouterHandle( HTTP_REQUEST_HEAD_S *pstHeader );
INT32 HTTP_ParsingHttpHead( CHAR* pcData, UINT32 uiLen, HTTP_REQUEST_HEAD_S *pstHttpHead );
HTTP_HTMLDATA_S* HTTP_GetHtmlData( CHAR* pcName );
UINT32 HTTP_GetHtmlDataLength();


#endif /* __USER_HTTP_H__ */
