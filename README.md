gorgone
=======

*gorgone* is an interactive device developped for the project *Plus bleu que bleu* by Stéfane Perraud.

There is an openFrameworks application running on a Raspberry Pi with its camera that detect people iris and generate shape according to that iris.
The shape is then projected thanks to a 405nm laser scanner system.
The laser is driven by Puredata.

OF application and PureData patch are remotely controlled by a Max path.

All the three are using Jamoma and Minuit protocole to communicate.

Compiling
---------

Make sure that [of](https://github.com/ofnode/of) and ofApp share the same folder.

Change directory to ofApp and perform these steps:

```bash
mkdir build
cd build
cmake .. -G Ninja
ninja
```

Configuration
-------------

All computers should be connected to a local network with a DHCP server.
Only the master computer is setup with a fixed IP address of 192.168.2.1.
DHCP server should address IP in the subnet 192.168.2.x.

RPi hostname should be set (with raspi-config utility) to gorgone-1, gorgone-2, gorgone-3 and gorgone-4.

