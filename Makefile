CC = gcc
CFLAGS := -Werror -Wfatal-errors -g
LDFLAGS =

SRC = main.c dynamicAllocation.c
OBJ = list.o $(SRC:.c=.o)
EXECUTABLE = Allocation

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
	zip assignment3.zip main.c dynamicAllocation.c dynamicAllocation.h list.h list.o Makefile