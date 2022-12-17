export SERVO_DIR=/home/pi/term_project_2022_Embedded_System/servo_driver
export JOY_DIR=/home/pi/term_project_2022_Embedded_System/joystick

rmmod adc_driver
rmmod pwm_driver 

cd $JOY_DIR

make
insmod adc_driver.ko
chmod 666 /dev/adc_driver
make clean

cd $SERVO_DIR

make
insmod pwm_driver.ko
chmod 666 /dev/my_pwm_driver
make clean
