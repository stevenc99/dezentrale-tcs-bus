#!/bin/sh -e
GPIO=44
echo "$GPIO" > "/sys/class/gpio/export" || :
echo out > "/sys/class/gpio/gpio$GPIO/direction"
cat "/sys/kernel/debug/gpio"
