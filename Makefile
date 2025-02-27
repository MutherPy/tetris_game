

targets = components/field_manager.c \
	components/object_manager.c \
	objects/object.c \
	objects/object_calculator/object_calculator.c \
	main.c

compile: $(targets)
	@(clang $? -o main.o || gcc $? -o main.o) && echo 'Yo, aka'

run: compile
	@./main.o

build: compile run

.DEFAULT_GOAL := build