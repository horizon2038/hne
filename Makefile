TARGET := hne
SRCDIR := ./src
BUILDDIR := ./build

SRCS := $(shell find $(SRCDIR) -type f \( -name "*.c" -or -name "*.cpp" \))
OBJS := $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SRCS:$(SRCDIR)/%=%))))
$(warning $(OBJS))
DEPS := $(OBJS:.o=.d)

INCDIR := $(SRCDIR)/include
INCFLAGS := $(addprefix -I, $(INCDIR))

$(warning $(INCFLAGS))

CC := clang
CXX := clang++
LD := ld.lld

CFLAGS := -g -O2 -Wall
CXXFLAGS := -g -O2 -Wall -Wextra
LDFLAGS := -e start -static

CPPFLAGS := $(INCFLAGS)

.PHONY: all clean

all: executable

executable: $(BUILDDIR)/$(TARGET)

$(BUILDDIR)/$(TARGET): $(OBJS)
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $^ -o $@
#	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)/*

-include $(DEPS)
