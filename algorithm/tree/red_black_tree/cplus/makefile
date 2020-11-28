CC := g++
TARGET := demo
SRCS := $(wildcard *.cpp)
SRCS += $(wildcard src/*.cpp)
INC := -I ./include
OBJS := $(patsubst %.cpp,%.o, $(SRCS))
$(TARGET):$(OBJS)
	$(CC) -o $@ $^
%.o:%.cpp
	$(CC) $(INC) -o $@ -c $< -g
.PHONY:
clean:
	rm $(TARGET) $(OBJS)
