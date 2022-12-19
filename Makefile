CC=g++
CFLAGS=-Wall -O
LDFLAGS=-Wall -c
EXEC=mykito
SRC_DIR=src
INCLUDE_DIR=include
LIB=lib

all: $(EXEC)

mykito: mymosq.o main-mqtt.o $(LIB)/libmosquittopp.so
	$(CC) mymosq.o main-mqtt.o $(LIB)/libmosquittopp.so -o $@ $(CFLAGS)

mqtt-pub: mymosq.o main-pub.o $(LIB)/libmosquittopp.so
	$(CC) mymosq.o main-pub.o $(LIB)/libmosquittopp.so -o $@ $(CFLAGS)

mqtt-sub: mymosq.o main-sub.o $(LIB)/libmosquittopp.so
	$(CC) mymosq.o main-sub.o $(LIB)/libmosquittopp.so -o $@ $(CFLAGS)

main-mqtt.o: $(SRC_DIR)/main-mqtt.cpp
	$(CC) $(SRC_DIR)/$*.cpp -o $@ $(LDFLAGS)

main-pub.o: $(SRC_DIR)/main-pub.cpp
	$(CC) $(SRC_DIR)/$*.cpp -o $@ $(LDFLAGS)

main-sub.o: $(SRC_DIR)/main-sub.cpp
	$(CC) $(SRC_DIR)/$*.cpp -o $@ $(LDFLAGS)

mymosq.o: $(INCLUDE_DIR)/MyMosq.h $(SRC_DIR)/MyMosq.cpp
	$(CC) $(SRC_DIR)/MyMosq.cpp -o $@ $(LDFLAGS)

clean:
	rm -fr *.o

mrproper: clean
	rm -rf $(EXEC)

install:
	cp mykito /usr/local/bin
