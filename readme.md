# TERM PROJECT
Embedded System Course Final Tem Project, DEC 2022
## Servo Motor
|file|description|
|---|---|
|`pwm_driver.c` | pwm device driver | 
|`test.c` | c function file |
|`test.dll` | shared library file |
|`test.py` | c function executable python file |

### Installation
```linux
make clean
make
sudo insmod pwm_driver.ko
sudo chmod 666 /dev/my_pwm_driver
```
### Servo Control 
```linux
python3 pwm.py {degree}
``` 
```python
import pwm
...
pwm.pwm(degree)
```

## Flask
|file|function| 
|---|---|
|`test.py`|flask test|



### Reference
---
`pwm_driver.c` from [Linux_Driver_Tutorial](https://github.com/Johannes4Linux/Linux_Driver_Tutorial/blob/main/06_pwm_driver/pwm_driver.c)