#ifndef __BOOK_H_
#define __BOOK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <pthread.h>
#include <sqlite3.h>

#include <errno.h>

#define SER_PORT 3001
#define N 20
#define M 256

struct message
{
    int action;
    long id;
    char name[N];
    char passwd[N];
    char toname[N];
    char msg[M];
    struct message *next;
};
typedef struct message Node;
typedef struct message * Link;

struct logword
{
    long id;
    char name[N];
    char paword[N];
    struct logword *next;
};
typedef struct logword LNode;
typedef struct logword * LLink;

struct online
{
    int cfd;
    int chatflag;
    char name[N];
    struct online *next;
};
typedef struct online ONode;
typedef struct online * OLink;

struct msgdownline
{
    int id;
    char name[N];
    char toname[N];
    char msg[M];
    struct msgdownline *next;
};
typedef struct msgdownline MNode;
typedef struct msgdownline * MLink;


extern int ser_cblis();

extern int reg_server(Link *btemp,LLink *ltemp,int cfd);
extern int logrecover(LLink *ltemp);
extern long myrandom();
extern long chartolong(char *str);
extern int log_server(Link *btemp,LLink *ltemp,OLink *otemp,MLink *mtemp,int cfd);
extern int chat_client(Link *btemp,OLink *otemp,MLink *mtemp,int cfd);
extern int moat_client(Link *btemp,OLink *otemp,int cfd);
extern int checknum(Link *btemp,OLink *otemp,int cfd);
extern int relog(Link *btemp,OLink *otemp,int cfd);
extern int kickpeople(Link *btemp,OLink *otemp,int cfd);
extern int banpeople(Link *btemp,OLink *otemp,int cfd);
extern int nobanpeople(Link *btemp,OLink *otemp,int cfd);
extern int reupdate(Link *btemp,LLink *ltemp,OLink *otemp,int cfd);


#endif
