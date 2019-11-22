CC = gcc
CFLAGS = 
TARGET = test

# $(wildcard *.c /xxx/xxx/*.c): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard *.c)
# $(patsubst %.c,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst %.c,%.o,$(SRCS))

all: $(TARGET) run
$(TARGET): $(OBJS)
	$(CC) -o $@ $^
run:
	./$(TARGET)
%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(TARGET) *.o