#!/usr/bin/python
# -*- coding: utf-8 -*-
#ADC121C021 I2C addres with ADR0, ADR1 connected to GND = 0x55 

import RPi.GPIO as GPIO
import time
import smbus
import os
import ADC121C021 as IC

def calc_current(adc_v):
	MAX9923_Av = 400
	R_sense = 1000
	I = adc_v/(MAX9923_Av * R_sense)
	return I

ADC121C021 = IC.i2c_adc()
ADC121C021.init()

GPIO.setmode(GPIO.BCM) #RPi init
GPIO.setup(4,GPIO.OUT) #RPi GPIO4 pin - status led

while True:

		adc_Vout = ADC121C021.get_voltage()
		I_meas = calc_current(adc_Vout)
		print 'Vout = ', "%0.3f" % adc_Vout
		print 'Iout = ', "%0.3e" % I_meas
		print ''
		
		GPIO.output(4, True)
		time.sleep(0.1)
		GPIO.output(4, False)
		time.sleep(0.9)