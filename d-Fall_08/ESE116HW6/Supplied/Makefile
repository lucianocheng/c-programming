all: weather

weather: weatherTest.c weatherFunctions.c weather.h
	cc -g -Wall weatherTest.c weatherFunctions.c -o weather

debug: weather.c weather.h
	cc -g -Wall -D DEBUG weatherTest.c weatherFunctions.c -o weather

run: weather
	./weather

clean:
	rm -f weather
