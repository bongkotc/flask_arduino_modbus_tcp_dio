from ModbusClientWrapper import ModbusClientWrapper

def main():
    # port = 'COM8'  # com port ที่ใช้
    modbus_client = ModbusClientWrapper()

    #เปิดการเชื่อมต่อ
    if not modbus_client.connect():
        print("Failed to connect to the Modbus TCP server")
        return

    # ทดสอบอ่าน holding registers
    # registers = modbus_client.read_holding_registers(address=0, count=1)

    # registers = modbus_client.read_coil_registers(address=10, count=8)
    # if registers is not None:
    #     print(f"Read registers: {registers}")
    # else:
    #     print("Failed to read registers")

    # ทดสอบเขียน to a holding register
    # if modbus_client.write_register(address=0, value=125):
    #     print("Write successful")
    # else:
    #     print("Failed to write register")

    # ทดสอบเขียน to a holding register
    if modbus_client.write_coil_register(address=2, boolValue=False):
        print("Write successful")
    else:
        print("Failed to write register")

    # if modbus_client.write_coil_registers(address=0, boolValueArray=[True, False, True, False, True, False, True, True]):
    #     print("Write successful")
    # else:
    #     print("Failed to write register")

    #ปิดการเชื่อมต่อ
    modbus_client.close()

if __name__ == "__main__":
    main()
