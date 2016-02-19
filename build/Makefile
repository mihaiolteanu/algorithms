CC=gcc
CFLAGS=-g
ROOT=..
TARGET=main
OBJS_PATH=$(ROOT)/obj
SRCS_PATH=$(ROOT)/src
INC=-I$(ROOT)/include

OBJS:=$(patsubst $(SRCS_PATH)/%.c,$(OBJS_PATH)/%.o,$(wildcard $(SRCS_PATH)/*.c))

$(TARGET) : $(OBJS)
	$(CC) $(INC) $(CFLAGS) -o main $(OBJS)

$(OBJS_PATH)/%.o : $(SRCS_PATH)/%.c | $(OBJS_PATH)
	$(CC) $(INC) $(CFLAGS) -c -o $@ $<

$(OBJS_PATH):
	mkdir $@

clean:
	rm -rf $(TARGET) $(OBJS)





