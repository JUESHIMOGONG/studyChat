#include "../../includeser/book.h"

int log_server(Link *btemp,LLink *ltemp,OLink *otemp,MLink *mtemp,int cfd)
{
    printf("这是logserver函数\n");
    Link usr = *btemp;    //来自客户端发送的结构体信息
    LLink temp = (*ltemp)->next; //密码链表头指针
    OLink uptemp = (*otemp);//在线用户头指针
    MLink mhead = (*mtemp); //离线消息链表头指针
    MLink mnext = (*mtemp)->next;
    
    long id;
    char name[N];
    char paword[N];

    id = usr->id;
    strcpy(name,usr->name);
    strcpy(paword,usr->passwd);

    while(temp != NULL)
    {
        if(strcmp(temp->name,name) == 0 || id == temp->id)
	{            //如果此位置设置标识位，可检查是否输入密码错误
	    strcpy(usr->name,temp->name);
            if(strcmp(temp->paword,paword) == 0)
            {   
	        if(checkcfd(&usr,&uptemp,cfd) == 0)  //检查此用户是否已经登录
	        {
		    usr->action = -2;  //表示登录成功
	            if((write(cfd,usr,sizeof(Node))) == -1)
	            {
	                perror("write error");
	                return 0;
	            }
	            printf("writemsg->action = %d\n",usr->action);

                    //usr->action = 7;  //表示发送离线消息
		    while(mnext != NULL)
		    {
		        if(strcmp(mnext->toname,name) == 0)//表示有此人的离线消息
			{
                            usr->action = 7;
			    strcpy(usr->name,mnext->name);
			    strcpy(usr->msg,mnext->msg);
	                    if((write(cfd,usr,sizeof(Node))) == -1)
	                    {
	                        perror("write error");
	                        return 0;
	                    }
			    mhead->next = mnext->next;
			    free(mnext);
			    mnext = NULL;
			    break;
			}
		        mhead = mnext;
			mnext = mnext->next;
		    }

	            return 0;
		}
		else
		{
		    break;
		}
            }
       	}
	temp = temp->next;
    }
    
    usr->action = 2;  //表示登录失败
    
    if((write(cfd,usr,sizeof(Node))) == -1)
    {
        perror("write error");
        return 0;
    }
    printf("writemsg->action = %d\n",usr->action);
    

    return -1;  //表示登录失败
}
