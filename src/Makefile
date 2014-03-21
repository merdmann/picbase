
include make.conf.win32


all :: main.hex

main.hex :: timer.o main.c crt0iz.o output.o proc.o
	$(CC) $(CFLAGS) --link="gplink -m -s main.lkr"  crt0iz.o timer.o proc.o main.c output.o 

load:
	../bin/fsusb main.hex

clean ::
	$(RM) *.o *.cod *.map *.lst *~ 
	rm ../bin/fsusb


	
