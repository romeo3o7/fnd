.PHONY: build rebuild clean

build:
	gcc -Wall -Wextra -O2 main.c src/package.c src/update.c src/child.c src/file.c -o fnd

rebuild: clean build

clean:
	rm -f fnd
