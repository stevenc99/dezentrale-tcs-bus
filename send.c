#define _BSD_SOURCE
#include <features.h>

#include <stdio.h>
#include <unistd.h>

int main() {
// :XXX: take as a command-line arg
//	const char frame[] = "0001010110101100101010101";	// door open
	const char frame[] = "000110101011011011011011001101010100110010101010011";	// door bell

#ifdef TEST
	FILE *fd = fopen("/dev/fd/1", "ab");
#else
	FILE *fd = fopen("/sys/devices/virtual/gpio/gpio44/value", "ab");
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

#ifdef TEST
	fputc('\n', fd);
#endif
	fclose(fd);
	return 0;
}
