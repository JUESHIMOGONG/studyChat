CC := gcc 
DD := -lsqlite3 -lpthread
Target := ydserver
Source := $(wildcard src/*.c)
Objs := $(patsubst %.c,%.o,$(Source))
Modules += banpeople nobanpeople checknum log_server moat_client reupdate chartoint myrandom chat_client kickpeople main reg_server ser_cblis checkcfd logrecover relog
Allobjs := $(addsuffix /src/*.o,$(Modules))
