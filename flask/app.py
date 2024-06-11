from flask import Flask,render_template,request,redirect, jsonify
from ModbusClientWrapper import ModbusClientWrapper

app=Flask(__name__)

def read_button():
    #สร้าง modbus client
    modbus_client = ModbusClientWrapper()

    #เปิดการเชื่อมต่อ
    if not modbus_client.connect():
        print("ไม่สามารถเชื่อมต่อ Modbus TCP server ได้")
        return

    # ทดสอบอ่าน holding registers
    registers = modbus_client.read_coil_registers(address=10, count=8)
    if registers is not None:
        print(f"Read ข้อมูล: {registers}")
    else:
        print("อ่าน Coil ไม่ได้")

    #ปิดการเชื่อมต่อ
    modbus_client.close()
    return registers

def read_led():
    # สร้าง Object MOdbus
    modbus_client = ModbusClientWrapper()

    #เปิดการเชื่อมต่อ
    if not modbus_client.connect():
        print("ไม่สามารถเชื่อมต่อ Modbus TCP server ได้")
        return

    # ทดสอบอ่าน Coils registers
    registers = modbus_client.read_coil_registers(address=0, count=8)
    if registers is not None:
        print(f"ข้อมูลที่อ่านได้คือ: {registers}")
    else:
        print("การอ่านข้อมูล Error")

    #ปิดการเชื่อมต่อ
    modbus_client.close()
    return registers

def write_led_by_bit(bit, value):
    # สร้าง Object MOdbus
    modbus_client = ModbusClientWrapper()

    #เปิดการเชื่อมต่อ
    if not modbus_client.connect():
        print("ไม่สามารถเชื่อมต่อ Modbus TCP server ได้")
        return

    # ทดสอบอ่าน Coils registers
    state = False
    if int(value) == 0:
        state = False
    elif int(value) == 1:
        state = True
    print(bit, value,state)
    registers = modbus_client.write_coil_register(address=int(bit), boolValue=state)
    if registers is not None:
        print(f"ข้อมูลที่อ่านได้คือ: {registers}")
    else:
        print("การอ่านข้อมูล Error")

    #ปิดการเชื่อมต่อ
    modbus_client.close()
    return registers


#ไฟล์ เริ่มต้น
@app.route("/")
def index():
    arduino_data = read_button()
    return render_template("index.html",arduino_data=jsonify(arduino_data))

#API อ่านค่า Modbus
@app.route('/readButtons')
def readButtons():
    arduino_data = read_button()
    return jsonify(arduino_data)

#API อ่านค่า Modbus
@app.route('/readLeds')
def readLeds():
    arduino_data = read_led()
    return jsonify(arduino_data)

@app.route('/writeLedByBit', methods=['GET'])
def writeLedByBit():
    # Get parameters from the URL
    bit = request.args.get('bit')
    value = request.args.get('value')

    if bit is not None and value is not None:
        write_led_by_bit(int(bit),int(value))
    data = {
        'bit': bit,
        'value': value,
    }
    return jsonify(data)

#API เขียนค่า Modbus
@app.route('/mosbudWrite',methods=['POST'])
def mosbudWrite():
    data = request.form["data"]
    print("data = ", data)
    arduino_data = write_arduino(data)
    return redirect("/")

if __name__ == "__main__":
    app.run(debug=True)