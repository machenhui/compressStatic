#include "include/readCSS.h"
#define BUFFIZE 1000

void removeCharSet(char *filePath,char *outPutPath){
	FILE *sourceFile = fopen(filePath,"rb");
	int outPutFileDes = open(outPutPath,O_CREAT|O_WRONLY,S_IRWXU);
	char *buf = malloc(BUFFIZE*sizeof(char));
	regex_t regex;
	int reti;
	char msgbuf[100];
	regmatch_t pmatch[20];
	/* Compile regular expression */
	reti = regcomp(&regex, "@CHARSET\\s+\"UTF-8\";",REG_ICASE | REG_NEWLINE | REG_EXTENDED);
	if (reti) {
		fprintf(stderr, "Could not compile regex\n");
		exit(1);
	}
	for(;buf!=NULL;){
		buf = fgets(buf,BUFFIZE,sourceFile);
		if (buf != NULL ) {
			//正则匹配
			reti = regexec(&regex, buf, 20, pmatch, 0);
			if (!reti) {
				//printf("%s\n", buf);
			} else if (reti == REG_NOMATCH) {
				//puts("No match");
				write(outPutFileDes, buf, strlen(buf));
			} else {
				regerror(reti, &regex, msgbuf, sizeof(msgbuf));
				fprintf(stderr, "Regex match failed: %s\n", msgbuf);
				exit(1);
			}
		}

	}
	regfree(&regex);
	close(outPutFileDes);
	fclose(sourceFile);
}
const char** getImportFiles(const char *fileURL,const char* fileName,char *outPutFile){
	//按行读取

	FILE *file = fopen(fileName,"rb");
    char *mergeFileName = ".merge.css";
	char *outPutFileName = malloc(strlen(fileName)+strlen(mergeFileName)+2);
	strcpy(outPutFileName,fileName);
	strcat(outPutFileName,mergeFileName);
	//int outPutFileDes = open(outPutFileName,O_CREAT|O_WRONLY,S_IRWXU);
	int outPutFileDes = creat(outPutFileName,O_CREAT|O_WRONLY);
	//FILE *outPutFile = fopen(outPutFileName,"w+");

	HTTP_URL *url = malloc(sizeof(HTTP_URL));

	getHTTPURL(fileURL,url);

	if(file == NULL){
		perror("文件打开失败");
		printf("文件打开失败:%d\n",errno);
		exit(-1);
	}
	if(outPutFileDes == -1){
		perror("文件打开失败");
		printf("文件打开失败outPutFile:%s\t%s\n",strerror(errno),outPutFileName);
		exit(-1);
	}
    //int file = open(fileName,O_RDONLY);

	char *buf = malloc(BUFFIZE*sizeof(char));
	if(buf == NULL){
		perror("malloc 异常");
		exit(-1);
	}

	char *contentBuffer = malloc(5*1024*1024);
	for(;buf!=NULL;){
		memset(buf,'\0',BUFFIZE*sizeof(char));
		buf = fgets(buf,BUFFIZE*sizeof(char),file);

		if(buf != NULL){

			const char *cssPath = hasImport(buf);

			if (cssPath != NULL ) {
				char *cssPath1 = malloc(strlen(cssPath));
				memset(cssPath1,'\0',strlen(cssPath));
				strcpy(cssPath1, cssPath);
				printf("----%s===%s\n",cssPath1,cssPath);
				char *rs = getHTTPPath(cssPath1, url);

				//char *contentBuffer = malloc(5*1024*1024);
				fsync(outPutFileDes);

				memset(contentBuffer,'\0',5*1024*1024);

				wgetFile(rs,NULL,contentBuffer);
				//fputs(contentBuffer,outPutFile);
				printf("长度：%d\n",strlen(contentBuffer));
				write(outPutFileDes,contentBuffer,strlen(contentBuffer));
				write(outPutFileDes,"\n",1);
				//memset(contentBuffer,'\0',strlen(contentBuffer));
				printf("%s\t%s\n", cssPath1, rs);
				//free(cssPath1);
				//fsync(outPutFileDes);
				//free(contentBuffer);
			}else{
				//fputs(buf,outPutFile);

				write(outPutFileDes,buf,strlen(buf));
			}

		}


	}

	free(buf);
	//free(row);
    fclose(file);
    close(outPutFileDes);
    char *outPutFileCharSet=".charset.css";
    char *outPutFileCharSetName = malloc(strlen(fileName)+strlen(outPutFileCharSet)+2);
    strcpy(outPutFileCharSetName,fileName);
    strcat(outPutFileCharSetName,outPutFileCharSet);
    removeCharSet(outPutFileName,outPutFileCharSetName);
    strcpy(outPutFile,outPutFileCharSetName);
    printf("输出文件地址%s\n",outPutFileCharSetName);
    const char** rs;
	return rs;
}
//返回开始的位置
int  getCSSPath(const char *line){
		regex_t regex;
		int reti;
		char msgbuf[100];
		regmatch_t pmatch[20];
		/* Compile regular expression */
		reti = regcomp(&regex, "@import\\s+url\\(", REG_ICASE|REG_NEWLINE|REG_EXTENDED);
		if (reti) {
			fprintf(stderr, "Could not compile regex\n");
			exit(1);
		}

		/* Execute regular expression */
		reti = regexec(&regex, line, 20, pmatch, 0);
		if (!reti) {
			//puts("Match");
			//printf("%d\t%d\n",pmatch[0].rm_so,pmatch[0].rm_eo);

			return pmatch[0].rm_eo;
		} else if (reti == REG_NOMATCH) {
			//puts("No match");
		} else {
			regerror(reti, &regex, msgbuf, sizeof(msgbuf));
			fprintf(stderr, "Regex match failed: %s\n", msgbuf);
			exit(1);
		}

		/* Free compiled regular expression if you want to use the regex_t again */
		regfree(&regex);

		return -1;
}
/**
 * 找到对应文件种的url();解析其中的路径，并将其转化成绝对地址
 * 1.正则匹配url(images/bb.png);
 * 2.判断其路径时相对路径，还是绝对路径
 * 		http:// 开头 /image 开头的，都是绝对路径，不用转化
 * 		images/bb.png ../ 两种类型的都是相对路径
 * 3.替换该字符串
 */
int getURLPath(){
	return 0;
}

//返回css文件地址
const char* hasImport(const char* line){
	regex_t regex;
	int reti;
	char msgbuf[100];
	regmatch_t pmatch[20];
	printf("===%s===\n",line);
	/* Compile regular expression */
	reti = regcomp(&regex, "@import\\s+url\\(.+\\)", REG_ICASE|REG_NEWLINE|REG_EXTENDED);
	if (reti) {
		fprintf(stderr, "Could not compile regex\n");
		exit(1);
	}

	/* Execute regular expression */
	reti = regexec(&regex, line, 20, pmatch, 0);
	if (!reti) {
		//puts("Match");
		//printf("%d\t%d\n",pmatch[0].rm_so,pmatch[0].rm_eo);
		int start = getCSSPath(line);
		int len = pmatch[0].rm_eo-start;
		char *cssPath = malloc(len);
		strncpy(cssPath,line+start,len-1);
		cssPath[len-1] = '\0';
		//printf("%d\t%lu\t%s\n",len,strlen(cssPath),cssPath);
		return cssPath;
	} else if (reti == REG_NOMATCH) {
		//puts("No match");
	} else {
		regerror(reti, &regex, msgbuf, sizeof(msgbuf));
		fprintf(stderr, "Regex match failed: %s\n", msgbuf);
		exit(1);
	}

	/* Free compiled regular expression if you want to use the regex_t again */
	regfree(&regex);
	return NULL;
}

void callClosureStyleSheet(char *fileName,char *outPutPath,char *outPutRenameMap){
	char *cmd = malloc(10000);
	strcpy(cmd,"java -jar ../lib/closure-stylesheets.jar ");
	strcat(cmd,fileName);
	strcat(cmd," --allowed-unrecognized-property ");
	strcat(cmd,"animation-fill-mode ");
	strcat(cmd," --allowed-unrecognized-property ");
	strcat(cmd,"-webkit-text-shadow ");
	strcat(cmd," --output-file ");
	strcat(cmd,outPutPath);
	if(outPutRenameMap != NULL){
		strcat(cmd," --rename CLOSURE");
		strcat(cmd," --output-renaming-map ");
		strcat(cmd,outPutRenameMap);
	}
	printf("cmd %s\n",cmd);
	system(cmd);
	free(cmd);
}

int main(int argc,char** argv){
	if(argc < 3){
		perror("缺少参数，参数1 为文件地址，参数2 为输出文件地址");
		perror("css 文件中的图片地址会修改为以参考输出文件地址的相对路径");
		return -1;
	}
	char filePath[100];
	char outPutFile[2000];
	char *fileURL = argv[1];
	char *currentBuffer = malloc(1024*8*1024);
	wgetFile(fileURL,filePath,currentBuffer);
	//printf("%s\n",currentBuffer);

	getImportFiles(fileURL,filePath,outPutFile);
	printf("文件名%s\n",outPutFile);
	//printf("文件名%s\n",fileName);
	//getImportFiles("/tmp/compress/http___s2.120ji.com_css_main.css");

	char *outputFilePath = "target/min.merge.css";
	if(argc >=3){
		outputFilePath = argv[2];
	}
	char *outPutRenameMap;
	if(argc >=4){
		outPutRenameMap = argv[3];
	}
	callClosureStyleSheet(outPutFile,outputFilePath,outPutRenameMap);
	//对生成的文件，做closure-stylesheet的压缩

}
