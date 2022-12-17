#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/kernel.h>

#define DRIVER_NAME "adc_driver"
#define DRIVER_CLASS "adc_driver_Class"

static struct i2c_adapter * bmp_i2c_adapter = NULL;
static struct i2c_client * bmp280_i2c_client = NULL;

/* Meta Information */
MODULE_AUTHOR("Johannes 4Linux");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A driver for reading out a PCF8591  temperature sensor");

/* Defines for device identification */ 
#define I2C_BUS_AVAILABLE	1		/* The I2C Bus available on the raspberry */
#define SLAVE_DEVICE_NAME	"PCF8591T"	/* Device and Driver Name */
#define BMP280_SLAVE_ADDRESS	0x48		/* BMP280 I2C address */

static const struct i2c_device_id bmp_id[] = {
		{ SLAVE_DEVICE_NAME, 0 }, 
		{ }
};

static struct i2c_driver bmp_driver = {
	.driver = {
		.name = SLAVE_DEVICE_NAME,
		.owner = THIS_MODULE
	}
};

static struct i2c_board_info bmp_i2c_board_info = {
	I2C_BOARD_INFO(SLAVE_DEVICE_NAME, BMP280_SLAVE_ADDRESS)
};

/* Variables for Device and Deviceclass*/
static dev_t myDeviceNr;
static struct class *myClass;
static struct cdev myDevice;

/* Variables for temperature calculation */
s32 dig_T1, dig_T2, dig_T3;


/**
 * @brief Get data out of buffer
 */
static ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs) {
	int to_copy, not_copied, delta;
	char tmp;
	s8 value;

	/* Get amount of bytes to copy */
	to_copy = min(sizeof(tmp), count);

	/* Get temperature */
	value = i2c_smbus_read_byte(bmp280_i2c_client);
	tmp = value;

	/* Copy Data to user */
	not_copied = copy_to_user(user_buffer, &tmp, to_copy);

	/* Calculate delta */
	delta = to_copy - not_copied;

	return delta;
}

/**
 * @brief This function is called, when the device file is opened
 */
static int driver_open(struct inode *deviceFile, struct file *instance) {
	printk("MyDeviceDriver -  Open was called\n");
	return 0;
}

/**
 * @brief This function is called, when the device file is close
 */
static int driver_close(struct inode *deviceFile, struct file *instance) {
	printk("MyDeviceDriver -  Close was called\n");
	return 0;
}

/* Map the file operations */
static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
	.read = driver_read,
};


/**
 * @brief function, which is called after loading module to kernel, do initialization there
 */
static int __init ModuleInit(void) {
	int ret = -1;
	u8 id;
	printk("MyDeviceDriver - Hello Kernel\n");

	/* Allocate Device Nr */
	if ( alloc_chrdev_region(&myDeviceNr, 0, 1, DRIVER_NAME) < 0) {
		printk("Device Nr. could not be allocated!\n");
	}
	printk("MyDeviceDriver - Device Nr %d was registered\n", myDeviceNr);

	/* Create Device Class */
	if ((myClass = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL) {
		printk("Device Class can not be created!\n");
		goto ClassError;
	}

	/* Create Device file */
	if (device_create(myClass, NULL, myDeviceNr, NULL, DRIVER_NAME) == NULL) {
		printk("Can not create device file!\n");
		goto FileError;
	}

	/* Initialize Device file */
	cdev_init(&myDevice, &fops);

	/* register device to kernel */
	if (cdev_add(&myDevice, myDeviceNr, 1) == -1) {
		printk("Registering of device to kernel failed!\n");
		goto KernelError;
	}

	bmp_i2c_adapter = i2c_get_adapter(I2C_BUS_AVAILABLE);

	if(bmp_i2c_adapter != NULL) {
		bmp280_i2c_client = i2c_new_client_device(bmp_i2c_adapter, &bmp_i2c_board_info);
		if(bmp280_i2c_client != NULL) {
			if(i2c_add_driver(&bmp_driver) != -1) {
				ret = 0;
			}
			else
				printk("Can't add driver...\n");
		}
		i2c_put_adapter(bmp_i2c_adapter);
	}
	printk("PCF8591T Driver added!\n");

	/* Initialice the sensor */
	i2c_smbus_write_byte(bmp280_i2c_client, 0x00);
	return ret;

KernelError:
	device_destroy(myClass, myDeviceNr);
FileError:
	class_destroy(myClass);
ClassError:
	unregister_chrdev(myDeviceNr, DRIVER_NAME);
	return (-1);
}

/**
 * @brief function, which is called when removing module from kernel
 * free alocated resources
 */
static void __exit ModuleExit(void) {
	printk("MyDeviceDriver - Goodbye, Kernel!\n");
	i2c_unregister_device(bmp280_i2c_client);
	i2c_del_driver(&bmp_driver);
	cdev_del(&myDevice);
    device_destroy(myClass, myDeviceNr);
    class_destroy(myClass);
    unregister_chrdev_region(myDeviceNr, 1);
}

module_init(ModuleInit);
module_exit(ModuleExit);
