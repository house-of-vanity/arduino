import serial
import time

PORT='/dev/ttyACM1'
BAUD=9600
INIT_TIME=3

ser = serial.Serial(PORT, BAUD)
time.sleep(INIT_TIME)
ser.write(bytearray('\11TITSADjsdaldkjhasdyLEasdhgasdgasdghsagdahsgdhsagdjasgjhdagsjhdgasjhdgjaghsad\0Loasdsadsadaslkmhdaskjdh\0','utf8'))
#ser.write(bytearray('{EQ','utf8'))
