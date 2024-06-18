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
    

# Initialize UART for communication with Arduino
uart = UART(1, baudrate=115200, tx=17, rx=16)

STA_Setup(ssidRouter,passwordRouter)
while True:
    if uart.any():
        data = uart.readline().strip()
        if data:
            motion_detected = data.decode()
            if motion_detected == 'test':
                print("la phrase est", motion_detected)
    time.sleep(1)
    
    
