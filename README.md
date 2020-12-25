# EPSON EH-TW6100 3D LCD projector ballast hack using Ardunino

This project will help you to hack and emulate EPSON EH-TW6100 3D LCD projector ballast.

If we try to use any light source other than the stock one, the projector will go to error mode (will blink both error lights). 
To overcome this, you need to hack and emulate communication between Ballast and the Motherboard.

Here is how you can mod the projector,

1. You need a projector with working lamp and ballast to monitor the data exchange

2. Use CP2102 USB to TTL USB UART Module Serial Converter with optocoupler to monitor the data exchange between motherboard and ballast. You may need two CP2102 in order to monitor both side (IN/OUT) of data exchange

3. Program the arduino to work like an emulator to respond to motherboard.

4. Build a good LED light source for your projector (Cree CXB3590 is a good choice but use proper heatsink).


Python script to monitor the data send to ballast (use the same script to monitor the response as well by changing the port)
-------------------------------------------------
import serial
import sys
from datetime import datetime


def get_time():
   return str(datetime.now().timestamp())

def get_timef():
   return datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f')[:-3]

def get_filename():
   return datetime.now().strftime('%Y_%m_%d_%H_%M_%S')+'.txt'


'# usb0 = serial.Serial(
'#     port='/dev/ttyUSB0',
'#     baudrate=4800,
'#     parity=serial.PARITY_EVEN,
'#     stopbits=serial.STOPBITS_ONE,
'#     bytesize=serial.EIGHTBITS
'# )
port = 'USB0'
usb = serial.Serial('/dev/tty'+port, 4800)
f = open('.data/'+port+'_'+get_filename(),'w')
msg = get_timef() +', '+port+' opened and waiting for data'
print(msg)
f.write(get_time()+','+msg+'\n')

while True:
   try:
      data = usb.read()  # .hex()
      msg = get_timef() +', Received on '+port+': , 0x'+data.hex()
      print(msg)
      f.write(get_time()+','+msg+'\n')
   except KeyboardInterrupt:
      msg = get_timef() +', Terminated by user'
      f.write(get_time()+','+msg+'\n')
      usb.close()
      f.close()
      print(msg)
      sys.exit()
