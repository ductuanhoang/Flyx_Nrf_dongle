from ble_class import user_ble
import sys
import time
import logging
import threading

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
            self.ble.user_ble_disconnection()

        else:
            self.connectButton.setText("BLE Connecting")
            self.debugTextEdit.clear()
            # self.new_value_update()
            self.ble.user_ble_connection()

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
        self.ble = user_ble(0, 0, 1, 0)
        self.ble.sensor_data_update.connect(self.new_value_update)
        self.ble.debug_text_log_update.connect(self.debug_text_log)
        self.ble.signal_ble_connected.connect(self.bleConnectionSignal)
        self.ble.signal_ble_disconnected.connect(self.bleDisconnectionSignal)
        # self.ble.sensor_data_update.emit()
        # self.connectSignalsSlots()
        self.connectButton.pressed.connect(self.connectButtonPressed)
        self.clearButton.pressed.connect(self.clearLogButton)

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


class FindReplaceDialog(QDialog, user_ble):
    def __init__(self, parent=None):
        super().__init__(parent)
        loadUi("controller.ui", self)


def thread_function(name):
    logging.info("Thread %s: starting", name)
    time.sleep(2)
    logging.info("Thread %s: finishing", name)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = Window()
    win.show()

    logging.basicConfig(format=format, level=logging.INFO,
                        datefmt="%H:%M:%S")

    # logging.info("Main    : before creating thread")
    # x = threading.Thread(target=thread_function, args=(1,))
    # logging.info("Main    : before running thread")
    # x.start()
    # logging.info("Main    : wait for the thread to finish")
    # # x.join()
    logging.info("Main    : all done")
    sys.exit(app.exec())
