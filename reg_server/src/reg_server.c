#include "../../includeser/book.h"

/*
    此函数返回值在主函数没有设置特殊意义
*/

int reg_server(Link *btemp,LLink *ltemp,int cfd)
{
    printf("这是注册函数\n");
    Link usr = *btemp;  //来自客户端发送的结构体信息
    LLink tempname = (*ltemp)->next; //ltemp是链表头指针的地址
    LLink tempid = (*ltemp)->next;
    
    int com = -1;
    int idflag = 0;
    
    long id = 0;

    char name[N];
    char paword[N];
    char sql[M];

    char *errmsg = NULL;
    sqlite3 *db = NULL;
    
    strcpy(name,usr->name);
    strcpy(paword,usr->passwd);

    while(tempname != NULL)   //while作用：查看要注册的用户名
    {                    // 是否和数据库用户名相同，不允许重名
	com = strcmp(tempname->name,name);
        if(com == 0)
	{
            usr->action = 1;  //表示注册不成功，名字重复
	    if((write(cfd,usr,sizeof(Node))) == -1)
	    {
	        perror("write error");
	        return 0;
	    }
	    printf("writemsg->action = %d\n",usr->action);
	    printf("writemsg->name = %s\n",usr->name);
	    printf("writemsg->passwd = %s\n",usr->passwd);
	    printf("writemsg->toname = %s\n",usr->toname);
	    printf("writemsg->msg = %s\n",usr->msg);
	    return 0;
       	}
	tempname = tempname->next;
    }

    while(idflag == 0)   //为每个帐号生成一个独一无二随即数
    {
        id = myrandom();
	while(tempid != NULL)
	{
	    if(idflag == tempid->id) //遍历密码链表的所有用户ID，
	    {
	        break;              //如果有重复，则再生成一个ID，
	    }
	    tempid = tempid->next;
	}
	if(tempid == NULL)   //如果if条件成立，表示遍历结束，生成的ID和
	{                    //其他已注册的ID没有重复
	    idflag = 1;     //修改循环标志位
	}
        tempid = (*ltemp)->next;//表示生成ID重复，
	                        //初始化密码链表位置，使下次能重新比较
    }
   
    usr->id = id;
    usr->action = -1;   //表示注册成功，
                        //下面的程序是将注册成功的用户信息写入数据库
    sprintf(sql,"insert into word (id,name,paword) values (%ld,'%s','%s')",id,name,paword);
    
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

	if((write(cfd,usr,sizeof(Node))) == -1)
	{
	    perror("write error");
	    return 0;
	}
	printf("writemsg->action = %d\n",usr->action);
	printf("writemsg->name = %s\n",usr->name);
	printf("writemsg->passwd = %s\n",usr->passwd);
	printf("writemsg->toname = %s\n",usr->toname);
	printf("writemsg->msg = %s\n",usr->msg);

    return 0;
}
