#!/usr/bin/python
# -*- coding: utf-8 -*-
import RPi.GPIO as GPIO
import time

#var count = 0
GPIO.setmode(GPIO.BCM)
GPIO.setup(4, GPIO.OUT)
while True:
    GPIO.output(4, False)
    time.sleep(100)
    GPIO.output(4, True)
    time.sleep(100)