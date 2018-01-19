#!/usr/bin/env python
#!-*-coding:utf-8-*-
import sys
import mainform
import time
# import PyQt4 QtCore and QtGui modules
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
import time
import picamera
from time import gmtime, strftime

my_dpi=160 # Rpi 7'LCD dpi
size = 300, 300

class MainWindow(QMainWindow,mainform.Ui_MainWindow):

    def __init__(self, parent=None):
        QMainWindow.__init__(self, parent)
        self.ui = mainform.Ui_MainWindow()
        self.ui.setupUi(self)

    def __del__(self):
        self.ui = None

    def slot1(self):
        w.ui.Log.clear()
        w.ui.Log.append(strftime("%Y-%m-%d %H:%M:%S", gmtime()))
        w.ui.Log.append("Initialization")
        self.ui.progressBar.setValue(0)
        value = self.ui.progressBar.value() + 25
        self.ui.progressBar.setValue(value)
        #self.ui.label .setText('ok!')
        # -------------------------------------------------------------
        # capturing the image
        with picamera.PiCamera() as camera:
            camera.resolution = (2560, 1920)
            w.ui.Log.append("Getting image")
            # print(camera.resolution)
            #camera.start_preview()
            #time.sleep(0.2)
            camera.capture('image1.png')
            #camera.stop_preview()
        value = self.ui.progressBar.value() + 25
        w.ui.Log.append("Analysing...")
        self.ui.progressBar.setValue(value)
        # -------------------------------------------------------------
        # crop the image fragment
        im = Image.open('image1.png')  # '2_strips.jpg')
        width_l, height_l = im.size
        im2 = im.crop((850, 450, 1700, 1300))
        im2.thumbnail(size, Image.ANTIALIAS)
        im2.save('crop.png')
        width_s, height_s = im2.size
        pixmap1 = QPixmap('crop.png')
        self.ui.Pic1lb.setPixmap(pixmap1)
        value = self.ui.progressBar.value() + 25
        self.ui.progressBar.setValue(value)
        # -------------------------------------------------------------
        pix_data = []  # array to store Y pixel scan sum values
        noise_level = 0  # noise level
        # scanning the image
        for i in range(0, width_s):
            sum = 0
            value = self.ui.progressBar.value() + 1
            self.ui.progressBar.setValue(value)
            for j in range(0, height_s):
                sum += im2.getpixel((i, j))[0]
            pix_data.append(int(sum))  # -noise_level))
        y_pos = np.arange(len(pix_data))
        w.ui.Log.append("Operation complete")
        plt.rcParams['toolbar'] = 'None'
        # -------------------------------------------------------------
        # plotting scan result
        plt.figure(figsize=(400 / my_dpi, 400 / my_dpi), dpi=160)
        plt.bar(y_pos, pix_data)  # ,marker='o', ms = 10, alpha=1, color='b')
        plt.tick_params(
            axis='both',
            which='both',
            bottom='off', top='off',
            labelbottom='off',
            right='off',
            left='off',
            labelleft='off')
        # plt.ylabel('Summ pixel value')
        # plt.title('Strip intensity profile')
        plt.savefig('result.png', dpi=160)
        result_im = Image.open('result.png')
        result_im.thumbnail(size, Image.ANTIALIAS)
        pixmap2 = QPixmap('result.png')
        self.ui.progressBar.setValue(500)
        self.ui.Pic2lb.setPixmap(pixmap2)
        #plt.show()

    # # def slot2(self):
    #     value = self.progressBar.value() + 1
    #     self.progressBar.setValue(value)

    def slot3(self):
        self.close()


#-----------------------------------------------------#
if __name__ == '__main__':
    # create application
    app = QApplication(sys.argv)
    app.setApplicationName('PyCharm_prj')

    # create widget
    w = MainWindow()
    w.setWindowTitle('RIHD v0.1')
    w.setFixedSize(800, 405)
    w.show()
    w.ui.Log.clear()
    w.ui.Log.append(strftime("%Y-%m-%d %H:%M:%S", gmtime()))

    # timer = QTimer()
    # timer.timeout.connect(w.slot2)

    # connection
    QObject.connect(app, SIGNAL('lastWindowClosed()'), app, SLOT('quit()'))

    # execute application
    sys.exit(app.exec_())
