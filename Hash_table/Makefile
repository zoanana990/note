CC		:= gcc
CFLAGS	:= -Wall

SRC		:= hashtable.c main.c
OBJ		:= $(SRC:.c =.o)
TARGET  := hashtable
LOG		:= log.Makefile

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ 2> $(LOG)

%.o: %.c
	$(CC) $(CFLAGS) 0c $<

clean:
	rm -rf *.o $(TARGET) $(LOG)
