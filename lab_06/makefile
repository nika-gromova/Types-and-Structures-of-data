CC := gcc
PARAMS := -std=gnu99 -Wall -Werror -pedantic
OBJ := io.o my_tree.o

ifeq ($(mode), debug)
	PARAMS += -g3
endif
ifeq ($(mode), drmemory)
	PARAMS += -ggdb
endif

app.exe: main.o $(OBJ)
	$(CC) -o $@ $^
	
main.o: main.c io.h my_tree.h defines.h
	$(CC) $(PARAMS) -c $<

io.o: io.c io.h my_tree.h defines.h
	$(CC) $(PARAMS) -c $<
	
my_tree.o: my_tree.c my_tree.h defines.h
	$(CC) $(PARAMS) -c $<

clean:
	rm *.o *.exe