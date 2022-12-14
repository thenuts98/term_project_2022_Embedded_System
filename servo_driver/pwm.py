from ctypes import cdll
import sys

test = cdll.LoadLibrary('/home/pi/term_project_2022_Embedded_System/servo_driver/test.dll')

def pwm(degree):
    test.pwm(degree)

if __name__ == "__main__":
    if len(sys.argv) == 2:
        pwm(int(sys.argv[1]))
    else:
        print("Invalid Argument")
