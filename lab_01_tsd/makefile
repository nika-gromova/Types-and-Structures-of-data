CC := gcc
PARAMS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	PARAMS += -g3
endif
ifeq ($(mode), release)
	PARAMS += -DNDEBUG -g0
endif

app.exe: io.o process.o main.o
	$(CC) -o $@ $^
	
main.o: main.c io.h defines.h
	$(CC) $(PARAMS) -c $<
	
io.o: io.c io.h defines.h
	$(CC) $(PARAMS) -c $<
	
process.o: process.c process.h
	$(CC) $(PARAMS) -c $<
	
clean:
	rm *.o *.exe