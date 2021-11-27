#include "../../includeser/book.h"

int chat_client(Link *btemp,OLink *otemp,MLink *mtemp,int cfd)
{
    printf("这里是chat_client函数\n");
    Link usr = *btemp;   //来自客户端的结构体信息
    OLink uptemp = (*otemp)->next; //在线用户链表表头
    MLink mhead = (*mtemp);  //保存离线信息列表
    OLink bantemp = (*otemp)->next; //检查是否被禁言
    
    int tocfd = 0; //保存被发送信息用户的套接字
    int flag = 0;  //如果找到被发送方得套接字，置为1
    char toname[N];
    char msg[M];
    
    strcpy(toname,usr->toname);
    strcpy(msg,usr->msg);
    
    while(bantemp != NULL)
    {
        if(strcmp(bantemp->name,usr->name) == 0)
	{
	    if(bantemp->chatflag == 1)
	    {
	        //表示你已经被禁言
                usr->action = 11;  //表示禁言标志
                if((write(cfd,usr,sizeof(Node))) == -1)
                {
                    perror("write error");
	            printf("write error 退出chatbanpeople函数\n");
	            return 0;
                }
		printf("服务器已经发送禁言消息给%s\n",usr->name);
	        return 0;
	    }
	    else
	    {
	        break;
	    }
       	}
	bantemp = bantemp->next;
    }

    if(uptemp == NULL)
    {
         printf("uptemp is NULL\n");
    }

    while(uptemp != NULL)
    {
        if(strcmp(uptemp->name,toname) == 0)
	{
	    tocfd = uptemp->cfd;  //找到toname
            flag = 1;
	    printf("find toname is %s\n",toname);
	    break;
       	}
	uptemp = uptemp->next;
    }
    
    if(flag == 0)
    {
        MLink newmsg = (MLink)malloc(sizeof(MNode));
	memset(newmsg,0,sizeof(MNode));
       
        newmsg->id = usr->id;    //保存离线信息
	strcpy(newmsg->name,usr->name);
	strcpy(newmsg->toname,usr->toname);
	strcpy(newmsg->msg,usr->msg);
	newmsg->next = NULL;

        newmsg->next = mhead->next;  //头插
	mhead->next = newmsg;


        printf("nofind people %s\n",toname);
        usr->action = 3; //表示toname没有上线，发送消息失败
	if((write(cfd,usr,sizeof(Node))) == -1)
	{
	    perror("write error");
	    return 0;
	}
	printf("send failed\n");
        printf("正在退出chat_client函数\n");
	return 0;
    }
    else
    {
        usr->action = 9;
	if((write(tocfd,usr,sizeof(Node))) == -1)
	{
	    perror("write error");
	    return 0;
	}
	printf("send toname %s msg is %s successed!\n",usr->toname,usr->msg);
        
	usr->action = -3;
        if((write(cfd,usr,sizeof(Node))) == -1)
        {
            perror("write error");
	    return 0;
        }
        printf("return %s send %s msg is %s successed\n",usr->name,usr->toname,usr->msg);
    printf("正在退出chat_client函数\n");
	return 0;
    }
}
