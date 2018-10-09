CC := gcc
PARAMS := -std=c99 -Wall -Werror

ifeq ($(mode), debug)
	PARAMS += -g3
endif
ifeq ($(mode), release)
	PARAMS += -DNDEBUG -g0
endif
ifeq ($(mode), drmemory)
	PARAMS += -ggdb
endif

main.exe: io.o operations.o sorting.o time.o main.o
	$(CC) -o $@ $^

main.o: main.c io.h defines.h structure.h
	$(CC) $(PARAMS) -c $<
	
io.o: io.c io.h defines.h structure.h
	$(CC) $(PARAMS) -c $<
	
operations.o: operations.c operations.h defines.h structure.h
	$(CC) $(PARAMS) -c $<
	
sorting.o: sorting.c sorting.h defines.h structure.h
	$(CC) $(PARAMS) -c $<
	
time.o: time.c
	$(CC) $(PARAMS) -c $<
	
clean:
	rm *.o *.exe