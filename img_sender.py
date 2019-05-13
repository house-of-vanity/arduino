import time
from PIL import Image, ImageDraw, ImageFont
import io
import serial
import time
import logging

from plugins.cpu import cpu
from plugins.ram import ram
from plugins.japanese import japanese

logging.basicConfig(
    level=logging.DEBUG,
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s')
log = logging.getLogger("serial." + __name__)

PORT='/dev/ttyACM0'
PORT='/dev/serial/by-id/usb-Arduino__www.arduino.cc__0043_557393238373515041C1-if00'
BAUD=115200
INIT_TIME=2


class MySerial:
    def __init__(self, PORT, BAUD):
        self.port = PORT
        self.baud = BAUD
        self.ser = self.serial_start()
        self.data = 0

    def serial_start(self):
        def start():
            try:
                ser = serial.Serial(self.port, self.baud, timeout=0.1)
                ser.writeTimeout = 1
                time.sleep(1)
            except serial.serialutil.SerialException as e:
                log.error("Can't start port: %s" % e)
                ser = None
            return ser
        try:
            self.ser.close()
        except:
            pass
        log.info("Starting serial port...")
        ser = start()
        while ser == None:
            time.sleep(5)
            ser = start()
        return ser
        

    def _write(self, msg):
        try:
#           log.debug('Writing to port %s bytes' % len(msg))
            self.ser.write(msg)
            time.sleep(0.1)
            self.data = self.data + len(msg)
        except serial.serialutil.SerialTimeoutException as e:
            log.error("Can't write to port: %s" % e)
            log.error("Bytes written: %s" % self.data)
            self.data = 0
            log.error("Restarting serial port...")
            self.ser = self.serial_start()
        except serial.serialutil.SerialException as e:
            log.error("Can't write to port: %s" % e)
            log.error("Bytes written: %s" % self.data)
            self.data = 0
            log.error("Restarting serial port...")
            self.ser = self.serial_start()
#       log.info("READ FROM SERIAL %s " % self.ser.readline())

    def write(self, array):
        self.ser.flushInput()
        self.ser.flushOutput()
        self._write(bytearray('\00','utf8'))
        self._write(array[:256])
        self._write(bytearray('\01','utf8'))
        self._write(array[256:512])
        self._write(bytearray('\02','utf8'))
        self._write(array[512:768])
        self._write(bytearray('\03','utf8'))
        self._write(array[768:])
    
    
ARDUINO = MySerial(PORT, BAUD)

counter = 0


while True:
#   ARDUINO.write(ram())
#   time.sleep(2)
    ARDUINO.write(japanese())
    time.sleep(10)
#   for i in range(50):
#       ARDUINO.write(cpu())
#   time.sleep(1)
