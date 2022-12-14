from ctypes import cdll

test = cdll.LoadLibrary('./test.dll')


test.pwm(0)