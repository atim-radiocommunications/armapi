#!/bin/bash

########################################################################
#
# - Script to prepare package library.
# - Date : 07.02.2016
#
########################################################################

libVersion=$1

if [ -z "$libVersion" ]; then
	echo "What is the library version?"
	exit
fi

########################################################################
# Generate cpp file
########################################################################
cd ../armfuser/
./armfuser.sh
cd ../pkg/

########################################################################
# Arduino pkg
########################################################################

##Prepare pkg for arduino
mkdir -p armapi/src/
mkdir -p armapi/exemples/

#cp library.properties armapi/
#Cerate library.properties file
echo "name=armapi" > armapi/library.properties
echo "version=$libVersion" >> armapi/library.properties
echo "author=Atim" >> armapi/library.properties
echo "maintainer=Atim" >> armapi/library.properties
echo "sentence=This API allow you to control easily the modules ARM from ATIM company." >> armapi/library.properties
echo "paragraph=You will be able to send and receive data on the Sigfox/LoRaWan network and local(fsk) network." >> armapi/library.properties
echo "category=Communication" >> armapi/library.properties
echo "url=http://atim-radiocommunications.github.io/armapi/" >> armapi/library.properties
echo "architectures=*" >> armapi/library.properties

cp ../../LICENSE armapi/
cp ../../README.md armapi/

cp -r ../../exemples/arduino/* armapi/exemples/

cp ../../bindings/cpp/armport.h armapi/src/
cp ../../bindings/cpp/armconst.h armapi/src/
cp ../../bindings/cpp/armconfig.h armapi/src/
cp ../../bindings/cpp/arm.h armapi/src/
cp ../../bindings/cpp/arm.cpp armapi/src/
cp ../../bindings/cpp/armport/armport_arduino.cpp armapi/src/

#Make pkg
zip -r arduino_armapi_v$libVersion.zip armapi

#Install the pkg
rm -fr ~/Arduino/libraries/armapi/
cp -r armapi ~/Arduino/libraries/armapi/

#Clean
rm -rf armapi

echo "Pkg for Arduino generated."

########################################################################
# cpp pkg
########################################################################

##Prepare pkg for arduino
mkdir -p armapi/src/

cp ../../LICENSE armapi/
cp ../../README.md armapi/

cp -r ../../bindings/cpp/* armapi/src/

#Make pkg
zip -r cpp_armapi_v$libVersion.zip armapi

#Clean
rm -rf armapi

echo "Pkg for cpp generated."
########################################################################
# c pkg
########################################################################

##Prepare pkg for arduino
mkdir -p armapi/src/

cp ../../LICENSE armapi/
cp ../../README.md armapi/

cp -r ../../bindings/c/* armapi/src/

#Make pkg
zip -r c_armapi_v$libVersion.zip armapi

#Clean
rm -rf armapi

echo "Pkg for c generated."
