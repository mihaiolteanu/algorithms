TARGET=main
CFLAGS=-g -std=c99
INC=-Iinclude

SRCS:=$(wildcard src/*.c)
OBJS:=$(SRCS:.c=.o)
OBJS:=$(subst src, obj, $(OBJS))
HDRS:=$(wildcard include/*.h)

$(TARGET) : $(OBJS) $(HDRS)
	$(LINK.o) -o $@ $(OBJS)

obj/%.o : src/%.c
	$(COMPILE.c) $(INC) -o $@ $<

clean:
	rm -rf $(TARGET) $(OBJS)





