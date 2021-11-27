#include "../../includeser/book.h"

int checkcfd(Link *btemp,OLink *otemp,int cfd)
{
    printf("这里是checkcfd函数\n");
    Link usr = (*btemp);//来自客户端的结构体信息
    OLink uphead = (*otemp);  //在线用户链表头指针
    OLink uptemp = (*otemp)->next;
    if(uptemp == NULL)  //表示还没有上线
    {
        OLink upnew = (OLink)malloc(sizeof(ONode));
	upnew->cfd = cfd;
	upnew->chatflag = 0;  //0表示能发言
	strcpy(upnew->name,usr->name);
	uphead->next = upnew;
	upnew->next = NULL;
	return 0;
    }
    while(uptemp != NULL)//检查是否重复登录
    {
        if(strcmp(uptemp->name,usr->name) == 0)
	{
            printf("发现重复登录\n");
            printf("正在退出checkcfd函数\n");
	    return -1;
	}
	uptemp = uptemp->next;
    }

    OLink upnew = (OLink)malloc(sizeof(ONode));
    upnew->cfd = cfd;
    upnew->chatflag = 0;  //0表示能发言
    strcpy(upnew->name,usr->name);
    
    upnew->next = uphead->next; //头插
    uphead->next = upnew;

    return 0;
}
