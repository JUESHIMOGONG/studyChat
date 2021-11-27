#include "../../includeser/book.h"

int moat_client(Link *btemp,OLink *otemp,int cfd)
{
    printf("这里是moat_client函数\n");
    Link usr = *btemp;
    OLink uptemp = (*otemp)->next;
    OLink bantemp = (*otemp)->next; //检查是否被禁言
    
    while(bantemp != NULL)  //检查是否被禁言
    {
        if(strcmp(bantemp->name,usr->name) == 0)
	{
	    if(bantemp->chatflag == 1)
	    {
	        //表示你已经被禁言
                usr->action = 11;  //表示禁言标志
                if((write(uptemp->cfd,usr,sizeof(Node))) == -1)
                {
                    perror("write error");
	            printf("write error 退出banpeople函数\n");
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
    
    int cout = 0;    //计数已发送的人数

    usr->action = 8; //表示群发消息
    
    if(uptemp == NULL)
    {
         printf("uptemp is NULL\n");
    }

    while(uptemp != NULL)   //对每一个在线用户都发送信息
    {
        if(strcmp(uptemp->name,usr->name) == 0)//如果是当前用户自己，则跳过
	{
	    uptemp = uptemp->next;
	    continue;
	}
	cout++;
	
	if((write(uptemp->cfd,usr,sizeof(Node))) == -1)
	{
	    perror("write error");
            printf("write error 退出chat_client函数\n");
	    return 0;
	}
	printf("have send toname %s msg is %s successed!\n",usr->toname,usr->msg);

	uptemp = uptemp->next;
    }
    
    usr->action = -4;   //返回发起群发信息的用户群发执行信息
    usr->id = cout;
    if((write(cfd,usr,sizeof(Node))) == -1)
    {
        perror("write error");
	return 0;
    }
    printf("return %s have send %d msg is successed\n",usr->name,usr->id);
    printf("正在退出moat_client函数\n");
    return 0;
}
