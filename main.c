#include "ncrx.h"
#include "string.h"
#include <time.h>
#include <klee/klee.h>

int main(int argc, char **argv) {
		unsigned char buf[4096];
	        int len = 4096;
		klee_make_symbolic(&buf, sizeof(buf), "buf");
		struct timespec ts;
		if (clock_gettime(CLOCK_MONOTONIC, &ts)) {
			perror("clock_gettime");
			return 1;
		}
		uint64_t now = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
		//ncrx fuzzing :D
		struct ncrx *ncrx = ncrx_create(NULL);
		myProcess(buf, now, 0,ncrx,len);
		ncrx_destroy(ncrx);
}

int myProcess(const char *payload, uint64_t now_mono, uint64_t now_real,
		struct ncrx *ncrx, unsigned int length) {
  	//In afl, you will need to NULL terminate the string since AFL would print anything.
	char *string = payload;
	string[length-1] = '\0';
	// Extract the first token
	char *token = strtok(string, "\n");
        // loop through the string to extract all other tokens
        while( token != NULL ) {
          printf("Processing: %s\n", token);
          ncrx_process(token, now_mono, now_real,ncrx);
          token = strtok(NULL, " ");
        }
}
