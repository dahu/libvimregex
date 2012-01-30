CFLAGS = -I../vendor/include
LDFLAGS = -L../vendor/lib -lonig
TEST_LDFLAGS = $(LDFLAGS) -ltap

%.c: %.peg
	./peg -o $@ $<

test : test_libvimregex
	./test_libvimregex

test_libvimregex : test_libvimregex.o libvimregex.o
	$(CC) $(TEST_LDFLAGS) -o $@ $^

libvimregex.o : libvimregex.c libvimregex.h libvimregexparser.o
test_libvimregex.o : test_libvimregex.c
libvimregexparser.o : libvimregexparser.c
libvimregexparser.c : libvimregexparser.peg

clean : .FORCE
	rm -f *~ *.o *.peg.[cd] *.leg.[cd] libvimregexparser.c test_libvimregex

.FORCE :
