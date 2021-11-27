#include "../../includeser/book.h"

int checknum(Link *btemp,OLink *otemp,int cfd)
{
    printf("这里是checknum函数\n");
    Link usr = *btemp;
    OLink uptemp = (*otemp)->next;
    
    int cout = 0;

    usr->action = -5; //表示返回在线人数信息

    while(uptemp != NULL)
    {
        strcpy(usr->name,uptemp->name);
	usr->id = cout;
	cout++;
	if((write(cfd,usr,sizeof(Node))) == -1)
	{
	    perror("write error");
            printf("write error 退出chat_client函数\n");
	    return 0;
	}
	printf("have send upusrname %s message successed!\n",usr->toname);

	uptemp = uptemp->next;
    }
    
    usr->action = 5;  //返回客户端总人数信息
    usr->id = cout;
    if((write(cfd,usr,sizeof(Node))) == -1)
    {
        perror("write error");
	return 0;
    }
    printf("return all upname num %d successed\n",usr->id);
    printf("正在退出checknum函数\n");
    return 0;
}
