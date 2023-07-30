#include "ncrx.h"
#include "string.h"
#include <time.h>

__AFL_FUZZ_INIT();

int main(int argc, char **argv) {
	#ifdef __AFL_HAVE_MANUAL_CONTROL
	__AFL_INIT();
	#endif
	
	unsigned char *buf = __AFL_FUZZ_TESTCASE_BUF;
	while (__AFL_LOOP(10000)) {
	        int len = __AFL_FUZZ_TESTCASE_LEN;
		struct timespec ts;
		if (clock_gettime(CLOCK_MONOTONIC, &ts)) {
			perror("clock_gettime");
			return 1;
		}
		uint64_t now = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
		//ncrx fuzzing :D
		struct ncrx *ncrx = ncrx_create(NULL);
		if(argc == 2) {
		  printf("myprocess\n");
		  myProcess(buf, now, 0,ncrx,len);
		} else {
		  printf("no myprocess\n");
		  ncrx_process(buf, now, 0,ncrx);
		}
		ncrx_destroy(ncrx);
	}
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
