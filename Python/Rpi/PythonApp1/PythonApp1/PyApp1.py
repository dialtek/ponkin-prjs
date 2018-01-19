import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BOARD)
GPIO.setup(25, GPIO.OUT)
while True:
    GPIO.output(25, True)
    time.sleep(1000)
    GPIO.output(25, False)
    time.sleep(1000)