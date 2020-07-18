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

port = serial.Serial('/dev/ttyUSB0', 4800)

snd = b'\x84'
port.write(snd)

while True:
    data = port.read()  # .hex()
    print(data)


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

port.close()
