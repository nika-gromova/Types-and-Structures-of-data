CC := gcc
PARAMS := -std=gnu99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	PARAMS += -g3
endif
ifeq ($(mode), drmemory)
	PARAMS += -ggdb
endif

app.exe: main.o my_queue.o allocate.o process.o
	$(CC) -o $@ $^

main.o: main.c allocate.h process.h
	$(CC) $(PARAMS) -c $<

my_queue.o: my_queue.c my_queue.h defines.h
	$(CC) $(PARAMS) -c $<
	
process.o: process.c process.h my_queue.h defines.h
	$(CC) $(PARAMS) -c $<

allocate.o: allocate.c allocate.h
	$(CC) $(PARAMS) -c $<
	
clean:
	rm *.o *.exe