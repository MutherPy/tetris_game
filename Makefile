
SRC_DIR := src


targets := $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*/*.c)

compile: $(targets)
	@(clang $? -o bin/main.o || gcc $? -o bin/main.o) && echo 'Yo, aka'

run: compile
	@./bin/main

build: compile run

.DEFAULT_GOAL := build