#include "include/httpURL.h"
int getProtocol(const char *httpURL,HTTP_URL *url){
	regex_t regex;
	int reti;
	regmatch_t pmatch[20];
	char msgbuf[100];
	/* Compile regular expression */
	reti = regcomp(&regex, "http[s]?://",
			REG_ICASE | REG_NEWLINE | REG_EXTENDED);
	if (reti) {
		perror("could not compiler ");
		exit(1);
	}

	reti = regexec(&regex, httpURL, 20, pmatch, 0);
	if (!reti) {
		//puts("Match");
		//printf("%d\t%d\n",pmatch[0].rm_so,pmatch[0].rm_eo);
		//匹配的结束点，到字符转的结束都是path
        if(url != NULL){
			int len = pmatch[0].rm_eo;
			char *protocol = malloc(len + 1);
			strncpy(protocol, httpURL, len);
			protocol[len] = '\0';
			url->protocol = protocol;
			//字符串剩下的内容，就是path
			char *path = malloc(strlen(httpURL) - len + 1);
			strncpy(path, httpURL + len, strlen(httpURL) - len);
			path[strlen(httpURL) - len] = '\0';
			url->path = path;
			printf("有匹配结果%s\t%s\n", url->protocol, path);
			regfree(&regex);
        }

		return 0;
	} else if (reti == REG_NOMATCH) {
		//puts("No match");
		regfree(&regex);
		return -1;
	} else {
		regerror(reti, &regex, msgbuf, sizeof(msgbuf));
		perror("Regex match failed\n");
		exit(1);
	}

	/* Free compiled regular expression if you want to use the regex_t again */
	regfree(&regex);
	return -1;
}
/**
 *使用递归，转化所有的../
 */
char* __transPath(char *rootPath,char *importPath){
	regex_t regex;
	int reti;
	regmatch_t pmatch[20],pmatch1[20];
	char msgbuf[100];
	/* Compile regular expression */
	reti = regcomp(&regex, "\\.\\./", REG_ICASE | REG_NEWLINE | REG_EXTENDED);
	if (reti) {
		perror("could not compiler ");
		exit(1);
	}

	reti = regexec(&regex, importPath, 20, pmatch, 0);
	if (!reti) {
		reti = regcomp(&regex, "/[^/]*$",
				REG_ICASE | REG_NEWLINE | REG_EXTENDED);
		if (reti) {
			perror("could not compiler ");
			exit(1);
		}

		reti = regexec(&regex, rootPath, 20, pmatch1, REG_NOTBOL);

		regmatch_t lastmatch = pmatch1[0];
		char *rs = malloc(lastmatch.rm_so + 1);
		strncpy(rs, rootPath, lastmatch.rm_so);
		rs[lastmatch.rm_so] = '\0';
		//printf("相对路径%s\t%s\t%d\n",rs,importPath+pmatch[0].rm_eo-1,pmatch[0].rm_eo);
		return __transPath(rs, importPath+pmatch[0].rm_eo-1);
	}else if (reti == REG_NOMATCH) {
		char *rss =  malloc(strlen(rootPath)+strlen(importPath));

		strncpy(rss,rootPath,strlen(rootPath));
		//printf("最终==返回相对路径%s\t%s\t%s\n",rootPath,rss,importPath);
		strncat(rss,importPath,strlen(importPath));
		//printf("最终==返回相对路径%s\t%s\t%s\n",rootPath,rss,importPath);
		return rss;
	}
	return NULL;
}
char* __getPath(char *currentPath,char *importPath){
	regex_t regex;
	int reti;
	regmatch_t pmatch[20];
	char msgbuf[100];
	/* Compile regular expression */
	reti = regcomp(&regex, "\\.\\./", REG_ICASE | REG_NEWLINE | REG_EXTENDED);
	if (reti) {
		perror("could not compiler ");
		exit(1);
	}

	reti = regexec(&regex, importPath, 20, pmatch, 0);
	if (!reti) {
		reti = regcomp(&regex, "/[^/]*$",REG_ICASE | REG_NEWLINE | REG_EXTENDED);
		if (reti) {
			perror("could not compiler ");
			exit(1);
		}

		reti = regexec(&regex, currentPath, 20, pmatch, REG_NOTBOL);
		regmatch_t lastmatch = pmatch[0];
		char *rs = malloc(lastmatch.rm_so +2);
		strncpy(rs, currentPath, lastmatch.rm_so + 1);
		rs[lastmatch.rm_so + 1] = '\0';
		//printf("相对路径%s\n",rs);
		return __transPath(rs,importPath);
	} else if (reti == REG_NOMATCH) {
		//是当前路径，或者是根路径
		reti = regcomp(&regex, "^/", REG_ICASE | REG_NEWLINE | REG_EXTENDED);
		if (reti) {
			perror("could not compiler ");
			exit(1);
		}

		reti = regexec(&regex, importPath, 20, pmatch, 0);
		if (!reti) {
			//从根路径开始
			return importPath;
		} else if (reti == REG_NOMATCH) {
			//当前目录的默认路径　　b.css or b/b1.css
			//从path中找到当前目录
			reti = regcomp(&regex, "/[^/]*$", REG_ICASE | REG_NEWLINE | REG_EXTENDED);
			if (reti) {
				perror("could not compiler ");
				exit(1);
			}

			reti = regexec(&regex, currentPath, 20, pmatch, REG_NOTBOL);
			//printf("%lu\t%d\n",sizeof(pmatch)/sizeof(regmatch_t),reti);

			regmatch_t lastmatch = pmatch[0];

			char *rs = malloc(lastmatch.rm_so + strlen(importPath));
			strncpy(rs, currentPath, lastmatch.rm_so+1);
			rs[lastmatch.rm_so+1] = '\0';
			//printf("%s\t%d\t%s\n",currentPath,lastmatch.rm_so,rs);
			strcat(rs, importPath);
			//printf("%d\t%s\n",lastmatch.rm_so,rs);
			rs[strlen(rs)] = '\0';
			return rs;

		} else {
			regerror(reti, &regex, msgbuf, sizeof(msgbuf));
			perror("Regex match failed\n");
			exit(1);
		}
		regfree(&regex);
		return NULL ;
	} else {
		regerror(reti, &regex, msgbuf, sizeof(msgbuf));
		perror("Regex match failed\n");
		exit(1);
	}

	/* Free compiled regular expression if you want to use the regex_t again */
	regfree(&regex);
	return NULL ;
}
/**
 * 根据import 的相对路径，和url对象，获取其绝对的路径
 * 1.判断是否是相对路径，http[s]?检测
 * ２. ../ ./的检测，并返回其路径
 */
char* getHTTPPath(char *importPath,HTTP_URL *url){
	int rs = getProtocol(importPath,NULL);
	if(rs<0){
		//代表相对路径，非绝对路径
		return __getPath(url->href,importPath);
	}else{
		return importPath;
	}
	return NULL;
}
int getHTTPURL(const char *httpURL,HTTP_URL *url){
	//url->href = httpURL;
	url->href = malloc(strlen(httpURL));
	strcpy(url->href,httpURL);
	getProtocol(httpURL,url);
	return 0;
}

const char* getImportURL(HTTP_URL *url,const char *importPath){
	return "";
}

/*int main(int argc,char **argv){
	HTTP_URL *url = malloc(sizeof(HTTP_URL));
	getURL("http://s2.120ji.com/css/main.css",url);
	char *rs = getPath("../../../reset.css",url);
	printf("%s\n%s\n",url->protocol,rs);
	return 0;
}*/
