SOURCES=oid.c
OBJECTS=$(SOURCES:%.c=build/%.o)
TEST_SOURCES=$(SOURCES:%.c=tests/%.c)
TEST_OBJECTS=build/test_$(notdir $(OBJECTS))
TEST_CFLAGS=$(shell pkg-config --cflags check) -Wall -ggdb
TEST_LIBS=$(shell pkg-config --cflags --libs check) -ggdb
CC=gcc
RM=rm
LIBS=
CFLAGS=

.PHONY: all clean

$(OBJECTS): $(SOURCES) 
	$(CC) $^ -c $(CFLAGS) -o $@

all: $(OBJECTS)
	$(CC) $(LIBS) $(OBJECTS) -o prg 

$(TEST_OBJECTS): $(TEST_SOURCES)
	$(CC) $^ $(TEST_CFLAGS) -c -o $@

test: $(TEST_OBJECTS) $(OBJECTS)
	$(CC) $^ $(TEST_LIBS) -o build/$(notdir $(TEST_OBJECTS:%.o=%))
	./build/$(notdir $(TEST_OBJECTS:%.o=%))

clean:
	$(RM) -f build/*
