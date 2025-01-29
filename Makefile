
compile: main.c
	@(clang $? -o main.o || gcc $? -o main.o) && echo 'Yo, aka'

run: compile
	@./main.o

build: compile run

.DEFAULT_GOAL := build