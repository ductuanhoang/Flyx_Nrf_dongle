import serial
import threading
import struct
import sys
import os
import time
import string
import logging
import queue

# from xmodem import XMODEM
from PyQt5.QtCore import pyqtSignal, QObject

def checksum(data, state=0xef):
    for b in data:
        if type(b) is int:  # python 2/3 compat
            state ^= b
        else:
            state ^= ord(b)

    return state

def decode(port, running_flag, log_fn):
    partial_packet = None
    waiting_header = 0
    packet_len = 0
    len_counter = 0
    while True and running_flag is True:
        waiting = port.inWaiting()
        read_bytes = port.read(1 if waiting == 0 else waiting)
        # print("data = %x", read_bytes[0])
        if read_bytes == b'':
            log_fn.error("Timeout packet")
            yield None
            # return

        for b in read_bytes:
            if type(b) is int:
                b = bytes([b])  # python 2/3 compat
            if waiting_header == 0:
                if b == b'\xaa':
                    waiting_header = 1
            elif waiting_header == 1:
                if b == b'\x55':
                    waiting_header = 2
                    partial_packet = b""
                else:
                    waiting_header = 0
            elif waiting_header == 2: # rec length
                partial_packet += b
                packet_len = int(b[0])
                print("packet_len = ", packet_len)
                waiting_header = 3
            elif waiting_header == 3: # rec data
                partial_packet += b
                len_counter += 1
                if len_counter == packet_len:
                    waiting_header = 4
            elif waiting_header == 4:
                # if checksum(partial_packet) == int(b[0]):
                if True:
                    # log_fn.info("True checksum")
                    yield partial_packet
                else:
                    log_fn.error("Wrong checksum")
                partial_packet = None
                len_counter = 0
                packet_len = 0
                waiting_header = 0

class serial_process(QObject):
    sending_queue = queue.Queue(maxsize=32)
    disconnected_signal = pyqtSignal()
    connected_signal = pyqtSignal()
    sensor_data_update = pyqtSignal(int, int, int, int, int, int, int, int, int, int, int)
    rfid_data_update = pyqtSignal(str, str)
    version_data_update = pyqtSignal(str, str)
    control_status_data_update = pyqtSignal(int, int, int)
    error_signal = pyqtSignal(str)
    config_data_update = pyqtSignal(int, int, int, int, int, int, int, int, int)
    calib_data_update = pyqtSignal(int, int, int)
    change_tank_waitime = pyqtSignal(int)
    fw_process = pyqtSignal(int)
    fw_update_status = pyqtSignal(int)
    message_data_update = pyqtSignal(int, int, int, int)
    debug_text_log_update = pyqtSignal(str)
    """Handle data from COM port"""
    def __init__(self, com_port='COM4', logger = None):
        print("serial com", com_port)
        super().__init__()
        self._port = com_port
        self._running = False
        self._serial = None
        if logger is None:
            self._logger=logging.getLogger()
        else:
            self._logger = logger
        self._is_connected = False
        self._control_status = 99
        self._error_code = 0
        self._active_tank = -1
        self._work_mode = 0 # 0 normal 1 upload fw
        self._fw_file_size = 0
        # self.start()

    def __del__(self):
        self.stop()

    def set_work_mode(self, mode):
        self._work_mode = mode

    def write(self, cmd_arr):
        if self._serial is None or not self._running:
            return

        if self._work_mode != 0:
            return

        buf =  struct.pack(b'B', len(cmd_arr)) + cmd_arr
        self._serial.write(b'\xaa\x55' + buf + struct.pack(b'B', checksum(buf)))

    def read(self):
        return next(self._protolcol_decode)

    def start_machine(self):
        if not self._running or self._serial == None:
            return
        self.sending_queue.put(b'\x01\x01') # start

    def start_cycle(self):
        if not self._running or self._serial == None:
            return
        self.sending_queue.put(b'\x01\x04') # start

    def stop_cycle(self):
        if not self._running or self._serial == None:
            return
        self.sending_queue.put(b'\x01\x05') # start

    def start_machine_without_wait(self):
        if not self._running or self._serial == None:
            return
        self.sending_queue.put(b'\x01\x03') # start without wait

    def stop_machine(self):
        if not self._running or self._serial == None:
            return
        self.sending_queue.put(b'\x01\x02') # stop

    def turn_off_machine(self):
        if not self._running or self._serial == None:
            return
        self.sending_queue.put(b'\x01\x07') # turn off
        self.sending_queue.put(b'\x01\x07') # turn off
        self.sending_queue.put(b'\x01\x07') # turn off
        self.sending_queue.put(b'\x01\x07') # turn off

    def reset_board(self):
        if not self._running or self._serial == None:
            return
        self.sending_queue.put(b'\x01\x06') # reset board

    def air_test(self):
        if not self._running or self._serial == None:
            return
        self.sending_queue.put(b'\x01\x08') # air test

    def write_all_config(self, tube_stuck_high, tube_stuck_norm, tube_stuck_low
                        , bat_volt_warn, bat_volt_err, tx_probe_temp_warn, tx_probe_temp_err
                        , env_temp, turnoff_tank_pressure_threshold):
        if not self._running or self._serial == None:
            return
        buf = b'\x08\x01' + struct.pack(b'<HHHHHHHHH', tube_stuck_high, tube_stuck_norm, tube_stuck_low
                        , bat_volt_warn, bat_volt_err, tx_probe_temp_warn, tx_probe_temp_err
                        , env_temp, turnoff_tank_pressure_threshold)
        self.sending_queue.put(buf) # write all config

    def mark_tank_is_verified(self, tank_num, status):
        if not self._running or self._serial == None:
            return

        print('mark_tank_is_verified', tank_num, status)

        buf = b'\x07'

        if tank_num == 1:
            buf += b'\x01'
        else:
            buf += b'\x02'

        if status != 0:
            buf += b'\x01'
        else:
            buf += b'\x00'

        self.sending_queue.put(buf)

    def read_all_config(self):
        if not self._running or self._serial == None:
            return
        self.sending_queue.put(b'\x08\x00') # read all config

    def read_calib_data(self):
        if not self._running or self._serial == None:
            return
        self.sending_queue.put(b'\x09\x00') # read all config

    def write_calib_data(self, vin_12v, v12v_tp101, v5v_tp111):
        if not self._running or self._serial == None:
            return
        buf = b'\x09\x01' + struct.pack(b'<III', vin_12v, v12v_tp101, v5v_tp111)
        self.sending_queue.put(buf)

    def read_change_tank_time(self):
        if not self._running or self._serial == None:
            return
        self.sending_queue.put(b'\x0a\x00') # read change time

    def write_change_tank_time(self, time_change):
        if not self._running or self._serial == None:
            return
        buf = b'\x0a\x01' + struct.pack(b'<I', time_change)
        self.sending_queue.put(buf) # write change time

    def _getc(self, size, timeout=3):
        return self._serial.read(size)
    def _putc(self, data, timeout=3):
        self._serial.write(data)

    def set_fw_file(self, file_path):
        pass

    def update_board_fw(self):
        if not self._running or self._serial == None:
            return
        self.sending_queue.put(b'\x05\x01') # update_board_fw
        self.sending_queue.put(b'\x05\x01')

    def _xmode_callback(self, total_packets, success_count, error_count):
        if self._fw_file_size == 0:
            percent = 0
        else:
            percent = success_count * 128 * 100 / self._fw_file_size
        self.fw_process.emit(percent)

    def _run(self):
        # create serial
        self._serial = serial.Serial(port = self._port,
                                baudrate=115200,
                                bytesize=serial.EIGHTBITS,
                                # timeout=0.1,
                                timeout=1,
                                stopbits=serial.STOPBITS_ONE,
                                parity=serial.PARITY_NONE)
        send_count = 0


        if self._work_mode == 0:
            self._protolcol_decode = decode(self._serial, self._running, self._logger)

            self.sending_queue.put(b'\x01\x06') # reset board
            self.sending_queue.put(b'\x06\x00') # read version

        # while loop
        while self._running or self.sending_queue.empty() is False:
            if self._work_mode == 0:
                try:
                    tmp_cmd_arr = b""
                    if self.sending_queue.empty():
                        self.sending_queue.put(b'\x02\x00') # read all sensor value
                        self.sending_queue.put(b'\x03\x00') # read all rfid tags
                        self.sending_queue.put(b'\x01\x00') # read all control status

                    tmp_cmd_arr = self.sending_queue.get()

                    self.write(tmp_cmd_arr)

                    # if tmp_cmd_arr == b'\x01\x06':
                    #     time.sleep(300)

                    if send_count < 10:
                        send_count += 1

                    read_val = self.read()
                    if read_val != None:
                        send_count = 0
                        if self._is_connected == False:
                            self._logger.debug("Connected")
                            self._is_connected = True
                            self.connected_signal.emit()

                        print("command = ", read_val[0])
                        print("command = ", read_val[1])
                        print("command = ", read_val[2])
                        print("command = ", read_val[3])
                        print("command = ", read_val[4])
                        print("command = ", read_val[5])
                        print("command = ", read_val[6])
                        print("command = ", read_val[7])
                        print("command = ", read_val[8])
                        print("command = ", read_val[9])
                        print("command = ", read_val[10])

                        buffer_vbat = read_val[2] << 8 | read_val[3]
                        buffer_knock = read_val[4] << 8 | read_val[5]
                        buffer_pressuare = read_val[6] << 8 | read_val[7]
                        buffer_rpm = read_val[8] << 16 | read_val[9] << 8 | read_val[10]

                        print("v_bat: ", buffer_vbat)
                        print("knock: ", buffer_knock)
                        print("press: ", buffer_pressuare)
                        print("rpm: ", buffer_rpm)
                        self.message_data_update.emit(buffer_vbat, buffer_knock,
                                              buffer_pressuare, buffer_rpm)
                    else:
                        self._logger.debug(read_val)

                    time.sleep(0.05)

                    if send_count == 10: # lost over 10 msgs (~1 sec), notify lost connection
                        send_count = 100 # Make sure emit one time signal
                        self._logger.debug("Lost connection")
                        self._is_connected = False
                        self.disconnected_signal.emit()
                        # self._logger.info
                except Exception as e:
                    self._logger.error(self._running)
                    self._logger.error(str(e))
                    time.sleep(1)
            else:
                self._logger.info("In _work_mode 0")
                time.sleep(1)

        if self._serial.out_waiting > 0:
            self._logger.info("Flush out_waiting data")
            self._serial.flush()

        self._serial.close()
        self._serial = None
        self._logger.debug("Exit thread serial_process")

    def start(self):
        if self._running:
            return

        self._running = True
        self._thread = threading.Thread(target = self._run)
        self._thread.start()

    def stop(self):
        if not self._running:
            return
        self._logger.debug("Stop func is calling")
        self._running = False
        self._thread.join()

# Only for test
if __name__ == '__main__':
    logging.basicConfig(level=logging.DEBUG)
    try:
        protocol_obj = serial_process(com_port='/dev/ttyUSB0')
        while True:
            pass

    except KeyboardInterrupt as e:
        protocol_obj.stop()
        print("Ok ok, quitting")
        sys.exit(1)

