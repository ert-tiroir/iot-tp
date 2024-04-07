
test.c:
	gcc -o out -I./src -I./testing testing/runner.c src/**/*.c drivers/test/drivers.c

gen.c:
	gcc -shared -o iot-tp.so -I./src src/**/*.c -I./ drivers/${PLATFORM}/*.c
gen.rpi.c:
	make gen.c PLATFORM="rpi"
