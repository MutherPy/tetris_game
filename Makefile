
SRC_DIR := src


targets := \
 $(wildcard $(SRC_DIR)/*.c) \
 $(wildcard $(SRC_DIR)/**/*.c) \
 $(wildcard $(SRC_DIR)/*/*/*.c) \
 $(wildcard $(SRC_DIR)/*/*/*/*.c)

compile: $(targets)
	#echo $?
	@(clang $? `pkg-config --cflags --libs gtk+-3.0` -o bin/main.o || gcc $? `pkg-config --cflags --libs gtk+-3.0` -o bin/main.o) && echo 'Yo, aka'

run: compile
	@./bin/main.o

build: compile run

.DEFAULT_GOAL := build