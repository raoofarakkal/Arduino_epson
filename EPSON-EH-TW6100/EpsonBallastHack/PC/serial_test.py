import serial
# import sys
# import time

# port = serial.Serial(
#     port='/dev/ttyUSB0',
#     baudrate=4800,
#     parity=serial.PARITY_EVEN,
#     stopbits=serial.STOPBITS_ONE,
#     bytesize=serial.EIGHTBITS
# )

usb0 = serial.Serial('/dev/ttyUSB0', 4800)
usb1 = serial.Serial('/dev/ttyUSB1', 4800)

snd = b'\x81'
usb0.write(snd)
print('Send to usb-0: ', snd)

data = usb1.read()  # .hex()
print('Received on usb-1: ', data)
	

snd = b'\x82'
usb1.write(snd)
print('Send to usb-1: ', snd)

data = usb0.read()  # .hex()
print('Received on usb-0: ', data)


# data = bytes(sys.argv[1], 'ascii')
# di = int(sys.argv[1],16)
# ds = str(di)

# data = bytes(sys.argv[1],'ascii')
# port.write(data)
# print('Send: ', data)


# while True:
    # data = 1 # bytes(sys.argv[1], 'ascii')
    # port.write(data)
    # print('Send: ', data)
    # time.sleep(.2)

# snd = b'\x48'
# port.write(snd)
#
# data = port.read() # .hex()
# print(data)
# # print(hex(int(data)))

# data = port.read()
# if len(data) > 0:
#     print('Received: ', data)
#     # break

usb0.close()
usb1.close()

