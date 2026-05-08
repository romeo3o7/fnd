.PHONY: build rebuild clean

build:
	gcc main.c package.c update.c child.c file.c -o fnd

rebuild: clean build

clean:
	rm -f fnd
