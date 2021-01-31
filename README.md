# EPSON EH-TW6100 3D LCD projector ballast hack using Arduino

This project will help you to hack and emulate EPSON EH-TW6100 3D LCD projector ballast.

If we try to use any light source other than the stock one, the projector will go to error mode (will blink both error lights). 
To overcome this, you need to hack and emulate communication between Ballast and the Motherboard.

Here is how you can mod any projector,

1. You need a projector with working lamp and ballast to monitor the data exchange 
   (for TW6100, req/resp data available in EPSON-EH-TW6100/EpsonBallastHack/PC/data-backup-working-version/Data-Req-Resp-MB-AND-BALLAST.ods file)

2. Use CP2102 USB to TTL USB UART Module Serial Converter with optocoupler to monitor the data exchange between motherboard and ballast. You may need two CP2102 in order to monitor both side (IN/OUT) of data exchange

3. Program the arduino to work like an emulator to respond to motherboard.

4. Build a good LED light source for your projector (Cree CXB3590 is a good choice).


Check EPSON-EH-TW6100/EpsonBallastHack/PC/usb0_listen.py file to monitor the data send to ballast (use the same script to monitor the response as well by changing the port):


