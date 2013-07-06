//根据指定的URL绝对地址，和一个相对地址，找到相对地址，对应的绝对地址
#include <string.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct http_url{
	char *host;
	char *path;
	char *href;
	int port;
	char *protocol;//http https
};
typedef struct http_url HTTP_URL;
/**
 * 根据URL字符串，返回HTTP_URL对象
 */
int getHTTPURL(const char *httpURL,HTTP_URL *url);
/**
 * 返回
 */
const char* getImportURL(HTTP_URL *url,const char *importPath);

char* getHTTPPath(char *importPath,HTTP_URL *url);

