#!/bin/zsh
echo "-- BUILDING..."
./builder.sh
echo "-- BUILDING... DONE"
echo "-- BOOTING..."
qemu-system-x86_64 daivik.hdd
clear