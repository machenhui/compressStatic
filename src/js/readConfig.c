//读取配置文件
#include <json/json.h>
#include <json/json_object_private.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const char* transToCommand(struct array_list *ja,const char* basePath){
	char *rs = malloc(10000*sizeof(char));
	memset(rs,0,strlen(rs));
	int i = 0;
	for(i=0;i<ja->length;i++){
		struct json_object *data = array_list_get_idx(ja,i);
		const char *d = json_object_get_string(data);

        char *tmp = " --js ";
        char *tmp1 = malloc(strlen(d)+strlen(tmp)+strlen(basePath));
        memset(tmp1,0,strlen(tmp1));
		strcat(tmp1,tmp);
		strcat(tmp1,basePath);
		strcat(tmp1,d);
		strcat(rs,tmp1);
		printf("文件:%s\n",tmp1);
	}

	return rs;
}
const char* getCommadStr(const char *prefix,const char* jsstr,const char* outputFile,const char *externs){
	char *rs = malloc(10000*sizeof(char));
	memset(rs,0,strlen(rs));
	strcat(rs,prefix);
	strcat(rs," --compilation_level ");
	strcat(rs," ADVANCED_OPTIMIZATIONS ");
	//strcat(rs," SIMPLE_OPTIMIZATIONS ");
	strcat(rs," --js_output_file ");
	strcat(rs,outputFile);
	strcat(rs,jsstr);
	if(strcmp(externs,"") != 0){
      strcat(rs," --externs ");
	  strcat(rs,externs);
    }
	return rs;
}

int main(int argc, char** argv){

	struct json_object *jb = json_object_from_file("testConfig.json");
	struct json_object *jb_name = json_object_object_get(jb,"name");
	const char *b = json_object_get_string(jb_name);
	printf("Hello World! %s\n",b);

	struct json_object *jb_basePath = json_object_object_get(jb,"basePath");
	const char *basePath = json_object_get_string(jb_basePath);
	struct json_object *jb_outputFile = json_object_object_get(jb,"outputFile");
	char *outputFile = malloc(10000*sizeof(char));
	memset(outputFile,0,strlen(outputFile));
	const char *outputFile1 = json_object_get_string(jb_outputFile);
	strcat(outputFile,basePath);
	strcat(outputFile,outputFile1);
	//获取extens js
	struct json_object *jb_externs = json_object_object_get(jb,"externs");
    const char *externs = json_object_get_string(jb_externs);
	char *externs1 = malloc(1000*sizeof(char));
	memset(externs1,0,strlen(externs1));
	strcat(externs1,basePath);
	strcat(externs1,externs);

	//获取js 文件数组
	struct json_object *jsFiles = json_object_object_get(jb,"files");
	struct array_list *ja = json_object_get_array(jsFiles);
	const char *cmd = transToCommand(ja,basePath);
	printf("命令行 %s\n",cmd);

	//system("java -version");
    printf("\n\n%s\n",getCommadStr("java -jar ../lib/compilerJS.jar ",cmd,outputFile,externs1));
	system(getCommadStr("java -jar ../lib/compilerJS.jar ",cmd,outputFile,externs1));


	return 0;
}
