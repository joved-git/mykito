* Presentation:
This project needs libmosquittopp.so lib (you will find it into the package libmosquittopp-dev).
Reference site: https://www.disk91.com/2013/technology/programming/mosquitto-c-sample-code-to-publish-message/

See also here: http://wiki.neuromeka.net/index.php?title=Implementing_MQTT_Client_using_C%2B%2B_with_libmosquitto

The program should make publisher or subscriber.
Syntax is:
mykito [-h <host, def:localhost>] [-p <port, def:1883>] [-t <topic, def:topic>] [-d <mode (pub|sub), def:pub]
---

* Utilisation:
You need a broker to use this publisher and subscriber. For example, mosquitto is great and you just have a machine with this binary running on it (example /usr/sbin/mosquitto -c /etc/mosquitto/mosquitto.conf).

After that, the subscriber command is: 
$ mykito -h host -t mytopic -d sub

The publisher command is:
$ mykito -h host -t mytopic -d pub

Type message after that to see it on the publisher.  Special message "quitnow" is used to quit both publisher and subscriber.
---

* Library installation:
Install libmosquittopp

$ sudo apt install libmosquittopp-dev

After that, find libmosquittopp.so.1 in /usr/local/... and link it.
In your dev directory (where the Makefile is).

$ mkdir lib
$ cd lib
$ ln -s /usr/lib/<your dir>/libmosquittopp.so.1 ./ libmosquitto.so
---

* Compilation:
You just need to link (ln -s ...) ./lib/libmosquittopp.so to your libmosquittopp.so.1 library, for example /usr/lib/arm-linux-gnueabihf/libmosquittopp.so.1

So...

$ make
$ sudo make install


