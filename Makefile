TARGET := main
TARGET_TEST := $(TARGET)_test
CFLAGS += -g
CFLAGS += -std=c99
INC := -Iinclude

# Automatic dependency generation from this link:
# http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
DEPDIR = .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:.c=.o)
OBJS := $(subst src, obj, $(OBJS))

TEST_SRCS := $(wildcard tests/*.c)
TEST_OBJS := $(TEST_SRCS:.c=.o)

obj/%.o : src/%.c
	$(COMPILE.c) $(DEPFLAGS) $(INC) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

# No automatic dependency for test files.
tests/%.o : tests/%.c
	$(COMPILE.c) $(INC) $(OUTPUT_OPTION) $<

all: $(TARGET) $(TARGET_TEST)

$(TARGET): $(OBJS)
	$(LINK.o) -o $@ $^

# The target usually has a source file with the target's name that contains a
# main method. Remove that, as the test target also has a main method.
OBJS_MINUS_TARGET := $(filter-out obj/$(TARGET).o, $(OBJS))
$(TARGET_TEST): $(OBJS_MINUS_TARGET) $(TEST_OBJS)
	$(LINK.o) -o $@ $^
	@rm tests/*.o

-include $(DEPDIR)/*.d

clean:
	@rm -rf $(TARGET) $(OBJS) $(TEST_OBJS) $(TARGET_TEST) $(DEPDIR)
