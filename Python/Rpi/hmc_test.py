#HMC5883L I2C 0x1E                                                                                                      
#!/usr/bin/python
# -*- coding: utf-8 -*-

import RPi.GPIO as GPIO
import time
import smbus
import os
import ctypes 

Sum = 0

class Accel():

	b = smbus.SMBus(1)
	
	def Calib(self):
		self.b.write_byte_data(0x1E,0x00,0x18)
		self.b.write_byte_data(0x1E,0x01,0xE0)
		self.b.write_byte_data(0x1E,0x02,0x00)
		time.sleep(0.001)

	def get_X_data(self):
		Xh = self.b.read_byte_data(0x1E,0x03)
		Xl = self.b.read_byte_data(0x1E,0x04)
		Sum = (Xh<<8)|Xl
		return Sum * 0.0039550781252
	
	def get_status(self):
		return self.b.read_byte_data(0x1E,0x09)
	
	def clear_status(self):
		return self.b.write_byte_data(0x1E,0x09,0x00)
		
	# def get_Y_data(self):
		# Yh = self.b.read_byte_data(0x1E,0x05)
		# Yl = self.b.read_byte_data(0x1E,0x06)
		# SumY = (Yh<<8)|Yl
		# return SumY * 0.0039550781252
		
	# def get_Z_data(self):
		# Zh = self.b.read_byte_data(0x1E,0x07)
		# Zl = self.b.read_byte_data(0x1E,0x08)
		# SumZ = (Zh<<8)|Zl
		# return SumZ * 0.0039550781252

HMC5883L = Accel()

#GPIO.setmode(GPIO.BCM)
#GPIO.setup(24,GPIO.IN) 

while True:

	try:
	#while GPIO.input(24) == False:
		HMC5883L.Calib()
		time.sleep(0.001)
	
		DRDY = HMC5883L.get_status()
	
		if (DRDY & 1) == True:
			print 'X = ',HMC5883L.get_X_data()
			HMC5883L.clear_status()
	except Exception:
		print 'Reading error, please check sensor connection...'
		time.sleep(0.4)
		
	time.sleep(0.07)