# acarsdec
source: https://github.com/TLeconte/acarsdec (https://github.com/TLeconte/acarsdec/archive/ac7f7a2c8a79764137050da0b4faae7b36fc740a.zip)

manual build:
````
mkdir -p build && cd build
CCC=i686-w64-mingw32-gcc -O3 -flto
$CCC -DWITH_RTL -c -o label.o ../label.c
$CCC -DWITH_RTL -c -o rtl.o ../rtl.c
$CCC -DWITH_RTL -c -o cJSON.o ../cJSON.c
$CCC -DWITH_RTL -c -o output.o ../output.c
$CCC -DWITH_RTL -c -o msk.o ../msk.c
$CCC -DWITH_RTL -c -o acars.o ../acars.c
$CCC -DWITH_RTL -c -o acarsdec.o ../acarsdec.c
$CCC -s -o acarsdec.exe acarsdec.o acars.o msk.o rtl.o output.o label.o cJSON.o -lws2_32 -pthread -lrtlsdr
````

# RTLSDR-Airband

see [Wiki](https://github.com/hhrhhr/rtl-sdr-windows/wiki)
