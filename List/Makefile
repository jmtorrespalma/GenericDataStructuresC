
CC=gcc
CFLAGS= -Wall -g 
LDFLAGS= -lc

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
INC=$(wildcard *.h)

TARGET=main

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS) 

%.o: %.c $(INC) 
	$(CC) $(CFLAGS) $< -c -o $@
	

clean:
	rm -rf $(OBJ) $(TARGET)

