#include "../../includeser/book.h"

/*
    此函数返回值在主函数没有设置特殊意义
*/

int reupdate(Link *btemp,LLink *ltemp,OLink *otemp,int cfd)
{
    printf("这是修改资料函数\n");
    Link usr = *btemp;  //来自客户端发送的结构体信息
    LLink tempname = (*ltemp)->next; //ltemp是链表头指针的地址
    LLink tempid = (*ltemp)->next;
    OLink headmp = (*otemp);//在线人数链表表头
    OLink uptemp = (*otemp)->next;
    
    
    int com = -1;
    long int id = 0;

    char name[N];
    char toname[N];
    char paword[M];
    char sql[M];

    char *errmsg = NULL;
    sqlite3 *db = NULL;
   
    strcpy(name,usr->name);
    strcpy(toname,usr->toname);
    strcpy(paword,usr->msg);  //要修改的密码放入msg里面了

    while(tempname != NULL)   //while作用：查看要修改的用户名
    {                    // 是否和数据库用户名相同，不允许重名
	com = strcmp(tempname->name,toname);
        if(com == 0)
	{
            usr->action = -11;  //表示修改不成功，名字重复
	    if((write(cfd,usr,sizeof(Node))) == -1)
	    {
	        perror("write error");
	        return 0;
	    }
	    return 0;
       	}
	tempname = tempname->next;
    }
  
    com = -1;
    while(tempid != NULL)   //记录唯一ID
    {                 
	com = strcmp(tempid->name,name);
        if(com == 0)
	{
	    id = tempid->id;
	    break;
       	}
	tempid = tempid->next;
    }
	
                        //下面的程序是将注册修改的用户信息写入数据库
    sprintf(sql,"update word set name = '%s',paword = '%s' where id = %ld",toname,paword,id);
    
    if((sqlite3_open("logword.db",&db)) != SQLITE_OK)
    {
        perror("logword.db open error: ");
	exit(1);
    }
    
    if((sqlite3_exec(db,sql,0,0,&errmsg)) != SQLITE_OK)
    {
         printf("exec errmsg = %s\n",errmsg);
	 exit(1);
    }
    
    if((sqlite3_close(db)) != SQLITE_OK)
    {
        perror("password.db close error: ");
	exit(1);
    }

    while(uptemp != NULL)        //修改成功，让他下线重新登录
    {
        if(strcmp(uptemp->name,name) == 0)
	{
	    headmp->next = uptemp->next;
	    free(uptemp);
	    uptemp = NULL;
	    usr->action = 12;
	    break;
	}

        headmp = uptemp;
	uptemp = uptemp->next;
    }
    if(usr->action == 9)
    {
        usr->action = -12;
    }
    if((write(cfd,usr,sizeof(Node))) == -1)
    {
        perror("write error");
        return 0;
    }

    return 0;
}
