# libusb

source: https://sourceforge.net/projects/libusb/files/libusb-1.0/libusb-1.0.21/libusb-1.0.21.tar.bz2/download

````
./configure --host=x86_64-w64-mingw32 --disable-log --prefix=/mingw64/
make
sudo make install-strip
````

# rtl-sdr

source: https://github.com/osmocom/rtl-sdr/archive/b04c2f9f035c5aede43d731e5d58e4725d2f8bb4.zip

Makefile.mingw:
````
CROSS?=x86_64-w64-mingw32-
CC=$(CROSS)gcc
CFLAGS=-O3 -Wall -Wextra -Iinclude -Wno-unused -Wno-format -Wno-unused-parameter -Wno-unknown-pragmas
USB_INC=-I/mingw64/include/libusb-1.0
USB_LIB=-L/mingw64/lib -lusb-1.0
PROG_LIB=-lws2_32 -lpthread -L. -lrtlsdr 
RTL_S=librtlsdr.c tuner_e4k.c tuner_fc0012.c tuner_fc0013.c tuner_fc2580.c tuner_r82xx.c
PROG=rtl_sdr rtl_tcp rtl_test rtl_fm rtl_eeprom rtl_adsb rtl_power
RTL_S:=$(addprefix src/, $(RTL_S))
PROG_E=$(PROG:=.exe)
all: conv.o librtlsdr.dll $(PROG_E)
conv.o:
	$(CC) $(CFLAGS) -c -o $@ src/convenience/convenience.c
%.dll:
	$(CC) $(CFLAGS) $(USB_INC) -shared -s -o $@ $(RTL_S) $(USB_LIB)
%.exe:
	$(CC) $(CFLAGS) -s -o $@ src/$(@:.exe=.c) conv.o  $(PROG_LIB)
clean:
	rm *.o *.exe *.dll
````
````
install rtl-sdr.h rtl-sdr_export.h
install libwinpthread-1.dll
````
