########################################################################
#
#	Makfile
#
# - author 	:	ATIM
# - version	:	0.1
# - date 	:	30.05.2016
#
########################################################################

########################################################################
# Start of user section
#

# Name of project
PROJECT_NAME = AcwMangohDemo

#
# End of user defines
########################################################################

########################################################################
# Start rules section
#

all:release

release:
	mkapp $(PROJECT_NAME).adef -t wp85
	
install:
	instapp $(PROJECT_NAME).wp85.update 192.168.2.2

clean:
	rm -rf _build_* *.update
	
#
# End rules section
########################################################################
