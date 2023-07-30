hellomake: main.c libncrx.c
	$(CC) -o fuzzme main.c libncrx.c -I.
