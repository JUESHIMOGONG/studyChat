#include "../../includeser/book.h"

int ser_cblis()
{
    int len;
    int sockfd;
    struct sockaddr_in ser_addr;

    int opt = 1;

    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        perror("create socket error");
	exit(1);
    }
    printf("create socket successful\n");
    printf("sockfd = %d\n",sockfd);
    
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    
    bzero(&ser_addr,sizeof(struct sockaddr_in));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = inet_addr("172.26.59.180");
    //ser_addr.sin_addr.s_addr = inet_addr("47.96.71.17");
    ser_addr.sin_port = htons(SER_PORT);

    if((bind(sockfd,(struct sockaddr *)&ser_addr,sizeof(struct sockaddr_in))) == -1)
    {
        perror("bind ser_addr error:");
	close(sockfd);
	exit(1);
    }
    printf("bind successful!\n");

    if(listen(sockfd,10) == -1)
    {
        perror("listen error:");
	close(sockfd);
	exit(1);
    }
    printf("listen successful!\n");
    
   
   return sockfd;
}
