
test.c:
	gcc -o out -I./src -I./testing testing/runner.c src/**/*.c drivers/test/drivers.c

gen.c:
	gcc -shared -o iot-tp.so -I./src src/**/*.c -I./ drivers/${PLATFORM}/*.c ${LFLAGS}
gen.rpi.c:
	make gen.c PLATFORM="rpi" LFLAGS="-L/usr/local/lib -lwiringPi -lwiringPiDev -lpthread -lm -lcrypt -lrt"
