#!/bin/bash

set -m

export LD_LIBRARY_PATH=.

OUT_A=./test_01_a.out.txt
OUT_B=./test_01_b.out.txt
FIFO_A=./app_a_in
FIFO_B=./app_b_in

echo " ZIPC test script #1"
echo " 1) Start app A and app B."
echo " 2) App B sends 10 bytes randomized data to app A"
echo " 3) Outputs are written to '$OUT_A' and '$OUT_B' files."

if [ -f $FIFIO_A ]; then
    rm -f $FIFO_A
fi
if [ -f $FIFIO_B ]; then
    rm -f $FIFO_B
fi

mkfifo $FIFO_A
mkfifo $FIFO_B

./app A < $FIFO_A > $OUT_A 2>&1 &
PID_A=$!
echo "receive" > $FIFO_A
sleep 1 

./app B < $FIFO_B > $OUT_B 2>&1 &
PID_B=$!
echo "send A 10" > $FIFO_B
echo "quit" > $FIFO_B
sleep 1

echo "quit" > $FIFO_A
sleep 1

rm -f $FIFO_A
rm -f $FIFO_B

kill -9 $PID_A  > /dev/null 2>&1
kill -9 $PID_B  > /dev/null 2>&1

