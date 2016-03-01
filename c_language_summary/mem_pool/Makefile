
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
LIB_FLAGS =  -lpthread


#
#	 the app obj name
#
obj = mem_pool_test mem_pool_multi_thread_test test_mem_pool test_malloc test_tcmalloc



default: $(obj)


mem_pool_test:mem_pool_test.c mem_pool.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
mem_pool_multi_thread_test:mem_pool_multi_thread_test.c mem_pool.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
test_mem_pool:test_malloc.c mem_pool.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
test_malloc:test_malloc.c mem_pool.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
test_tcmalloc:test_tcmalloc.c mem_pool.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS) -ltcmalloc

install:
	#@install -c $(obj) $(BIN_INSTALL)	

clean: 
	@rm -f *.o $(obj)
