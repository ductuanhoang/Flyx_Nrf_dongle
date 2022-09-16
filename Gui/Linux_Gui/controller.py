# from ble_class import user_ble

import sys
import time
import logging
import threading
from serial_process import serial_process

from PyQt5.QtWidgets import (
    QApplication, QDialog, QMainWindow, QMessageBox, QPinchGesture, QPushButton
)

from PyQt5.QtCore import (Qt, pyqtSignal)

from PyQt5.uic import loadUi

from main_window_ui import Ui_MainWindow


class Window(QMainWindow, Ui_MainWindow):
    def connectButtonPressed(self):
        if self.connectButton.isChecked():
            self.connectButton.setText("BLE Disconnect")
            self.rpmTextEdit.clear()
            self.pressuareTextEdit.clear()
            self.knockTextEdit.clear()
            self.voltplainTextEdit.clear()
            self.serial_process.stop()
            self.debug_text_log("disconnect BLE device")

        else:
            self.connectButton.setText("BLE Connecting")
            self.debugTextEdit.clear()
            # self.ble.user_ble_connection()
            self.serial_process.start()
            self._running = 1
            self.debug_text_log("connecting BLE device")


    def bleConnectionSignal(self):
        self.connectButton.setText("BLE Connected")

    def bleDisconnectionSignal(self):
        self.connectButton.setText("BLE Disconnect")
        self.connectButton.setChecked(0)
        self.rpmTextEdit.clear()
        self.pressuareTextEdit.clear()
        self.knockTextEdit.clear()
        self.voltplainTextEdit.clear()

    def clearLogButton(self):
        self.debugTextEdit.clear()

    def __init__(self, parent=None):
        super().__init__(parent)
        self.setupUi(self)
        self.serial_process = serial_process(com_port='/dev/ttyUSB0')
        self.connectButton.pressed.connect(self.connectButtonPressed)
        self.clearButton.pressed.connect(self.clearLogButton)

        self.serial_process.message_data_update.connect(self.new_value_update)
        self.serial_process.debug_text_log_update.connect(self.debug_text_log)

    def findAndReplace(self):
        dialog = FindReplaceDialog(self)
        dialog.exec()

    def about(self):
        QMessageBox.about(
            self,
            "About Sample Editor",
            "<p>A sample text editor app built with:</p>"
            "<p>- PyQt</p>"
            "<p>- Qt Designer</p>"
            "<p>- Python</p>",
        )

    def new_value_update(self, v_bat, knock, pressuare, rpm):
        print("new_value_update")
        ummed = int(rpm)
        self.rpmTextEdit.setPlainText(str(ummed) + " rpm")
        ummed = float(pressuare)
        self.pressuareTextEdit.setPlainText(str(ummed) + ' mBar')
        ummed = float(knock)
        self.knockTextEdit.setPlainText(str(ummed) + ' %')
        ummed = int(v_bat)
        self.voltplainTextEdit.setPlainText(str(ummed) + ' mV')

    def debug_text_log(self, text_log):
        self.debugTextEdit.setPlainText(text_log)
    def closeEvent(self, event):
        if(self._running == 1):
            self.serial_process.stop()
        print("closeEvent")

class FindReplaceDialog(QDialog, serial_process):
    def __init__(self, parent=None):
        super().__init__(parent)
        loadUi("controller.ui", self)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = Window()
    win.show()

    logging.basicConfig(format=format, level=logging.INFO,
                        datefmt="%H:%M:%S")
    logging.info("Main    : all done")
    sys.exit(app.exec())
