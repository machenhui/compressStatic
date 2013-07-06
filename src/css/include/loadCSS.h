//负责加载css文件
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <regex.h>
#include <openssl/md5.h>
#include <curl/curl.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

void wgetFile(const char* fileName,char* filePath,char *contentBuffer);
void curlGetFile(const char* fileURL,char *filePath,char *contentBuffer);
const char* getMD5(const char* key);
