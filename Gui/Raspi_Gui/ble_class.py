from main_window_ui import Ui_MainWindow
import sys
import struct
import array as arr
import threading
#  add new for bluepy lib
from PyQt5.QtCore import pyqtSignal, QObject
from bluepy import btle
from bluepy.btle import Scanner, DefaultDelegate
import time

# Notification BLE message


class MyDelegate(QObject, btle.DefaultDelegate):
    message_data_update = pyqtSignal(int, int, int, int)
    message_text_update = pyqtSignal(str)

    def __init__(self):
        super().__init__()
        btle.DefaultDelegate.__init__(self)
        self.buffer_vbat = 0
        self.buffer_knock = 0
        self.buffer_pressuare = 0
        self.buffer_rpm = 0

    def handleNotification(self, cHandle, data):
        print("A notification was received: %x", (data))
        self.read_data = data
        self.id_message_parser(self.read_data)
        self.message_text_update.emit("data recive :  " + str(self.read_data))

    def id_message_parser(self, data):
        if data[0] == 0xAA:
            if data[1] == 0x55:
                print("true message")
                self.buffer_vbat = data[4] << 8 | data[5]
                self.buffer_knock = data[6] << 8 | data[7]
                self.buffer_pressuare = data[8] << 8 | data[9]
                self.buffer_rpm = data[10] << 16 | data[11] << 8 | data[12]
                self.message_data_update.emit(self.buffer_vbat, self.buffer_knock,
                                              self.buffer_pressuare, self.buffer_rpm)
        else:
            print("false message")


class user_ble(MyDelegate):
    sensor_data_update = pyqtSignal(int, int, int, int)
    debug_text_log_update = pyqtSignal(str)
    signal_ble_connected = pyqtSignal()
    signal_ble_disconnected = pyqtSignal()

    def __init__(self, rpm=0, pressuare=0, knock=0, volt=0):
        super().__init__()
        self._running = False
        self._connected = False
        self.ble_connect_id = None
        self.sensor_rpm = rpm
        self.sensor_pressuare = pressuare
        self.sensor_knock = knock
        self.sensor_volt = volt
        self._address = None
        print("user_ble create")
        self.my_delegate = MyDelegate()
        self.my_delegate.message_data_update.connect(self.message_parser)
        self.my_delegate.message_text_update.connect(self.message_logger)

    def user_ble_connection(self):
        if self._running == True:
            return
        print("user_ble_connecting")
        self._running = True
        self._thread = threading.Thread(target=self._ble_scaner)
        self._thread.start()

    def user_ble_disconnection(self):
        if not self._running:
            return
        self._running = False
        print("user_ble_disconnection")
        # if self._connected == True:
        self.ble_connect_id.Peripheral(self._address).disconnect()
        self._connected = False
        self._address = None
        self._thread.join()

    def user_ble_scan(self):
        print("user_ble_scan")

    def message_logger(self, message):
        self.debug_text_log_update.emit(message)
        print("message_logger")

    def message_parser(self, v_bat, knock, pressuare, rpm):
        self.sensor_data_update.emit(v_bat, knock, pressuare, rpm)

    def _ble_scaner(self):
        print('Scanning...')
        scanner = Scanner().withDelegate(ScanDelegate())
        devices = scanner.scan(10.0)

        for dev in devices:
            print("Device %s (%s), RSSI=%d dB" %
                  (dev.addr, dev.addrType, dev.rssi))
            for (adtype, desc, value) in dev.getScanData():
                print("  %s = %s" % (desc, value))
                if desc == 'Complete Local Name' and value == 'Feasycom':
                    self._address = dev.addr
                    self._connected = True
        if self._connected:
            print("Connecting...")
            self.debug_text_log_update.emit(
                "BLE connected: " + str(self._address))
            self.signal_ble_connected.emit()  # send signal to graphic
            
            # address = "YOUR_FIX_DEVICE_MAC"

            ble_connect_id = btle.Peripheral(
                self._address, btle.ADDR_TYPE_RANDOM)
            ble_connect_id.setDelegate(self.my_delegate)
            # Setup to turn notifications on, e.g.
            # svc = ble_connect_id.getServiceByUUID(0x180F)
            svc = ble_connect_id.getServiceByUUID(0xFFF0)

            ch = svc.getCharacteristics()[1]
            print(ch.valHandle)
            setup_data = b"\x01\x00"
            # ch.write(setup_data)
            ble_connect_id.writeCharacteristic(ch.valHandle + 1, setup_data)

            ch_data = ble_connect_id.readCharacteristic(ch.valHandle + 1)
            print(type(ch_data))
            print(ch_data)

            print("=== Main Loop ===")
            while True:
                try:
                    if ble_connect_id.waitForNotifications(1.0):
                        # handleNotification() #was called
                        continue
                except btle.BTLEDisconnectError:
                    self.signal_ble_disconnected.emit()
                    self.user_ble_disconnection()
                    print("Waiting...")
                    pass
                # Perhaps do something else here
        else:
            print("Not found BLE server")
            self.signal_ble_disconnected.emit()
            self.debug_text_log_update.emit("Not found BLE server")
            self.user_ble_disconnection()
# BLE class
# Scan Delegate...


class ScanDelegate(DefaultDelegate):
    def __init__(self):
        DefaultDelegate.__init__(self)

    def handleDiscovery(self, dev, isNewDev, isNewData):
        if isNewDev:
            print("Discovered device", dev.addr)
        elif isNewData:
            print("Received new data from", dev.addr)
