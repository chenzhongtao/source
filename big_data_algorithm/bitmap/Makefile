
DEBUG := y

CC = gcc

ifeq ($(DEBUG), y)
  DBG_FLAGS := -O0 -Wall -g -DDEBUG
else
  DBG_FLAGS := -O2 -Wall
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
obj = bitmap_test



default: $(obj)


bitmap_test:bitmap_test.c bitmap.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)

install:
	#@install -c $(obj) $(BIN_INSTALL)	

clean: 
	@rm -f *.o $(obj)
