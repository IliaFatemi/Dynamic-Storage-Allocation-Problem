CC = gcc
CFLAGS := -Werror -Wfatal-errors -g
LDFLAGS =

SRC = mem_test.c my_malloc.c
OBJ = $(SRC:.c=.o)
EXECUTABLE = mem_test

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) -pthread $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(filter-out list.o, $(OBJ)) $(EXECUTABLE)
	rm -f assignment3.zip

zip:
	rm -f assignment3.zip
	zip assignment3.zip mem_test.c my_malloc.c my_malloc.h Makefile