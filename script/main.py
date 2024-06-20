import time
import network
from machine import UART, Pin

ssidRouter     = 'Coworking' #Enter the router name
passwordRouter = 'C0w0rking!' #Enter the router password

def STA_Setup(ssidRouter,passwordRouter):
    print("Setup start")
    sta_if = network.WLAN(network.STA_IF)
    if not sta_if.isconnected():
        print('connecting to',ssidRouter)
        sta_if.active(True)
        sta_if.connect(ssidRouter,passwordRouter)
        while not sta_if.isconnected():
            pass
    print('Connected, IP address:', sta_if.ifconfig())
    print("Setup End")

try:
    STA_Setup(ssidRouter,passwordRouter)
except:
    sta_if.disconnect()
    
uart = UART(1, baudrate=115200, tx=17, rx=16)

while True:
    if uart.any():
        data = uart.readline()
        data = data.decode()
        data = data.strip()
        if data: 
            motion_detected = data
            print(motion_detected)
            print(data)
    time.sleep(1)

# Product data configuration
#APIKEY = "pv8nhcrtntbfopwmordfhx3ckw53ioxs7lls5ezr9mgwk1p6ouh73gyudm7sssd2"
#DEVICE_DEVELOPER_ID = "236c337c-ef76-44db-944a-93e5191ab33b"
#DEVICE_CHECKSUM = "siszZ86MWaBT8229zITXFkk+H02w/obKYrmXXmqw7Ws="
#DATA_VERSION = "S1"
#protocol_version = "v3"
    
    # Explanation
# Arduino Code: The Arduino code initializes the motion sensor pin and sets up serial communication. It reads the sensor data (either HIGH or LOW), prints it to the Serial, and then waits for 1 second before reading again.
# ESP32 MicroPython Code: The ESP32 code sets up a UART connection with the Arduino. It continuously checks for incoming data from the UART, reads it, and prints whether motion is detected.

# Connections
# Ensure the following connections between Arduino and ESP32:

# Arduino TX (Pin 1) to ESP32 RX (Pin 16)
# Arduino RX (Pin 0) to ESP32 TX (Pin 17)
# Common Ground between Arduino and ESP32

# Additional Considerations
# Voltage Levels: Ensure that the voltage levels between Arduino (5V) and ESP32 (3.3V) are compatible. You might need a level shifter if you encounter issues.
# Serial Monitor: If you're using the Arduino's Serial Monitor for debugging, disconnect the TX and RX pins to avoid conflicts.
# With this setup, the motion sensor data collected by the Arduino Uno will be sent to the ESP32, where it can be processed further or used in other applications.
    
