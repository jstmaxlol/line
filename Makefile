all:
	cc -o line line.c -O2 -Wall -Wextra -pedantic

clean:
	rm ./line
	rm ./buff

install:
	cc -o line line.c -O2 -Wall -Wextra -pedantic
	sudo install -m 0755 ./line /usr/bin/line
