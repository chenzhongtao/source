
DEBUG := y

CC = gcc

ifeq ($(DEBUG), y)
  DBG_FLAGS := -O0 -g -W -Wall -ansi -pedantic
else
  DBG_FLAGS := -O2 -W -Wall -ansi -pedantic
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
testers = bst-test avl-test rb-test tbst-test tavl-test trb-test	\
rtbst-test rtavl-test rtrb-test pbst-test pavl-test prb-test
targets = $(testers) bin-ary-test bsts seq-test slr srch-test
obj = $(targets)
 


default: $(obj)

bst-test: bst.c bst-test.c test.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
avl-test: avl.c avl-test.c test.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
rb-test: rb.c rb-test.c test.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
tbst-test: tbst.c tbst-test.c test.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
tavl-test: tavl.c tavl-test.c test.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
trb-test: trb.c trb-test.c test.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
rtbst-test: rtbst.c rtbst-test.c test.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
rtavl-test: rtavl.c rtavl-test.c test.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
rtrb-test: rtrb.c rtrb-test.c test.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
pbst-test: pbst.c pbst-test.c test.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
pavl-test: pavl.c pavl-test.c test.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
prb-test: prb.c prb-test.c test.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)

bin-ary-test: bin-ary-test.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
bsts: bsts.c test.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)
seq-test: seq-test.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)

slr: slr.c
	$(CC) $(CFLAGS) -o $@  $^  $(LIB_FLAGS)

install:
	#@install -c $(obj) $(BIN_INSTALL)	

clean: 
	@rm -f *.o $(obj)