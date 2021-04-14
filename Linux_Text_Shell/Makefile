OBJ = main.o shell.o
all: shellKK
shellKK: $(OBJ)
	gcc $(OBJ) -g -o shellKK
$(OBJ): shell.h
.PHONY: clean
clean:
	rm -f *.o shellKK