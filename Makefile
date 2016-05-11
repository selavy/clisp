CC=gcc
CFLAGS=-Wall -Werror -g
RE2C=re2c
#OBJS=first.o
#TARGET=first
OBJS=lexer.o main.o token.o
TARGET=clisp
LEMON=lemon

all: $(TARGET)

$(TARGET): $(LEMON) $(OBJS)
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJS)
$(LEMON): lemon.c
	$(CC) $< -o $@
main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@
%.o: %.c %.h
	$(CC) -o $@ $(CFLAGS) -c $<
#lexer.o: lexer.c lexer.h
#	$(CC) $(CFLAGS) -c $< -o $@
#token.o: token.h token.c
#	$(CC) $(CFLAGS) -c $< -o $@
#first.o: first.c
#	$(CC) $(CFLAGS) -c first.c
#first.c: first.re
#	$(RE2C) -o first.c first.re
.PHONY: clean
clean:
	rm -rf $(OBJS) first.c $(TARGET) $(LEMON)
