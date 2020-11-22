CC := gcc
TARGET := demo
INC := -I ./include
SRCS := $(wildcard *.c)
SRCS += $(wildcard src/*.c)
OBJS := $(patsubst %.c,%.o, $(SRCS))
$(TARGET):$(OBJS)
	$(CC) $^ -o $@
%.o:%.c
	$(CC) $(INC) -o $@ -c $< -g
.PHONY:
clean:
	rm $(TARGET) $(OBJS)
