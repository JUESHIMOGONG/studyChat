#include "../../includeser/book.h"

int kickpeople(Link *btemp,OLink *otemp,int cfd)
{
    printf("这里是kickpeople函数\n");
    Link usr = *btemp;  //保存来自客户端的结构体信息
    OLink headmp = (*otemp);//在线人数链表表头
    OLink uptemp = (*otemp)->next;
    
    while(uptemp != NULL)
    {
        if(strcmp(uptemp->name,usr->toname) == 0)
	{
            usr->action = 4;  //表示被踢标志
            if((write(uptemp->cfd,usr,sizeof(Node))) == -1)
            {
                perror("write error");
	        printf("write error 退出kickpeople函数\n");
	        return 0;
            }

	    headmp->next = uptemp->next;
	    free(uptemp);
	    uptemp = NULL;
	    usr->action = -7;  //表示踢人成功
	    break;
	}

        headmp = uptemp;
	uptemp = uptemp->next;
    }
    if(usr->action == 7)
    {
        usr->action = -8;
    }
    if((write(cfd,usr,sizeof(Node))) == -1)
    {
        perror("write error");
	printf("write error 退出kickpeople函数\n");
	return 0;
    }
    printf("write successed usr->action is %d\n",usr->action);
    printf("正在退出kickpeople函数\n");
    return 0;
}
