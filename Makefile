# your c compiler
CC = clang

# where to install
PREFIX = /usr/local/bin

# your project name
TARGET = poof

CFLAGS = -Ideps -Wall -g3 -fno-inline -fno-omit-frame-pointer -fsanitize=address
LDFLAGS = -fsanitize=address

# all the source files
SRC = $(wildcard src/*.c)
SRC += $(wildcard deps/*/*.c)

OBJS = $(SRC:.c=.o)

.PHONY:
all: $(TARGET)

.PHONY:
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS)

.PHONY:
%.o: %.c
	$(CC) $(DEP_FLAG) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

.PHONY:
clean:
	rm -f $(OBJS)

.PHONY:
install: $(TARGET)
	cp -f $(TARGET) $(PREFIX)

.PHONY:
uninstall: $(PREFIX)/$(TARGET)
	rm -f $(PREFIX)/$(TARGET)

.PHONY:
format:
	clang-format -i src/{*.h,*.c}

.PHONY:
valgrind: poof
	valgrind ./poof

_build-boilerplate:
	@mkdir build 2>/dev/null || true

.PHONY:
test-%: _build-boilerplate
	$(CC) $(CFLAGS) $(LDFLAGS) -o build/$* test/$*.c $(filter-out src/poof.o, $(OBJS) )
	./build/$*

.PHONY:
test: test-generator
