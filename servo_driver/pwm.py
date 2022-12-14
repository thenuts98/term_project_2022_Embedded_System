from ctypes import cdll
import sys

test = cdll.LoadLibrary('./test.dll')

def pwm(degree):
    test.pwm(degree)

if __name__ == "__main__":
    if len(sys.argv) == 2:
        pwm(int(sys.argv[1]))
    else:
        print("Invalid Argument")
