#define _BSD_SOURCE
#include <features.h>

#include <stdio.h>
#include <unistd.h>

int main() {
//	const char frame[] = "0001010110101100101010101";	// door open
	const char frame[] = "000110101011011011011011001101010100110010101010011";	// door bell

#ifdef TEST
	FILE *fd = fopen("/dev/fd/0", "ab");
#else
	FILE *fd = fopen("/sys/devices/virtual/gpio/gpio44/value", "ab");
#endif

	for (int i = 0; i < sizeof(frame)-1; i++) {
		int output = frame[i] ^ 0x1;
		fputc(output, fd);
#ifdef TEST
		fflush(fd);
#endif
		usleep(2000);
	}

	fclose(fd);
	return 0;
}
