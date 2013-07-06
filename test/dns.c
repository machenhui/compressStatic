#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

void print_family(struct addrinfo *aip){
  printf(" family ");
  switch(aip->ai_family){
  case AF_INET:
	  printf("inet");
	  break;
  case AF_INET6:
	  printf("inet6");
	  break;
  case AF_UNIX:
	  printf("unix");
	  break;
  case AF_UNSPEC:
	  printf("unspecified");
	  break;
  default:
	  printf("unknow");break;
  }

  printf("\n");
}

void print_type(struct addrinfo *aip){
	printf(" type ");
	switch(aip->ai_socktype){
	case SOCK_STREAM:
		printf("stream");break;
	case SOCK_DGRAM:
		printf("datagram");break;
	case SOCK_SEQPACKET:
		printf("seqpacket");break;
	case SOCK_RAW:
		printf("raw");break;
	default:
		printf("unknow (%d) ",aip->ai_socktype);break;
	}

	 printf("\n");
}

int main(int argc,char **argv){
	char *hostname = "www.google.com";
	struct addrinfo *hints, *res,*result_pointer;
	struct sockaddr_in *sinp;
	hints = malloc(sizeof(struct addrinfo));
	memset(hints, 0, sizeof(struct addrinfo));
	//hints->ai_flags = AI_ALL;
	hints->ai_family = AF_INET;
	hints->ai_socktype = SOCK_STREAM;
	//hints->ai_protocol = htons(80);

	int err;
	if ((err = getaddrinfo(hostname, NULL, hints, &res)) != 0) {
	 printf("error %s\n", gai_strerror(err));
	 return 1;
	 };

	result_pointer =  res;
	 while(result_pointer->ai_next != NULL){
		 result_pointer = result_pointer->ai_next;
		 print_family(result_pointer);
		 print_type(result_pointer);
		 char hostname[1025] = "";
		 char ipBuf[1024];
		 if(result_pointer->ai_family == AF_INET){

			 sinp = (struct sockaddr_in *)(result_pointer->ai_addr);

			 const char *rs = inet_ntop(AF_INET,&sinp->sin_addr,ipBuf,sizeof(ipBuf));
			 printf("ip: %s\t%d \n",ipBuf,result_pointer->ai_flags);
		 }

		err = getnameinfo(result_pointer->ai_addr, result_pointer->ai_addrlen,
				hostname, sizeof(hostname), NULL, 0, NI_NAMEREQD);

		if (err != 0) {

			fprintf(stderr, "error in getnameinfo: %s \n", gai_strerror(err));

		} else {

			printf("hostname: %s \n", hostname);

		}

	 }

	 freeaddrinfo(res);
	 return 0;
}
