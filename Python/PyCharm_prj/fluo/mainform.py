# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'Form1.ui'
#
# Created by: PyQt4 UI code generator 4.11.4
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName(_fromUtf8("MainWindow"))
        MainWindow.resize(800, 405)
        MainWindow.setWindowTitle(_fromUtf8(""))
        MainWindow.setLayoutDirection(QtCore.Qt.LeftToRight)
        MainWindow.setAutoFillBackground(False)
        self.centralwidget = QtGui.QWidget(MainWindow)
        self.centralwidget.setObjectName(_fromUtf8("centralwidget"))
        self.StartB = QtGui.QPushButton(self.centralwidget)
        self.StartB.setGeometry(QtCore.QRect(210, 310, 191, 61))
        font = QtGui.QFont()
        font.setPointSize(14)
        self.StartB.setFont(font)
        self.StartB.setObjectName(_fromUtf8("StartB"))
        self.progressBar = QtGui.QProgressBar(self.centralwidget)
        self.progressBar.setGeometry(QtCore.QRect(10, 380, 781, 23))
        self.progressBar.setMaximum(500)
        self.progressBar.setProperty("value", 0)
        self.progressBar.setTextVisible(False)
        self.progressBar.setObjectName(_fromUtf8("progressBar"))
        self.Pic1lb = QtGui.QLabel(self.centralwidget)
        self.Pic1lb.setGeometry(QtCore.QRect(170, 0, 300, 300))
        self.Pic1lb.setAutoFillBackground(True)
        self.Pic1lb.setText(_fromUtf8(""))
        self.Pic1lb.setObjectName(_fromUtf8("Pic1lb"))
        self.Pic2lb = QtGui.QLabel(self.centralwidget)
        self.Pic2lb.setGeometry(QtCore.QRect(490, 0, 300, 300))
        self.Pic2lb.setAutoFillBackground(True)
        self.Pic2lb.setText(_fromUtf8(""))
        self.Pic2lb.setObjectName(_fromUtf8("Pic2lb"))
        self.ExitB = QtGui.QPushButton(self.centralwidget)
        self.ExitB.setGeometry(QtCore.QRect(550, 310, 191, 61))
        font = QtGui.QFont()
        font.setPointSize(14)
        self.ExitB.setFont(font)
        self.ExitB.setObjectName(_fromUtf8("ExitB"))
        self.Log = QtGui.QTextEdit(self.centralwidget)
        self.Log.setGeometry(QtCore.QRect(10, 50, 141, 171))
        font = QtGui.QFont()
        font.setPointSize(8)
        self.Log.setFont(font)
        self.Log.setReadOnly(True)
        self.Log.setObjectName(_fromUtf8("Log"))
        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        QtCore.QObject.connect(self.StartB, QtCore.SIGNAL(_fromUtf8("pressed()")), MainWindow.slot1)
        QtCore.QObject.connect(self.ExitB, QtCore.SIGNAL(_fromUtf8("pressed()")), MainWindow.slot3)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        self.StartB.setText(_translate("MainWindow", "Провести тест", None))
        self.ExitB.setText(_translate("MainWindow", "Завершить тест", None))

