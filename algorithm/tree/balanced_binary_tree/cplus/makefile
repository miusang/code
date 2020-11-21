CC := g++
TARGET := demo
INC := -I ./include
SRCS := $(wildcard *.cpp)
SRCS += $(wildcard src/*.cpp)
OBJS := $(patsubst %.cpp,%.o, $(SRCS))
$(TARGET):$(OBJS)
	$(CC) -o $@ $^
%.o:%.cpp
	$(CC) $(INC) -o $@ -c $< -g
all:$(TARGET)
.PHONY:
clean:
	rm $(OBJS) $(TARGET)
