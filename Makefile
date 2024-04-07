
test.c:
	gcc -o out -I./ -I./drivers -I./testing testing/runner.c iot-tp/**/*.c drivers/test/drivers.c

gen.c:
	gcc -shared -o iot-tp.so iot-tp/**/*.c -I./ -I./drivers drivers/${PLATFORM}/*.c ${LFLAGS}
gen.rpi.c:
	make gen.c PLATFORM="rpi" LFLAGS="-L/usr/local/lib -lwiringPi -lwiringPiDev -lpthread -lm -lcrypt -lrt"
