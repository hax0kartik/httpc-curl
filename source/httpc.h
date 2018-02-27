#include <cctype>
#include <cstring>
#include <string>
#include <inttypes.h>
#include <curl/curl.h>
#include <iostream>
#include <malloc.h>
#include <vector>

#define u32 uint32_t
#define u16 uint16_t
#define u8 uint8_t
#define Handle int32_t
#define Result int

typedef struct {
	Handle servhandle; ///< Service handle.
	u32 httphandle;    ///< HTTP handle.
} httpcContext;

/// HTTP request method.
typedef enum {
	HTTPC_METHOD_GET = 0x1,
	HTTPC_METHOD_POST = 0x2,
	HTTPC_METHOD_HEAD = 0x3,
	HTTPC_METHOD_PUT = 0x4,
	HTTPC_METHOD_DELETE = 0x5
} HTTPC_RequestMethod;

/// HTTP request status.
typedef enum {
	HTTPC_STATUS_REQUEST_IN_PROGRESS = 0x5, ///< Request in progress.
	HTTPC_STATUS_DOWNLOAD_READY = 0x7       ///< Download ready.
} HTTPC_RequestStatus;

/// HTTP KeepAlive option.
typedef enum {
	HTTPC_KEEPALIVE_DISABLED = 0x0,
	HTTPC_KEEPALIVE_ENABLED = 0x1
} HTTPC_KeepAlive;

class HTTPC{
	public:
	//Result Init(u32 mem);
	//Result exit(void);
	Result OpenContext(httpcContext *context, HTTPC_RequestMethod method, char *url, u32 use_defaultproxy);
	Result CloseContext(httpcContext *context);
	Result GetResponseStatusCode(httpcContext *context, u32 *statuscode);
	Result AddRequestHeaderField(httpcContext *context, char *name, char *url);
	Result BeginRequest(httpcContext *context);
	Result GetResponseHeader(httpcContext *context, char* _name, char* value, u32 valuebuf_maxsize);
	Result RecieveData(httpcContext *context, u8 *buffer, u32 size);
	Result GetDownloadSizeState(httpcContext *context, u32 *downloadedsize, u32 *contentsize);
	Result SetSSLOpt(httpcContext *context, u32 option);
	private:
	CURL *handle;
	CURLcode res;
	struct curl_slist *header_chunk = nullptr;
	u32 downloaded_size;
	std::vector <std::string> headers;
};