import time, math
from pyb import UART

uart = UART(3, 9600)

while(True):

    img_data=bytearray([0xFF,0x5A,0x87,0XFE])#十六进制，帧头FF，帧尾FE
    uart.write(img_data)
    #time.sleep_ms(1000)