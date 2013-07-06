//负责分析css文件，并找到其中的@import

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include "loadCSS.h"
#include "httpURL.h"

const char** getImportFiles(const char *fileURL,const char* fileName,char *outPutFile);
/**
 * 根据源地址和import的css地址，获取实际的URL地址
 */
const char* getURL(const char* sourceFileURL,const char* importPath);
int  getCSSPath(const char *line);
const char* hasImport(const char* line);
