import serial
import time

PORT='/dev/ttyACM0'
BAUD=9600
INIT_TIME=3

ser = serial.Serial(PORT, BAUD)
time.sleep(INIT_TIME)
ser.write(bytearray('\11Anal Nosorog\0Gazavat (2009)\0','utf8'))
#ser.write(bytearray('{EQ','utf8'))
