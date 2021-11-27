#include "../../includeser/book.h"

int logrecover(LLink *ltemp)
{
    printf("这是logrecover函数\n");

    LLink temp = *ltemp;
    
    int i;
    int nrow;
    int ncolumn;

    char **result = NULL;
    char *errmsg = NULL;
    
    sqlite3 *db = NULL;
    
    if((sqlite3_open("logword.db",&db)) != SQLITE_OK)
    {
        perror("logword.db open error: ");
	exit(1);
    }
    if((sqlite3_get_table(db,"select * from word",&result,&nrow,&ncolumn,&errmsg)) != SQLITE_OK)
    {
        printf("get table error: %s\n",errmsg);
	exit(1);
    }
    
    if((sqlite3_close(db)) != SQLITE_OK)
    {
        perror("logword.db close error: ");
	exit(1);
    }

    if(nrow == 0)
    {
        sqlite3_free_table(result);
	temp->next = NULL;
        return 0;
    }
    
    LLink newnode;
    LLink newnodenext;

    newnode = (LLink)malloc(sizeof(LNode));

    LLink tem = newnode;

    temp->next = newnode;

    for(i = 1; i <= nrow; i++)
    {
        newnode->id = chartolong(result[i * ncolumn + 0]);
        strcpy(newnode->name,result[i * ncolumn + 1]);
        strcpy(newnode->paword,result[i * ncolumn + 2]);
	newnodenext = (LLink)malloc(sizeof(LNode));
	newnode->next = newnodenext;
	tem = newnode;
	newnode = newnode->next;
    }
    tem->next = NULL;
    free(newnodenext);
    newnodenext = NULL;

    sqlite3_free_table(result);
    printf("正在退出logrecover函数\n");
    
    return 0;
}
