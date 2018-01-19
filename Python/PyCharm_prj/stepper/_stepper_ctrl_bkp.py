#!/usr/bin/env python
#!-*-coding:utf-8-*-
import sys
import mainform
import time
# import PyQt4 QtCore and QtGui modules
from PyQt4.QtCore import *
from PyQt4.QtGui import *
import RPi.GPIO as GPIO
import time
from time import gmtime, strftime
from PyQt4.QtCore import QTimer

class MainWindow(QMainWindow,mainform.Ui_MainWindow):

    def __init__(self, parent=None):
        QMainWindow.__init__(self, parent)
        self.ui = mainform.Ui_MainWindow()
        self.ui.setupUi(self)

    def __del__(self):
        self.ui = None

    def slot1(self):                # UP
        self.ui.progressBar.setValue(0)  # progressbar reset
        try:  # if NaN
            v_steps = int(w.ui.u_step.text())
            v_speed = int(w.ui.v_speed.text())
            self.ui.progressBar.setMaximum(v_steps-5)  # progressbar init
            w.ui.statusbox.setText("")
        except Exception:
            v_steps = 0
            v_speed = 0
            w.ui.statusbox.setText("Not a number!")
        GPIO.output(15, True)              # dir UP
        for i in range(0, v_steps):        # step pulses
            self.ui.progressBar.setValue(i)   # progressbar increment
            GPIO.output(14, True)
            time.sleep(v_speed/1000.0)
            GPIO.output(14, False)
            time.sleep(v_speed/1000.0)

    # # def slot2(self):
    #     value = self.progressBar.value() + 1
    #     self.progressBar.setValue(value)

    def slot3(self):              # DOWN
        self.ui.progressBar.setValue(0)  # progressbar reset
        try:  # if NaN
            v_steps = int(w.ui.d_step.text())
            v_speed = int(w.ui.v_speed.text())
            self.ui.progressBar.setMaximum(v_steps-5)  # progressbar init
            w.ui.statusbox.setText("")
        except Exception:
            v_steps = 0
            v_speed = 0
            w.ui.statusbox.setText("Not a number!")
        GPIO.output(15, False)              # dir DOWN
        for i in range(0, v_steps):        # step pulses
            self.ui.progressBar.setValue(i)   # progressbar increment
            GPIO.output(14, True)
            time.sleep(v_speed/1000.0)
            GPIO.output(14, False)
            time.sleep(v_speed/1000.0)

    def slot2(self):             # LEFT
        self.ui.progressBar.setValue(0)  # progressbar reset
        try:  # if NaN
            h_steps = int(w.ui.l_step.text())
            h_speed = int(w.ui.h_speed.text())
            self.ui.progressBar.setMaximum(h_steps-5)  # progressbar init
            w.ui.statusbox.setText("")
        except Exception:
            h_steps = 0
            h_speed = 0
            w.ui.statusbox.setText("Not a number!")
        GPIO.output(27, True)              # dir L
        for i in range(0, h_steps):        # step pulses
            self.ui.progressBar.setValue(i)   # progressbar increment
            GPIO.output(17, True)
            time.sleep(h_speed/1000.0)
            GPIO.output(17, False)
            time.sleep(h_speed/1000.0)

    def slot4(self):              # RIGHT
        # settings.setValue('r_step', w.ui.r_step.value())  # saving step size to file
        self.ui.progressBar.setValue(0)  # progressbar reset
        try:  # if NaN
            h_steps = w.ui.r_step.value()
            h_speed = w.ui.h_speed.value()
            self.ui.progressBar.setMaximum(h_steps-5)  # progressbar init
            w.ui.statusbox.setText("")
        except Exception:
            h_steps = 0
            h_speed = 0
            w.ui.statusbox.setText("Not a number!")
        GPIO.output(27, False)  # dir UP
        for i in range(0, h_steps):  # step pulses
            self.ui.progressBar.setValue(i)  # progressbar increment
            GPIO.output(17, True)
            time.sleep(h_speed / 1000.0)
            GPIO.output(17, False)
            time.sleep(h_speed / 1000.0)

    # def slot5(self):
    #     w.ui.time_label.setText(strftime("%Y-%m-%d %H:%M:%S", gmtime()))

#-----------------------------------------------------#
if __name__ == '__main__':
    # create application
    app = QApplication(sys.argv)
    app.setApplicationName('PyCharm_prj')

    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BCM)
    # -----------------------------------------------------#
    # horizontal motors
    GPIO.setup(17, GPIO.OUT)  # step
    GPIO.setup(27, GPIO.OUT)  # dir
    GPIO.setup(22, GPIO.OUT)  # en

    GPIO.output(22, False)  # enable the motor 1
    GPIO.output(27, True)   # dir 1
    # -----------------------------------------------------#
    # vertical motors
    GPIO.setup(14, GPIO.OUT)  # step
    GPIO.setup(15, GPIO.OUT)  # dir 2
    GPIO.setup(18, GPIO.OUT)  # en 2

    GPIO.output(18, False)  # enable the motor 2
    GPIO.output(15, True)   # dir 1.1
    # -----------------------------------------------------#

    # create widget
    w = MainWindow()
    w.setWindowTitle('Step motor test control')
    w.setFixedSize(300, 400)
    #
    # settings = QSettings('settings.ini', QSettings.IniFormat)
    # settings.setFallbacksEnabled(False)  # File only, no fallback to registry or or.
    # try:
    #     w.ui.r_step.setValue(settings.value('r_step', 123))
    # except Exception:
    #     w.ui.statusbox.setText("No file to load")


    #settings.setValue("data")
    # w.timer = QTimer()
    # w.timer.timeout.connect(slot5())
    # w.timer.start(1000)
    w.show()
    # connection
    QObject.connect(app, SIGNAL('lastWindowClosed()'), app, SLOT('quit()'))

    # execute application
    sys.exit(app.exec_())
