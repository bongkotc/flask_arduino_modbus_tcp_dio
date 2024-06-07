import logging
# from pymodbus.client.sync import ModbusSerialClient as ModbusClient
# from pymodbus.client.serial import ModbusSerialClient as ModbusClient
from pymodbus.exceptions import ModbusException
from pymodbus.client.tcp import ModbusTcpClient as ModbusClient

class ModbusClientWrapper:
    #  = '192.168.1.177'
    # server_port = 502
    def __init__(self, server_ip="192.168.1.177", server_port=502, unit=1, timeout=5):
        self.client = ModbusClient(
            server_ip,port=server_port,
            timeout=timeout,
        )
        logging.basicConfig()
        self.unit = unit
        self.log = logging.getLogger()
        self.log.setLevel(logging.DEBUG)

    def connect(self):
        return self.client.connect()

    def close(self):
        self.client.close()

    def read_holding_registers(self, address, count):
        try:
            rr = self.client.read_holding_registers(address, count, self.unit)
            if not rr.isError():
                print(f"Read registers: {rr.registers}")
                return rr.registers
            else:
                self.log.error(f"Error reading registers: {rr}")
                return None
        except ModbusException as e:
            self.log.error(f"Modbus error: {e}")
            return None

    def read_coil_registers(self, address, count):
        try:
            result = self.client.read_coils(address , count , self.unit)
            if not result.isError():
                print(f"Coil values: {result.bits}")
                return result.bits
            else:
                print("Error reading coils")
                return None
        except ModbusException as e:
            self.log.error(f"Modbus error: {e}")
            return None

    def write_register(self, address, value):
        try:
            rq = self.client.write_register(address, value, self.unit)
            if not rq.isError():
                return True
            else:
                self.log.error(f"Error writing register: {rq}")
                return False
        except ModbusException as e:
            self.log.error(f"Modbus error: {e}")
            return False

    def write_coil_register(self, address, boolValue):
        # Example: Write a single coil at address 0x0000 to True
        write_result = self.client.write_coil(address, boolValue, self.unit)
        if not write_result.isError():
            print("Successfully wrote to coil {address}")
        else:
            print("Error writing to coil {address}")

    def write_coil_registers(self, address, boolValueArray):
        # Example: Write a single coil at address 0x0000 to True
        write_result = self.client.write_coils(address, boolValueArray, self.unit)
        if not write_result.isError():
            print("Successfully wrote to coil {address}")
        else:
            print("Error writing to coil {address}")
