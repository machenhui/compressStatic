/**获取css 文件中的URL字符串**/
#include <stdio.h>
#include <regex.h>
#include <errno.h>
#include <string.h>

//从源文件种获取url()的字符串
void css_replaceImagePath(char *source,char *result);
