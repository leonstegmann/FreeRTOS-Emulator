#!/bin/bash

echo "----------------- LINKING LIBRARIES---------------------------------------"
cmake ../

echo "----------------- COMPILING PROJECT---------------------------------------"
make

echo "----------------- EXECUTING BINARY----------------------------------------"
./../bin/FreeRTOS_Emulator