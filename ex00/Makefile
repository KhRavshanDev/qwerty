# -*- Makefile -*-

CC = gcc

CFLAGS += -Wall -Wextra -Werror

LINKERFLAG = -lm

SOURCES = my_mastermind.c my_mastermind.h
OBJECTS = $(SOURCES: .c=.o)
TARGET = my_mastermind

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LINKERFLAG)

.PHONY: clean fclean re

clean:
	@rm -f *.o

fclean:
	@rm $(TARGET0)
	$(clean)

re:
	$(fclean)
	$(MAKE)
