# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'controller.ui'
#
# Created by: PyQt5 UI code generator 5.10.1
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.setEnabled(True)
        MainWindow.resize(681, 500)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.debugTextEdit = QtWidgets.QPlainTextEdit(self.centralwidget)
        self.debugTextEdit.setGeometry(QtCore.QRect(10, 270, 651, 171))
        self.debugTextEdit.setAutoFillBackground(True)
        self.debugTextEdit.setObjectName("debugTextEdit")
        self.connectButton = QtWidgets.QPushButton(self.centralwidget)
        self.connectButton.setGeometry(QtCore.QRect(10, 10, 141, 41))
        self.connectButton.setAutoFillBackground(True)
        self.connectButton.setCheckable(True)
        self.connectButton.setChecked(False)
        self.connectButton.setAutoRepeat(False)
        self.connectButton.setObjectName("connectButton")
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(10, 250, 109, 17))
        self.label.setAutoFillBackground(True)
        self.label.setObjectName("label")
        self.label_2 = QtWidgets.QLabel(self.centralwidget)
        self.label_2.setGeometry(QtCore.QRect(10, 60, 91, 41))
        self.label_2.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.label_2.setAutoFillBackground(True)
        self.label_2.setObjectName("label_2")
        self.clearButton = QtWidgets.QPushButton(self.centralwidget)
        self.clearButton.setGeometry(QtCore.QRect(580, 240, 80, 25))
        self.clearButton.setAutoFillBackground(True)
        self.clearButton.setObjectName("clearButton")
        self.label_3 = QtWidgets.QLabel(self.centralwidget)
        self.label_3.setGeometry(QtCore.QRect(40, 100, 91, 41))
        self.label_3.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.label_3.setAutoFillBackground(True)
        self.label_3.setObjectName("label_3")
        self.label_4 = QtWidgets.QLabel(self.centralwidget)
        self.label_4.setGeometry(QtCore.QRect(190, 100, 131, 41))
        self.label_4.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.label_4.setAutoFillBackground(True)
        self.label_4.setObjectName("label_4")
        self.label_5 = QtWidgets.QLabel(self.centralwidget)
        self.label_5.setGeometry(QtCore.QRect(370, 100, 111, 41))
        self.label_5.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.label_5.setAutoFillBackground(True)
        self.label_5.setObjectName("label_5")
        self.label_6 = QtWidgets.QLabel(self.centralwidget)
        self.label_6.setGeometry(QtCore.QRect(530, 100, 111, 41))
        self.label_6.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.label_6.setAutoFillBackground(True)
        self.label_6.setObjectName("label_6")
        self.rpmTextEdit = QtWidgets.QPlainTextEdit(self.centralwidget)
        self.rpmTextEdit.setEnabled(True)
        self.rpmTextEdit.setGeometry(QtCore.QRect(20, 140, 141, 41))
        self.rpmTextEdit.setUndoRedoEnabled(True)
        self.rpmTextEdit.setObjectName("rpmTextEdit")
        self.pressuareTextEdit = QtWidgets.QPlainTextEdit(self.centralwidget)
        self.pressuareTextEdit.setGeometry(QtCore.QRect(180, 140, 141, 41))
        self.pressuareTextEdit.setObjectName("pressuareTextEdit")
        self.knockTextEdit = QtWidgets.QPlainTextEdit(self.centralwidget)
        self.knockTextEdit.setGeometry(QtCore.QRect(340, 140, 141, 41))
        self.knockTextEdit.setObjectName("knockTextEdit")
        self.voltplainTextEdit = QtWidgets.QPlainTextEdit(self.centralwidget)
        self.voltplainTextEdit.setGeometry(QtCore.QRect(510, 140, 141, 41))
        self.voltplainTextEdit.setObjectName("voltplainTextEdit")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 681, 22))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.toolBar = QtWidgets.QToolBar(MainWindow)
        self.toolBar.setObjectName("toolBar")
        MainWindow.addToolBar(QtCore.Qt.TopToolBarArea, self.toolBar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.connectButton.setText(_translate("MainWindow", "BLE Disconnect"))
        self.label.setText(_translate("MainWindow", "Debug message"))
        self.label_2.setText(_translate("MainWindow", "Sensor value"))
        self.clearButton.setText(_translate("MainWindow", "Clear Log"))
        self.label_3.setText(_translate("MainWindow", "RPM sensor"))
        self.label_4.setText(_translate("MainWindow", "Pressuare sensor"))
        self.label_5.setText(_translate("MainWindow", "knock sensor"))
        self.label_6.setText(_translate("MainWindow", "Batterry Volt "))
        self.toolBar.setWindowTitle(_translate("MainWindow", "toolBar"))

