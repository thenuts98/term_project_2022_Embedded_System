from ctypes import cdll
import sys

adc = cdll.LoadLibrary('/home/pi/term_project_2022_Embedded_System/joystick/adc.dll')

def read():
    return adc.adc_read()

if __name__ == "__main__":
    print(adc.adc_read())
