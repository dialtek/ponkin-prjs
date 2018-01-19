#!/usr/bin/python
# -*- coding: utf-8 -*-
#ADC121C021 I2C addres with ADR0, ADR1 connected to GND = 0x55 

import time
import smbus

adc_addr = 0x55      #ADC121C021 I2C addres
conv_result = 0x00
config_reg  = 0x02
adc_ref  = 3.287

class i2c_adc():
	try:
		i2c = smbus.SMBus(1) #RPi i2c device = i2c-1 
	except Exception:
		print 'i2c device not found'
		
		
	def init(self):
		try:
			self.i2c.write_byte_data(adc_addr,config_reg,0x00) #0xCC
		except Exception:
			print 'i2c device writing error'
		#ADC convert freq = 0.9 ksps
		#alert pin enable, alert active LOW
		time.sleep(0.1)

	def get_conv_result(self):
		try:
			read_data = self.i2c.read_word_data(adc_addr,conv_result)
			# i2c.read_word_data returns LSB first, MSB - second !!!
			low_byte = read_data & 0xff00
			low_byte = read_data>>8
			up_byte = read_data & 0x00ff
			read_data = (up_byte<<8) | low_byte
			read_data = read_data & 0x0fff #upper bits clearing..
		except Exception:
			print 'i2c device reaing error'
			read_data = 0
		return read_data

	def read_config_reg(self):
		return self.i2c.read_byte_data(adc_addr, config_reg)
		
	def get_voltage(self):
		adc_rd_count = self.get_conv_result()
		Vout = (adc_rd_count * adc_ref)/4096
		return Vout
