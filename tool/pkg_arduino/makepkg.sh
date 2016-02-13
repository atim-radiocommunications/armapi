#!/bin/bash

########################################################################
#
#	Script to prepare Arduino package library.
# - date : 07.02.2016
#
########################################################################

#Prepare pkg
mkdir -p armapi/src/
mkdir -p armapi/exemples/

cp library.properties armapi/
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
zip -r armapi.zip armapi

#Install the pkg
rm -fr ~/Arduino/libraries/armapi/
cp -r armapi ~/Arduino/libraries/armapi/

#Clean
rm -rf armapi