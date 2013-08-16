#include "include/loadCSS.h"

enum fcurl_type_e {
  CFTYPE_NONE=0,
  CFTYPE_FILE=1,
  CFTYPE_CURL=2
};

struct fcurl_data
{
  enum fcurl_type_e type;     /* type of handle */
  union {
    CURL *curl;
    FILE *file;
  } handle;                   /* handle */

  char *buffer;               /* buffer to store cached data*/
  size_t buffer_len;          /* currently allocated buffers length */
  size_t buffer_pos;          /* end of data in buffer*/
  int still_running;          /* Is background url fetch still in progress */
};
typedef struct fcurl_data URL_FILE;
/**
 * 替换url中的:,/ 特殊字符
 */
void replaceURL(char* input){
	int len = strlen(input);
	int i = 0;
	for(;i<len;i++){
		int rs = input[i]-':';
		int rs1 = input[i]-'/';
		if(rs == 0||rs1 == 0){
			input[i]='_';
		}
	}
}

char *cmd;
char *rsStr;
void wgetFile(const char* fileName,char *filePath,char *contentBuffer){
	mkdir("/tmp/compress",(S_IRUSR|S_IWUSR|S_IXUSR));
	if(cmd == NULL){
		cmd = malloc(10000*sizeof(char));
	}else{
		memset(cmd,'\0',10000);
	}

    strcat(cmd,"wget ");
    strcat(cmd,fileName);
    strcat(cmd," -O ");
    strcat(cmd," /tmp/compress/");
    char *fileNameTmp = malloc(strlen(fileName));
    strcpy(fileNameTmp,fileName);
    replaceURL(fileNameTmp);
    strcat(cmd,fileNameTmp);
    //strcat(cmd,getMD5(fileName));
    /*printf("cmd :: %s \n",cmd);
    int rs = system(cmd);*/
    if(rsStr == NULL){
    	rsStr = malloc(10000*sizeof(char));
    }else{
    	memset(rsStr,'\0',10000);
    }

    strcat(rsStr,"/tmp/compress/");
    strcat(rsStr,fileNameTmp);
    if(filePath != NULL)
    	strcpy(filePath,rsStr);

    curlGetFile(fileName,filePath,contentBuffer);
}

static size_t write_callback(char *buffer,
                             size_t size,
                             size_t nitems,
                             void *userp)
{
  char *newbuff;
  size_t rembuff;
  size = size*nitems;
  //char *filePath = (char *)userp;
  /*char *filePath = "/tmp/compress/test.css";
  FILE *file = fopen(filePath,"w+");*/
  URL_FILE *file = (URL_FILE *)userp;
  rembuff=file->buffer_len - file->buffer_pos; /* remaining space in buffer */
  if(size > rembuff) {
      /* not enough space in buffer */
	  //按照实际使用大小，重新分配内存
      newbuff=realloc(file->buffer,file->buffer_len + (size - rembuff));
      if(newbuff==NULL) {
        fprintf(stderr,"callback buffer grow failed\n");
        size=rembuff;
      }else {
        /* realloc suceeded increase buffer size*/
    	  file->buffer_len+=size - rembuff;
    	  file->buffer=newbuff;
      }
    }
  memcpy(&file->buffer[file->buffer_pos], buffer, size);
  file->buffer_pos += size;
    //fclose(file);

  //printf("找回的内容\n%s\n",buffer);


  return size;
}

CURL *curl;
CURLcode res;
//给指定的url，将下载的文件，保存到指定的位置
void curlGetFile(const char* fileURL,char *filePath,char *contentBuffer){

	if(curl == NULL){
		curl = curl_easy_init();
	}

	if (curl) {
		printf("===%s\n",fileURL);
		curl_easy_setopt(curl, CURLOPT_URL, fileURL);
		/* example.com is redirected, so we tell libcurl to follow redirection */
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		//写文件
		URL_FILE *file;
		file = malloc(sizeof(URL_FILE));
		file->buffer_len = 0;
		file->buffer_pos = 0;
		//提前给buffer 分配一个空间，否则relloc的时候，出错
		file->buffer = malloc(10000);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
		if(filePath != NULL){
			//FILE *outputFile;
			int fileDes = open(filePath,O_CREAT|O_WRONLY,S_IRWXU);
			if(fileDes == -1){
				perror("文件打开异常！");
			}
			write(fileDes,file->buffer,file->buffer_len);
			//free(file->buffer);
			close(fileDes);
			//outputFile = fopen(filePath, "w+");

			/*if (outputFile == NULL ) {
				perror("文件打开失败");
				free(outputFile);

				exit(-1);
			}
			fwrite(file->buffer, 1, file->buffer_len, outputFile);
			free(outputFile);*/
		}

        //file->buffer = "asdlfjasldkj";
       // for(;pos<=file->buffer_len;){
        	//printf("%s",file->buffer);

        	if(contentBuffer != NULL){

        		memcpy(contentBuffer,file->buffer,file->buffer_len);
        		free(file->buffer);
        		//printf("%s\n",contentBuffer);
        	}
       // }

		/* always cleanup */
		//curl_easy_cleanup(curl);
		free(file);
	}

}

void cleanup(){
	if(curl != NULL){
		curl_easy_cleanup(curl);
	}

}

const char* getMD5(const char* key){
	MD5_CTX ctx;

	unsigned char md[MD5_DIGEST_LENGTH];
	int i;

	MD5_Init(&ctx);
	MD5_Update(&ctx, (void *) key, strlen(key));
	MD5_Final(md, &ctx);

	printf("%s md5: ", key);
	for (i = 0; i < MD5_DIGEST_LENGTH; i++)
		printf("%02x", md[i]);
	printf("/n");
	return md;
}
/*int main(int argc,char* argv[]){
	wgetFile("http://s2.120ji.com/css/main.css");
}*/
