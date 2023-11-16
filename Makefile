CC = gcc
CFLAGS := -Werror -Wfatal-errors -g
LDFLAGS =

SRC = main.c dynamicAllocation.c
OBJ = list.o $(SRC:.c=.o)
EXECUTABLE = dynamicAll

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) -pthread $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(filter-out list.o, $(OBJ)) $(EXECUTABLE)
	rm -f assignment2.zip

zip:
	rm -f assignment2.zip
	zip assignment2.zip main.c list.h list.o dynamicAllocation.c Makefile