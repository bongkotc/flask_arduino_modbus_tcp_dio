from flask import Flask,render_template,request,redirect
from ModbusClientWrapper import ModbusClientWrapper

app=Flask(__name__)

def read_arduino():
    port = 'COM8'  # เลือก Com port ที่ Arduino ต่อใช้งาน
    button_address = 0
    modbus_client = ModbusClientWrapper(port=port)

    #เปิดการเชื่อมต่อ
    if not modbus_client.connect():
        print("Failed to connect to the Modbus RTU server")
        return

    # อ่าน holding registers
    registers = modbus_client.read_holding_registers(address=button_address, count=1)
    if registers is not None:
        print(f"Read registers: {registers}")
    else:
        print("Failed to read registers")

    #ปิดการเชื่อมต่อ
    modbus_client.close()
    return registers

def write_arduino(data):
    port = 'COM8'  # เลือก Com port ที่ Arduino ต่อใช้งาน
    led_address = 1
    modbus_client = ModbusClientWrapper(port=port)

    #เปิดการเชื่อมต่อ
    if not modbus_client.connect():
        print("Failed to connect to the Modbus RTU server")
        return

    # Write to a holding register
    if modbus_client.write_register(address=led_address, value=int(data)):
        print("Write successful")
    else:
        print("Failed to write register")

    #ปิดการเชื่อมต่อ
    modbus_client.close()
    return True
#ไฟล์ เริ่มต้น
@app.route("/")
def index():
    arduino_data = read_arduino()
    return render_template("index.html",arduino_data=arduino_data)

#API อ่านค่า Modbus
@app.route('/mosbudRead')
def mosbudRead():
    arduino_data = read_arduino()
    return arduino_data

#API เขียนค่า Modbus
@app.route('/mosbudWrite',methods=['POST'])
def mosbudWrite():
    data = request.form["data"]
    print("data = ", data)
    arduino_data = write_arduino(data)
    return redirect("/")

if __name__ == "__main__":
    app.run(debug=True)