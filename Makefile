export DPKG_EXPORT_BUILDFLAGS=1
include /usr/share/dpkg/buildflags.mk

CFLAGS+=-Wall -std=c99

all: send send-test
clean:
	rm -f send send-test

send: send.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o send $<

send-test: send-test.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -DTEST -o send-test $<
