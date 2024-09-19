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

CFLAGS := -O2 -Wall -flto
CXXFLAGS := -std=c++20 -O2 -Wall -Wextra -flto -fwhole-program-vtables -fforce-emit-vtables -fvirtual-function-elimination
LDFLAGS := -O2 -Wall -Wextra -flto
# -e start -static

CPPFLAGS := $(INCFLAGS)

.PHONY: all clean

all: executable

executable: $(BUILDDIR)/$(TARGET)

$(BUILDDIR)/$(TARGET): $(OBJS)
	mkdir -p $(dir $@)
	$(CXX) $(LDFLAGS) $(CPPFLAGS) $^ -o $@
#	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)/*

-include $(DEPS)
