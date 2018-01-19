#import RPi.GPIO as GPIO
import time
import serial

port = serial.Serial("/dev/ttyAMA0", baudrate=115200, timeout=1.0)
#var count = 0
#GPIO.setmode(GPIO.BCM)
#GPIO.setup(25, GPIO.OUT)
while True:
    #GPIO.output(25, False)
    port.write("hello from Rpi\r\n");
    time.sleep(1000)