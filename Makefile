CC=gcc
CFLAGS=-Wall 
RM = rm -f 

TARGET = game

build: $(TARGET)

$(TARGET): game.c
	$(CC) $(CFLAGS) game.c -o $(TARGET) -lncurses

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(TARGET)

.PHONY: pack clean run
