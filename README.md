# prepare
````
mkdir -p /mingw/bin /mingw/include/libusb-1.0
cp /usr/x86_64-w64-mingw32/lib/libwinpthread-1.dll /mingw/bin/
strip 
````

# libusb

source: https://github.com/libusb/libusb (https://github.com/libusb/libusb/archive/5912d561a755c0af799530fb47d5e65eb25fde4a.zip)

with autotools:
````
./bootstrap.sh
mkdir -p build && cd build
../configure --host=x86_64-w64-mingw32 --disable-log --prefix=/mingw/
make
make install-strip
````
or manually:
````
mkdir -p build && cd build
CCC=x86_64-w64-mingw32-gcc -O3 -flto
x86_64-w64-mingw32-windres -o libusb-1.0-rc.o ../libusb/libusb-1.0.rc
$CCC -I. -c -o core.o ../libusb/core.c
$CCC -I. -c -o descriptor.o ../libusb/descriptor.c
$CCC -I. -c -o hotplug.o ../libusb/hotplug.c
$CCC -I. -c -o io.o ../libusb/io.c
$CCC -I. -c -o strerror.o ../libusb/strerror.c
$CCC -I. -c -o sync.o ../libusb/sync.c
$CCC -I. -I../libusb -c -o poll_windows.o ../libusb/os/poll_windows.c
$CCC -I. -I../libusb -c -o threads_windows.o ../libusb/os/threads_windows.c
$CCC -I. -I../libusb -c -o windows_nt_common.o ../libusb/os/windows_nt_common.c
$CCC -I. -I../libusb -c -o windows_usbdk.o ../libusb/os/windows_usbdk.c
$CCC -I. -I../libusb -c -o windows_winusb.o ../libusb/os/windows_winusb.c
$CCC -shared -s -o libusb-1.0.dll *.o
cp libusb-1.0.dll /mingw/bin
cp ../libusb/libusb.h /mingwbin/include/libusb-1.0
````

# rtl-sdr

source: https://github.com/osmocom/rtl-sdr (https://github.com/osmocom/rtl-sdr/archive/9047eef701f50d8bc4748233a31d65a0519ed86c.zip)

with cmake:
````
mkdir -p build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=/mnt/e/devel/mingw64.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/mingw -DLIBUSB_INCLUDE_DIR=/mingw/include/libusb-1.0 -D"LIBUSB_LIBRARIES=-L/mingw/lib -lusb-1.0" ..
make
make install/strip
````
or manually:
````
CCC=x86_64-w64-mingw32-gcc -O3 -flto
RTLI=-I../include
RTLL="-L. -lrtlsdr"
USBI=-I/mingw/include/libusb-1.0/
USBL="-L/mingw/lib -lusb-1.0"
$CCC $RTLI -c -o conv.o ../src/convenience/convenience.c
$CCC $RTLI -c -o tuner_e4k.o ../src/tuner_e4k.c
$CCC $RTLI -c -o tuner_fc0012.o ../src/tuner_fc0012.c
$CCC $RTLI -c -o tuner_fc0013.o ../src/tuner_fc0013.c
$CCC $RTLI -c -o tuner_fc2580.o ../src/tuner_fc2580.c
$CCC $RTLI -c -o tuner_r82xx.o ../src/tuner_r82xx.c
$CCC $RTLI $USBI -c -o librtlsdr.o ../src/librtlsdr.c
$CCC -shared -s -o librtlsdr.dll librtlsdr.o tuner_e4k.o tuner_fc0012.o tuner_fc0013.o tuner_fc2580.o tuner_r82xx.o $USBL
$CCC -c $RTLI -o rtl_sdr.o ../src/rtl_sdr.c
$CCC -c $RTLI -o rtl_tcp.o ../src/rtl_tcp.c
$CCC -c $RTLI -o rtl_test.o ../src/rtl_test.c
$CCC -c $RTLI -o rtl_eeprom.o ../src/rtl_eeprom.c
$CCC -c $RTLI $USBI -o rtl_fm.o ../src/rtl_fm.c
$CCC -c $RTLI $USBI -o rtl_adsb.o ../src/rtl_adsb.c
$CCC -c $RTLI $USBI -o rtl_power.o ../src/rtl_power.c
$CCC -s -o rtl_sdr.exe rtl_sdr.o conv.o $RTLL
$CCC -s -o rtl_tcp.exe rtl_tcp.o conv.o $RTLL -lpthread -lws2_32
$CCC -s -o rtl_test.exe rtl_test.o conv.o $RTLL
$CCC -s -o rtl_eeprom.exe rtl_eeprom.o conv.o $RTLL
$CCC -s -o rtl_fm.exe rtl_fm.o conv.o $RTLL -lpthread
$CCC -s -o rtl_adsb.exe rtl_adsb.o conv.o $RTLL -lpthread
$CCC -s -o rtl_power.exe rtl_power.o conv.o $RTLL
cp *.dll *.exe /mingw/bin/
cp ../include/rtl-*.h /mingw/include/
````
