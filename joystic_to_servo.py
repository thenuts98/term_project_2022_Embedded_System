from ctypes import cdll
import sys
from servo_driver import pwm
from joystick import adc

test = cdll.LoadLibrary('/home/pi/term_project_2022_Embedded_System/servo_driver/test.dll')

# 조이스틱으로 모터 제어

if __name__ == "__main__":
    while(1):
        data = int(adc.read() / 256 * 170)
        pwm.pwm(data)
        
