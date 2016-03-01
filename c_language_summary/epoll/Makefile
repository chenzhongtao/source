
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
LIB_FLAGS =  -lpthread


#
#	 the app obj name
#
obj = epoll_test



default: $(obj)


epoll_test:epoll_test.c event-epoll.c event.c event-poll.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)

install:
	#@install -c $(obj) $(BIN_INSTALL)	

clean: 
	@rm -f *.o $(obj)
