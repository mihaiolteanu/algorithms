CC=gcc
CFLAGS=-g -std=c99
TARGET=main
OBJS_PATH=obj
SRCS_PATH=src
INC=-Iinclude

OBJS:=$(patsubst $(SRCS_PATH)/%.c,$(OBJS_PATH)/%.o,$(wildcard $(SRCS_PATH)/*.c))
HDRS:=include/*.h

$(TARGET) : $(OBJS) $(HDRS)
	$(LINK.o) -o $@ $(OBJS)

$(OBJS_PATH)/%.o : $(SRCS_PATH)/%.c $(HDRS) | $(OBJS_PATH)
	$(COMPILE.c) $(INC) -o $@ $<

$(OBJS_PATH):
	mkdir $@

clean:
	rm -rf $(TARGET) $(OBJS)





