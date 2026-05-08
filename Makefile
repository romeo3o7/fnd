.PHONY: build rebuild clean

build:
	gcc main.c src/package.c src/update.c src/child.c src/file.c -o fnd

rebuild: clean build

clean:
	rm -f fnd
