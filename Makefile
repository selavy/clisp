CC=gcc
CFLAGS=-Wall -Werror -g
OBJS=lexer.o main.o token.o
TARGET=clisp
LEMON=lemon

all: $(TARGET)

$(TARGET): $(LEMON) $(OBJS)
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJS)
$(LEMON): lemon.c
	$(CC) $< -o $@
%.o: %.c %.h
	$(CC) -o $@ $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -rf $(OBJS) $(TARGET) $(LEMON)
