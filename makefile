CC=clang
CFLAGS=-Ilibs -Llibs/ -framework IOKit -framework Cocoa -framework OpenGL libs/libraylib.a
OBJ = main.c

bin/rayplots: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
