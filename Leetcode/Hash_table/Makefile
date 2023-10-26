CC		:= gcc
CFLAGS	:= -Wall

SRC		:= hashtable.c main.c
OBJ		:= $(SRC:.c =.o)
TARGET  := hashtable

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ 2> log.Makefile

%.o: %.c
	$(CC) $(CFLAGS) 0c $<

clean:
	rm -rf *.o $(TARGET)
