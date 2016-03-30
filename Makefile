TARGET := main
CFLAGS += -g
CFLAGS += -std=c99
INC := -Iinclude

# Automatic dependency generation from this link:
# http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
DEPDIR = .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

COMPILE.c += $(DEPFLAGS)
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:.c=.o)
OBJS := $(subst src, obj, $(OBJS))

obj/%.o : src/%.c
	$(COMPILE.c) $(INC) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LINK.o) -o $@ $^

-include $(DEPDIR)/*.d

clean:
	@rm -rf $(TARGET) $(OBJS) $(DEPDIR)
