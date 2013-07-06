#include "include/httpURL.h"
int main(int argc,char **argv){
	HTTP_URL *url = malloc(sizeof(HTTP_URL));
	getHTTPURL("http://s2.120ji.com/css/main.css", url);
	int i = 0;
	for(i = 0;i<10;i++){
		char *rs = getHTTPPath("card.css", url);
		printf("%s\n", rs);
	}

	return 0;
}
