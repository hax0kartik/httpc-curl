#include "httpc.h"
#include <iostream>
#include <cstdio>
using namespace std;
string url;
int http(char *url)
{
	printf("Works before open -context");
	HTTPC httpc;
	httpcContext context;
	httpc.OpenContext(&context, HTTPC_METHOD_GET, url, 0);
	printf("Works after open-context");
	
	httpc.AddRequestHeaderField(&context, (char*)"User-Agent", (char*)"HTTPC_CURL_2018");
	Result ret = httpc.BeginRequest(&context);
	//printf("ret :%d", ret);
	u32 statuscode = 1;
	httpc.GetResponseStatusCode(&context, &statuscode);
	//std::cout<<"Statuscode : "<<(int)statuscode<< '\n';
	if(statuscode > 300 && statuscode < 400)
	{
		char newUrl[1024];
		httpc.GetResponseHeader(&context, "Location", newUrl, 1024);
		//cout << newUrl;
	
		httpc.CloseContext(&context);
		//url = std::string(newUrl);
		http(newUrl);
		return 2;
	}
	else if(statuscode >= 400) return 3;
	//http(newUrl);
	u32 size;
	httpc.GetDownloadSizeState(&context, nullptr, &size);
	cout<<"Content-Size"<< size << '\n';
	u8 *buf = (u8*)std::malloc(size);
	httpc.RecieveData(&context, buf, size);
	FILE *file = fopen("file.tar.bz2", "w+b");
	fwrite(buf, size, 1, file);
	fclose(file);
	free(buf);
	httpc.CloseContext(&context);
}

int main()
{
	int ret = http("https://github.com/smealum/ctrulib/releases/download/v1.4.0/libctru-1.4.0.tar.bz2");
	//if(ret == 2) http((char*)url.c_str());
}