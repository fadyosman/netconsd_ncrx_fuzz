#include "ncrx.h"
#include <time.h>

__AFL_FUZZ_INIT();

int main(int argc, char **argv) {
	#ifdef __AFL_HAVE_MANUAL_CONTROL
	__AFL_INIT();
	#endif
	struct ncrx *ncrx = ncrx_create(NULL);
	unsigned char *buf = __AFL_FUZZ_TESTCASE_BUF;
	while (__AFL_LOOP(10000)) {
		struct timespec ts;
		if (clock_gettime(CLOCK_MONOTONIC, &ts)) {
			perror("clock_gettime");
			return 1;
		}
		uint64_t now = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
		ncrx_process(buf, now, 0,ncrx);
	}
	ncrx_destroy(ncrx);
}
