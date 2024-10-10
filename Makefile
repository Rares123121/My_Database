# Copyright Gheorghe Rares-Mihail 311CA 2023-2024

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS = program #sfl

build: $(TARGETS)

program: program.c
	$(CC) $(CFLAGS) sfl.c -lm -o sfl

pack:
	zip -FSr 3XYCA_FirstnameLastname_Tema1.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
