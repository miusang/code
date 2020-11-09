CC=gcc

TARGET := demo
SRCS := ./src/tree.c ./binary_search_tree.c

INC := -I ./include

OBJS := $(SRCS:.c=.o)

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o $@ $^

%.o:%.c
	$(CC) $(INC) -o $@ -c $<

.PHONY:clean
clean:
	rm $(TARGET) $(OBJS)
