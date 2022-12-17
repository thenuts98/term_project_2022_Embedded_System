# TERM PROJECT
Embedded System Course Final Tem Project, DEC 2022

### Installation
```linux
sudo bash install.sh
```
## Servo Motor
|file|description|
|---|---|
|`pwm_driver.c` | pwm device driver | 
|`test.c` | c function file |
|`test.dll` | shared library file |
|`test.py` | c function executable python file |


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
|`input.html`|input page template|



## Joystick
|file|function| 
|---|---|
|`adc_driver.c` | ADC device driver | 
|`adc.c`|c function file|
|`adc.py` | c function executable python file |

checking joystick resistance by ADC TCF8591T

### Example
`joystick_to_servo.py` syncs joystick movement to servo motor




### Reference
---
`pwm_driver.c` from [Linux_Driver_Tutorial](https://github.com/Johannes4Linux/Linux_Driver_Tutorial/blob/main/06_pwm_driver/pwm_driver.c)