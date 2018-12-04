CC := gcc
PARAMS := -std=c99 -Wall

ifeq ($(mode), debug)
	PARAMS += -g3
endif
ifeq ($(mode), release)
	PARAMS += -DNDEBUG -g0
endif
ifeq ($(mode), drmemory)
	PARAMS += -ggdb
endif

app.exe: queue_array.o queue_list.o io.o main.o
	$(CC) -o $@ $^
	
main.o: main.c queue_array.h defines.h my_types.h
	$(CC) $(PARAMS) -c $<
	
queue_array.o: queue_array.c queue_array.h defines.h my_types.h
	$(CC) $(PARAMS) -c $<
	
queue_list.o: queue_list.c queue_list.h defines.h my_types.h
	$(CC) $(PARAMS) -c $<
	
io.o: io.c defines.h io.h
	$(CC) $(PARAMS) -c $<
	
clean:
	rm *.o *.exe