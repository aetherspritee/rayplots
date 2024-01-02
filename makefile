CC=clang
CFLAGS=-Ilibs -Llibs/ -framework IOKit -framework Cocoa -framework OpenGL libs/libraylib.a
OBJ = main.c

rayplots: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
