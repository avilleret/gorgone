#!/bin/sh
while [ 1 ]
do
  echo On
  ${0%/*}/turnOnWhite.sh
  sleep 1
  echo Off
  ${0%/*}/turnOffLed.sh
  sleep 1
done


