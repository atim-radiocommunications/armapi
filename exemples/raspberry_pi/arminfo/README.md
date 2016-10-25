# ARM get information #
This example for Raspberry Pi initialise armapi, get informations about
the ARM module and print this information.


## Serial port ##
You must have right and if necessary you must disable the terminable on the serial port. 
The serial port on RPi 1 and RPi 2 is /dev/ttyAMA0 and on the RPi 3 the serial port is /dev/ttyS0.


## Compilation ###

### On raspberry pi ###
You have need to executer the 'make' command into this folder with
the TTY parameter. For example on RPi 1 and 2 you neet to call:

	$make TTY=/dev/ttyAMA0
	
### On host ###
You have need to executer the 'make' command 
with TARGET and TTY option into this folder.
For example, if your cross comparator is installed on you system and
is named by 'arm-linux-gnueabihf-', the commend to call is:

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






