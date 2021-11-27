#include "../../includeser/book.h"

int nobanpeople(Link *btemp,OLink *otemp,int cfd)
{
    printf("这里是nobanpeople函数\n");
    Link usr = *btemp;  //保存来自客户端的结构体信息
    OLink headmp = (*otemp);//在线人数链表表头
    OLink uptemp = (*otemp)->next;
    
    while(uptemp != NULL)
    {
        if(strcmp(uptemp->name,usr->toname) == 0)
	{
            usr->action = 13;  //表示no禁言标志
            if((write(uptemp->cfd,usr,sizeof(Node))) == -1)
            {
                perror("write error");
	        printf("write error 退出banpeople函数\n");
	        return 0;
            }
            uptemp->chatflag = 0;  //解除禁言
	    usr->action = -13;  //表示no禁言成功
	    break;
	}

        headmp = uptemp;
	uptemp = uptemp->next;
    }
    if(usr->action == 10)
    {
        usr->action = 14; //表示no禁言失败，该用户没有上线
    }
    if((write(cfd,usr,sizeof(Node))) == -1)
    {
        perror("write error");
	printf("write error 退出banpeople函数\n");
	return 0;
    }
    printf("write successed usr->action is %d\n",usr->action);
    printf("正在退出nobanpeople函数\n");
    return 0;
}
