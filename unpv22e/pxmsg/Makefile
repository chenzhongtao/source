
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
LIB_FLAGS =  -lrt


#
#	 the app obj name
#
obj = mqcreate mqunlink



default: $(obj)


mqcreate:mqcreate.c ../lib/lib.c 
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
mqunlink:mqunlink.c ../lib/lib.c 
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)



install:
	#@install -c $(obj) $(BIN_INSTALL)	

clean: 
	@rm -f *.o $(obj)
