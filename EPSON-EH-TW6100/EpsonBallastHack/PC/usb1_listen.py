import serial
import sys
from datetime import datetime


def get_time():
	return str(datetime.now().timestamp())

def get_timef():
	return datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f')[:-3]

def get_filename():
	return datetime.now().strftime('%Y_%m_%d_%H_%M_%S')+'.txt'


# usb0 = serial.Serial(
#     port='/dev/ttyUSB0',
#     baudrate=4800,
#     parity=serial.PARITY_EVEN,
#     stopbits=serial.STOPBITS_ONE,
#     bytesize=serial.EIGHTBITS
# )
port = 'USB1'
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


