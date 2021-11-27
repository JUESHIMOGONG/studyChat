#include "../../includeser/book.h"

//线程要执行的函数

OLink uphead = NULL; //线程共享全局变量，已经上线的用户信息
LLink lhead = NULL;//密码链表头指针
MLink mhead = NULL; //离线信息链表头指针

void *read_msg(void *arg)
{
    int cfd = *((int *)arg);
    int n_read = 0;
    Link msg = (Link)malloc(sizeof(Node));  //用来读取套接字发送来的信息
    
    while(1)
    {
        memset(msg,0,sizeof(Node));
        n_read = read(cfd,msg,sizeof(Node));
        printf(" SERVER READ OK ********* n_read = %d\n",n_read);
	if(n_read == -1)
	{
	    perror("read error:");
	    break;
	}
	
	if(n_read == 0)
	{
	    printf("client is close!\n");
	    break;
	}
	//根据msg的action讨论
	printf("readmsg->action = %d\n",msg->action);

	switch(msg->action)
	{
	    case 1:    //注册用户
	        printf("reg in\n");
	        reg_server(&msg,&lhead,cfd);
	        printf("reg out\n");
	        break;
	    case 2:    //登录用户
	        printf("logrecover in\n");
                logrecover(&lhead);  //密码链表恢复函数
	        printf("logrecover out\n");
	        printf("logserver in\n");
	        log_server(&msg,&lhead,&uphead,&mhead,cfd); //登录函数
	        printf("logserver out\n");
		//发送离线信息函数
	        break;
	    case 3:    //单人聊天
	        printf("chat_client in\n");
	        chat_client(&msg,&uphead,&mhead,cfd);
	        printf("chat_client out\n");
		break;
	    case 4:    //多人聊天
	        printf("moat_client in\n");
	        moat_client(&msg,&uphead,cfd);
	        printf("moat_client out\n");
		break;
	    case 5:    //返回当前在线人数
	        printf("checknum in\n");
	        checknum(&msg,&uphead,cfd);
	        printf("checknum out\n");
		break;
	    case 6:    //表示注销登录
	        printf("relog in\n");
	        relog(&msg,&uphead,cfd);
	        printf("relog out\n");
		break;
	    case 7:    //表示踢人
	        printf("kickpeople in\n");
		kickpeople(&msg,&uphead,cfd);
	        printf("kickpeople out\n");
	        break;
	    case 8:  //表示禁言
	        printf("banpeople in\n");
		banpeople(&msg,&uphead,cfd);
	        printf("banpeople out\n");
	        break;
	    case 9:  //表示修改资料
	        reupdate(&msg,&lhead,&uphead,cfd);
	        break;
	    case 10:  //表示解除禁言
	        printf("nobanpeople in\n");
		nobanpeople(&msg,&uphead,cfd);
	        printf("nobanpeople out\n");
	        break;
	    default:
	        printf("msg->action is error\n");
	        break;
	}

    }
}


//服务器端主函数
int main()
{
    /*先写接收连接*/
    int sockfd = 0;    //主套接字
    sockfd = ser_cblis();
    int cfd = 0;   //新套接字
    struct sockaddr_in client_addr;
    int len = sizeof(client_addr);

    lhead = (LLink)malloc(sizeof(LNode));//密码链表头指针
    lhead->next = NULL;
    logrecover(&lhead);  //密码链表恢复函数

    uphead = (OLink)malloc(sizeof(ONode));//上线人数链表头指针
    uphead->next = NULL;

    mhead = (MLink)malloc(sizeof(MNode));//离线信息链表头指针
    mhead->next = NULL;
    
    pthread_t id;
    
    while(1)
    {
        memset(&client_addr,0,len);
        if((cfd = accept(sockfd,(struct sockaddr *)&client_addr,&len)) < 0)
	{
	    perror("accept error:");
	    exit(1);
	}
	printf("%s %d have accept successed!\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));  //打印客户端的网址和端口号
	
	pthread_create(&id,NULL,read_msg,(void *)&cfd);
    }
    
    return 0;
}
