
DEBUG := y

CC = gcc

ifeq ($(DEBUG), y)
  DBG_FLAGS := -O0 -Wall -g -DDEBUG  -DUSE_XOPEN2K -std=c99
else
  DBG_FLAGS := -O2 -Wall  -DUSE_XOPEN2K -std=c99
endif

#
#  	add compile flags
#
CFLAGS += $(DBG_FLAGS)

#CFLAGS += -I$(SW_INC) -I$(USR_INC) 
#
#  the lib needed
#
LIB_FLAGS = -laio


#
#	 the app obj name
#
obj = aio_read_test aio_write_test write_test
 


default: $(obj)


aio_read_test:aio_read_test.c 
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
aio_write_test:aio_write_test.c 
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
write_test:write_test.c 
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)

install:
	#@install -c $(obj) $(BIN_INSTALL)	

clean: 
	@rm -f *.o $(obj)
