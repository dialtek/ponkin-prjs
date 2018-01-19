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
from PyQt4.QtCore import QTimer

class MainWindow(QMainWindow,mainform.Ui_MainWindow):

    def __init__(self, parent=None):
        QMainWindow.__init__(self, parent)
        self.ui = mainform.Ui_MainWindow()
        self.ui.setupUi(self)

    def __del__(self):
        self.ui = None

    def tick(self):
        h_speed = w.ui.h_speed.value()
        v_speed = w.ui.v_speed.value()
        v_speed_s = w.ui.v_speed_s.value()
##--------------------------------------------------------
        # right
        if (w.ui.Right_b.isDown()):
            GPIO.output(27, False)  # dir R
            GPIO.output(22, False)  # enable the motor 1
            GPIO.output(17, True)
            time.sleep(h_speed / 1000.0)
            GPIO.output(17, False)
            time.sleep(h_speed / 1000.0)
            GPIO.output(22, True)   # disable the motor 1
##--------------------------------------------------------
        # left
        if (w.ui.Left_b.isDown()):
            GPIO.output(27, True)   # dir L
            GPIO.output(22, False)  # enable the motor 1
            GPIO.output(17, True)
            time.sleep(h_speed / 1000.0)
            GPIO.output(17, False)
            time.sleep(h_speed / 1000.0)
            GPIO.output(22, True)  # disable the motor 1
##--------------------------------------------------------
        # up
        if (w.ui.Up_b.isDown()):
            GPIO.output(15, True)   # dir UP
            GPIO.output(18, False)  # enable the motor 2
            GPIO.output(14, True)
            time.sleep(v_speed/1000.0)
            GPIO.output(14, False)
            time.sleep(v_speed/1000.0)
            GPIO.output(18, True)   # disable the motor 2
##--------------------------------------------------------
        # down
        if (w.ui.Down_b.isDown()):
            GPIO.output(15, False)  # dir DOWN
            GPIO.output(18, False)  # enable the motor 2
            GPIO.output(14, True)
            time.sleep(v_speed / 1000.0)
            GPIO.output(14, False)
            time.sleep(v_speed / 1000.0)
            GPIO.output(18, True)   # disable the motor 2
##--------------------------------------------------------
        # up шприц
        if (w.ui.Up_bs.isDown()):
            GPIO.output(3, True)    # dir UPs
            GPIO.output(4, False)   # enable the motor 3
            GPIO.output(2, True)
            time.sleep(v_speed_s / 1000.0)
            GPIO.output(2, False)
            time.sleep(v_speed_s / 1000.0)
            GPIO.output(4, True)    # disable the motor 3
##--------------------------------------------------------
        # down шприц
        if (w.ui.Down_bs.isDown()):
            GPIO.output(3, False)  # dir DOWNs
            GPIO.output(4, False)  # enable the motor 3
            GPIO.output(2, True)
            time.sleep(v_speed_s / 1000.0)
            GPIO.output(2, False)
            time.sleep(v_speed_s / 1000.0)
            GPIO.output(4, True)   # disable the motor 3
#-----------------------------------------------------#
if __name__ == '__main__':
    # create application
    app = QApplication(sys.argv)
    app.setApplicationName('PyCharm_prj')

    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BCM)
    # -----------------------------------------------------#
    # horizontal motors капилляр
    GPIO.setup(17, GPIO.OUT)  # step
    GPIO.setup(27, GPIO.OUT)  # dir
    GPIO.setup(22, GPIO.OUT)  # en
    # -----------------------------------------------------#
    # vertical motors капилляр
    GPIO.setup(14, GPIO.OUT)  # step
    GPIO.setup(15, GPIO.OUT)  # dir 2
    GPIO.setup(18, GPIO.OUT)  # en 2
    # -----------------------------------------------------#
    # motors шприц
    GPIO.setup(2, GPIO.OUT)   # step 3
    GPIO.setup(3, GPIO.OUT)   # dir 3
    GPIO.setup(4, GPIO.OUT)   # en 3
    # -----------------------------------------------------#
    # create widget
    w = MainWindow()
    w.setWindowTitle('Step motor test control')
    w.setFixedSize(425, 400)

    w.ui.r_step.setVisible(False)
    w.ui.l_step.setVisible(False)
    w.ui.u_step.setVisible(False)
    w.ui.d_step.setVisible(False)

    #GPIO.output(22, False)  # enable the motor 1
    #GPIO.output(18, False)  # enable the motor 2

    timer = QTimer()
    timer.timeout.connect(w.tick)
    timer.start(1)

    #
    # settings = QSettings('settings.ini', QSettings.IniFormat)
    # settings.setFallbacksEnabled(False)  # File only, no fallback to registry or or.
    # try:
    #     w.ui.r_step.setValue(settings.value('r_step', 123))
    # except Exception:
    #     w.ui.statusbox.setText("No file to load")


    #settings.setValue("data")

    w.show()
    # connection
    QObject.connect(app, SIGNAL('lastWindowClosed()'), app, SLOT('quit()'))
    # execute application
    sys.exit(app.exec_())
