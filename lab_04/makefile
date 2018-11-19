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

app.exe: main.o io.o array_st.o list_st.o
	$(CC) -o $@ $^
	
main.o: main.c defines.h my_types.h list_st.h io.h array_st.h
	$(CC) $(PARAMS) -c $<
	
io.o: io.c io.h defines.h
	$(CC) $(PARAMS) -c $<
	
array_st.o: array_st.c my_types.h array_st.h
	$(CC) $(PARAMS) -c $<
	
list_st.o: list_st.c my_types.h list_st.h
	$(CC) $(PARAMS) -c $<
	
clean:
	rm *.o *.exe