
SRC_DIR := src


targets := \
 $(wildcard $(SRC_DIR)/*.c) \
 $(wildcard $(SRC_DIR)/**/*.c) \
 $(wildcard $(SRC_DIR)/*/*/*.c) \
 $(wildcard $(SRC_DIR)/*/*/*/*.c)

compile: $(targets)
	#echo $?
	@(clang $? `pkg-config --cflags --libs gtk+-3.0` -o bin/main || gcc $? `pkg-config --cflags --libs gtk+-3.0` -o bin/main) && echo 'Yo, aka'

run: compile
	@./bin/main

build: compile run

.DEFAULT_GOAL := build