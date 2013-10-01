#include "include/replaceURLImage.h"

regex_t regex;
int regNo;
regmatch_t pmatch[20];

//获取字符串中的
char* get_imagePath(char *line){
   //从第四个字符
   int len = strlen(line);
   char result[len];
   strncpy(result,line[4],len-5);
   return result;
}

void css_replaceImagePath(char *source,char *result){
	/* Execute regular expression */
	regNo = regexec(&regex, source, 20, pmatch, 0);
	if (!regNo) {
		//puts("Match");
		//printf("%d\t%d\n",pmatch[0].rm_so,pmatch[0].rm_eo);
		int len = pmatch[0].rm_eo-pmatch[0].rm_so;
		char result[len+5];
		strncpy(result,source[pmatch[0].rm_so],len);
		char imageURL = get_imagePath(result);

	} else if (regNo == REG_NOMATCH) {
		//puts("No match");
	} else {
		regerror(regNo, &regex, msgbuf, sizeof(msgbuf));
		fprintf(stderr, "Regex match failed: %s\n", msgbuf);
		exit(1);
	}
};

void init(){
	//编译正则表达式
	regNo = regcomp(&regex, "url\\([^\\)]*\\)", REG_ICASE|REG_NEWLINE|REG_EXTENDED);
	if (regNo) {
			fprintf(stderr, "Could not compile regex\n");
			exit(1);
	}
}

void destory(){
	//释放正则表达式
	regfree(&regex);
}
