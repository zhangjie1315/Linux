.PHONY: clean

OBJ = obj/def.o \
		obj/tetris.o \
		obj/keyboard.o \
		obj/main.o

CFLAGS= -Iinclude -g

all:main 

main: $(OBJ)
	gcc $(CFLAGS) $^ -o bin/$@ 

obj/%.o : src/%.c
	gcc $(CFLAGS) -c $< -o $@ 

clean:
	rm -rf obj/*

