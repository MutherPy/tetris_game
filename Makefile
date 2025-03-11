
CFLAGS =  -Wall `pkg-config --cflags gtk+-3.0` -pthread
LDFLAGS =  -Wall `pkg-config --libs gtk+-3.0` -pthread

SRC_DIR := src

GTK_CHECK := $(shell pkg-config --exists gtk+-3.0 && echo 1 || echo 0)

targets := \
 $(wildcard $(SRC_DIR)/*.c) \
 $(wildcard $(SRC_DIR)/**/*.c) \
 $(wildcard $(SRC_DIR)/*/*/*.c) \
 $(wildcard $(SRC_DIR)/*/*/*/*.c)

compile: $(targets)
	@if [ $(GTK_CHECK) -eq 0 ]; then \
		brew install gtk+3; \
	fi
	@(clang $? $(CFLAGS) -o bin/main $(LDFLAGS) || gcc $? $(CFLAGS) -o bin/main $(LDFLAGS)) && echo 'Yo, aka'

run: compile
	@./bin/main

build: compile run

.DEFAULT_GOAL := build