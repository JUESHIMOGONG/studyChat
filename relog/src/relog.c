#include "../../includeser/book.h"

int relog(Link *btemp,OLink *otemp,int cfd)
{
    printf("这里是relog函数\n");
    Link usr = *btemp;  //保存来自客户端的结构体信息
    OLink headmp = (*otemp);//在线人数链表表头
    OLink uptemp = (*otemp)->next;
    
    while(uptemp != NULL)
    {
        if(strcmp(uptemp->name,usr->name) == 0)
	{
	    headmp->next = uptemp->next;
	    free(uptemp);
	    uptemp = NULL;
	    usr->action = -6;
	    break;
	}

        headmp = uptemp;
	uptemp = uptemp->next;
    }
    if((write(cfd,usr,sizeof(Node))) == -1)
    {
        perror("write error");
	printf("write error 退出relog函数\n");
	return 0;
    }
    printf("write successed usr->action is %d\n",usr->action);
    printf("正在退出relog函数\n");
    return 0;
}
