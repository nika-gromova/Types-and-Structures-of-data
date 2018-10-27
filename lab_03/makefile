CC := gcc
PARAMS := -std=c99 -Wall -Werror

ifeq ($(mode), debug)
	PARAMS += -g3
endif
ifeq ($(mode), drmemory)
	PARAMS += -ggdb
endif

main.exe: main.o io.o allocate.o process.o
	$(CC) -o $@ $^
	
main.o: main.c defines.h io.h allocate.h
	$(CC) $(PARAMS) -c $<

io.o: io.c defines.h io.h allocate.h
	$(CC) $(PARAMS) -c $<
	
allocate.o: allocate.c allocate.h
	$(CC) $(PARAMS) -c $<

process.o: process.c process.h
	$(CC) $(PARAMS) -c $<
	
clean:
	rm *.exe *.o