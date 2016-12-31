#!/bin/bash
# Author: Luciano Cheng
# Testing script for packets.c
# packets.c must be compiled to "packets" like so:
# gcc packets.c -o packets

newline="
"

test=("" "hello" "abcdefghijklmnopqrstuvwxyz" "1234567890" "abcdefghijklmnopqrstuvwxyz/!/@/#" ":" "ii")

echo ">> Testing script for packets.c, ESE 116 Fall 07 HW2"
echo ">> Author: Luciano Cheng"
echo ">> Program must be compiled to './packets'"

for arg in "" ${test[@]}
do
  result=`echo -n "$arg"|./packets`
  correct=`echo -n "Data Sent: $arg$newline""Data Received: $arg$newline"`

  echo ">>"
  echo -n ">> Testing sending '$arg' ... "
  if [[ $result = $correct ]]
  then
    echo "SUCCESS!"
  else
    echo "FAILURE!"
    echo ">> Program './packets' EXPECTED Output:"
    echo "$correct"
    echo ">> Program './packets' RECEIVED Output:"
    echo "$result"
    echo ">> EXPECTED != RECEIVED, SHELL EXITING..."
    exit
  fi
done
echo ">>"
echo ">> ALL TESTS SUCCESSFUL!"