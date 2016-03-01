
DEBUG := y

CC = gcc

ifeq ($(DEBUG), y)
  DBG_FLAGS := -O0 -Wall -g -DDEBUG -DHAVE_SYS_EPOLL_H
else
  DBG_FLAGS := -O2 -Wall -DHAVE_SYS_EPOLL_H
endif

#
#  	add compile flags
#
CFLAGS += $(DBG_FLAGS)

#CFLAGS += -I$(SW_INC) -I$(USR_INC) 
#
#  the lib needed
#
LIB_FLAGS =  


#
#	 the app obj name
#
obj = mainpipe fduplex mainpopen mainfifo client_main server_main pipeconf



default: $(obj)


mainpipe:mainpipe.c client.c server.c ../lib/lib.c 
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)

fduplex:fduplex.c  ../lib/lib.c 
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)

mainpopen:mainpopen.c  ../lib/lib.c 
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
	
mainfifo:mainfifo.c client.c server.c ../lib/lib.c 
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
	
client_main:client_main.c  client.c  ../lib/lib.c 
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
	
server_main:server_main.c  server.c ../lib/lib.c 
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)

pipeconf:pipeconf.c ../lib/lib.c 
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)

install:
	#@install -c $(obj) $(BIN_INSTALL)	

clean: 
	@rm -f *.o $(obj)
