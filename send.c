#define _BSD_SOURCE
#include <features.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define GPIO "/sys/devices/virtual/gpio/gpio44/value"

int main(int argc, char *argv[]) {
	// Door-Open code
	const char frame[] = "000101011010110010101010";

#ifdef TEST
// Send output to stderr instead of the real GPIO
# define fd stderr
#else
	FILE *fd = fopen(GPIO, "ab");
	if (!fd) {
		fprintf(stderr, "%s: failed to open '%s':\n", argv[0], GPIO);
		perror(NULL);
		exit(1);
	}
#endif

	for (unsigned int i = 0; i < sizeof(frame)-1; i++) {
		unsigned char output = frame[i] ^ 0x1;
// :XXX: putc_unlocked may be faster
// :XXX: benchmark this without any sleeps
		fputc(output, fd);
		fflush(fd);
// :XXX: trigger from a real clock source
//		usleep(2000);
		usleep(1800);
	}

	// Put the line back into idle state
	fputs("0\n", fd);
	fclose(fd);
	return 0;
}
