# ARM get information #
This example for Raspberry Pi initialise armapi, get informations about
the ARM module and print this information.


## Serial port ##
You must have right and if necessary you must disable the terminal on the serial port. 
The serial port on RPi 1 and RPi 2 is /dev/ttyAMA0 and on the RPi 3 the serial port is /dev/ttyS0.

## Reset pin ##
By default, on the acw_rpi the reset is enable on the shield.
To run this example you will must to disable the reset.
For this, you will need to set the gpio4 in output and drive this one to top level.

There are many ways of doing. For example you can use the echo command:

	# Set the gpio4 in output
	$echo 4 > /sys/class/gpio/export
	$echo out > /sys/class/gpio/gpio4/direction
	# Set pin to top level
	$echo 1 > /sys/class/gpio/gpio4/value

## Compilation ###

### On raspberry pi ###
You have need to executer the 'make' command into this folder with
the TTY parameter. 

For example on RPi 1 and 2 you need to call:

	$make TTY=/dev/ttyAMA0

Or on RPi 3 you need to call:

	$make TTY=/dev/ttyS0
	
### On host ###
You have need to executer the 'make' command 
with TARGET and TTY option into this folder.
For example, if your cross toolchain is installed on you system and
is named by 'arm-linux-gnueabihf-', the command to call is:

	$make TARGET=arm-linux-gnueabihf- TTY=/dev/ttyAMA0

## Installation ##

### On raspberry pi ###
After compilation, you can directly execute the generated binary near of
makefile, call './arminfo'.
Or install into the system with the 'make install' command.
### On host (with scp) ###
Execute the 'make installscp' command with your parameters USER, IP and
DIRECTORY. For example, if the username is 'pi' and if the IP addressee is
'192.168.0.1', finally you can specific the installation folder in user
home.

	$make installscp USER=pi IP=192.168.0.1 DIRECTORY=.
	




